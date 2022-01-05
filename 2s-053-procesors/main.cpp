#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

//////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 53: Procesors
//////////////////////////////////////////////////////////////

const int MAX_X = 101;
const int MAX_Y = 101;
int circuit[MAX_X][MAX_Y];
int X, Y, N;
int xa, ya, xb, yb;

const int UNVISITED = -1;
const int IMPOSSIBLE = -2;

struct Coords {
    int x, y;
    Coords(int x, int y) : x(x), y(y) {}
};

queue<Coords> bfsQueue;

void readCircuitFromFile(const char *filename) {
    ifstream inputFile;
    inputFile.open(filename);
    inputFile >> X >> Y >> N;
    int x1, y1, x2, y2;
    for (int i = 0; i < N; ++i) {
        inputFile >> x1 >> y1 >> x2 >> y2;
        circuit[x1][y1] = IMPOSSIBLE;
        circuit[x2][y2] = IMPOSSIBLE;
    }
    inputFile >> xa >> ya >> xb >> yb;
    inputFile.close();
}

void writeAnswerToFile(const char *filename, const string &answer) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << answer;
    outputFile.close();
}

void resetCircuitVertices() {
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            circuit[i][j] = UNVISITED;
        }
    }
}

void enqueueVertex(int x, int y, int stepCount) {
    if (x >= 0 && x <= X && y >= 0 && y <= Y
        && circuit[x][y] == UNVISITED) {
        bfsQueue.push(Coords(x, y));
        circuit[x][y] = stepCount;
    }
}

int runBreadthFirstSearchFrom(int x, int y) {
    bfsQueue.push(Coords(x, y));
    circuit[x][y] = 0;
    int stepCount;
    Coords c(x, y);
    while (!bfsQueue.empty() && !(c.x == xb && c.y == yb)) {
        c = bfsQueue.front();
        bfsQueue.pop();
        stepCount = circuit[c.x][c.y];
        enqueueVertex(c.x - 1, c.y, stepCount + 1);
        enqueueVertex(c.x + 1, c.y, stepCount + 1);
        enqueueVertex(c.x, c.y - 1, stepCount + 1);
        enqueueVertex(c.x, c.y + 1, stepCount + 1);
    }
    return (c.x == xb && c.y == yb) ? stepCount : IMPOSSIBLE;
}

string intToString(int u) {
    stringstream ss;
    ss << u;
    return ss.str();
}

string getConnectionLength() {
    int stepCount = runBreadthFirstSearchFrom(xa, ya);
    return stepCount >= 0 ? intToString(stepCount) : "NEVAR";
}

int main() {
    resetCircuitVertices();
    readCircuitFromFile("proc.in");
    writeAnswerToFile("proc.out", getConnectionLength());
    return 0;
}

