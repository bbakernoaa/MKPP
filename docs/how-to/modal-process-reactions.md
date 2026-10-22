# Modal process reactions in YAML

[The complete mechanism](../../examples/modal_processes.yaml) demonstrates modal
exchange, empirical nucleation, and coating-driven aging with `CUSTOM` laws.
These are illustrative closures with explicit units, not a MAM4 calibration.
Coefficients, molecular weights, densities and size widths must match the host's
EX-aero configuration. This small example has acid, organic and black-carbon
material; a larger mechanism must transfer every configured material during aging.

## Custom coefficients and full fluxes

`parameters.rate_expression` is an arithmetic expression. Use `C_<species>` for
the current concentration, and `rate_definitions` for named expressions in
dependency order. Definitions expand symbolically, so their state dependence is
included in Jacobians and sensitivities. They are not extra prognostic variables
or host-updated parameter slots. Forward references and unknown names are errors.

```yaml
rate_definitions:
  uptake: 0.001*C_number
reactions:
  - type: CUSTOM
    reactants: {gas: 1}
    products: {particle: 1}
    parameters:
      rate_expression: uptake*(C_gas-0.2*C_particle)
      rate_basis: flux
    stiff: true
```

With `rate_basis: flux`, the expression is the **entire signed reaction flux**;
MKPP adds products and subtracts reactants with their declared stoichiometry.
Negative flux reverses the exchange. Without that option the expression is a
coefficient, multiplied by reactant concentrations once according to the reaction
orders. `rate_basis: flux` is supported only for `CUSTOM` and cannot be combined
with `reaction_orders`. Existing reaction types retain their default coefficient
behavior. Nested `parameters` and reaction-level parameters are both accepted;
conflicting duplicate values fail compilation.

Arithmetic supports `+ - * / **`, parentheses, declared scalar names, `exp`,
`log`, `sqrt`, `tanh`, `sin`, `cos`, `Abs`, and `Piecewise`. Comparisons and
`and`/`or` form Piecewise conditions. Each Piecewise expression needs a final
unconditional branch. Attribute access, indexing, arbitrary function calls, and
Python evaluation are forbidden. Unknown symbols and nonfinite constants fail.
The parser builds SymPy nodes directly from an allowlisted AST.

Use Piecewise guards around divisions for empty populations and around positive
coating budgets. Jacobians differentiate the active branch; values at switching
surfaces need the host's boundary policy. Such piecewise closures are not globally
differentiable. Do not assume smooth adjoint sensitivities across switches.

Environmental expression names are `Temp`, `M_density` (`cair`), `S_a`, and
`v_gas`; existing code generation conventions still apply. In particular,
temperature is frozen to the compilation environment in a mechanism without
equilibrium, and `S_a`/`v_gas` retain legacy substitution behavior. They are not
new runtime parameter bindings. The modal example uses explicit constants and
stage concentrations instead.

## Nucleation: yields and orders are independent

```yaml
reactions:
  - type: CUSTOM
    reactants: {H2SO4: 100}
    products: {ACID_aitken: 100, N_aitken: 1}
    parameters:
      rate_expression: 1.0e-8
      reaction_orders: {H2SO4: 1.5}
    stiff: true
```

This gives J=1e-8*C_H2SO4^1.5 particles/cm3/s, acid loss=100*J and seed acid
production=100*J formula units/cm3/s. The seed contains 100 acid molecules;
stoichiometry does not introduce a 100th-order law. `reaction_orders` replaces
the entire default order map: `{}` means zero order. Orders must be finite,
nonnegative numbers and refer to declared species. Fractional orders remain
fractional, including when inferred from reactant coefficients.

The seed yield is illustrative. Derive it from configured seed radius, density,
composition, molecular weight and the receiving mode's lognormal volume moment
exp(4.5*ln(sigma)^2). With concentrations/cm3 and exponent p, an
EX-aero empirical SI prefactor A_SI becomes A_cm=A_SI*10^(6*(p-1)). Convert
source material to mass using its configured molecular weight. The example uses
complete H2SO4 mass (0.098079 kg/mol); it does not use the MAM4 SO4-equivalent
basis (0.09606 kg/mol). Neither acid uptake nor number creation supplies missing
neutralization chemistry. The integrator must enforce precursor availability.

## Exchange, shell aging, and coagulation ownership

The complete example recomputes dry radius from all source material masses and
number. Its uptake is the exact lognormal **continuum-limit** integral
4*pi*D*N*E[r], not EX-aero's transition-regime Fuchs-Sutugin quadrature.
Organic equilibrium uses the illustrative relation Ceq=0.2*Cparticle. Production
thermodynamics and transport must replace these illustrative expressions.

The shared aging frequency is max(coating_volume_rate,0)/shell_volume, using the
exact lognormal shell moment. Every material and number transfers with this
same frequency; coating material is not consumed a second time. All derivatives
of geometry and signed condensation enter the symbolic Jacobian automatically.

`COAG_VOLUME_RATE` is a **fixed-role auxiliary species**, in m3 coating/m3 air/s.
It is neither chemical mass nor aerosol number and must be excluded from those
budgets. The host sets it to the selected gross incoming coagulation mass gains
divided by densities and the accepted chemical interval. It is held fixed during
integration (zero RHS); its Jacobian column remains available as a sensitivity
to the supplied forcing. Do not use net mode-mass changes, include number gains,
or replay the budget across accepted intervals. A frozen split-interval forcing
does not supply derivatives of a fully coupled coagulation RHS.

MKPP computes this example's process rates from expressions directly; there is
no EX-aero callback installation. Do not also add `modalPhaseExchange` or
`modalAgingTerms` for the same processes. If the host uses those interfaces to
obtain the production closures, replace the corresponding YAML contributions
in the combined RHS/Jacobian instead. Keep coagulation in EX-aero and call
growth renaming once after acceptance with host transfer ownership. Dust and
additional configured materials get matching aging rows. Nitrate chemistry must
include appropriate NH3/HNO3 partners and distinguish ionic from complete-salt mass.

## Generate and validate

```sh
python -m mkpp.cli compile examples/modal_processes.yaml \
  --test-env examples/modal_processes.environment.yaml --out build/modal-processes
pytest tests/python/test_custom_reaction_expressions.py
```

The examples use material formula units/cm3 and particles/cm3; concentration units
are a mechanism contract, not inferred from `phase`. The fixed coagulation input
has the separate units above. Use the EX-aero mechanism mapping for SI conversion
and the scale_row/scale_column chain rule for Jacobians.
