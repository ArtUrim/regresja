#!/usr/bin/env python3

class Regresja:

    def __init__(self,n,delta=1):
        self.n = n
        self.delta = 12.0/(delta*n*(n*n-1))
        self.step = 1
        self.vals = []
        self.sxy = 0.0
        self.sy = 0.0

    def calc( self, val ):
        regresja = None
        if self.step <= self.n:
            self.vals.append( val )
            self.sy += val
            self.sxy += val*(self.step+1)
            self.step += 1
            if self.step == self.n:
                self.step += 1
                return self.delta*(self.sxy-(self.n+1)/2*self.sy)
            else:
                return None
        else:
            self.sxy -= self.sy
            self.sxy += self.n*val

            self.sy += val
            self.sy -= self.vals.pop(0)

            self.vals.append(val)
            regresja = self.delta*(self.sxy-(self.n+1)/2*self.sy)

        return regresja

if __name__ == "__main__":

    r = Regresja(5)

    for n in range(10):
        vv = r.calc(n)
        if vv:
            print( "{}: {}".format(n,vv) )
