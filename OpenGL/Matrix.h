#pragma once

template<class T> class Matrix {
	T* _elements;
	int _dimension;
	int* _size;
	int _allSize;
public:
	Matrix() {
		_elements = new T();
		_dimension = 0;
		_size = new int(1){ 1 };
	}
	Matrix(int dimension, int* size, T& element) {
		_dimension = dimension;
		_size = new int(dimension);
		_allSize = 0;
		for (int i = 0; i < _dimension; i++)
			_allSize += _size[i] = size[i];
		_elements = new T(_allSize);
		for (int i = 0; i < _allSize; i++)
			_elements[i] = element;
	}
	Matrix(int dimension, int* size, T* elements) {
		_dimension = dimension;
		_size = new int(dimension);
		_allSize = 0;
		for (int i = 0; i < _dimension; i++)
			_allSize += _size[i] = size[i];
		_elements = new T(_allSize);
		for (int i = 0; i < _allSize; i++)
			_elements[i] = elements[i];
	}
	~Matrix() {
		delete _elements;
		delete _size;
	}
	int getDimension() {
		return _dimension;
	}
	int getSize(int s) {
		if (s > _dimension)
			return -1;
		return _size[s];
	}
	T getElem() {

	}
	T operator[] (int i) {
		int s[_dimension - 1 > 0 ? _dimension - 1 : 1];
		int sumS = 0;
		for (int j = 0; j < _dimension-1>0? _dimension - 1:1; j++)
			sumS*=s[j] = _size[j];
		T* elem = new T(sumS);
		for (int j = 0; j < sumS; j++)
		{
			elem[j] = _elements[_size[_dimension - 2 >= 0 ? _dimension - 2:0 ] * i + j];
		}
		Matrix m(_dimension-1, s, elem);
		return m;
	}
	Matrix operator* (Matrix mat) {
		int dim = mat.getDimension();
		int s[dim];
		for (int i = 0, i < dim, ++i)
			s[i] = mat.getSize(i);
		if (_dimension != dim + 1)
			throw("Wrong dimention");
		T perem = 0;
		int* newSize = new int(_dimension - dim);
		for (int i = 0; i < _dimension - dim; i++)
		{
			newSize[i] = _size[_dimension - i];
		}
		Matrix m(_dimension - dim, newSize, perem);
		T sum = 0;
		for (int i = 0, i < _size[0], ++i) {
			sum = 0;
			for (int j = 0; j < _size[1]; ++j) {
				sum += _elements[i * _size[1] + j] * mat[j][i];
			}
			m[i][j] = sum;
		}
		return m;
	}
};