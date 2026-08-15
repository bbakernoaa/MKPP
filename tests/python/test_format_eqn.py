from mkpp.format_eqn import _strength_reduce_squares


def test_strength_reduce_powers():
    # Integer power 2 (square)
    code_sq1 = "pow(S_0, 2)"
    assert _strength_reduce_squares(code_sq1) == "(S_0 * S_0)"

    code_sq2 = "pow(state(1), 2.0)"
    assert _strength_reduce_squares(code_sq2) == "(state(1) * state(1))"

    # Integer power 3 (cube)
    code_cube = "pow(state(1), 3)"
    assert _strength_reduce_squares(code_cube) == "((state(1) * state(1)) * state(1))"

    code_cube2 = "pow(x, 3.0)"
    assert _strength_reduce_squares(code_cube2) == "((x * x) * x)"

    # Integer power 1
    code_pow1 = "pow(x, 1)"
    assert _strength_reduce_squares(code_pow1) == "x"

    code_pow1_float = "pow(x, 1.0)"
    assert _strength_reduce_squares(code_pow1_float) == "x"

    # Integer power 0
    code_pow0 = "pow(x, 0)"
    assert _strength_reduce_squares(code_pow0) == "1.0"

    code_pow0_float = "pow(x, 0.0)"
    assert _strength_reduce_squares(code_pow0_float) == "1.0"

    # Fractional exponents MUST remain unchanged as pow(...)
    code_frac1 = "pow(x, 0.5)"
    assert _strength_reduce_squares(code_frac1) == "pow(x, 0.5)"

    code_frac2 = "pow(x, 2.5)"
    assert _strength_reduce_squares(code_frac2) == "pow(x, 2.5)"
