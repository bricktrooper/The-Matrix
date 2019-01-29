#include <iostream>
#include <stdlib.h>

#include "Matrix.h"

#define VALID 1
#define QUIT 0
#define INVALID -1
#define OVERFLOW -2


using namespace std;

void inputDimensions(int& rows, int& cols);
void inputElements(Matrix& A);
void inputAugment(Matrix& b);

int parseInt(char input[], int& number);
int parseFraction(char input[], Fraction& fraction);
int parseDigit(char number);

void clearBuffer();
int exitMenu();

int main()
{
	cout << endl << "~~~~~~~ Welcome to the Matrix ~~~~~~~ " << endl;

	do
	{
		int rows = 0;
		int cols = 0;

		cout << "======================" << endl;
		cout << "Matrix specifications:" << endl;
		cout << "======================" << endl;
		
		inputDimensions(rows, cols);
		Matrix A = Matrix(rows, cols, Fraction(0));

		cout << "Matrix:" << endl;
		cout << A << endl;

		inputElements(A);

		if (cols > 0 && rows > 0)
		{
			Matrix b = Matrix(rows, 1, Fraction(0));

			cout << "Augment:" << endl;
			cout << b << endl;

			inputAugment(b);

			cout << "System:" << endl;
			Matrix::printAugmentedMatrix(A, b);

			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "Solution:" << endl;
			A.solve(b);
		}

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		if (A.isInvertible())
		{
			cout << "Inverse:" << endl;
			cout << ~A << endl;
		}
		else
		{
			cout << "Not Invertible!" << endl;
		}

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	}
	while (!exitMenu());

	return 0;
}

void clearBuffer()
{
	while (getchar() != '\n');
}

