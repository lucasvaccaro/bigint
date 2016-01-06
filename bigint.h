#include <iostream>
#include <vector>
using namespace std;

// FIXME: make into char or short array for even less space?
    
class BigInt {
    public:
        BigInt();
        BigInt(string val);
        BigInt(int val);
        BigInt(long long val);
        BigInt(vector<int> listOfDigits);
        BigInt(vector<int> listOfDigits, bool isNegative);
        
        BigInt operator+(BigInt bi);
        BigInt operator-(BigInt bi);
        BigInt operator*(BigInt bi);
        bool operator<(BigInt bi);
        bool operator>(BigInt bi);
        bool operator<=(BigInt bi);
        bool operator>=(BigInt bi);
        bool operator==(BigInt bi);
        
        BigInt divideInt(BigInt bi);
        double divideDouble(BigInt bi);
        double divideDouble(BigInt bi, int precision);
        
        friend ostream& operator<<(ostream &out, BigInt &bi);
        friend istream& operator>>(istream &in, BigInt &bi);
        
        bool numericalValZero(); // is this useful for something?
        double numericalValDouble();
        int getDigit(int index);
        int getNumDigits();
        bool isNegative();
        void setNegative(bool neg);
    private:
        vector<int> digits;
        bool negative;
        BigInt addBI(BigInt bi);
        BigInt subtractBI(BigInt bi);
        void loadStringVal(string val);
};

vector< vector<BigInt> > addMatrix(vector< vector<BigInt> > left, vector< vector<BigInt> > toAdd);
vector< vector<BigInt> > addScalarMatrix(vector< vector<BigInt> > left, int toAdd);
//vector< vector<BigInt> > multMatrix(vector< vector<BigInt> > left, vector< vector<BigInt> > toMult);
vector< vector<BigInt> > multScalarMatrix(vector< vector<BigInt> > left, int toMult);