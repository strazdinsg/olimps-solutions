#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// Solution for "LIO Olimps" Problem Nr 38: Taka, 2 stars
///////////////////////////////////////////////////////////////////////////////

ifstream inputFile;

bool openInputFile(const char *filename) {
    inputFile.open(filename);
    return inputFile.is_open();
}

void writeAnswerToFile(const char *filename, unsigned long long stepCount) {
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << stepCount << endl;
    outputFile.close();
}

// Command types
const unsigned char NONE = 'N';
const unsigned char TURN_LEFT = 'K';
const unsigned char TURN_RIGHT = 'L';
const unsigned char MOVE_FORWARD = 'S';
const unsigned char END = 'V';

class Command {
    unsigned char type;
    int stepCount;
public:
    Command(unsigned char commandType, int stepCount) : type(commandType), stepCount(stepCount) {}
    Command() : type(NONE), stepCount(0) {}

    bool isEnd() const {
        return type == END;
    }

    unsigned char getType() const {
        return type;
    }

    int getStepCount() const {
        return stepCount;
    }
};

void discardCharsUntilNextLine() {
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Command readNextCommandFromFile() {
    unsigned char commandTypeChar = inputFile.get();
    int stepCount = 0;
    if (commandTypeChar == 'S') {
        inputFile >> stepCount;
    }
    discardCharsUntilNextLine();
    return Command(commandTypeChar, stepCount);
}

// THe possible headings
const unsigned NORTH = 0;
const unsigned EAST = 1;
const unsigned SOUTH = 2;
const unsigned WEST = 3;

class Gnome {
    int x;
    int y;
    unsigned heading;
public:
    Gnome() : x(0), y(0), heading(NORTH) {}

    void act(Command command) {
        switch (command.getType()) {
            case TURN_RIGHT:
                heading = (heading + 1) % 4;
                break;
            case TURN_LEFT:
                heading = (heading + 3) % 4;
                break;
            case MOVE_FORWARD:
                switch (heading) {
                    case NORTH:
                        y -= command.getStepCount();
                        break;
                    case EAST:
                        x += command.getStepCount();
                        break;
                    case SOUTH:
                        y += command.getStepCount();
                        break;
                    case WEST:
                        x -= command.getStepCount();
                        break;
                }
            case NONE:
            case END:
            default:
                break;
        }
    }

    /**
     * The shortest distance is to go x to lef/right and y steps up/down
     * @return
     */
    unsigned getReturnStepCount() const {
        return abs(x) + abs(y);
    }
};

int main() {
    if (openInputFile("taka.in")) {
        Command command;
        Gnome gnome;
        while (!command.isEnd()) {
            command = readNextCommandFromFile();
            gnome.act(command);
        }
        writeAnswerToFile("taka.out", gnome.getReturnStepCount());
    } else {
        return -1;
    }
}
