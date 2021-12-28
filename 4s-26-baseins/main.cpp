#include <iostream>
#include <fstream>
#include <list>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 26: Baseins, 4 stars
///////////////////////////////////////////////////////////////////////////////

void readAreaFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    // TODO
}

struct Cell {
    int row;
    int column;
private:
    Cell() : row(-1), column(-1) {}

public:
    bool isValid() const {
        return row >= 0 && column >= 0;
    }

    static Cell createInvalid() {
        Cell c;
        return c;
    }
};

void writeAnswerToFile(const char *filename, unsigned long long waterAmount) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << waterAmount << endl;
    outputFile.close();
}

void markWallContour(list<Cell> &contour) {
    // TODO
}

Cell getAdjacentWaterCell(list<Cell> &contour) {
    // TODO
    return Cell::createInvalid();
}

unsigned long long int fillWaterStartingAt(Cell cell) {
    // TODO
    return 0;
}

Cell findNextUnmarkedCell() {
    // TODO
    return Cell::createInvalid();
}

void addSidesToQueue() {
    // TODO - add all outside cells as "need to be inspected as part of the initial contour"
}

unsigned long long calculateWaterAmount() {
    unsigned long long waterAmount = 0;
    addSidesToQueue();
    list<Cell> wallContour;
    do {
        markWallContour(wallContour);
        Cell waterCell = getAdjacentWaterCell(wallContour);
        while (waterCell.isValid()) {
            waterAmount += fillWaterStartingAt(waterCell);
        }
        Cell nextContourCell = findNextUnmarkedCell();
        if (nextContourCell.isValid()) {
            wallContour.push_back(nextContourCell);
        }
    } while (!wallContour.empty());
    return waterAmount;
}


int main() {
    readAreaFromFile("baseins.in");
    writeAnswerToFile("baseins.out", calculateWaterAmount());
    return 0;
}
