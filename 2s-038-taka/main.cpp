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

const unsigned MAX_DISTANCE_IN_STEP = 1000;

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

    unsigned getVerticalCommandCount(bool onlyVertical) const {
        unsigned stepCount;
        unsigned verticalDistance = abs(y);
        // How many full 1000-step commands?
        stepCount = verticalDistance / MAX_DISTANCE_IN_STEP;
        if ((verticalDistance % MAX_DISTANCE_IN_STEP) > 0) {
            // Some more steps left after the thousand
            stepCount++;
        }

        if (onlyVertical) {
            // Need to turn in the right direction
            if ((y < 0 && heading == NORTH) || (y > 0 && heading == SOUTH)) {
                // Must turn twice to get back in the right direction
                stepCount += 2;
            } else if (heading == WEST || heading == EAST) {
                // When sideways, must turn once anyway
                stepCount++;
            }
        }
        return stepCount;
    }

    unsigned getHorizontalCommandCount(bool onlyHorizontal) const {
        unsigned stepCount;
        unsigned horizontalDistance = abs(x);
        // How many full 1000-step commands?
        stepCount = horizontalDistance / MAX_DISTANCE_IN_STEP;
        if ((horizontalDistance % MAX_DISTANCE_IN_STEP) > 0) {
            // Some more steps left after the thousand
            stepCount++;
        }

        if (onlyHorizontal) {
            // Need to turn in the right direction
            if ((x < 0 && heading == WEST) || (x > 0 && heading == EAST)) {
                // Moved North, must turn twice to go south now
                stepCount += 2;
            } else if (heading == NORTH || heading == SOUTH) {
                // When facing north or south, must turn once anyway
                stepCount++;
            }
        }
        return stepCount;
    }

    bool headingAlongPerimeter() const {
        return x > 0 && heading == WEST
               || x < 0 && heading == EAST
               || y > 0 && heading == NORTH
               || y < 0 && heading == SOUTH;
    }

/**
     * How many times the gnome must turn to start traveling back along the perimeter
     * @return
     */
    unsigned getTurnCommandCount() const {
        return headingAlongPerimeter() ? 1 : 2;
    }

    unsigned getMinCommandCount() const {
        if (x == 0 && y == 0) {
            return 0;
        } else if (x == 0) {
            return getVerticalCommandCount(true);
        } else if (y == 0) {
            return getHorizontalCommandCount(true);
        } else {
            return getHorizontalCommandCount(false) + getVerticalCommandCount(false)
                   + getTurnCommandCount();
        }
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
        writeAnswerToFile("taka.out", gnome.getMinCommandCount());
    } else {
        return -1;
    }
}
