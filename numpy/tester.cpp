#include <iostream>
#include <boost/python.hpp>
#include "numpy_array.h"

double vector_dot(PyObject* A,PyObject* B)
{
	ndarray_to_C_ptr_wrapper<double> wrapperA(A);
	ndarray_to_C_ptr_wrapper<double> wrapperB(B);
	
	const int size = std::min(wrapperA.get_total_size(),wrapperB.get_total_size());
	double result = 0;
	for(int i=0;i<size;++i)
		result += wrapperA[i] * wrapperB[i];
	return result;
}

void scalar_dot(PyObject* A,int B)
{
	ndarray_to_C_ptr_wrapper<double> wrapperA(A);
	const int size = wrapperA.get_total_size();
	for(int i=0;i<size;++i)
		wrapperA[i] *= B;
}


BOOST_PYTHON_MODULE(tester)
{
	import_array();
	boost::python::def("vector_dot",vector_dot);
	boost::python::def("scalar_dot",scalar_dot);
}
