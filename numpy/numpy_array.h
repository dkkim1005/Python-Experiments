#if !defined(PYTHON_NUMPY_WRAPPER)
#define PYTHON_NUMPY_WRAPPER

#include <iostream>
#include <string>
#include <Python.h>
#include <numpy/ndarrayobject.h>

// Reference
// : https://jianfengwang.wordpress.com/2015/11/19/how-python-calls-cc-functions/
// : http://stackoverflow.com/questions/18780570/passing-a-c-stdvector-to-numpy-array-in-python


// python ndarray  -->  C++ array
template <typename T>
class ndarray_to_C_ptr_wrapper
{
public:
	ndarray_to_C_ptr_wrapper(PyObject* num_array);
	~ndarray_to_C_ptr_wrapper();
	T* get_ptr() const;
	int get_total_size() const;
	int get_size(const int i) const;
	int get_ndim() const;
	T& operator[](const int i) const;
private:
	PyArrayObject* in_con;
	int count;
	int num_dim;
	npy_intp* pdim;
	T* ptr;
};

template <typename T>
ndarray_to_C_ptr_wrapper<T>::ndarray_to_C_ptr_wrapper(PyObject* num_array)
: in_con(NULL), count(1), num_dim(0), pdim(NULL), ptr(NULL)
{
	in_con = PyArray_GETCONTIGUOUS((PyArrayObject*)num_array);
	ptr = (T*)PyArray_DATA(in_con);
	pdim = PyArray_DIMS(in_con);
	num_dim = PyArray_NDIM(in_con);

	for(int i=0;i<num_dim;++i) count *= pdim[i];
}

template <typename T>
ndarray_to_C_ptr_wrapper<T>::~ndarray_to_C_ptr_wrapper() 
{
	if(in_con != NULL)
		Py_DECREF(in_con);
}

template <typename T>
T* ndarray_to_C_ptr_wrapper<T>::get_ptr() const
{
	return ptr;
}

template <typename T>
int ndarray_to_C_ptr_wrapper<T>::get_total_size() const
{
	return count;
}

template <typename T>
int ndarray_to_C_ptr_wrapper<T>::get_size(const int i) const
{
	return pdim[i];
}

template <typename T>
int ndarray_to_C_ptr_wrapper<T>::get_ndim() const
{
	return num_dim;
}

template <typename T>
T& ndarray_to_C_ptr_wrapper<T>::operator[](const int i) const
{
	return ptr[i];
}


/*
C++ array  -->  python ndarray

argument:
	C_ptr : Data type (e.g. float, double, ...)
	NUM_DIMENSION : Dimension of ndarray (e.g. 1,2, ...)
	DIMS : Shape of ndarray (e.g. {dim1,dim2,dim3,...})
	TYPE : dtype of ndarray (e.g. NPY_FLOAT32, NPY_FLOAT64, ...)

*/

template<typename T>
PyObject* C_ptr_to_ndarray_wrapper(const T* C_ptr,const int NUM_DIMENSION, npy_intp* const DIMS, const int TYPE)
{
	PyObject* numpyArray = (PyObject*)PyArray_SimpleNew(NUM_DIMENSION,DIMS,TYPE);
	ndarray_to_C_ptr_wrapper<T> wrapper(numpyArray);
	memcpy(wrapper.get_ptr(),C_ptr,sizeof(T)*wrapper.get_total_size());
	return numpyArray;
}

#endif
