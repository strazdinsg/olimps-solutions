#include <iostream>
#include <fstream>

using namespace std;

unsigned short readNumberFromFile(const char *filename);
void writeNumberToFile(const char *filename, int number);

//////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 1: Reizinasana ar 2
//////////////////////////////////////////////////////////////
int main() {
    unsigned short n = readNumberFromFile("reiz.in");
    writeNumberToFile("reiz.out", n * 2);
    return 0;
}

void writeNumberToFile(const char *filename, int number) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << number;
    outputFile.close();
}

unsigned short readNumberFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    unsigned n = 0;
    inputFile >> n;
    inputFile.close();
    return n;
}
