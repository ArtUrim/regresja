import csv
import pytest
import pdb

import regresja

@pytest.fixture(scope="module")
def read_data():
    vv = []
    with open( "octave/edges2.csv", "rt" ) as fh:
        reader = csv.reader(fh)
        for row in reader:
            vv.append(row)
    return vv

def test_up123(read_data):
    vv = read_data[1]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 5:
            assert val == 1.0
        elif i == 14:
            assert val == 2.0
        elif i == 24:
            assert val == 3.0

def test_up132(read_data):
    vv = read_data[2]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 5:
            assert val == 1.0
        elif i == 14:
            assert val == 3.0
        elif i == 24:
            assert val == 2.0

def test_down123(read_data):
    vv = read_data[3]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 5:
            assert val == -1.0
        elif i == 14:
            assert val == -2.0
        elif i == 24:
            assert val == -3.0

def test_down132(read_data):
    vv = read_data[4]
    r = regresja.Regresja(5)
    for (i,v) in enumerate(vv):
        val = r.calc( float(v) )
        if i == 5:
            assert val == -1.0
        elif i == 14:
            assert val == -3.0
        elif i == 24:
            assert val == -2.0
