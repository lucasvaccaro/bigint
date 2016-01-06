#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <string>
#include "bigint.h"
using namespace std;

// CONSTRUCTORS

BigInt::BigInt() {
    this->digits.push_back(0);
    this->setNegative(false);
}

BigInt::BigInt(string val) {
    this->loadStringVal(val);
}

BigInt::BigInt(int val) {
    if (val < 0)
        this->setNegative(true);
    else
        this->setNegative(false);
    
    //See how many array slots we need
    int numPlaces = 0;
    int val_temp = val;
    
    while (val_temp > 0) {
        val_temp /= 10;
        numPlaces++;
    }
    
    digits.resize(numPlaces);
    
    // Put each digit in each index
    int i = numPlaces - 1;
    while (i >= 0) {
        this->digits.at(i) = val % 10;
        val = val / 10;
        i--;
    }
}

BigInt::BigInt(long long val) {
    if (val < 0)
        this->setNegative(true);
    else
        this->setNegative(false);
    
    //See how many array slots we need
    int numPlaces = 0;
    long long val_temp = val;
    
    while (val_temp > 0) {
        val_temp /= 10;
        numPlaces++;
    }
    
    digits.resize(numPlaces);
    
    // Put each digit in each index
    int i = numPlaces - 1;
    while (i >= 0) {
        this->digits.at(i) = val % 10;
        val = val / 10;
        i--;
    }
}

BigInt::BigInt(vector<int> listOfDigits) { //What about negative here?
    //one vector = another vector? stack.overflow told me it's okay...
    this->digits = listOfDigits;
    this->setNegative(false);
}

BigInt::BigInt(vector<int> listOfDigits, bool isNegative) {
    //one vector = another vector? stack.overflow told me it's okay...
    this->digits = listOfDigits;
    this->negative = isNegative;
}

void BigInt::loadStringVal(string val) {
    int length = val.length();
    char digit;
    int j = 0;
    digit = val[j];
    if (digit == '-') {
        this->setNegative(true);
        j++;
        length--;
    } else {
        this->setNegative(false);
    }
    this->digits.resize(length);
    for (int i = 0; i < length; i++) {
        digit = val[j];
        this->digits[i] = atoi(&digit);
        j++;
    }
}

// SETTERS/GETTERS

int BigInt::getDigit(int index) {
    return this->digits.at(index);
}

int BigInt::getNumDigits() {
    return this->digits.size();
}

bool BigInt::isNegative() {
    return this->negative;
}

void BigInt::setNegative(bool neg) {
    this->negative = neg;
}

// is this useful for something?
//Chris - I used it once
bool BigInt::numericalValZero() { //is it just 0?
    for (int i = 1; i < this->digits.size(); i++) {
        if (this->digits.at(i) != 0) {
            return false;
        }
    }
    
    return true;
}

double BigInt::numericalValDouble() {
    
    double val = 0.0;
   
    for (int i = 1; i < this->digits.size(); i++) {
        val += this->digits.at(i) * pow(10, (this->digits.size() - i));
    }
    
    return val;
}

//HELPER FUNCTIONS FOR OPERATORS

BigInt BigInt::addBI(BigInt bi) {
    int carry = 0;
    vector<int> sumVec(0);
    
    //Setting up for the for loop
    int largerIndex, smallerIndex;
    BigInt larger, smaller;
    if(bi.getNumDigits() > this->getNumDigits()){
        larger = bi;
        largerIndex = bi.getNumDigits() - 1;
        smaller = *this;
        smallerIndex = this->getNumDigits() - 1;
    }
    else{
        larger = *this;
        largerIndex = this->getNumDigits() - 1;
        smaller = bi;
        smallerIndex = bi.getNumDigits() - 1;
    }
    
    for (; largerIndex >= 0; largerIndex--) {
        int sum = 0;
        if(smallerIndex >= 0){
            sum = larger.getDigit(largerIndex) + smaller.getDigit(smallerIndex) + carry;
            smallerIndex--;
        }
        else
            sum = larger.getDigit(largerIndex) + carry; //is the plus carry necessary? it may be for the first time this else gets triggered
        
        if (largerIndex == 0) { //we're at the front element/highest place //Chris: Fixed.
            if (sum >= 10) { //we need to add a digit to the vector
                sumVec.insert(sumVec.begin(), sum % 10);
                carry = sum / 10;
                sumVec.insert(sumVec.begin(), carry);
            } else {
                sumVec.insert(sumVec.begin(), sum);
            }
        }
        else {
            if (sum >= 10) {
                sumVec.insert(sumVec.begin(), sum % 10);
                carry = sum / 10;
            } 
            else {
                sumVec.insert(sumVec.begin(), sum);
                carry = 0;
            }
        }
    }
    
    BigInt diffBI(sumVec);
    return diffBI;
}

