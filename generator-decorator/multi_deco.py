#!/usr/bin/python2.7

class Decorator3:
    def __init__(self,f):
        print "----- deco lev3 -----"
        self.f = f

    def __del__(self):
        print "----- end deco lev3 -----"

    def __call__(self,*args,**kwargs):
        print "do! deco lev3",len(args),len(kwargs)
        for arg in args:
            print arg
        self.f(*args,**kwargs)
        for kwarg in kwargs:
            print "key:",kwarg,"| value:",kwargs[kwarg]

class Decorator2:
    def __init__(self,f):
        print "----- deco lev2 -----"
        self.f = f

    def __del__(self):
        print "----- end deco lev2 -----"

    def __call__(self,*args,**kwargs):
        print "do! deco lev2",len(args),len(kwargs)
        for arg in args:
            print arg
        self.f(*args,**kwargs)
        for kwarg in kwargs:
            print "key:",kwarg,"| value:",kwargs[kwarg]


class Decorator1:
    def __init__(self,f):
        print "----- deco lev1 -----"
        self.f = f

    def __del__(self):
        print "----- end deco lev1 -----"

    def __call__(self,*args,**kwargs):
        print "do! deco lev1",len(args),len(kwargs)
        for arg in args:
            print arg
        self.f(*args,**kwargs)
        for kwarg in kwargs:
            print "key:",kwarg,"| value:",kwargs[kwarg]

@Decorator3
@Decorator2
@Decorator1
def tester(a=1,b=2,c=3):
   print "we are in tester."
   print 'a=',a,'b=',b,'c=',c
   print "end tester."

tester(a=2)
print '---------------------------'
tester(b=9)
print '---------------------------'
tester(b=9,c=10)
print '---------------------------'
tester(a=-10,b=9,c=10)
