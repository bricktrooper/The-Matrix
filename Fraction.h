#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>

class Fraction
{
	private:

		// DATA FIELDS //
	
		int _numerator;								// value of numerator
		int _denominator;							// value of denominator

	public:

		// CONSTRUCTORS //

		Fraction();									// default constructor (initializes to 0/0 = NAN)
		Fraction(const int n, const int d);						// parametric constructor
		Fraction(const int n);						// parametric constructor for whole numbers
		Fraction(const Fraction& f);				// copy constructor

		// DESTRUCTOR //

		~Fraction();								// destructor

		// FIELD ACCESSORS //

		int numerator() const; 						// return value of numerator
		int denominator() const;					// return value of denominator
		bool isANumber() const;						// return whether fraction is a number or not (NAN)

		// FIELD MUTATORS //

		void setNumerator(const int n);					//  sets value of numerator
		void setDenominator(const int d);					// set value of denominator

		// METHODS //

		void reduce();							// reduce fraction to lowest terms
		void commonDenominate(Fraction& f1, Fraction& f2) const;		// common denominate two fractions by reference

		// OPERATORS //


		void operator =(const Fraction& f);				// assigns value of fraction to the parameter

		bool operator ==(const Fraction& f) const;				// determine if two fractions are equal
		bool operator !=(const Fraction& f) const;				// determine if two fractions are equal

		bool operator <(const Fraction& f) const;				// determine if first fraction is less than second fraction
		bool operator >(const Fraction& f) const;					// determine if first fraction is greater than second fraction

		bool operator <=(const Fraction& f) const;				// determine if first fraction is less than OR equal to second fraction
		bool operator >=(const Fraction &f) const;				// determine if first fraction is greater OR equal to than second fraction

		Fraction operator~(); // reciprocate fraction
		Fraction operator +(const Fraction& f) const;			// add two fractions
		Fraction operator -(const Fraction& f) const;			// subtract two fractions
		Fraction operator *(const Fraction& f) const;			// multiply two fractions
		Fraction operator /(const Fraction& f) const;			// divide two fractions
		Fraction operator ^(const Fraction& f) const;		// raise a fraction to a power (includes nth roots)

		
		void operator +=(const Fraction& f);			// add two fractions and set reassign the sum to the first fraction
		void operator -=(const Fraction& f);			// subtract two fractions and set reassign the difference to the first fraction
		void operator *=(const Fraction& f);			// multiply two fractions and set reassign the product to the first fraction
		void operator /=(const Fraction& f);			// divide two fractions and set reassign the quotient to the first fraction
		void operator ^=(const Fraction& f);			// raise a fraction to a power (includes nth roots) and reassign the result



		friend std::ostream& operator <<(std::ostream& os, const Fraction& f);		// print fraction
};

#endif /* FRACTION_H */