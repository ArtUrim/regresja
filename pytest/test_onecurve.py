import csv
import pytest
import pdb

import regresja

@pytest.fixture(scope="module")
def read_data():
    vv = []
    with open( "octave/onecurve.csv", "rt" ) as fh:
        reader = csv.reader(fh)
        for row in reader:
            vv.append(row)
    return vv

def test_upslowedge(read_data):
    vv = read_data[1]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 5:
            assert val == 1.0
        elif i == 20:
            assert val == 2.0

def test_upfastedge(read_data):
    vv = read_data[2]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 20:
            assert val == 1.0
        elif i == 5:
            assert val == 2.0

def test_downslowedge(read_data):
    vv = read_data[3]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 5:
            assert val == -1.0
        elif i == 20:
            assert val == -2.0

def test_downfastedge(read_data):
    vv = read_data[4]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 20:
            assert val == -1.0
        elif i == 5:
            assert val == -2.0

def test_upslowsmooth(read_data):
    vv = read_data[5]
    r = regresja.Regresja(5)
    #breakpoint()
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 4:
            assert val == 1.0
        elif i == 20:
            assert val == 2.0

def test_upfastsmooth(read_data):
    vv = read_data[6]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 20:
            assert val == 1.0
        elif i == 4:
            assert val == 2.0

def test_downslowsmooth(read_data):
    vv = read_data[7]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 4:
            assert val == -1.0
        elif i == 20:
            assert val == -2.0

def test_downfastsmooth(read_data):
    vv = read_data[8]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 20:
            assert val == -1.0
        elif i == 4:
            assert val == -2.0
