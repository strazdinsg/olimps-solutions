#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 26: Baseins, 4 stars
///////////////////////////////////////////////////////////////////////////////

const unsigned MAX_ROWS = 100;
const unsigned MAX_COLS = 100;
int rowCount, colCount;

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

    string toString() const {
        std::ostringstream sstream;
        sstream << "[" << row << ", " << column << "]";
        return sstream.str();
    }
};

typedef vector<Cell> Wall;
typedef vector<Cell> Water;
Wall wall;
Water water;

bool indexWithinBounds(int row, int column) {
    return row >= 0 && row < rowCount && column >= 0 && column < colCount;
}

bool isUnmarked(int row, int column) {
    return indexWithinBounds(row, column) && cellTypes[row][column] == UNMARKED;
}

void markCellAsWall(unsigned row, unsigned column) {
    wall.push_back(Cell((int) row, (int) column));
    cellTypes[row][column] = WALL;
}

void markCellAsWater(unsigned row, unsigned column) {
    water.push_back(Cell((int) row, (int) column));
    cellTypes[row][column] = WATER;
}

/**
 * The top and bottom row, as well as the left and right side can't hold any water - these cells will always be a wall
 */
void markSidesAsWall() {
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
        }
    }
}

// Start with the cells existing in the wall list, check if any of them has an adjacent cell that also
// belongs to the wall. If so, add it to the end of the wall (and process it later - add its adjacent
// cells, and so on)
void findAllWallCells() {
    for (unsigned i = 0; i < wall.size(); ++i) {
        const Cell &c = wall[i];
        cout << "Checking " << c.toString() << endl;
        unsigned height = heights[c.row][c.column];
        markUnknownHighCellAsWall(c.row - 1, c.column, height); // left
        markUnknownHighCellAsWall(c.row + 1, c.column, height); // right
        markUnknownHighCellAsWall(c.row, c.column - 1, height); // up
        markUnknownHighCellAsWall(c.row, c.column + 1, height); // down
    }
}

bool compareCells(Cell c1, Cell c2) {
    return heights[c1.row][c1.column] < heights[c2.row][c2.column]; // !!! 0;
}

void sortWallCellsByHeight() {
    sort(wall.begin(), wall.end(), compareCells);
}

void printWallHeights() {
    Wall::iterator it;
    for (it = wall.begin(); it != wall.end(); ++it) {
        cout << it->toString() << ": " << heights[it->row][it->column] << endl;
    }
    cout << "---" << endl;
}

/**
 * If the given cell is in unknown state and lower than the specified height, mark it as water
 * @param row Row of current cell
 * @param column Column of current cell
 */
void markUnknownLowCellAsWater(int row, int column, unsigned height) {
    if (indexWithinBounds(row, column)
        && cellTypes[row][column] == UNMARKED) {
        if (heights[row][column] < height) {
            markCellAsWater(row, column);
        }
    }
}

unsigned long long floodWaterFromCell(int row, int column, unsigned wallHeight) {
    if (isUnmarked(row, column)) {

        // TODO - is this clear in the right place?
        water.clear();

        markCellAsWater(row, column);
        // Explore all connected water cells
        for (unsigned i = 0; i < water.size(); ++i) {
            const Cell &c = water[i];
            cout << "Water check " << c.toString() << endl;
            markUnknownLowCellAsWater(c.row - 1, c.column, wallHeight); // left
            markUnknownLowCellAsWater(c.row + 1, c.column, wallHeight); // right
            markUnknownLowCellAsWater(c.row, c.column - 1, wallHeight); // up
            markUnknownLowCellAsWater(c.row, c.column + 1, wallHeight); // down
        }
        // Now calculate total water amount in this pool
        unsigned long long waterAmount = 0;
        for (unsigned i = 0; i < water.size(); ++i) {
            waterAmount += wallHeight - heights[water[i].row][water[i].column];
        }
        // TODO - mark all adjacent unmarked cells as wall, re-sort the wall cell queue?
        return waterAmount;
    } else {
        return 0;
    }
}

/**
 * Sort all wall cells by height. Then iterate through them - from the lowest cell to highest.
 * If there is an unmarked cell nearby, it must be water, flood water from that cell and
 * calculate the total amount of water in the current "pool".
 * Explore all water pools touching the current wall.
 * Also add all water cells to the water queue.
 * @return Total amount of water in all pools touching the current wall
 * (NB: only those pools not already marked by previous iterations!)
 */
unsigned long long floodWater() {
    unsigned long long waterAmount = 0;
    sortWallCellsByHeight();
    Wall::iterator it;
    for (it = wall.begin(); it != wall.end(); ++it) {
        unsigned wallHeight = heights[it->row][it->column];
        waterAmount += floodWaterFromCell(it->row - 1, it->column, wallHeight);
        waterAmount += floodWaterFromCell(it->row + 1, it->column, wallHeight);
        waterAmount += floodWaterFromCell(it->row, it->column - 1, wallHeight);
        waterAmount += floodWaterFromCell(it->row, it->column + 1, wallHeight);
    }
    return waterAmount;
}

/**
 * We have processed all the water in the previous round. Then it must be that all unmarked
 * cells next to current water pool are walls again
 */
void markWallNextToWater() {
    wall.clear();

    Water::iterator it;
    for (it = water.begin(); it != water.end(); ++it) {
        markUnknownHighCellAsWall(it->row - 1, it->column, 0);
        markUnknownHighCellAsWall(it->row + 1, it->column, 0);
        markUnknownHighCellAsWall(it->row, it->column - 1, 0);
        markUnknownHighCellAsWall(it->row, it->column + 1, 0);
    }
}

void printArea() {
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < colCount; ++column) {
            char c = (cellTypes[row][column] == WALL ? 'X' : (cellTypes[row][column] == WATER ? '-' : ' '));
            cout << c;
        }
        cout << endl;
    }
}

unsigned long long calculateWaterAmount() {
    unsigned long long waterAmount = 0;
    markSidesAsWall();
    do {
        findAllWallCells();
        printArea();
        waterAmount += floodWater();
        printArea();
        markWallNextToWater();
    } while (!wall.empty());
    return waterAmount;
}


int main() {
    readAreaFromFile("baseins.in");
    writeAnswerToFile("baseins.out", calculateWaterAmount());
    return 0;
}
