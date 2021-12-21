#include <iostream>
#include <fstream>

using namespace std;

//////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 99: CIK?
//////////////////////////////////////////////////////////////
void readNumbersFromFile(const char *filename, unsigned int &x, unsigned short &y) {
    ifstream inputFile;
    inputFile.open(filename);
    inputFile >> x >> y;
    inputFile.close();
}

void writeNumberToFile(const char *filename, unsigned short number) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << number;
    outputFile.close();
}

bool containsDigit(unsigned int x, unsigned short digit) {
    bool contains;
    do {
        contains = (x % 10) == digit;
        x /= 10;
    } while (!contains && x > 0);
    return contains;
}

unsigned short cik(unsigned int x, unsigned short y) {
    unsigned short cik = 1;
    while (!containsDigit(x + cik, y)) {
        ++cik;
    }
    return cik;
}

int main() {
    unsigned int x;
    unsigned short y;
    readNumbersFromFile("cik.in", x, y);
    writeNumberToFile("cik.out", cik(x, y));
    return 0;
}

