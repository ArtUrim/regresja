import regresja

def test_zero():
    r = regresja.Regresja(2)
    assert r

def test_o5():
    r = regresja.Regresja(5)

    for n in range(10):
        vv = r.calc(n)
        if vv:
            print( "{}: {}".format(n,vv) )
