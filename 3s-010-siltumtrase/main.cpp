#include <iostream>
#include <fstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 3: Siltumtrase, 3 stars
///////////////////////////////////////////////////////////////////////////////

const unsigned short MAX_ROW_COUNT = 10;
const unsigned short MAX_COL_COUNT = 10;

// Pipe and obstacle types
const unsigned short EMPTY = 0;
const unsigned short PIPE_TOP_RIGHT = 1;
const unsigned short PIPE_LEFT_BOTTOM = 2;
const unsigned short PIPE_HORIZONTAL = 3;
const unsigned short PIPE_VERTICAL = 4;
// const unsigned short OBSTACLE = 5; // This is not really used, for documentation only


class Area {
private:
    unsigned rows, columns;
    unsigned cells[MAX_ROW_COUNT + 1][MAX_COL_COUNT + 1];

    void initCells() {
        // Set all to zero first
        for (unsigned i = 0; i <= rows; ++i) {
            for (unsigned j = 0; j <= columns; ++j) {
                cells[i][j] = EMPTY;
            }
        }
        cells[0][0] = PIPE_VERTICAL; // Initial connection to cell(1, 1) from the top
    }

    bool allowsIncomingFromTop(unsigned row, unsigned column) const {
        unsigned c = cells[row][column];
        return c == EMPTY || c == PIPE_VERTICAL || c == PIPE_TOP_RIGHT;
    }

    bool allowsOutgoingDown(unsigned row, unsigned column) const {
        unsigned c = cells[row][column];
        return c == EMPTY || c == PIPE_VERTICAL || c == PIPE_LEFT_BOTTOM;
    }

    bool allowsIncomingFromLeft(unsigned row, unsigned column) const {
        unsigned c = cells[row][column];
        return c == EMPTY || c == PIPE_HORIZONTAL || c == PIPE_LEFT_BOTTOM;
    }

    bool allowsOutgoingRight(unsigned row, unsigned column) const {
        unsigned c = cells[row][column];
        return c == EMPTY || c == PIPE_HORIZONTAL || c == PIPE_TOP_RIGHT;
    }

    unsigned canFlowFromTop(unsigned row, unsigned column) const {
        return allowsIncomingFromTop(row, column) && allowsOutgoingDown(row - 1, column) ? 1 : 0;
    }

    unsigned canFlowFromLeft(unsigned row, unsigned column) const {
        return allowsIncomingFromLeft(row, column) && allowsOutgoingRight(row, column - 1) ? 1 : 0;
    }

public:
    Area(unsigned rows, unsigned columns) {
        this->rows = rows;
        this->columns = columns;
        initCells();
    }

    void setCellContent(unsigned row, unsigned column, unsigned content) {
        cells[row][column] = content;
    }


    unsigned long long getPipePathCount(Area area) const {
        unsigned long long pathCount[rows + 1][columns + 1];
        // Set all to zero first
        for (unsigned row = 0; row <= rows; ++row) {
            for (unsigned column = 0; column <= columns; ++column) {
                pathCount[row][column] = 0;
            }
        }
        // The only possible flow currently is at cell (0, 1), going down
        pathCount[0][1] = 1;

        // Path count p(i, j) for cell (i, j) is sum of path count for the cell above it and left from it,
        // if the flow can come from top and/or left
        for (unsigned row = 1; row <= rows; ++row) {
            for (unsigned column = 1; column <= columns; ++column) {
                unsigned pathsFromTop = pathCount[row - 1][column] * canFlowFromTop(row, column);
                unsigned pathsFromLeft = pathCount[row][column - 1] * canFlowFromLeft(row, column);
                pathCount[row][column] = pathsFromTop + pathsFromLeft;
            }
        }

        return pathCount[rows][columns];
    }
};

Area readAreaFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    unsigned m, n;
    inputFile >> n >> m;
    Area area(m, n);
    unsigned cellContent;
    for (unsigned row = 1; row <= m; ++row) {
        for (unsigned column = 1; column <= n; ++column) {
            inputFile >> cellContent;
            area.setCellContent(row, column, cellContent);
        }
    }
    inputFile.close();
    return area;
}

void writeAnswerToFile(const char *filename, unsigned long long pathCount) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << pathCount << endl;
    outputFile.close();
}

int main() {
    Area area = readAreaFromFile("trase.in");
    writeAnswerToFile("trase.out", area.getPipePathCount(area));
    return 0;
}