BigInt BigInt::subtractBI(BigInt bi){
    vector<int> diffVec, smallerVec;
    int diffVecIndex, smallerVecIndex;
    if(bi.getNumDigits() > this->getNumDigits()){
        diffVec = bi.digits;
        diffVecIndex = bi.getNumDigits() - 1;
        smallerVec = this->digits;
        smallerVecIndex = this->getNumDigits() - 1;
    }
    else{
        diffVec = this->digits;
        diffVecIndex = this->getNumDigits() - 1;
        smallerVec = bi.digits;
        smallerVecIndex = bi.getNumDigits() - 1;
    }
    
    for(; diffVecIndex >= 0; diffVecIndex--){
        if(smallerVecIndex >= 0){
            if(diffVec.at(diffVecIndex) >= smallerVec.at(smallerVecIndex))
               diffVec.at(diffVecIndex) = diffVec.at(diffVecIndex) - smallerVec.at(smallerVecIndex);
            else{
                if(diffVec.at(diffVecIndex - 1) == 0){ //special case, have to borrow from one or more 0s
                    for(int k = diffVecIndex - 1; k >= 0; k--){
                        if(diffVec.at(k) == 0)
                            diffVec.at(k) = 9;
                        else{
                            diffVec.at(k)--;
                            break;
                        }
                    }
                    diffVec.at(diffVecIndex) = (diffVec.at(diffVecIndex) + 10) - smallerVec.at(smallerVecIndex);
                }
                else{
                    diffVec.at(diffVecIndex - 1)--;
                    diffVec.at(diffVecIndex) = (diffVec.at(diffVecIndex) + 10) - smallerVec.at(smallerVecIndex);
                }
            }
            smallerVecIndex--;
        }
    }
    
    BigInt diffBI(diffVec);
    return diffBI;
}

//OPERATORS

bool BigInt::operator<(BigInt bi){
    if(this->getNumDigits() < bi.getNumDigits())
        return true;
    else if(this->getNumDigits() > bi.getNumDigits())
        return false;
        
    for(int i = 0; (i < bi.getNumDigits()) || (i < this->getNumDigits()); i++){
        if(this->getDigit(i) < bi.getDigit(i))
            return true;
        else if(this->getDigit(i) > bi.getDigit(i))
            return false;
    }
    return false;
}

bool BigInt::operator<=(BigInt bi){
    if(this->getNumDigits() < bi.getNumDigits())
        return true;
    else if(this->getNumDigits() > bi.getNumDigits())
        return false;
        
    for(int i = 0; (i < bi.getNumDigits()) || (i < this->getNumDigits()); i++){
        if(this->getDigit(i) < bi.getDigit(i))
            return true;
        else if(this->getDigit(i) > bi.getDigit(i))
            return false;
    }
    return true;
}

bool BigInt::operator>(BigInt bi){
    if(this->getNumDigits() > bi.getNumDigits())
        return true;
    else if(this->getNumDigits() < bi.getNumDigits())
        return false;
        
    for(int i = 0; (i < bi.getNumDigits()) || (i < this->getNumDigits()); i++){
        if(this->getDigit(i) > bi.getDigit(i))
            return true;
        else if(this->getDigit(i) < bi.getDigit(i))
            return false;
    }
    return false;
}

bool BigInt::operator>=(BigInt bi){
    if(this->getNumDigits() > bi.getNumDigits())
        return true;
    else if(this->getNumDigits() < bi.getNumDigits())
        return false;
        
    for(int i = 0; (i < bi.getNumDigits()) || (i < this->getNumDigits()); i++){
        if(this->getDigit(i) > bi.getDigit(i))
            return true;
        else if(this->getDigit(i) < bi.getDigit(i))
            return false;
    }
    return true;
}

