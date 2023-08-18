import regresja

def test_zero():
    r = regresja.Regresja(2)
    assert r

def test_o5():
    r = regresja.Regresja(5)

    for n in range(10):
        vv = r.calc(n)
        if n < 4:
            assert vv is None
        else:
            assert vv == 1.0

def test_o10():
    r = regresja.Regresja(5)

    for n in range(15):
        if n < 10:
            vv = r.calc(n)
        else:
            vv = r.calc(2.0*n)
        if n < 4:
            assert vv is None
        elif n < 10:
            assert vv == 1.0
        elif n >= 14:
            assert vv == 2.0
        else:
            assert vv != 1.0
            assert vv != 2.0
