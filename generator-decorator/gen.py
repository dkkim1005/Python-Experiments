#!/usr/bin/python2.7

########### Example of Python Generator and Decorator syntax. ###########
# Generator helps using lazy evaluation, which have been mainly used in #
# functional programming paradigm.                                      #
# Decorator was derived from decorator-pattern                          #
# which cames from design-pattern.                                      #
#                                                                       #
#------------------------------------------------------------------------

def gen_list(obj):
    try: assert type(obj) == int or obj <= 0
    except: raise TypeError()
    obj_lists = iter(range(obj))
    for obj_list in obj_lists:
        yield obj_list

def gen_fibonaci():
    init = 1
    value1 = init
    value2 = init
    value3 = value1 + value2
    while(True):
        yield value1
        value1 = value2
        value2 = value3
        value3 = value1 + value2    


class Property:
    def __init__(self,f):
        print 'Initiate decoratortion'
        self.f = f

    def __call__(self,*args,**kwargs):
        arg   = iter(args)
        kwarg = iter(kwargs)
        print 'List of input parameter.'
        for ar in arg: print ar
        self.f(args,kwargs)
        for kwar in kwarg: print 'key:',kwar,'/ value:',kwargs[kwar]
        print 'End of print.'

            
@Property
def Decorator_test(*args,**kwargs):
    print 'We are in Decorator_test.'
    for arg in args: print arg
    for kwarg in kwargs: print 'key:',kwarg,'/ value:',kwargs[kwarg]
    print 'Evacuation from Decorator_test.'


Decorator_test(1,2,3,a=4,b=5)

a = gen_fibonaci()

for i in range(10):
    print a.next()
