#include <iostream>
#include <fstream>

using namespace std;


//////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 5: Taisnsturis
//////////////////////////////////////////////////////////////
void readNumbersFromFile(const char *filename, unsigned &m, unsigned &n);
void writeNumberToFile(const char *filename, unsigned number);
unsigned getSquareCount(unsigned m, unsigned n);

int main() {
    unsigned int m, n;
    readNumbersFromFile("taisnst.in", m, n);
    writeNumberToFile("taisnst.out", getSquareCount(m, n));
    return 0;
}

void writeNumberToFile(const char *filename, unsigned number) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << number;
    outputFile.close();
}

void readNumbersFromFile(const char *filename, unsigned &m, unsigned &n) {
    ifstream inputFile;
    inputFile.open(filename);
    inputFile >> m >> n;
    inputFile.close();
}

unsigned getSquareCount(unsigned m, unsigned n) {
    unsigned squareCount = 0;
    while (m > 0 && n > 0) {
        if (m > n) {
            squareCount += m / n;
            m = m % n;
        } else {
            squareCount += n / m;
            n = n % m;
        }
    }
    return squareCount;
}
