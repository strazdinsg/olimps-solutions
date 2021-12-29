#include <iostream>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 26: Baseins, 4 stars
///////////////////////////////////////////////////////////////////////////////

const unsigned MAX_ROWS = 100;
const unsigned MAX_COLS = 100;
unsigned rowCount, colCount;

// Cell heights, from input file
unsigned heights[MAX_ROWS][MAX_COLS];

// Cell types, will be updated during the process
enum CELL_TYPE {
    UNMARKED, WALL, WATER
};
CELL_TYPE cellTypes[MAX_ROWS][MAX_COLS];


void readAreaFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    inputFile >> rowCount >> colCount;
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            inputFile >> heights[i][j];
        }
    }
}

void writeAnswerToFile(const char *filename, unsigned long long waterAmount) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << waterAmount << endl;
    outputFile.close();
}

struct Cell {
    int row;
    int column;
private:
    Cell() : row(-1), column(-1) {}

public:
    Cell(int r, int c) : row(r), column(c) {}

    bool isValid() const {
        return row >= 0 && column >= 0;
    }

    static Cell createInvalid() {
        return Cell();
    }

    string toString() const {
        std::ostringstream sstream;
        sstream << "[" << row << ", " << column << "]";
        return sstream.str();
    }
};

typedef list<Cell> Wall;
Wall wall;

// To speed up search of the next water-search starting point, we cache
// the first encountered cachedUnmarkedCell cell which is adjacent to the wall
Cell cachedUnmarkedCell = Cell::createInvalid();


bool indexWithinBounds(int row, int column) {
    return row >= 0 && row < rowCount && column >= 0 && column < colCount;
}

bool isUnmarked(int row, int column) {
    return indexWithinBounds(row, column) && cellTypes[row][column] == UNMARKED;
}

/**
 * Find first unmarked cell next to wall
 * @return
 */
Cell getUnmarkedCellNextToWall() {
    if (cachedUnmarkedCell.isValid()) {
        return cachedUnmarkedCell;
    } else {
        Wall::iterator it;
        for (it = wall.begin(); it != wall.end(); ++it) {
            if (isUnmarked(it->row - 1, it->column)) {
                return Cell(it->row - 1, it->column);
            }
            if (isUnmarked(it->row + 1, it->column)) {
                return Cell(it->row + 1, it->column);
            }
            if (isUnmarked(it->row, it->column - 1)) {
                return Cell(it->row, it->column - 1);
            }
            if (isUnmarked(it->row, it->column + 1)) {
                return Cell(it->row, it->column + 1);
            }
        }
    }
}

/**
 * Fill water starting from the given cell. Return the total amount of water filled in this pool
 * @param cell
 * @return
 */
unsigned long long int fillWaterStartingAt(Cell cell) {
    // TODO

    // !!!
    cellTypes[cell.row][cell.column] = WATER;

    cachedUnmarkedCell = Cell::createInvalid(); // Invalidate the cache
    return 0;
}

Cell findNextUnmarkedCell() {
    // TODO
    return Cell::createInvalid();
}

void markCellAsWall(unsigned row, unsigned column) {
    wall.push_back(Cell((int) row, (int) column));
    cellTypes[row][column] = WALL;
}

/**
 * The top and bottom row, as well as the left and right side can't hold any water - these cells will always be a wall
 */
void addSidesToWall() {
    for (int row = 0; row < rowCount; ++row) {
        markCellAsWall(row, 0);
        markCellAsWall(row, colCount - 1);
    }
    for (int column = 1; column < colCount - 1; ++column) {
        markCellAsWall(0, column);
        markCellAsWall(rowCount - 1, column);
    }
}

/**
 * If the given cell is in unknown state and at least as high as specified, mark it as a wall
 * @param row Row of current cell
 * @param column Column of current cell
 */
void markUnknownHighCellAsWall(int row, int column, unsigned height) {
    if (indexWithinBounds(row, column)
        && cellTypes[row][column] == UNMARKED) {
        if (heights[row][column] >= height) {
            markCellAsWall(row, column);
        } else if (!cachedUnmarkedCell.isValid()) {
            // We will start flooding water in this cell, cache it for speed-up
            cachedUnmarkedCell = Cell(row, column);
        }
    }
}

// Start with the cells existing in the wall list, check if any of them has an adjacent cell that also
// belongs to the wall. If so, add it to the end of the wall (and process it later - add its adjacent
// cells, and so on)
void findNextWall() {
    Wall::iterator it;
    for (it = wall.begin(); it != wall.end(); ++it) {
        cout << "Checking " << it->toString() << endl;
        unsigned height = heights[it->row][it->column];
        markUnknownHighCellAsWall(it->row - 1, it->column, height); // left
        markUnknownHighCellAsWall(it->row + 1, it->column, height); // right
        markUnknownHighCellAsWall(it->row, it->column - 1, height); // up
        markUnknownHighCellAsWall(it->row, it->column + 1, height); // down
    }
}

unsigned long long calculateWaterAmount() {
    unsigned long long waterAmount = 0;
    addSidesToWall();
    do {
        findNextWall();
        Cell waterCell = getUnmarkedCellNextToWall();
        while (waterCell.isValid()) {
            waterAmount += fillWaterStartingAt(waterCell);
            waterCell = getUnmarkedCellNextToWall();
        }
        Cell nextWallCell = findNextUnmarkedCell();
        wall.clear();
        if (nextWallCell.isValid()) {
            wall.push_back(nextWallCell);
        }
    } while (!wall.empty());
    return waterAmount;
}


int main() {
    readAreaFromFile("baseins.in");
    writeAnswerToFile("baseins.out", calculateWaterAmount());
    return 0;
}
