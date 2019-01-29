#include <iostream>
#include <stdlib.h>

#include "Matrix.h"

using namespace std;

// ============================ CONSTRUCTORS ============================ //

Matrix::Matrix()
{
    _rows = -1;
    _cols = -1;
    _numElements = 0;
    _data = NULL;
}

Matrix::Matrix(const int rows, const int cols, Fraction initValue)
{
    if (rows < 0 || cols < 0 || !initValue.isANumber())
    {
        _rows = -1;
        _cols = -1;
        _numElements = 0;
        _data = NULL;
    }
    else
    {
        _rows = rows;
        _cols = cols;
        _numElements = rows * cols;
        _data = new Fraction[_numElements];

        for (int i = 0; i < _numElements; i++)
        {
            _data[i] = Fraction(initValue);
        }
    }
}

Matrix::Matrix(const int rows, const int cols, const Fraction data[])
{
    if (rows < 0 || cols < 0 || data == NULL)
    {
        _rows = -1;
        _cols = -1;
        _numElements = 0;
        _data = NULL;
    }
    else
    {
        for (int i = 0; i < rows * cols; i++)
        {
            if (!data[i].isANumber())
            {
                _rows = -1;
                _cols = -1;
                _numElements = 0;
                _data = NULL;
                return;
            }
        }

        _rows = rows;
        _cols = cols;
        _numElements = rows * cols;
        _data = new Fraction[_numElements];

        for (int i = 0; i < _numElements; i++)
        {
            _data[i] = Fraction(data[i]);
        }
    }
}

Matrix::Matrix(const Matrix& m)
{
    _rows = m.numRows();
    _cols = m.numColumns();
    _numElements = _rows * _cols;
    _data = new Fraction[_numElements];

    for (int i = 0; i < _numElements; i++)
    {
        _data[i] = Fraction(*m.data(i));
    }
}

// ============================= DESTRUCTOR ============================ //

Matrix::~Matrix()
{
    _rows = -2;
    _cols = -2;
    _numElements = 0;

    delete[] _data;
    _data = NULL;
}
// ========================== FIELD ACCESSORS ========================== //

int Matrix::numRows() const
{
    return _rows;
}

int Matrix::numColumns() const
{
    return _cols;
}

int Matrix::numElements() const
{
    return _numElements;
}

Fraction* Matrix::data(int index) const
{
    return &_data[index];
}

Fraction* Matrix::data() const
{
    return _data;
}

// ========================== FIELD MUTATORS ========================== //

void Matrix::setRows(const int rows)
{
    if (rows >= 0)
    {
        _rows = rows;
    }
}

void Matrix::setColumns(const int cols)
{
    if (cols >= 0)
    {
        _cols = cols;
    }
}

void Matrix::setData(const int size, const Fraction data[])
{
    if (size == _numElements)
    {
        for (int i = 0; i < size; i++)
        {
            _data[i] = data[i];
        }
    }
}

// ============================== METHODS ============================= //

