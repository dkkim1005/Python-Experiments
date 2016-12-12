#!/bin/bash
g++ -fPIC -shared -o tester.so tester.cpp -I/usr/include/python2.7  -lpython2.7 -lboost_python
