#include <iostream>
#include <fstream>

using namespace std;

void writeNumberToFile(const char *filename, unsigned number) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << number << endl;
    outputFile.close();
}

void stripBadChars(string &s) {
    for (unsigned i = 0; i < s.length(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            s.erase(i, 1);
        }
    }
}

void readNumbersFromFile(const char *filename, string &k, string &m) {
    ifstream inputFile;
    inputFile.open(filename);
    getline(inputFile, k);
    getline(inputFile, m);
    stripBadChars(k);
    stripBadChars(m);
    inputFile.close();
}

unsigned convertCharToDigit(unsigned char c) {
    return c - '0';
}

unsigned multiplyDigits(unsigned char digit1, unsigned char digit2) {
    return convertCharToDigit(digit1) * convertCharToDigit(digit2);
}

unsigned sumDigitsFor(unsigned s) {
    while (s > 9u) {
        s = (s / 10) + (s % 10);
    }
    return s;
}

unsigned calcSuperSum(const string &k, const string &m) {
    unsigned superSum = 0;
    // Multiply each digit of m by each digit of k, add the multiplication to super-sum
    // Get a single-digit value after each multiplication
    for (unsigned i = 0; i < k.length(); ++i) {
        for (unsigned j = 0; j < m.length(); ++j) {
            unsigned digitMultiplication = multiplyDigits(k[i], m[j]);
            superSum += digitMultiplication;
            superSum = sumDigitsFor(superSum);
        }
    }
    return superSum;
}


//////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 97: Supersumma
//////////////////////////////////////////////////////////////
int main() {
    string k, m;
    readNumbersFromFile("super.in", k, m);
    writeNumberToFile("super.out", calcSuperSum(k, m));
    return 0;
}