bool BigInt::operator==(BigInt bi){
    if(this->getNumDigits() > bi.getNumDigits())
        return false;
    else if(bi.getNumDigits() > this->getNumDigits())
        return false;
    for(int i = 0; i < this->getNumDigits(); i++)
        if(this->getDigit(i) != bi.getDigit(i))
            return false;
    return true;
}

BigInt BigInt::operator+(BigInt bi) {
    BigInt sumBI; //equal to zero.
    
    if (this->isNegative() && bi.isNegative()) {
        sumBI = this->addBI(bi);
        sumBI.setNegative(true);
    }
    else if (this->isNegative()) {
        if (*this < bi) //number + smaller neg. number
            sumBI = bi.subtractBI(*this);
        else if (*this > bi) { //number + larger neg. number
            sumBI = this->subtractBI(bi);
            sumBI.setNegative(true);
        }
    }
    else if (bi.isNegative()) {
        if (bi < *this) //number + smaller neg. number
            sumBI = this->subtractBI(bi);
        else if (bi > *this) { //number + larger neg. number
            sumBI = bi.subtractBI(*this); //get the abs value
            sumBI.setNegative(true);
        }
    } else {
        sumBI = this->addBI(bi);
    }
    
    return sumBI;
}

BigInt BigInt::operator-(BigInt bi) {
    BigInt diffBI; //equal to zero
    
    if (this->isNegative() && bi.isNegative()) {
        if (*this < bi) //negative num - larger negative
            diffBI = bi.subtractBI(*this);
        else if (*this > bi) //negative num - smaller negative
            diffBI = this->subtractBI(bi);
    }
    else if (this->isNegative()){ //negative num - a positive num
        diffBI = this->addBI(bi);
        diffBI.setNegative(true);
    }
    else if(bi.isNegative()) // positive number - negative
        diffBI = this->addBI(bi);
    else{ //if both are positive //NOT WORKING
        if(*this < bi){
            diffBI = bi.subtractBI(*this);
            diffBI.setNegative(true);
        }
        else{// if (*this > bi){
            diffBI = this->subtractBI(bi);
            diffBI.setNegative(false);
        }
    }
    
    return diffBI;
}

BigInt BigInt::operator*(BigInt bi) {
    int new_length = this->getNumDigits() + bi.getNumDigits() - 1;
    vector<int> smaller, bigger;
    
    if (bi.getNumDigits() > this->getNumDigits()) {
        bigger = bi.digits;
        smaller = this->digits;
    }
    else {
        bigger = this->digits;
        smaller = bi.digits;
    }
    
    int bigger_size = bigger.size();
    int zeros = 0;
    BigInt prodBI(0);
    
    for (int j = smaller.size() - 1; j >= 0; j--) {
        vector<int> prodVec(bigger_size);
        int number = smaller.at(j);
        int carry = 0;
        
        for (int i = bigger.size() - 1; i >= 0; i--) {
            int mult = number * bigger.at(i) + carry;
            if (mult >= 10) {
                prodVec.at(i) = mult % 10;
                carry = mult / 10;
                if (i == 0) {
                    prodVec.insert(prodVec.begin(), carry);
                }
            } else {
                prodVec.at(i) = mult;
                carry = 0;
            }
        }
        
        if (zeros > 0) {
            for (int k = 0; k < zeros; k++) {
                prodVec.push_back(0);
            }
        }
        
        BigInt newBI(prodVec);
        prodBI = prodBI + newBI;
        
        zeros++;
    }
    
    //check what the sign should be
    if (!(this->isNegative() && bi.isNegative())) { //they aren't both negative
        if (this->isNegative() || bi.isNegative()) { //one is negative
            prodBI.setNegative(true);
        }
    }
    
    return prodBI;
}

