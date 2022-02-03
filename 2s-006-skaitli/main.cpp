#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

using namespace std;

//////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 6: Skaitli
//////////////////////////////////////////////////////////////

const int UNKNOWN = 0;
int a, b, x, y; // x = a^2b, y = ab^2
// x/y = a/b
// a = xb / y
// b = ay / x
// x2/y = a4b2 / ab2 = a3
// a = root3(x2/y)

void readNumbersFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    inputFile >> a >> b >> x >> y;
    inputFile.close();
}

void writeAnswerToFile(const char *filename) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << a << " " << b << " " << x << " " << y << endl;
    outputFile.close();
}

void findBFromY(int minB, int maxB) {
    b = minB;
    bool found = false;
    while (b <= maxB && !found) {
        a = y / (b * b);
        if (b > a) {
            b = -b;
        }
        found = (a * b * b == y && a >= b);
        if (!found) {
            ++a;
        }
    }
}

void findAFromX(int minA, int maxA) {
    a = minA;
    bool found = false;
    while (a <= maxA && !found) {
        b = x / (a * a);
        if (a < b && a > 0) {
            b = -b;
        }
        found = (a * a * b == x && a >= b);
        if (!found) {
            ++a;
        }
    }
}

void findUnknownValues() {
    if (a == UNKNOWN && b == UNKNOWN && x == UNKNOWN && y == UNKNOWN) {
        a = -999;
        b = -999;
        x = a * a * b;
        y = a * b * b;
    } else if (a == UNKNOWN && b == UNKNOWN && x == UNKNOWN) {
        if (y > 0) {
            // ab^2 is positive ==> a is positive. Minimum possible a = 1
            findBFromY((int) -sqrt(y), (int) sqrt(y));
        } else {
            // ab^2 is negative ==> a is negative
            findBFromY((int) -sqrt(-y), -1);
        }
        x = a * a * b;
    } else if (a == UNKNOWN && b == UNKNOWN && y == UNKNOWN) {
        if (x > 0) {
            // a^2b is positive ==> b is positive
            findAFromX(1, 999);
        } else {
            findAFromX((int) -sqrt(-x), -1);
        }
        y = a * b * b;
    } else if (a == UNKNOWN && b == UNKNOWN) {
        // a = root3(x2/y)
        a = (int) round(pow((double) (x * x / y), 1.0 / 3.0));
        b = a * y / x;
    } else if (a == UNKNOWN && x == UNKNOWN && y == UNKNOWN) {
        // Only b is known
        a = b;
        x = a * a * b;
        y = a * b * b;
    } else if (a == UNKNOWN && x == UNKNOWN) {
        // b and y are known
        a = y / (b * b);
        x = a * a * b;
    } else if (a == UNKNOWN && y == UNKNOWN) {
        // b and x are known
        a = (int) sqrt(x / b);
        y = a * b * b;
    } else if (a == UNKNOWN) {
        // b, x and y are known
        a = y / (b * b);
    } else if (b == UNKNOWN && x == UNKNOWN && y == UNKNOWN) {
        // Only a known
        b = -999;
        x = a * a * b;
        y = a * b * b;
    } else if (b == UNKNOWN && x == UNKNOWN) {
        // a and y known
        b = -(int) sqrt(y / a);
        x = a * a * b;
    } else if (b == UNKNOWN) {
        // a and x are known
        b = x / (a * a);
        y = a * b * b;
    } else {
        // a and b are known
        x = a * a * b;
        y = a * b * b;
    }
}

int main() {
    readNumbersFromFile("skaitli.in");
    findUnknownValues();
    writeAnswerToFile("skaitli.out");
    return 0;
}