bool Matrix::isAMatrix() const
{
    if (_rows < 0 || _cols < 0 || _data == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Matrix::isSqaure() const
{
    if (_rows == _cols)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Matrix::isInvertible() const
{
    if ((~(*this)).isAMatrix())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Matrix::appendRow(const int cols, const Fraction data[])
{
    if (!isAMatrix() || cols <= 0 || cols != _cols)
	{
		return false;
	}

    _numElements += cols;
    Fraction *newData = new Fraction[_numElements];

    int a = 0;
    int b = 0;

    while (a < (_cols * _rows))
    {
        newData[a] = _data[a];
        a++;
    }

    while (a < _numElements)
    {
        newData[a] = _data[b];
        a++;
        b++;
    }

    delete[] _data;
    _data = newData;
    _rows++;

    return true;
}

bool Matrix::appendColumn(const int rows, const Fraction data[])
{
    if (!isAMatrix() || rows <= 0 || rows != _rows)
    {
        return false;
    }

    _numElements += rows;
    Fraction* newData = new Fraction[_numElements];

    int a = 0;
    int b = 0;
    int c = 0;
    int colsTraversed = 0;

    while (a < _numElements)
    {
        if (colsTraversed == _cols)
        {
            newData[a] = data[b];
            colsTraversed = 0;
            b++;
        }
        else
        {
            newData[a] = _data[c];
            c++;
            colsTraversed++;
        }

        a++;
    }

    delete[] _data;
    _data = newData;
    _cols++;

    return true;
}

bool Matrix::deleteRow(const int rowNumber)
{
    if (!isAMatrix() || rowNumber >= _rows || rowNumber < 0 || _rows == 0)
    {
        return false;
    }

    _numElements = (_cols * (_rows - 1));
    Fraction *newData = new Fraction[_numElements];

    int a = 0;
    int b = 0;

    while (a < (_cols * rowNumber))
    {
        newData[b] = _data[a];
        a++;
        b++;
    }

    for (int i = 0; i < _cols; i++)
    {
        a++;
    }

    while (a < (_cols * _rows))
    {
        newData[b] = _data[a];
        a++;
        b++;
    }

    delete[] _data;
    _data = newData;
    _rows--;

    return true;
}

bool Matrix::deleteColumn(const int colNumber)
{
    if (!isAMatrix() || colNumber >= _cols || colNumber < 0 || _cols == 0)
    {
        return false;
    }

    _numElements = ((_cols - 1) * _rows);
    Fraction *newData = new Fraction[_numElements];

    int a = 0;
    int b = 0;

    while (a < _numElements)
    {

        if ((b - colNumber) % _cols == 0)
        {
            b++;
        }

        newData[a] = _data[b];

        b++;
        a++;
    }

    delete[] _data;
    _data = newData;
    _cols--;

    return true;
}

void Matrix::transpose()
{
    if (isAMatrix())
    {
        Fraction *transposeData = new Fraction[_numElements];

        int j = 0; // column index
        int i = 0; // row index
        int t = 0; // transpose matrix index

        while (j < _cols)
        {
            i = 0;

            while (i < _rows)
            {
                transposeData[t] = _data[(i * _cols) + j];
                i++;
                t++;
            }

            j++;
        }

        delete[] _data;
        _data = transposeData;

        int temp = _rows;
        _rows = _cols;
        _cols = temp;
    }
}

bool Matrix::append(const Matrix& m)
{
    if (!isAMatrix() || !m.isAMatrix())
	{
		return false;
	}

	if (m.numRows() == _rows)
	{
		for (int i = 0; i < m.numColumns(); i++)
		{
			appendColumn(_rows, m.column(i).data());
		}

		return true;
	}
	else if (m.numColumns() == _cols)
	{
		for (int i = 0; i < m.numRows(); i++)
		{
			appendRow(_cols, m.row(i).data());
		}

		return true;
	}
	else
	{
		return false;
	}
}

Matrix Matrix::row(const int rowNumber) const
{
    if (!isAMatrix() || rowNumber >= _rows || rowNumber < 0)
	{
		return Matrix();
	}

    Fraction rowData[_cols];

    for (int i = 0; i < _cols; i++) // copy out row numbers
    {
        rowData[i] = _data[i + (rowNumber * _cols)];
    }

    return Matrix(1, _cols, rowData);	
}

Matrix Matrix::column(const int colNumber) const
{
    if (!isAMatrix() || colNumber >= _cols || colNumber < 0)
	{
		return Matrix();
	}

    Fraction colData[_rows];
    int a = 0;

    for (int i = 0; i < _numElements; i += _cols) // copy out column numbers
    {
        colData[a] = _data[i + colNumber];
        a++;
    }

    return Matrix(_rows, 1, colData);
}

Matrix Matrix::identity(const int n)
{
    Matrix identityMatrix = Matrix(n, n, Fraction(0));

	for (int i = 0; i < n; i++)
	{
		*identityMatrix.data(i * (n + 1)) = Fraction(1);
	}

	return identityMatrix;
}

// ==================== ELEMENTARY ROW OPERATIONS ===================== //

bool Matrix::addRows(int row1, int row2)
{
    if (row1 < 0 || row1 >= _rows || row2 < 0 || row2 >= _rows || row1 == row2)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < _cols; i++)
		{
			_data[i + (row1 * _cols)] += _data[i + (row2 * _cols)];
		}

		return true;
	}   
}

bool Matrix::subtractRows(int row1, int row2)
{
    if (row1 < 0 || row1 >= _rows || row2 < 0 || row2 >= _rows || row1 == row2)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < _cols; i++)
		{
			_data[i + (row1 * _cols)] -= _data[i + (row2 * _cols)];
		}

		return true;
	} 
}

