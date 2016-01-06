#include <iostream>
#include <time.h>
#include <string>
#include "bigint.h"
using namespace std;

void printTimeTests();
void additionTests();
void subtractionTests();
void multiplicationTests();
void divisionIntTests();
void divisionDoubleTests();

int main() {
    string userInput = "";
    while (userInput != "exit"){
        BigInt a, b, result;
        double resultD;
        cout << "Please enter your first number: ";
        cin >> a;
        cout << "Please enter your second number: ";
        cin >> b;
    
        result = (a + b);
        cout << "Addition: " << a << " + " << b << " = " << result << endl;
        result = (a - b);
        cout << "Subtraction: " << a << " - " << b << " = " << result << endl;
        result = (a * b);
        cout << "Multiplication: " << a << " * " << b << " = " << result << endl;
        result = a.divideInt(b);
        cout << "Division returning a BigInt: " << a << " / " << b << " = " << result << endl;
        resultD = a.divideDouble(b);
        cout << "Division returning a double: " << a << " / " << b << " = " << resultD << endl;
        
        cout << "Type 'exit' to quit, type anything else to continue." << endl;
        cin >> userInput;
    }
    
    /*
    additionTests();
    subtractionTests();
    multiplicationTests();
    divisionIntTests();
    divisionDoubleTests();
    printTimeTests();
    */
    
    /*
    // testing I/O
    BigInt bi2;
    cin >> bi2;
    cout << bi2 << endl;
    */
    
    /*// Testing Matrix addition
    vector< vector<BigInt> > biVec1;
    for(int i = 0; i < 5; i++) //let's make example a 5x5 matrix
        ...;*/
    
    
    return 0;
}

void printTimeTests(){
    cout << "Time testing" << endl;
    BigInt *bi = new BigInt(2147483);
    BigInt *bi2 = new BigInt(2147483647);
    BigInt *bi3 = new BigInt("2147483647321123");
    BigInt *bi4 = new BigInt("2147483647321123584893");
    clock_t t;
    
    cout << "Using " << (*bi) << " and " << (*bi2) << "," << endl;
    // Test Addition
    t = clock();
    *bi + *bi2;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to add them together" << endl;
    // Test Subtraction
    t = clock();
    *bi - *bi2;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to subtract them together" << endl;
    // Test Multiplication
    t = clock();
    *bi * *bi2;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to multiply them together" << endl;
    // Test Division
    t = clock();
    bi->divideInt(*bi2);
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to divide them together" << endl;

    cout << "Using " << (*bi2) << " and " << (*bi3) << "," << endl;
    // Test Addition
    t = clock();
    *bi2 + *bi3;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to add them together" << endl;
    // Test Subtraction
    t = clock();
    *bi2 - *bi3;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to subtract them together" << endl;
    // Test Multiplication
    t = clock();
    *bi2 * *bi3;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to multiply them together" << endl;
    // Test Division
    t = clock();
    bi2->divideInt(*bi3);
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to divide them together" << endl;
    
    cout << "Using " << (*bi4) << " and " << (*bi3) << "," << endl;
    // Test Addition
    t = clock();
    *bi3 + *bi4;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to add them together" << endl;
    // Test Subtraction
    t = clock();
    *bi3 - *bi4;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to subtract them together" << endl;
    // Test Multiplication
    t = clock();
    *bi3 * *bi4;
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to multiply them together" << endl;
    // Test Division
    t = clock();
    bi4->divideInt(*bi2);
    cout << "It took " << ((float) (clock() - t) / CLOCKS_PER_SEC) * 1000 << " milliseconds to divide them together" << endl;
    
    delete bi;
    delete bi2;
}

void additionTests(){
    cout << "Addition tests:" << endl;
    
    BigInt* biggerBi = new BigInt(3000123);
    BigInt* mediumBi = new BigInt(750000);
    BigInt* smallerBi = new BigInt(12344);
    BigInt* nBiggerBi = new BigInt("-3000123");
    BigInt* nMediumBi = new BigInt("-750000");
    BigInt* nSmallerBi = new BigInt("-12344");
    
    BigInt result1 = *biggerBi + *mediumBi;
    BigInt result2 = *smallerBi + *biggerBi;
    BigInt result3 = *smallerBi + *biggerBi + *mediumBi;
    BigInt result4 = *smallerBi + *nMediumBi;
    BigInt result5 = *smallerBi + *nBiggerBi;
    BigInt result6 = *nBiggerBi + *nSmallerBi;
    
    cout << *biggerBi << " + " << *mediumBi << " = " << result1 << endl;
    cout << *smallerBi << " + " << *biggerBi << " = " << result2 << endl;
    cout << *smallerBi << " + " << *biggerBi << " + " << *mediumBi << " = " << result3 << endl;
    cout << *smallerBi << " + " << *nMediumBi << " = " << result4 << endl;
    cout << *smallerBi << " + " << *nBiggerBi << " = " << result5 << endl;
    cout << *nBiggerBi << " + " << *nSmallerBi << " = " << result6 << endl;
    
    delete biggerBi, mediumBi, smallerBi, nSmallerBi, nMediumBi, nBiggerBi;
}

