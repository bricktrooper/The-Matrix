#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "Fraction.h"

using namespace std;

int gcd(int a, int b);
double fracpt(double x);

// ============================ CONSTRUCTORS ============================ //

Fraction::Fraction()
{
    _numerator = 0;
    _denominator = 0;
}

Fraction::Fraction(const int n, const int d)
{
    _numerator = abs(n);
    _denominator = abs(d);

    if ((n < 0 && d > 0) || (n > 0 && d < 0))
    {
        _numerator *= -1;
    }
}

Fraction::Fraction(const int n)
{
    _numerator = n;
    _denominator = 1;
}

Fraction::Fraction(const Fraction &f)
{
    if (f.isANumber())
    {
        _numerator = f.numerator();
        _denominator = f.denominator();
    }
    else
    {
        _numerator = 0;
        _denominator = 0;
    }
}

// ============================= DESTRUCTOR ============================ //

Fraction::~Fraction()
{
    _numerator = 0;
    _denominator = 0;
}

// ========================== FIELD MUTATORS ========================== //

void Fraction::setNumerator(const int n)
{
    _numerator = n;
}

void Fraction::setDenominator(const int d)
{
    _denominator = d;
}

// ========================== FIELD ACCESSORS ========================== //

int Fraction::numerator() const
{
    return _numerator;
}

int Fraction::denominator() const
{
    return _denominator;
}

bool Fraction::isANumber() const
{
    if (_denominator == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// ============================== METHODS ============================= //

void Fraction::reduce()
{
    if (isANumber())
    {
        if (_numerator == _denominator)
        {
            _numerator = 1;
            _denominator = 1;
        }
        else
        {
            int gcf = gcd(_numerator, _denominator);

            _numerator /= gcf;
            _denominator /= gcf;
        }
    }
}

void Fraction::commonDenominate(Fraction& f1, Fraction& f2) const
{
    if (f1.denominator() != f2.denominator())
    {
        int f1Denominator = f1.denominator();

        f1.setNumerator(f1.numerator() * f2.denominator());
        f1.setDenominator(f1Denominator * f2.denominator());

        f2.setNumerator(f2.numerator() * f1Denominator);
        f2.setDenominator(f2.denominator() * f1Denominator);
    }
}

// ============================= OPERATORS ============================ //

void Fraction::operator =(const Fraction &f)
{
    _numerator = f.numerator();
    _denominator = f.denominator();
}

bool Fraction::operator ==(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return false;
    }

    f1.reduce();
    f2.reduce();

    if (f1.numerator() == f2.numerator() && f1.denominator() == f2.denominator())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Fraction::operator !=(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return true;
    }

    f1.reduce();
    f2.reduce();

    if (f1.numerator() == f2.numerator() && f1.denominator() == f2.denominator())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Fraction::operator <(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return false;
    }

    f1.reduce();
    f2.reduce();

    commonDenominate(f1, f2);

    if (f1.numerator() < f2.numerator())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Fraction::operator >(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return false;
    }

    f1.reduce();
    f2.reduce();

    commonDenominate(f1, f2);

    if (f1.numerator() > f2.numerator())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Fraction::operator <=(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return false;
    }

    if (f1 == f2)
    {
        return true;
    }

    f1.reduce();
    f2.reduce();

    commonDenominate(f1, f2);

    if (f1.numerator() < f2.numerator())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Fraction::operator >=(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return false;
    }

    if (f1 == f2)
    {
        return true;
    }

    f1.reduce();
    f2.reduce();

    commonDenominate(f1, f2);

    if (f1.numerator() > f2.numerator())
    {
        return true;
    }
    else
    {
        return false;
    }
}

Fraction Fraction::operator ~()
{
    Fraction reciprocal = Fraction(_denominator, _numerator);
    reciprocal.reduce();
    return reciprocal;
}

Fraction Fraction::operator +(const Fraction& f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return Fraction();
    }

    f1.reduce();
    f2.reduce();

    commonDenominate(f1, f2);

    Fraction sum = Fraction(f1.numerator() + f2.numerator(), f1.denominator());
    sum.reduce();

    return sum;
}

Fraction Fraction::operator -(const Fraction& f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return Fraction();
    }

    f1.reduce();
    f2.reduce();

    commonDenominate(f1, f2);

    Fraction difference = Fraction(f1.numerator() - f2.numerator(), f1.denominator());
    difference.reduce();

    return difference;
}

Fraction Fraction::operator *(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return Fraction();
    }

    f1.reduce();
    f2.reduce();

    Fraction product = Fraction(f1.numerator() * f2.numerator(), f1.denominator() * f2.denominator());
    product.reduce();

    return product;
}

Fraction Fraction::operator /(const Fraction &f) const
{
    Fraction f1 = *this;
    Fraction f2 = f;

    if (!f1.isANumber() || !f2.isANumber())
    {
        return Fraction();
    }

    f1.reduce();
    f2.reduce();

    Fraction quotient = f1 * (~f2);
    quotient.reduce();

    return quotient;
}