bool Matrix::scalarMultiplyRow(int row, Fraction scalar)
{
    if (row < 0 || row >= _rows)
	{
        return false;
    }
    else
    {
        for (int i = 0; i < _cols; i++)
        {
            _data[i + (row * _cols)] = scalar * _data[i + (row * _cols)];
        }

        return true;
    }
}

bool Matrix::swapRow(const int row1, const int row2)
{
	if (row1 >= _rows || row2 >= _rows || row1 < 0 || row2 < 0 || row1 == row2)
	{
		return false;
	}
	else
	{
		Fraction row1Data[_cols];
		Fraction row2Data[_cols];

		for (int i = 0; i < _cols; i++)	// copy out row 1 and row 2 numbers
		{
			row1Data[i] = _data[i + (row1 * _cols)];
			row2Data[i] = _data[i + (row2 * _cols)];
		}

		for (int i = 0; i < _cols; i++)		// swap row 1 and row 2 numbers
		{
			_data[i + (row1 * _cols)] = row2Data[i];
			_data[i + (row2 * _cols)] = row1Data[i];
		}

		return true;
	}
}

bool Matrix::swapColumn(const int column1, const int column2)
{
	if (column1 >= _cols || column2 >= _cols || column1 < 0 || column2 < 0 || column1 == column2)
	{
		return false;
	}
	else
	{
		int a = 0;			// index of column1Data, column2Data

		Fraction column1Data[_rows];
		Fraction column2Data[_rows];

		for (int i = 0; i < _numElements; i += _cols)
		{
			column1Data[a] = _data[i + column1];
			column2Data[a] = _data[i + column2];
			a++;
		}

		a = 0;

		for (int i = 0; i < _numElements; i += _cols)
		{
			_data[i + column1] = column2Data[a];
			_data[i + column2] = column1Data[a];
			a++;
		}

		return true;
	}
}

