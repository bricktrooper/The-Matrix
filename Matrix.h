#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include "Fraction.h"

class Matrix
{
    private:

        // DATA FIELDS //

        int _rows;
        int _cols;
        int _numElements;
        Fraction *_data;

    public:

        // CONSTRUCTORS //

		Matrix();									                    // default constructor (initializes to NOT_A_MATRIX)
		Matrix(const int rows, const int cols, Fraction initValue);		// parametric constructor, initializes all element to initValue
		Matrix(const int rows, const int cols, const Fraction data[]);  // parametric constructor with data array
		Matrix(const Matrix& m);				                        // copy constructor

		// DESTRUCTOR //

		~Matrix();								// destructor

		// FIELD ACCESSORS //

		int numRows() const; 						// return number of rows
		int numColumns() const;					// return number of columns
		int numElements() const;				// return number of elements
		Fraction* data(int index) const;		// return element at index in data
		Fraction* data() const;					// return data array

		// FIELD MUTATORS //

		void setRows(const int rows);					//  sets number of rows
		void setColumns(const int cols);					// set number of cols
        void setData(const int size, const Fraction data[]);           // set matrix elements

		// METHODS //

        bool isAMatrix() const;
		bool isSqaure() const;
        bool isInvertible() const;

        bool appendRow(const int cols, const Fraction data[]);
		bool appendColumn(const int rows, const Fraction data[]);

		bool deleteRow(const int rowNumber);
		bool deleteColumn(const int colNumber);

        void transpose();
        bool append(const Matrix& m);

		Matrix row(const int rowNumber) const;
		Matrix column(const int columnNumber) const;

        static Matrix identity(const int n);

        // ELEMENTARY ROW OPERATIONS //

        bool addRows(int row1, int row2);
        bool subtractRows(int row1, int row2);
        bool scalarMultiplyRow(int row, Fraction scalar);
        bool swapRow(const int row1, const int row2);
		bool swapColumn(const int column1, const int column2);

		Matrix solve(const Matrix b);

		// OPERATORS //

        Fraction* operator ()(int row, int col) const;

        void operator =(const Matrix& m);
		bool operator ==(const Matrix& m) const;
		bool operator !=(const Matrix& m) const;

		Matrix operator +(const Matrix& m) const;
		Matrix operator -(const Matrix& m) const;
		Matrix operator *(const Matrix& m) const;
		Matrix operator ^(const int exponent) const;
		Matrix operator ~() const;

		void operator +=(const Matrix& m);
		void operator -=(const Matrix& m);
		void operator *=(const Matrix& m);
		void operator ^=(const int exponent);

		friend std::ostream& operator <<(std::ostream& os, const Matrix& m);
		static void printAugmentedMatrix(const Matrix& m, const Matrix& b);
};

#endif /* MATRIX_H */