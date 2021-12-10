#include <iostream>
#include <fstream>

using namespace std;

///////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 25: Burtu klucisi, 1 star
///////////////////////////////////////////////////////////////////

const unsigned NUMBER_OF_LETTERS = 26;

class LetterStorage {
private:
    unsigned letterCount[NUMBER_OF_LETTERS];

    void cleanLetterCount() {
        for (unsigned i = 0; i < NUMBER_OF_LETTERS; ++i) {
            letterCount[i] = 0;
        }
    }

    void addLetter(const char &l) {
        unsigned letterIndex = l - 'A';
        letterCount[letterIndex]++;
    }

public:
    LetterStorage(const string &letters) {
        cleanLetterCount();
        for (unsigned i = 0; i < letters.length(); ++i) {
            addLetter(letters[i]);
        }
    }

    bool containsAll(LetterStorage lettersToCheck) {
        bool letterShortage = false;
        unsigned i = 0;
        while (!letterShortage && i < NUMBER_OF_LETTERS) {
            letterShortage = this->letterCount[i] < lettersToCheck.letterCount[i];
            ++i;
        }
        return !letterShortage;
    }
};

void stripBadChars(string &s) {
    for (unsigned i = 0; i < s.length(); ++i) {
        if (s[i] < 'A' || s[i] > 'Z') {
            s.erase(i, 1);
        }
    }
}

void readLettersFromFile(const char *filename, string &rotaLetters, string &zigmarsLetters) {
    ifstream inputFile;
    inputFile.open(filename);
    getline(inputFile, rotaLetters);
    stripBadChars(rotaLetters);
    getline(inputFile, zigmarsLetters);
    stripBadChars(zigmarsLetters);
    inputFile.close();
}

void writeAnswerToFile(const char *filename, bool possible) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << (possible ? "VAR" : "NEVAR") << endl;
    outputFile.close();
}


int main() {
    string rotaLetters, zigmarsLetters;
    readLettersFromFile("burti.in", rotaLetters, zigmarsLetters);
    LetterStorage rota(rotaLetters);
    LetterStorage zigmars(zigmarsLetters);
    writeAnswerToFile("burti.out", rota.containsAll(zigmars));
    return 0;
}
