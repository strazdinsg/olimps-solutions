#include <iostream>
#include <fstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 31: Labi sakartotie skaitli, 2 stars
///////////////////////////////////////////////////////////////////////////////

unsigned short readNumberFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    unsigned short n;
    inputFile >> n;
    inputFile.close();
    return n;
}

void writeAnswerToFile(const char *filename, unsigned long long a) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << a << endl;
    outputFile.close();
}

// This function is used to calculate the values
unsigned long long getSortedNumberCount(unsigned short n) {
    if (n == 1) {
        return 10;
    } else {
        // count[i][j] - Count of numbers having i digits where the front-most digit is j
        unsigned long long count[41][10];

        // One-digit number count = 1
        for (unsigned j = 0; j <= 9; ++j) {
            count[1][j] = 1;
        }
        // Set all "zeroes" also to 1
        for (unsigned i = 0; i <= n; ++i) {
            count[i][0] = 1;
        }

        // s(i, j) = sum[k=0..j](s(i-1,k))
        for (unsigned i = 2; i <= n; ++i) {
            for (unsigned j = 1; j <= 9; ++j) {
                count[i][j] = count[i - 1][j] + count[i][j - 1];
            }
        }

        unsigned long long sum = 0;
        for (unsigned j = 1; j <= 9; ++j) {
            sum += count[n][j];
        }

        return sum;
    }
}

int main() {
    unsigned short n = readNumberFromFile("labi.in");
    writeAnswerToFile("labi.out", getSortedNumberCount(n));
    return 0;
}