int exitMenu()
{
	char menu[100];

	do
	{

		do
		{
			cout << "Exit? (y/n): ";

			for (int i = 0; i < 100; i++)
			{
				menu[i] = '\0';
			}

			if (!scanf("%[^\n]%*c", menu))
			{
				clearBuffer();
			}

			if (strlen(menu) != 1)
			{
				cout << "INVALID INPUT" << endl;
			}
		} while (strlen(menu) != 1);

		if (menu[0] != 'y' && menu[0] != 'Y' && menu[0] != 'n' && menu[0] != 'N')
		{
			cout << "That is not an option!" << endl;
		}

	} while (menu[0] != 'y' && menu[0] != 'Y' && menu[0] != 'n' && menu[0] != 'N');

	if (menu[0] == 'y' || menu[0] == 'Y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void inputDimensions(int& rows, int& cols)
{
	char rowsInput[100];
	char colsInput[100];
	int directive = INVALID;

	// Get ROWS

	do
	{
		rows = 0;

		cout << "Enter number of ROWS: ";

		if (!scanf("%[^\n]%*c", rowsInput))
		{
			clearBuffer();
		}

		directive = parseInt(rowsInput, rows);

		if (directive == VALID && rows < 0)
		{
			cout << "[ERROR] - (NUMBER OF ROWS CANNOT BE NEGATIVE!)" << endl;
		}
		else if (directive == INVALID)
		{
			cout << "[ERROR] - (NOT AN INTEGER!)" << endl;
		}
		else if (directive == OVERFLOW)
		{
			cout << "[ERROR] - (NUMBER OF ROWS IS OUT OF VALID RANGE!)" << endl;
		}
	}
	while (directive != VALID || rows < 0);

	// Get COLUMNS

	do
	{
		cols = 0;
		
		cout << "Enter number of COLUMNS: ";

		if (!scanf("%[^\n]%*c", colsInput))
		{
			clearBuffer();
		}

		directive = parseInt(colsInput, cols);

		if (directive == VALID && cols < 0)
		{
			cout << "[ERROR] - (NUMBER OF COLUMNS CANNOT BE NEGATIVE!)" << endl;
		}
		else if (directive == INVALID)
		{
			cout << "[ERROR] - (NOT AN INTEGER!)" << endl;
		}
		else if (directive == OVERFLOW)
		{
			cout << "[ERROR] - (NUMBER OF COLUMNS IS OUT OF VALID RANGE!)" << endl;
		}
	}
	while (directive != VALID || cols < 0);
}

void inputElements(Matrix& A)
{
	char input[100];
	int directive = INVALID;
	Fraction fraction = Fraction();

	for (int i = 0; i < A.numRows(); i++)
	{
		for (int j = 0; j < A.numColumns(); j++)
		{
			do
			{
				for (int a = 0; a < 100; a++)
				{
					input[a] = '\0';
				}

				cout << "Enter element (" << (i + 1) << ", " << (j + 1) << "): ";

				if (!scanf("%[^\n]%*c", input))
				{
					clearBuffer();
				}

				directive = parseFraction(input, fraction);

				if (directive == INVALID)
				{
					cout << "[ERROR] - (NOT A NUMBER!)" << endl;
				}
				else if (directive == OVERFLOW)
				{
					cout << "[ERROR] - (NUMBER IS OUT OF VALID RANGE!)" << endl;
				}
			}
			while (directive != VALID);

			*A(i, j) = fraction;
			cout << A << endl;
		}
	}
}

void inputAugment(Matrix& b)
{
	char input[100];
	int directive = INVALID;
	Fraction fraction = Fraction();

	for (int i = 0; i < b.numRows(); i++)
	{
		do
		{
			for (int a = 0; a < 100; a++)
			{
				input[a] = '\0';
			}

			cout << "Enter row " << (i + 1) << " augment: ";

			if (!scanf("%[^\n]%*c", input))
			{
				clearBuffer();
			}

			directive = parseFraction(input, fraction);

			if (directive == INVALID)
			{
				cout << "[ERROR] - (NOT A NUMBER!)" << endl;
			}
			else if (directive == OVERFLOW)
			{
				cout << "[ERROR] - (NUMBER IS OUT OF VALID RANGE!)" << endl;
			}
		}
		while (directive != VALID);

		*b(i, 0) = fraction;
		cout << b << endl;
	}
}

int parseDigit(char number)
{
	switch (number)
	{
		case '0':

			return 0;

		case '1':

			return 1;

		case '2':

			return 2;

		case '3':

			return 3;

		case '4':

			return 4;

		case '5':

			return 5;

		case '6':

			return 6;

		case '7':

			return 7;

		case '8':

			return 8;

		case '9':

			return 9;

		default:

			return -1;
	}
}

int parseInt(char input[], int& number)
{
	enum Character {START, SIGN, NUMBER, FINISH};

	int i = 0;
	int digit = 0;

	unsigned char numberOfDigits = 0;
	const unsigned char MAX_NUMBER_OF_DIGITS = 10;

	Character state = START;
	bool isNegative = false;

	while (state != FINISH)
	{
		switch (state)
		{
			case START:

				if (input[i] == '+' || input[i] == '-')
				{
					state = SIGN;
				}
				else if (input[i] >= '0' && input[i] <= '9')
				{
					state = NUMBER;
				}
				else
				{
					return INVALID;
				}

				break;

			case SIGN:

				if (input[i] == '-')
				{
					isNegative = true;
				}

				i++;

				if (input[i] >= '0' && input[i] <= '9')
				{
					state = NUMBER;
				}
				else
				{
					return INVALID;
				}

				break;

			case NUMBER:

				digit = parseDigit(input[i]);

				if ((INT_MAX - (number * 10) < digit) || (numberOfDigits >= MAX_NUMBER_OF_DIGITS))
				{
					return OVERFLOW;
				}
				else
				{
					number = (number * 10) + digit;
					numberOfDigits++;
				}

				i++;

				if (input[i] == 0)
				{
					state = FINISH;
				}
				else if (input[i] >= '0' && input[i] <= '9')
				{
					state = NUMBER;
				}
				else
				{
					return INVALID;
				}

				break;
			
			case FINISH:

				break;
		}
	}

	if (isNegative)
	{
		number = number * -1;
	}

	return VALID;
}

int parseFraction(char input[], Fraction& fraction)
{
	enum Character {START, SIGN_NUMERATOR, SIGN_DENOMINATOR, NUMERATOR, DENOMINATOR, FINISH};
	
	int i = 0;
	int n = 0;
	int d = 0;
	bool hasDenominator = false;
	char numerator[100];
	char denominator[100];
	Character state = START;

	for (int i = 0; i < 12; i++)
	{
		numerator[i] = '\0';
		denominator[i] = '\0';
	}

	while (state != FINISH)
	{
		switch (state)
		{
			case START:

				if (input[i] == '+' || input[i] == '-')
				{
					state = SIGN_NUMERATOR;
				}
				else if (input[i] >= '0' && input[i] <= '9')
				{
					state = NUMERATOR;
				}
				else
				{
					return INVALID;
				}

				break;

			case SIGN_NUMERATOR:

				numerator[n] = input[i];

				n++;
				i++;

				if (input[i] >= '0' && input[i] <= '9')
				{
					state = NUMERATOR;
				}
				else
				{
					return INVALID;
				}

				break;

			case SIGN_DENOMINATOR:

				denominator[d] = input[i];

				d++;
				i++;

				if (input[i] >= '0' && input[i] <= '9')
				{
					state = DENOMINATOR;
				}
				else
				{
					return INVALID;
				}

				break;
			
			case NUMERATOR:

				numerator[n] = input[i];

				n++;
				i++;

				if (input[i] == '\0')
				{
					state = FINISH;
					hasDenominator = false;
				}
				else if (input[i] == '/')
				{
					hasDenominator = true;
					i++;

					if (input[i] == '+' || input[i] == '-')
					{
						state = SIGN_DENOMINATOR;
					}
					else if (input[i] >= '0' && input[i] <= '9')
					{
						state = DENOMINATOR;
					}
					else
					{
						return INVALID;
					}
				}
				else if (!(input[i] >= '0' && input[i] <= '9'))
				{
					return INVALID;
				}

				break;

			case DENOMINATOR:

				denominator[d] = input[i];

				d++;
				i++;

				if (input[i] == '\0')
				{
					state = FINISH;
				}
				else if (!(input[i] >= '0' && input[i] <= '9'))
				{
					return INVALID;
				}

				break;

			case FINISH:

				break;
			}
	}

	int directive = 0;
	n = 0;
	d = 0;

	directive = parseInt(numerator, n);

	if (directive == INVALID)
	{
		return INVALID;
	}
	else if (directive == OVERFLOW)
	{
		return OVERFLOW;
	}
	else
	{
		fraction.setNumerator(n);
	}

	if (hasDenominator)
	{
		directive = parseInt(denominator, d);

		if (directive == INVALID)
		{
			return INVALID;
		}
		else if (directive == OVERFLOW)
		{
			return OVERFLOW;
		}
	}
	else
	{
		d = 1;
	}

	fraction.setDenominator(d);

	return VALID; 
}