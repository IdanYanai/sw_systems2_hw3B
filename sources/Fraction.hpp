#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

namespace ariel {
    class Fraction {
        private:
            int numerator, denominator;

        public:
            // inline
            Fraction() : numerator(1), denominator(1) {}
            Fraction(int nume, const int deno) : numerator(nume), denominator(deno) {
                if(deno == 0) {
                    throw invalid_argument("Denominator cannot be 0!");
                }
                if(this->denominator<0) {
                    this->denominator = abs(this->denominator);
                    this->numerator = -this->numerator;
                }
                this->reduce();
            }

            void setNumerator(int newNume) {this->numerator = newNume; }
            int getNumerator() const { return this->numerator; }
            void setDenominator(int newDeno) { this->denominator = newDeno; }
            int getDenominator() const { return this->denominator; }

            void reduce() {
                if((this->numerator<0) && (this->denominator<0)) {
                    this->numerator = abs(this->numerator);
                    this->denominator = abs(this->denominator);
                }

                int greatestdiv = abs(gcd(this->numerator, this->denominator));

                this->numerator /= greatestdiv;
                this->denominator /= greatestdiv;
            }

            // helper function for reduce
            int gcd(int nume, int deno) {
                if(nume==0) {
                    return deno;
                }
                return gcd(deno % nume, nume);
            }

            // postfix
            Fraction operator++(int dummyFlag) {
                Fraction copy = *this;
                this->numerator += this->denominator;
                this->reduce();
                return copy;
            }

            // prefix
            Fraction& operator++() {
                this->numerator += this->denominator;
                this->reduce();
                return *this;
            }

            // postfix
            Fraction operator--(int dummyFlag) {
                Fraction copy = *this;
                this->numerator -= this->denominator;
                this->reduce();
                return copy;
            }

            // prefix
            Fraction& operator--() {
                this->numerator -= this->denominator;
                this->reduce();
                return *this;
            }

            friend bool operator==(const Fraction& num1, const Fraction& num2) {
                if((num1.numerator == 0) && (num2.numerator == 0)) {
                    return true;
                }
                if(((num1.numerator<0) || (num1.denominator<0)) && (num2.numerator>0) && (num2.denominator>0)) {
                    return false;
                }
                if(((num2.numerator<0) || (num2.denominator<0)) && (num1.numerator>0) && (num1.denominator>0)) {
                    return false;
                }

                int nume1 = num1.numerator*num2.denominator;
                int nume2 = num2.numerator*num1.denominator;
                return (nume1 == nume2);
            }

            // outline
            Fraction(float num);

            friend bool operator<=(const Fraction& num1, const Fraction& num2);
            friend bool operator>=(const Fraction& num1, const Fraction& num2);
            friend bool operator<(const Fraction& num1, const Fraction& num2);
            friend bool operator>(const Fraction& num1, const Fraction& num2);

            friend Fraction operator+(const Fraction& num1, const Fraction& num2);
            friend Fraction operator-(const Fraction& num1, const Fraction& num2);
            friend Fraction operator*(const Fraction& num1, const Fraction& num2);
            friend Fraction operator/(const Fraction& num1, const Fraction& num2);

            friend ostream& operator<< (ostream& output, const Fraction& num);
            friend istream& operator>> (istream& input, Fraction& num);
    };
}