//version that doesn't let you change precision
double BigInt::divideDouble(BigInt bi) {
    int decimalPoint = 0;
    
    int divisor = 0;
    for (int i = 0; i < bi.getNumDigits(); i++) {
        divisor = divisor * 10 + bi.getDigit(i);
    }
    
    int dividend = 0;
    int dividendNumDigits = 0;
    int i = 0;
    if (*this >= bi) { //true dividend >= true divisor
        while (dividend < divisor) {
            dividend = dividend * 10 + this->getDigit(i);
            dividendNumDigits++;
            decimalPoint++;
            i++;
        }
    }
    else { //true dividend < true divisor
        //don't need to modify the dividend
    }
    
    
    double result = 0;
    int division_rem = dividend;
    int j = dividendNumDigits - 1;
    int numDigits = this->getNumDigits();
    while (j < numDigits) {
        double division_resDoub = 0;
        int division_res = 0;
        if(j == numDigits - 1)
            division_resDoub = double(division_rem) / double(divisor);
        else
            division_res = division_rem / divisor;
            
        division_rem = division_rem % divisor;
        if (j == numDigits - 1)
            result = result * 10 + division_resDoub;
        else 
            result = result * 10 + division_res;
        
        if (j < numDigits - 1)
            division_rem = division_rem * 10 + this->getDigit(j+1);
        j++;
    }
    
    if (!(this->isNegative() && bi.isNegative())) { //they aren't both negative //this line is redundant
        if (this->isNegative() || bi.isNegative()) { //one is negative
            result *= -1;
        }
    }
    
    return result;
}

//just a copy of non-precision version for now
double BigInt::divideDouble(BigInt bi, int precision) {
    int decimalPoint = 0;
    
    int divisor = 0;
    for (int i = 0; i < bi.getNumDigits(); i++) {
        divisor = divisor * 10 + bi.getDigit(i);
    }
    
    int dividend = 0;
    int dividendNumDigits = 0;
    int i = 0;
    while (dividend < divisor) {
        dividend = dividend * 10 + this->getDigit(i);
        dividendNumDigits++;
        decimalPoint++;
        i++;
    }
    
    double result = 0;
    int division_rem = dividend;
    int j = dividendNumDigits - 1;
    int numDigits = this->getNumDigits();
    while (j < numDigits) {
        double division_resDoub = 0;
        int division_res = 0;
        if(j == numDigits - 1)
            division_resDoub = double(division_rem) / double(divisor);
        else
            division_res = division_rem / divisor;
            
        division_rem = division_rem % divisor;
        if (j == numDigits - 1)
            result = result * 10 + division_resDoub;
        else 
            result = result * 10 + division_res;
        
        if (j < numDigits - 1)
            division_rem = division_rem * 10 + this->getDigit(j+1);
        j++;
    }
    
    if (!(this->isNegative() && bi.isNegative())) { //they aren't both negative //this line is redundant
        if (this->isNegative() || bi.isNegative()) { //one is negative
            result *= -1;
        }
    }
    
    return result;
}

BigInt BigInt::divideInt(BigInt bi) {
    if (*this < bi) {
        return BigInt();
    }
    
    int divisor = 0;
    for (int i = 0; i < bi.getNumDigits(); i++) {
        divisor = divisor * 10 + bi.getDigit(i);
    }
    
    int dividend = 0;
    int dividendNumDigits = 0;
    int i = 0;
    while (dividend < divisor) {
        dividend = dividend * 10 + this->getDigit(i);
        dividendNumDigits++;
        i++;
    }
    
    int result = 0;
    int division_rem = dividend;
    int j = dividendNumDigits - 1;
    int numDigits = this->getNumDigits();
    while (j < numDigits) {
        int division_res = division_rem / divisor;
        division_rem = division_rem % divisor;
        if (j == 0) {
            result = division_res;
        } else {
            result = result * 10 + division_res;
        }
        if (j < numDigits - 1) {
            division_rem = division_rem * 10 + this->getDigit(j+1);
        }
        j++;
    }
    
    BigInt divBI(result);
    if (!(this->isNegative() && bi.isNegative())) { //they aren't both negative //this line is redundant
        if (this->isNegative() || bi.isNegative()) { //one is negative
            divBI.setNegative(true);
        }
    }
    return divBI;
}

