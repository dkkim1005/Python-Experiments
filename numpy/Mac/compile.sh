#!/bin/bash
# This script file is written to compile a c(++) code in the Mac OS X enviroment.

TARGET=tester.so

g++ -fPIC -shared -o $TARGET tester.cpp -I/usr/include/python2.7 \
    -lpython2.7 -lboost_python \
    -I/Users/dongkyukim/Library/Python/2.7/lib/python/site-packages/numpy/core/include/ \
    -I$BOOST_INCLUDE -L$BOOST_LIBRARY

# BOOST_LIBRARY : location for the boost_python.dylib
echo "BOOST Python dylib location: $BOOST_LIBRARY"

install_name_tool -change libboost_python.dylib $BOOST_LIBRARY/libboost_python.dylib tester.so

# Checking linked libraries
otool -L $TARGET
