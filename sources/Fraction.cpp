#include <iostream>
#include <limits>

using namespace std;

#include "Fraction.hpp"

namespace ariel {
    Fraction::Fraction(float num) {
        num *= 1000;
        int inum = static_cast<int>(num);
        this->denominator = 1000;
        this->numerator = inum;
        this->reduce();
    }

    // All comparison operations -------------------

    bool operator<=(const Fraction& num1, const Fraction& num2) {
        if((num1.numerator == 0) && (num2.numerator == 0)) {
            return true;
        }
        if(((num1.numerator<0) || (num1.denominator<0)) && (num2.numerator>0) && (num2.denominator>0)) {
            return true;
        }
        if(((num2.numerator<0) || (num2.denominator<0)) && (num1.numerator>0) && (num1.denominator>0)) {
            return false;
        }

        int nume1 = num1.numerator*num2.denominator;
        int nume2 = num2.numerator*num1.denominator;
        return (nume1 <= nume2);
    }

    bool operator>=(const Fraction& num1, const Fraction& num2) {
        if((num1.numerator == 0) && (num2.numerator == 0)) {
            return true;
        }
        if(((num1.numerator<0) || (num1.denominator<0)) && (num2.numerator>0) && (num2.denominator>0)) {
            return false;
        }
        if(((num2.numerator<0) || (num2.denominator<0)) && (num1.numerator>0) && (num1.denominator>0)) {
            return true;
        }

        int nume1 = num1.numerator*num2.denominator;
        int nume2 = num2.numerator*num1.denominator;
        return (nume1 >= nume2);
    }

    bool operator<(const Fraction& num1, const Fraction& num2) {
        if((num1.numerator == 0) && (num2.numerator == 0)) {
            return false;
        }
        if(((num1.numerator<0) || (num1.denominator<0)) && (num2.numerator>0) && (num2.denominator>0)) {
            return true;
        }
        if(((num2.numerator<0) || (num2.denominator<0)) && (num1.numerator>0) && (num1.denominator>0)) {
            return false;
        }

        int nume1 = num1.numerator*num2.denominator;
        int nume2 = num2.numerator*num1.denominator;
        return (nume1 < nume2);
    }

    bool operator>(const Fraction& num1, const Fraction& num2) {
        if((num1.numerator == 0) && (num2.numerator == 0)) {
            return false;
        }
        if(((num1.numerator<0) || (num1.denominator<0)) && (num2.numerator>0) && (num2.denominator>0)) {
            return false;
        }
        if(((num2.numerator<0) || (num2.denominator<0)) && (num1.numerator>0) && (num1.denominator>0)) {
            return true;
        }

        int nume1 = num1.numerator*num2.denominator;
        int nume2 = num2.numerator*num1.denominator;
        return (nume1 > nume2);
    }

    // All math operations -------------------

    Fraction operator+(const Fraction& num1, const Fraction& num2) {
        int max_int = numeric_limits<int>::max();
        int min_int = numeric_limits<int>::min();

        if(num2.numerator > 0 && num1.numerator > max_int - num2.numerator) {
            throw overflow_error("overflow");
        }
        if(num2.numerator < 0 && num1.numerator < min_int - num2.numerator) {
            throw overflow_error("underflow");
        }

        int nume = num1.getNumerator()*num2.getDenominator() + num2.getNumerator()*num1.getDenominator();
        int deno = num1.getDenominator()*num2.getDenominator();

        Fraction toReturn = Fraction(nume, deno);
        toReturn.reduce();
        return toReturn;
    }

    Fraction operator-(const Fraction& num1, const Fraction& num2) {
        int max_int = numeric_limits<int>::max();
        int min_int = numeric_limits<int>::min();

        if(num2.numerator < 0 && num1.numerator > max_int + num2.numerator) {
            throw overflow_error("overflow");
        }
        if(num2.numerator > 0 && num1.numerator < max_int + num2.numerator) {
            throw overflow_error("underflow");
        }

        int nume = num1.getNumerator()*num2.getDenominator() - num2.getNumerator()*num1.getDenominator();
        int deno = num1.getDenominator()*num2.getDenominator();

        Fraction toReturn = Fraction(nume, deno);
        toReturn.reduce();
        return toReturn;
    }

    Fraction operator*(const Fraction& num1, const Fraction& num2) {
        int max_int = numeric_limits<int>::max();
        int min_int = numeric_limits<int>::min();

        if(num2.numerator != 0 && abs(num1.numerator) > max_int / abs(num2.numerator)) {
            throw overflow_error("overflow");
        }
        if(num2.denominator != 0 && abs(num1.denominator) > max_int / abs(num2.denominator)) {
            throw overflow_error("overflow");
        }

        int nume = num1.getNumerator()*num2.getNumerator();
        int deno = num1.getDenominator()*num2.getDenominator();

        Fraction toReturn = Fraction(nume, deno);
        toReturn.reduce();
        return toReturn;
    }

    Fraction operator/(const Fraction& num1, const Fraction& num2) {
        if (num2.numerator == 0){
            throw runtime_error("Division by zero is illegal!");
        }

        int max_int = numeric_limits<int>::max();
        int min_int = numeric_limits<int>::min();

        if(num2.denominator != 0 && abs(num1.numerator) > max_int / abs(num2.denominator)) {
            throw overflow_error("overflow");
        }
        if(num2.numerator != 0 && abs(num1.denominator) > max_int / abs(num2.numerator)) {
            throw overflow_error("overflow");
        }

        int nume = num1.getNumerator()*num2.getDenominator();
        int deno = num1.getDenominator()*num2.getNumerator();

        Fraction toReturn = Fraction(nume, deno);
        toReturn.reduce();
        return toReturn;
    }

    // All IO operations -------------------

    ostream& operator<< (ostream& output, const Fraction& num) {
        if(num.getDenominator() < 0)
            return (output << "-" << num.getNumerator() << "/" << abs(num.getDenominator()));
        return (output << num.getNumerator() << "/" << num.getDenominator());
    }

    istream& operator>> (istream& input, Fraction& num) {
        if(input >> num.numerator) {;}
        else {
            throw runtime_error("Please input 2 numbers");
        }
        if(input >> num.denominator) {;}
        else {
            throw runtime_error("Please input 2 numbers");
        }

        if(num.denominator == 0) {
            throw runtime_error("Denominator cannot be 0!");
        }

        return input;
    }
}