void subtractionTests(){
    cout << "Subtraction tests:" << endl;
    
    BigInt* biggerBi = new BigInt(3000123);
    BigInt* mediumBi = new BigInt(750000);
    BigInt* smallerBi = new BigInt(12344);
    BigInt* nBiggerBi = new BigInt("-3000123");
    BigInt* nMediumBi = new BigInt("-750000");
    BigInt* nSmallerBi = new BigInt("-12344");
    BigInt* thousand = new BigInt(1000);
    BigInt* nineninenine = new BigInt(999);
    
    //nineninenine = new BigInt("999");   //for each: left bigger, right bigger
    BigInt result999 = *thousand - *nineninenine;
    cout << "1000 - 999: " << result999 << endl; //works but has trailing 0's
    
    
    BigInt result1 = *nBiggerBi - *mediumBi; //Left negative, left bigger
    BigInt result2 = *nSmallerBi - *biggerBi; //Left negative, right bigger
    BigInt result3 = *mediumBi - *nSmallerBi; //Right negative, left bigger
    BigInt result4 = *smallerBi - *nMediumBi; //Right negative, right bigger
    BigInt result5 = *nBiggerBi - *nMediumBi; //Both negative, left bigger
    BigInt result6 = *nSmallerBi - *nBiggerBi; //Both, right bigger
    BigInt result7 = *biggerBi - *mediumBi; //Neither, left
    BigInt result8 = *smallerBi - *mediumBi; //Neither, right
    
    cout << *nBiggerBi << " - " << *mediumBi << " = " << result1 << endl;
    cout << *nSmallerBi << " - " << *biggerBi << " = " << result2 << endl;
    cout << *mediumBi << " - " << *nSmallerBi << " = " << result3 << endl;
    cout << *smallerBi  << " - " << *nMediumBi << " = " << result4 << endl;
    cout << *nBiggerBi  << " - " << *nMediumBi << " = " << result5 << endl;
    cout << *nSmallerBi << " - " << *nBiggerBi << " = " << result6 << endl;
    cout << *biggerBi << " - " << *mediumBi << " = " << result7 << endl;
    cout << *smallerBi  << " - " << *mediumBi  << " = " << result8 << endl;
    
    delete biggerBi, mediumBi, smallerBi, nSmallerBi, nMediumBi, nBiggerBi, thousand, nineninenine;
}

void multiplicationTests() {
    cout << "Multiplication tests:" << endl;
    
    BigInt* biggerBi = new BigInt(92833809);
    BigInt* mediumBi = new BigInt(75763);
    BigInt* smallerBi = new BigInt(12344);
    BigInt* nBiggerBi = new BigInt("-3000123");
    BigInt* nMediumBi = new BigInt("-750000");
    BigInt* nSmallerBi = new BigInt("-12344");
    
    BigInt result1 = *biggerBi * *mediumBi;
    BigInt result2 = *smallerBi * *biggerBi;
    BigInt result3 = *smallerBi * *nBiggerBi;
    BigInt result4 = *smallerBi * *nMediumBi;
    BigInt result5 = *smallerBi * *nBiggerBi;
    BigInt result6 = *nBiggerBi * *nSmallerBi;
    
    cout << *biggerBi << " * " << *mediumBi << " = " << result1 << endl;
    cout << *smallerBi << " * " << *biggerBi << " = " << result2 << endl;
    cout << *smallerBi << " * " << *nBiggerBi << " = " << result3 << endl;
    
    cout << *smallerBi << " * " << *nMediumBi << " = " << result4 << endl;
    cout << *smallerBi << " * " << *nBiggerBi << " = " << result5 << endl;
    cout << *nBiggerBi << " * " << *nSmallerBi << " = " << result6 << endl;
    
    delete biggerBi, mediumBi, smallerBi, nSmallerBi, nMediumBi, nBiggerBi;
}

void divisionIntTests() {
    cout << "Division (int) tests:" << endl;
    
    BigInt* biggerBi = new BigInt(10550);
    BigInt* mediumBi = new BigInt(50);
    BigInt* smallerBi = new BigInt(12344);
    BigInt* nBiggerBi = new BigInt("-3000123");
    BigInt* nMediumBi = new BigInt("-750000");
    BigInt* nSmallerBi = new BigInt("-12344");
    
    BigInt result1 = biggerBi->divideInt(*mediumBi);
    BigInt result2 = smallerBi->divideInt(*biggerBi);
    BigInt result3 = nBiggerBi->divideInt(*smallerBi);
    BigInt result4 = nMediumBi->divideInt(*smallerBi);
    BigInt result5 = smallerBi->divideInt(*nBiggerBi);
    BigInt result6 = nBiggerBi->divideInt(*nSmallerBi);
    
    cout << *biggerBi << " / " << *mediumBi << " = " << result1 << endl;
    cout << *smallerBi << " / " << *biggerBi << " = " << result2 << endl;
    cout << *nBiggerBi << " / " << *smallerBi << " = " << result3 << endl;
    cout << *nMediumBi << " / " << *smallerBi << " = " << result4 << endl;
    cout << *smallerBi << " / " << *nBiggerBi << " = " << result5 << endl;
    cout << *nBiggerBi << " / " << *nSmallerBi << " = " << result6 << endl;
    
    delete biggerBi, mediumBi, smallerBi, nSmallerBi, nMediumBi, nBiggerBi;
}

void divisionDoubleTests() {
    cout << "Division (double) tests:" << endl;
    
    BigInt* biggerBi = new BigInt(10550);
    BigInt* smallerBi = new BigInt(2000);
    
    double result1 = biggerBi->divideDouble(*biggerBi, 2);
    double result2 = biggerBi->divideDouble(*smallerBi, 2);
    
    cout << *biggerBi << " / " << *biggerBi << " = " << result1 << endl;
    cout << *biggerBi << " / " << *smallerBi << " = " << result2 << endl;
    
    delete biggerBi, smallerBi;
}