/*
// fourier division (not working)
BigInt BigInt::divideInt(BigInt divisor) {
    int numDigitsC = this->getNumDigits();
    vector<int> c(ceil(numDigitsC/(double)2));
    int j = 0;
    for (int i = 0; i < numDigitsC; i += 2) {
        if (i == numDigitsC-1) {
            c.at(j) = this->getDigit(i);
        } else {
            c.at(j) = this->getDigit(i) * 10 + this->getDigit(i+1);
        }
        j++;
    }
    
    int numDigitsA = divisor.getNumDigits();
    vector<int> a(ceil(numDigitsA/(double)2));
    j = 0;
    for (int i = 0; i < numDigitsA; i += 2) {
        if (i == numDigitsA-1) {
            a.at(j) = divisor.getDigit(i);
        } else {
            a.at(j) = divisor.getDigit(i) * 10 + divisor.getDigit(i+1);
        }
        j++;
    }
    
    vector<int> r;
    vector<int> b;
    
    int c1 = c.at(0);
    int c2 = c.at(1);
    int b_1 = (c1 * 100 + c2) / a.at(0);
    int r_1 = (c1 * 100 + c2) % a.at(0);
   // if (b_1 > 100) {
     //   b_1 = b_1/10;
    //}
    b.push_back(b_1);
    r.push_back(r_1);
    for (int i = 1; i < a.size(); i++) {
        int summation = 0;
        for (int j = 1; j <= i; j++) {
            summation += b.at(i-j) * a.at(j);
        }
        int b_i = (r.at(i-1) * 100 + c.at(i+1) - summation) / a.at(0);
        int r_i = (r.at(i-1) * 100 + c.at(i+1) - summation) % a.at(0);
        if (b_i > 100) {
            b_i = b_i/10;
        }
        b.push_back(b_i);
        r.push_back(r_i);
    }
    
    int num_zeros = b.size() - 1;
    int result = 0;
    for (int i = 0; i < b.size() - 1; i++) {
        result += b.at(i) * pow(10, num_zeros);
        num_zeros -= 2;
    }
    
    cout << "Result: " << result << endl;
} */

// this is for printing BigInt with cout << nicely
// what about printing negatives
ostream& operator<<(ostream &out, BigInt &bi) {
    int size = bi.digits.size();
    if(bi.isNegative())
        cout << "-";
    for (int i = 0; i < size; i++) {
        //out << bi.digits[i] << " "; //added " " for testing purposes
        out << bi.digits[i];
    }
    return out;
}

// this is for storing into BigInt from cin >>
istream& operator>>(istream &in, BigInt &bi) {
    string val;
    in >> val;
    bi.loadStringVal(val);
    return in;
}


//Matrix Operations
// Matrix Addition
// returns an empty matrix if the two aren't equal in dimension
vector< vector<BigInt> > addMatrix(vector< vector<BigInt> > left, vector< vector<BigInt> > toAdd){
    vector< vector<BigInt> > result;
    //Can't add if matrices are of different sizes
    if(left.size() != toAdd.size())
        return result;
    else if(left.at(0).size() != toAdd.at(0).size())
        return result;
        
    for(int row = 0; row < left.size(); row++){
        vector<BigInt> rowVec;
        result.push_back(rowVec);
        for(int col = 0; col < left.at(row).size(); col++)
            result.at(row).push_back(left.at(row).at(col) + toAdd.at(row).at(col));
    }
            
    return result;
}

// Scalar Matrix Multiplication //NOT DONE
vector< vector<BigInt> > addScalarMatrix(vector< vector<BigInt> > left, int toAdd){
    vector< vector<BigInt> > result;

    for(int row = 0; row < left.size(); row++){
        vector<BigInt> rowVec;
        result.push_back(rowVec);
        for(int col = 0; col < left.at(row).size(); col++)
            result.at(row).push_back(left.at(row).at(col) + toAdd); //toMult automatically cast as a BigInt?
    }
    
    return result;
}

// Scalar Matrix Multiplication //NOT DONE
vector< vector<BigInt> > multScalarMatrix(vector< vector<BigInt> > left, int toMult){
    vector< vector<BigInt> > result;

    for(int row = 0; row < left.size(); row++){
        vector<BigInt> rowVec;
        result.push_back(rowVec);
        for(int col = 0; col < left.at(row).size(); col++)
            result.at(row).push_back(left.at(row).at(col) * toMult); //toMult automatically cast as a BigInt?
    }
    
    return result;
}