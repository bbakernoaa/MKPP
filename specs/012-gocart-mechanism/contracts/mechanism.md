# Mechanism Contract: GOCART

The MKPP parser expects mechanisms to align with the OpenAtmos schema.

## Host Interaction Contract
The host model must provide:
1. **Chemical State Vector**: Concentration array covering all defined species.
2. **Meteorological Fields**: Instead of relying on Exaero, the host model must pass `METEO_STRUCT` or an equivalent structure containing:
   - `temperature` (K)
   - `pressure` (Pa)
   - `cloud_liquid_water` (kg/kg) for aqueous SO2 oxidation
   - `relative_humidity` (optional, if needed for swelling/heterogeneous)

MKPP will output the updated chemical state vector. It will **not** compute dust or sea salt emissions.