Matrix Matrix::solve(const Matrix b)
{
	if (!isAMatrix() || !b.isAMatrix())
	{
		return Matrix();
	}

    if (_rows != b.numRows() || b.numColumns() != 1)
    {
        return Matrix();
    }

    // Start row reduction process

    const Fraction ZERO = Fraction(0);

	Fraction pivot = Fraction(0);		// value of pivot
    Fraction factor = Fraction(0);		// multiplication factor for row containing pivot
    Fraction element = Fraction(0);     // current element being dealt with

    Matrix augment = Matrix(b);               // identity matrix that will become the inverse
    Matrix matrix = Matrix(*this);          // copy of original matrix that will be row reduced

    int i = 0;          // index counter for rows
    int j = 0;          // index counter for columns

    while (i < _rows && j < _cols)       // move down the diagonal and deviate if pivot is zero
    {
		pivot = *matrix(i, j);

        // check if pivot == 0
		// if it is zero then must attempt to swap with a row below that row
		// can only swap if the the is a non-zero element below
		// if only zeros below then the matrix is non-invertible

        bool foundSwap = false;

        while (pivot == ZERO && j < _cols)
        {
			for (int a = i; a < _rows && !foundSwap; a++)       // start at pivot and go down the column to find a non-zero swap
			{	
                element = *matrix(a, j);                  // get new possible pivot

				if (element != ZERO)                             // swap if pivot is non-zero
				{
					matrix.swapRow(a, i);
					augment.swapRow(a, i);
                    pivot = element;                               // set new pivot value
					foundSwap = true;

                    // cout << "Swapped Rows: " << a << " and " << i << endl << "==============" << endl << matrix << endl << "==============" << endl;
				}
			}

            if (!foundSwap)
            {
                j++; // shift over one column if swap is not possible (free variable)
            }

            if (j >= _cols)
            {
                printAugmentedMatrix(matrix, augment);
                return augment;
            }
            else
            {
                pivot = *matrix(i, j);
            }

        } // end of zero pivot case

        // Divide row by the pivot to obtain a leading 1

		matrix.scalarMultiplyRow(i, ~pivot);
		augment.scalarMultiplyRow(i, ~pivot);
        pivot = *matrix(i, j);

		// cout << "Divide by Pivot:" <<  endl << "==============" << endl << matrix << endl << "==============" << endl;

        // take out the elements BELOW the pivot

		for (int a = i + 1; a < _rows; a++)       // run down rows that are BELOW the pivot
		{
            element = *matrix(a, j);

            // if element is already zero then no need to take it out (also avoids multiplying pivot row by zero)

			if (element != ZERO)
			{
				if ((element < ZERO && pivot < ZERO) || (element > ZERO && pivot > ZERO)) // if signs are same then SUBTRACT rows
				{
                    factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl;
                    // cout << "Pivot: " << pivot << endl;
                    // cout << "i: " << i << " j: " << j << endl;

					// Eliminate

					matrix.scalarMultiplyRow(i, factor);        // multiply pivot row in preparation for elimination
					augment.scalarMultiplyRow(i, factor);         // and apply to identity matrix

					matrix.subtractRows(a, i);                  // subtract pivot row (k) from row (a)
					augment.subtractRows(a, i);                   // and apply to identity matrix

					matrix.scalarMultiplyRow(i, ~factor);       // return pivot row to its original state
					augment.scalarMultiplyRow(i, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Below (-):" << endl << "==============" << endl << matrix << endl << "==============" << endl;
				}
				else	// if signs are different then ADD rows
				{
					factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl;
                    // cout << "Pivot: " << pivot << endl;
                    // cout << "i: " << i << " j: " << j << endl;

					// Eliminate

					matrix.scalarMultiplyRow(i, factor);        // multiply pivot row in preparation for elimination
					augment.scalarMultiplyRow(i, factor);         // and apply to identity matrix

					matrix.addRows(a, i);                       // add pivot row (k) to row (a)
					augment.addRows(a, i);                        // and apply to identity matrix

					matrix.scalarMultiplyRow(i, ~factor);       // return pivot row to its original state
					augment.scalarMultiplyRow(i, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Below (+):" << endl << "==============" << endl << matrix << endl << "==============" << endl;
				}
			}

		} // end of eliminaton BELOW

         // take out the elements ABOVE the pivot

		for (int a = i - 1; a >= 0; a--)       // run down rows that are ABOVE the pivot
		{
            element = *matrix(a, j);

            // if element is already zero then no need to take it out (also avoids multiplying pivot row by zero)

			if (element != ZERO)
			{
				if ((element < ZERO && pivot < ZERO) || (element > ZERO && pivot > ZERO)) // if signs are same then SUBTRACT rows
				{
                    factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl;
                    // cout << "Pivot: " << pivot << endl;
                    // cout << "i: " << i << " j: " << j << endl;

					// Eliminate

					matrix.scalarMultiplyRow(i, factor);        // multiply pivot row in preparation for elimination
					augment.scalarMultiplyRow(i, factor);         // and apply to identity matrix

					matrix.subtractRows(a, i);                  // subtract pivot row (k) from row (i)
					augment.subtractRows(a, i);                   // and apply to identity matrix

					matrix.scalarMultiplyRow(i, ~factor);       // return pivot row to its original state
					augment.scalarMultiplyRow(i, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Above (-):" << endl << "==============" << endl << matrix << endl << "==============" << endl;
				}
				else	// if signs are different then ADD rows
				{
					factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl;
                    // cout << "Pivot: " << pivot << endl;
                    // cout << "i: " << i << " j: " << j << endl;

					// Eliminate

					matrix.scalarMultiplyRow(i, factor);        // multiply pivot row in preparation for elimination
					augment.scalarMultiplyRow(i, factor);         // and apply to identity matrix

					matrix.addRows(a, i);                       // add pivot row (k) to row (a)
					augment.addRows(a, i);                        // and apply to identity matrix

					matrix.scalarMultiplyRow(i, ~factor);       // return pivot row to its original state
					augment.scalarMultiplyRow(i, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Above (+):" << endl << "==============" << endl << matrix << endl << "==============" << endl;
				}
			}

		} // end of eliminaton ABOVE

        // increment down diagonal

        i++;
        j++;

    } // end of diagonal traversal with deviation

    printAugmentedMatrix(matrix, augment);
    return augment;
}

// ============================= OPERATORS ============================ //

Fraction* Matrix::operator ()(int row, int col) const
{
    if (!isAMatrix() || row < 0 || row > _rows || col < 0 || col > _cols)
    {
        return NULL;
    }
    else
    {
        return &_data[row * _cols + col];
    }
}

void Matrix::operator =(const Matrix &m)
{
    if (!m.isAMatrix())
	{
		_rows = -1;
		_cols = -1;
		_numElements = 0;
        _data = NULL;
        return;
    }

    _rows = m.numRows();
    _cols = m.numColumns();
    _numElements = _rows * _cols;
    delete[] _data;
    _data = new Fraction[_numElements];

    for (int i = 0; i < _numElements; i++)
    {
        _data[i] = *m.data(i);
    }
}

bool Matrix::operator ==(const Matrix &m) const
{
    if (!isAMatrix() || !m.isAMatrix())
	{
		return false;
	}

	if (_rows != m.numRows() || _cols != m.numColumns())
	{
		return false;
	}

	for (int i = 0; i < _numElements; i++)
	{
		if (_data[i] != *m.data(i))
		{
			return false;
		}
	}

	return true;
}

bool Matrix::operator !=(const Matrix &m) const
{
     if (!isAMatrix() || !m.isAMatrix())
	{
		return true;
	}

	if (_rows != m.numRows() || _cols != m.numColumns())
	{
		return true;
	}

	for (int i = 0; i < _numElements; i++)
	{
		if (_data[i] != *m.data(i))
		{
			return true;
		}
	}

	return false;
}

Matrix Matrix::operator +(const Matrix &m) const
{
    if (!isAMatrix() || !m.isAMatrix())
	{
		return Matrix();
	}

	if (_rows != m.numRows() || _cols != m.numColumns())
	{
		return Matrix();
	}

	Matrix sum = Matrix(_rows, _cols, Fraction(0));

	for (int i = 0; i < _numElements; i++)
	{
		*sum.data(i) = _data[i] + *m.data(i);
	}

	return sum;
}

Matrix Matrix::operator -(const Matrix &m) const
{
    if (!isAMatrix() || !m.isAMatrix())
	{
		return Matrix();
	}

	if (_rows != m.numRows() || _cols != m.numColumns())
	{
		return Matrix();
	}

	Matrix difference = Matrix(_rows, _cols, Fraction(0));

	for (int i = 0; i < _numElements; i++)
	{
		*difference.data(i) = _data[i] - *m.data(i);
	}

	return difference;
}

Matrix Matrix::operator *(const Matrix &m) const
{

    if (!isAMatrix() || !m.isAMatrix())
	{
		return Matrix();
	}

	if (_cols != m.numRows())
	{
		return Matrix();
	}

	Fraction dot = Fraction(0);

	int j2 = 0;		// column index matrix 2 (m)
	int i2 = 0;		// row index matrix 2 (m)
	int j1 = 0;		// column index for matrix 1 (this)
	int i1 = 0;		// row index for matrix 1 (this)
	int p = 0;		// product matrix index

	Matrix newMatrix = Matrix(_rows, m.numColumns(), Fraction(0));

	while (i1 < _rows)
	{
		while (j2 < m.numColumns())
		{
			i2 = 0;
			j1 = (i1 * _cols);

			while (i2 < m.numRows())
			{
				dot += (_data[j1]) * (*m.data((i2 * m.numColumns()) + j2));
				j1++;
				i2++;
			}

			*newMatrix.data(p) = dot;
			dot = Fraction(0);
			p++;
			j2++;
		}

		j2 = 0;
		i1++;
	}

	return newMatrix;
}

Matrix Matrix::operator ^(const int exponent) const
{
    if (!isAMatrix() || exponent < 0 || _cols != _rows)
    {
        return Matrix();
    }

    if (exponent == 0)
    {
        return identity(_rows);
    }

    Matrix newMatrix = Matrix(*this);

    for (int i = 1; i < exponent; i++)
    {
        newMatrix *= *this;
    }

    return newMatrix;
}

Matrix Matrix::operator ~() const
{
    if (!isSqaure() || !isAMatrix())
    {
        return Matrix();
    }

    const Fraction ZERO = Fraction(0);

	Fraction pivot = Fraction(0);		// value of pivot
    Fraction factor = Fraction(0);		// multiplication factor for row containing pivot
    Fraction element = Fraction(0);     // current element being dealt with

    Matrix inverseMatrix = identity(_rows);         // identity matrix that will become the inverse
    Matrix originalMatrix = Matrix(*this);          // copy of original matrix that will be row reduced

    for (int k = 0; k < _rows; k++)                 // move down the diagonal
    {
		pivot = *originalMatrix(k, k);

        // check if pivot == 0
		// if it is zero then must attempt to swap with a row below that row
		// can only swap if the the is a non-zero element below
		// if only zeros below then the matrix is non-invertible

        if (pivot == ZERO)
        {
			bool foundSwap = false;

			for (int i = k; i < _rows && !foundSwap; i++)       // start at pivot and go down the column to find a non-zero swap
			{	
                element = *originalMatrix(i, k);                  // get new possible pivot

				if (element != ZERO)                             // swap if pivot is non-zero
				{
					originalMatrix.swapRow(i, k);
					inverseMatrix.swapRow(i, k);
                    pivot = element;                               // set new pivot value
					foundSwap = true;

                    // cout << "Swapped Rows: " <<  endl << "==============" << endl << originalMatrix << endl << "==============" << endl;
				}
			}

            // if inversion is successful, return invertedMatrix, otherwise return an invalidMatrix

			if (!foundSwap)
			{
				return Matrix();
			}
        } // end of zero pivot case

        // Divide row by the pivot to obtain a leading 1

		originalMatrix.scalarMultiplyRow(k, ~pivot);
		inverseMatrix.scalarMultiplyRow(k, ~pivot);
        pivot = *originalMatrix(k, k);

		// cout << "Divide by Pivot:" <<  endl << "==============" << endl << originalMatrix << endl << "==============" << endl;

        // take out the elements BELOW the pivot

		for (int i = k + 1; i < _rows; i++)       // run down rows that are BELOW the pivot
		{
            element = *originalMatrix(i, k);

            // if element is already zero then no need to take it out (also avoids multiplying pivot row by zero)

			if (element != ZERO)
			{
				if ((element < ZERO && pivot < ZERO) || (element > ZERO && pivot > ZERO)) // if signs are same then SUBTRACT rows
				{
                    factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl << "Pivot: " << pivot << endl;

					// Eliminate

					originalMatrix.scalarMultiplyRow(k, factor);        // multiply pivot row in preparation for elimination
					inverseMatrix.scalarMultiplyRow(k, factor);         // and apply to identity matrix

					originalMatrix.subtractRows(i, k);                  // subtract pivot row (k) from row (i)
					inverseMatrix.subtractRows(i, k);                   // and apply to identity matrix

					originalMatrix.scalarMultiplyRow(k, ~factor);       // return pivot row to its original state
					inverseMatrix.scalarMultiplyRow(k, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Below (-):" << endl << "==============" << endl << originalMatrix << endl << "==============" << endl;
				}
				else	// if signs are different then ADD rows
				{
					factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl << "Pivot: " << pivot << endl;

					// Eliminate

					originalMatrix.scalarMultiplyRow(k, factor);        // multiply pivot row in preparation for elimination
					inverseMatrix.scalarMultiplyRow(k, factor);         // and apply to identity matrix

					originalMatrix.addRows(i, k);                       // add pivot row (k) to row (i)
					inverseMatrix.addRows(i, k);                        // and apply to identity matrix

					originalMatrix.scalarMultiplyRow(k, ~factor);       // return pivot row to its original state
					inverseMatrix.scalarMultiplyRow(k, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Below (+):" << endl << "==============" << endl << originalMatrix << endl << "==============" << endl;
				}
			}

		} // end of eliminaton BELOW

         // take out the elements ABOVE the pivot

		for (int i = k - 1; i >= 0; i--)       // run down rows that are ABOVE the pivot
		{
            element = *originalMatrix(i, k);

            // if element is already zero then no need to take it out (also avoids multiplying pivot row by zero)

			if (element != ZERO)
			{
				if ((element < ZERO && pivot < ZERO) || (element > ZERO && pivot > ZERO)) // if signs are same then SUBTRACT rows
				{
                    factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl << "Pivot: " << pivot << endl;

					// Eliminate

					originalMatrix.scalarMultiplyRow(k, factor);        // multiply pivot row in preparation for elimination
					inverseMatrix.scalarMultiplyRow(k, factor);         // and apply to identity matrix

					originalMatrix.subtractRows(i, k);                  // subtract pivot row (k) from row (i)
					inverseMatrix.subtractRows(i, k);                   // and apply to identity matrix

					originalMatrix.scalarMultiplyRow(k, ~factor);       // return pivot row to its original state
					inverseMatrix.scalarMultiplyRow(k, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Above (-):" << endl << "==============" << endl << originalMatrix << endl << "==============" << endl;
				}
				else	// if signs are different then ADD rows
				{
					factor = element;

					if (factor < ZERO)	// take absolute value of factor so the signs don't change
					{
						factor = factor * Fraction(-1);
					}
                    
					// cout << "Factor: " << factor << endl << "Pivot: " << pivot << endl;

					// Eliminate

					originalMatrix.scalarMultiplyRow(k, factor);        // multiply pivot row in preparation for elimination
					inverseMatrix.scalarMultiplyRow(k, factor);         // and apply to identity matrix

					originalMatrix.addRows(i, k);                       // add pivot row (k) to row (i)
					inverseMatrix.addRows(i, k);                        // and apply to identity matrix

					originalMatrix.scalarMultiplyRow(k, ~factor);       // return pivot row to its original state
					inverseMatrix.scalarMultiplyRow(k, ~factor);        // and apply to identity matrix

					// cout << "Eliminate Above (+):" << endl << "==============" << endl << originalMatrix << endl << "==============" << endl;
				}
			}

		} // end of eliminaton ABOVE

    } // end of diagonal traversal

    return inverseMatrix;
}

void Matrix::operator +=(const Matrix &m)
{
    *this = *this + m;
}

void Matrix::operator -=(const Matrix &m)
{
    *this = *this - m;
}

void Matrix::operator *=(const Matrix &m)
{
    *this = *this * m;
}

void Matrix::operator ^=(const int exponent)
{
    *this = *this ^ exponent;
}

// ================================ PRINT ============================= //

std::ostream& operator <<(std::ostream& os, const Matrix& m)
{
    if (m.numRows() == -2 || m.numColumns() == -2)
	{
		os << "[ERROR] - (MATRIX DELETED) Could not display matrix!" << endl;
        return os;
	}

	if (!m.isAMatrix())
	{
		os << "[ERROR] - (NOT A MATRIX) Could not display matrix!" << endl;
		return os;
	}

    if (m.numRows() == 0)
    {
        os << "[ ]";
    }

    for (int i = 0; i < m.numRows(); i++)
    {
        os << "[";

        for (int j = 0; j < m.numColumns(); j++)
        {
            os << *m(i, j);

			if (j < (m.numColumns() - 1))
			{
                os << "  ";
			}
        }

        os << "]";

		if (i < (m.numRows() - 1))
		{
			os << std::endl;
		}
    }

    return os;
}

void Matrix::printAugmentedMatrix(const Matrix& A, const Matrix& b)
{
    if (A.numRows() == -2 || A.numColumns() == -2)
	{
		cout << "[ERROR] - (MATRIX DELETED) Could not display matrix!" << endl;
        return;
	}

	if (!A.isAMatrix())
	{
		cout << "[ERROR] - (NOT A MATRIX) Could not display matrix!" << endl;
		return;
	}

    if (b.numRows() == -2 || b.numColumns() == -2)
	{
		cout << "[ERROR] - (MATRIX DELETED) Could not display augment!" << endl;
        return;
	}

	if (!b.isAMatrix())
	{
		cout << "[ERROR] - (NOT A MATRIX) Could not display augment!" << endl;
		return;
	}

    if (A.numRows() != b.numRows() || b.numColumns() != 1)
    {
        cout << "[ERROR] - (NOT A MATRIX) matrix and augment are not compatible!" << endl;
        return;
    }

    if (A.numRows() == 0)
    {
        cout << "[  | ]";
    }

    for (int i = 0; i < A.numRows(); i++)
    {
        cout << "[";

        for (int j = 0; j < A.numColumns(); j++)
        {
            cout << *A(i, j);

			if (j < (A.numColumns() - 1))
			{
                cout << "  ";
			}
        }

        cout << " | ";
        cout << *b(i, 0);
        cout << "]";

		if (i < (A.numRows() - 1))
		{
			cout << std::endl;
		}
    }

    cout << endl;

    return;
}