Fraction Fraction::operator ^(const Fraction &f) const
{
    const Fraction ZERO = Fraction(0);

    if (!f.isANumber())
    {
        return Fraction();
    }

    if (f == ZERO)
    {
        return Fraction(1);
    }

    Fraction result = *this;
    double exponent = ((double)(abs(f.numerator())) / (double)(f.denominator()));
    double numeratorResult = pow(_numerator, exponent);
    double denominatorResult = pow(_denominator, exponent);

    if (fracpt(numeratorResult) != 0 || fracpt(denominatorResult) != 0)
    {
        return Fraction();      // NAN if numerator and denominator are not whole numbers after applying exponent
    }

    result.setNumerator(numeratorResult);
    result.setDenominator(denominatorResult);

    if (f < ZERO)
    {
        result = ~result;
    }

    return result;
}

void Fraction::operator +=(const Fraction &f)
{
    *this = *this + f;
}

void Fraction::operator -=(const Fraction &f)
{
    *this = *this - f;
}

void Fraction::operator *=(const Fraction &f)
{
    *this = *this * f;
}

void Fraction::operator /=(const Fraction &f)
{
    *this = *this / f;
}

void Fraction::operator ^=(const Fraction &f)
{
    *this = *this ^ f;
}

// ================================ PRINT ============================= //

std::ostream &operator <<(std::ostream &os, const Fraction &f)
{
    if (!f.isANumber())
    {
        cout << "NAN";
    }
    else
    {
        if (f.numerator() == 0)
        {
            cout << "0";
        }
        else if (f.denominator() == 1)
        {
            cout << f.numerator();
        }
        else
        {
            cout << f.numerator() << "/" << f.denominator();
        }
    }

    return os;
}

// ========================== SUPPORT FUNCTIONS ======================= //

int gcd(int a, int b)
{
	int smallerNumber = 0;
	int gcd = 0;

    if (a == 0)
    {
        return abs(b);
    }

    if (b == 0)
    {
        return abs(a);
    }

	if (abs(a) < abs(b))
	{
		smallerNumber = abs(a);
	}
	else
	{
		smallerNumber = abs(b);
	}

	for (int i = 1; i <= smallerNumber; i++)
	{
		if (a % i == 0 && b % i == 0)
		{
			gcd = i;
		}
	}

	return gcd;
}


double fracpt(double x)
{
    return (double)(x - floor(x));
}

// main //
// int main()
// {
//     Fraction f1 = Fraction(-27, 8);
//     cout << "f1: " << f1 << endl;
   
//     Fraction f2 = Fraction(-1, 3);
//     cout << "f2: " << f2 << endl;

//     Fraction f3 = Fraction(-2, 3);
//     cout << "f3: " << f3 << endl;

//     if (f1 == f2)
//     {
//         cout << "(" << f1 << ") == (" << f2 << ")" << endl;
//     }
//     else
//     {
//         cout << "(" << f1 << ") != (" << f2 << ")" << endl;
//     }

//     if (f1 != f2)
//     {
//         cout << "(" << f1 << ") != (" << f2 << ")" << endl;
//     }
//     else
//     {
//         cout << "(" << f1 << ") == (" << f2 << ")" << endl;
//     }

//     cout << "1 / (" << f3 << ") = " << (~f3) << endl;

//     cout << "(" << f1 << ") + (" << f2 << ") = (" << (f1 + f2) << ")" << endl;
//     cout << "(" << f1 << ") - (" << f2 << ") = (" << (f1 - f2) << ")" << endl;
//     cout << "(" << f1 << ") * (" << f2 << ") = (" << (f1 * f2) << ")" << endl;
//     cout << "(" << f1 << ") / (" << f2 << ") = (" << (f1 / f2) << ")" << endl;
//     cout << "(" << f1 << ") ^ (" << f2 << ") = (" << (f1 ^ f2) << ")" << endl;

//     Fraction temp;

//     cout << "f1: " << f1 << endl;
//     cout << "f2: " << f2 << endl;

//     temp = f1;
//     f1 += f2;
//     cout << "(" << temp << ") + (" << f2 << ") = (" << f1 << ")" << endl;

//     cout << "f1: " << f1 << endl;
//     cout << "f2: " << f2 << endl;

//     temp = f1;
//     f1 -= f2;
//     cout << "(" << temp << ") - (" << f2 << ") = (" << f1 << ")" << endl;

//     cout << "f1: " << f1 << endl;
//     cout << "f2: " << f2 << endl;

//     temp = f1;
//     f1 *= f2;
//     cout << "(" << temp << ") * (" << f2 << ") = (" << f1 << ")" << endl;

//     cout << "f1: " << f1 << endl;
//     cout << "f2: " << f2 << endl;

//     temp = f1;
//     f1 /= f2;
//     cout << "(" << temp << ") / (" << f2 << ") = (" << f1 << ")" << endl;

//     cout << "f1: " << f1 << endl;
//     cout << "f2: " << f2 << endl;

//     temp = f1;
//     f1 ^= f2;
//     cout << "(" << temp << ") ^ (" << f2 << ") = (" << f1 << ")" << endl;

//     cout << "f1: " << f1 << endl;
//     cout << "f2: " << f2 << endl;
// }