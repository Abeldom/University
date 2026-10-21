#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

const int MAX_COLS = 50;
const int MIN_SIZE = 3;   // smallest map side, so there is always at least 1 bomb
const int MAX_ROWS = 50;

// Console colors
const int COLOR_FRAME  = 3;   // cyan: row/column numbers
const int COLOR_NUMBER = 10;  // green: revealed numbers
const int COLOR_BOMB   = 14;  // yellow: bombs
const int COLOR_TEXT   = 15;  // white: everything else

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Reads a whole number between min and max. Asks again on letters or out-of-range values.
int readNumber(const char *prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            return value;
        }
        if (cin.eof()) {
            exit(0);  // input closed (e.g. Ctrl+Z), nothing more to read
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a number from " << min << " to " << max << "." << endl;
    }
}

void printColumnNumbers(int cols) {
    cout << " ";
    for (int col = 0; col < cols; col++) {
        if (col > 10) {
            cout << " " << col;
        } else {
            cout << "  " << col;
        }
    }
}

// Prints the board with row numbers on both sides and column numbers above and below.
void printMap(char view[][MAX_COLS], int rows, int cols) {
    setColor(COLOR_FRAME);
    printColumnNumbers(cols);
    cout << endl;

    for (int row = 0; row < rows; row++) {
        if (row >= 10) {
            cout << row;
        } else {
            cout << " " << row;
        }

        for (int col = 0; col < cols; col++) {
            char cell = view[row][col];
            if (cell == '*') {
                setColor(COLOR_BOMB);
            } else if (cell >= '0' && cell < '9') {
                setColor(COLOR_NUMBER);
            } else {
                setColor(COLOR_TEXT);
            }
            cout << " " << cell << " ";
        }

        setColor(COLOR_FRAME);
        cout << row << endl;
    }

    printColumnNumbers(cols);
    setColor(COLOR_TEXT);
    cout << endl << endl;
}

// Counts the bombs in the 3x3 area around (row, col), not counting the cell itself
// (the cell is assumed to be a bomb). Every non-bomb cell in the area is added to safeCells.
int countBombsAround(char board[][MAX_COLS], int row, int col, int rows, int cols, int &safeCells) {
    int rowFrom = row - 1;
    int rowTo   = row + 1;
    int colFrom = col - 1;
    int colTo   = col + 1;
    if (rowFrom < 0)       rowFrom = 0;
    if (rowTo > rows - 1)  rowTo = rows - 1;
    if (colFrom < 0)       colFrom = 0;
    if (colTo > cols - 1)  colTo = cols - 1;

    int bombs = 0;
    for (int r = rowFrom; r <= rowTo; r++) {
        for (int c = colFrom; c <= colTo; c++) {
            if (board[r][c] == '*') {
                bombs++;
            } else {
                safeCells++;
            }
        }
    }

    return bombs - 1;
}

// Checks every cell in the 3x3 area around (row, col).
// Returns 8 if any of them is surrounded by too many bombs, otherwise 0.
int checkSurroundings(char board[][MAX_COLS], int row, int col, int rows, int cols, int &safeCells) {
    int rowFrom = row - 1;
    int rowTo   = row + 1;
    int colFrom = col - 1;
    int colTo   = col + 1;
    if (rowFrom < 0)       rowFrom = 0;
    if (rowTo > rows - 1)  rowTo = rows - 1;
    if (colFrom < 0)       colFrom = 0;
    if (colTo > cols - 1)  colTo = cols - 1;

    for (int r = rowFrom; r <= rowTo; r++) {
        for (int c = colFrom; c <= colTo; c++) {
            int bombsAround = countBombsAround(board, r, c, rows, cols, safeCells);
            if (board[r][c] == '*') {
                if (bombsAround > 7 || safeCells == 0) {
                    return 8;
                }
            } else if (board[r][c] == '0') {
                if (bombsAround + 1 > 7) {
                    return 8;
                }
            }
            safeCells = 0;
        }
    }

    return 0;
}

// Reveals the neighbours of an empty ('0') cell. Neighbouring empty cells are opened
// recursively. Returns how many cells were newly revealed.
int revealArea(char view[][MAX_COLS], char board[][MAX_COLS], int row, int col, int rows, int cols) {
    int rowFrom = row - 1;
    int rowTo   = row + 1;
    int colFrom = col - 1;
    int colTo   = col + 1;
    if (rowFrom < 0)       rowFrom = 0;
    if (rowTo > rows - 1)  rowTo = rows - 1;
    if (colFrom < 0)       colFrom = 0;
    if (colTo > cols - 1)  colTo = cols - 1;

    int revealed = 0;
    for (int r = rowFrom; r <= rowTo; r++) {
        for (int c = colFrom; c <= colTo; c++) {
            if (r == row && c == col) {
                // skip the cell itself
            } else if (board[r][c] == '0' && view[r][c] != '0') {
                view[r][c] = '0';
                revealed = revealed + 1 + revealArea(view, board, r, c, rows, cols);
            } else if (view[r][c] != board[r][c]) {
                view[r][c] = board[r][c];
                revealed++;
            }
        }
    }
    return revealed;
}


int main() {
    // --- Game settings ---
    int mode;
    cout << "Difficulty:" << endl;
    cout << "  1 - easy" << endl;
    cout << "  2 - medium" << endl;
    cout << "  3 - hard" << endl;
    mode = readNumber("Choose (1-3): ", 1, 3);

    int rows, cols;
    cout << "Map size:" << endl;
    rows = readNumber("  rows: ", MIN_SIZE, MAX_ROWS);
    cols = readNumber("  columns: ", MIN_SIZE, MAX_COLS);

    int bombCount;
    if (mode == 1) {
        bombCount = rows * cols * 20 / 100;
    } else if (mode == 2) {
        bombCount = rows * cols * 30 / 100;
    } else {
        bombCount = rows * cols * 40 / 100;
    }

    // --- Empty boards ---
    char view[rows][MAX_COLS];   // what the player sees
    char board[rows][MAX_COLS];  // the real board
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            view[r][c] = '?';
            board[r][c] = '0';
        }
    }

    system("cls");
    cout << bombCount << " bombs" << endl;
    printMap(view, rows, cols);
    cout << endl;

    // --- Place bombs at random ---
    srand(time(NULL));
    int cellNumber;
    int bombs[bombCount][2];
    int row, col;
    for (int i = 0; i < bombCount; i++) {
        cellNumber = rand() % (rows * cols) + 1;
        if (cellNumber % cols == 0) {
            col = cols - 1;
            row = cellNumber / cols - 1;
        } else {
            row = cellNumber / cols;
            col = cellNumber % cols - 1;
        }
        if (board[row][col] == '*') {
            i--;  // already a bomb here, try again
        } else {
            board[row][col] = '*';
            bombs[i][0] = row;
            bombs[i][1] = col;
        }
    }

    // --- Move bombs that are packed too tightly ---
    bool takeNextBomb = true;
    int safeCells = 0;
    for (int i = 0; i < bombCount; i++) {
        if (takeNextBomb) {
            row = bombs[i][0];
            col = bombs[i][1];
        }
        safeCells = 0;
        if (countBombsAround(board, row, col, rows, cols, safeCells) > 7 ||
            checkSurroundings(board, row, col, rows, cols, safeCells) > 7) {

            // bad spot: move this bomb to a new random cell, then check it again
            takeNextBomb = false;
            board[row][col] = '0';
            do {
                cellNumber = rand() % (rows * cols) + 1;
                if (cellNumber % cols == 0) {
                    col = cols - 1;
                    row = cellNumber / cols - 1;
                } else {
                    col = cellNumber % cols - 1;
                    row = cellNumber / cols;
                }
            } while (board[row][col] == '*');
            board[row][col] = '*';
            i--;
        } else {
            takeNextBomb = true;
            bombs[i][0] = row;
            bombs[i][1] = col;
        }
    }

    // --- Number every cell next to a bomb ---
    int rowFrom, rowTo, colFrom, colTo;
    for (int i = 0; i < bombCount; i++) {
        row = bombs[i][0];
        col = bombs[i][1];

        rowFrom = row - 1;
        rowTo   = row + 1;
        colFrom = col - 1;
        colTo   = col + 1;
        if (rowFrom < 0)       rowFrom = 0;
        if (rowTo > rows - 1)  rowTo = rows - 1;
        if (colFrom < 0)       colFrom = 0;
        if (colTo > cols - 1)  colTo = cols - 1;

        for (int r = rowFrom; r <= rowTo; r++) {
            for (int c = colFrom; c <= colTo; c++) {
                if (board[r][c] != '*') {
                    board[r][c] = board[r][c] + 1;
                }
            }
        }
    }

    // printMap(board, rows, cols);  // debug: show the real board

    // --- Game loop ---
    int pickRow, pickCol;
    int revealed = 0;
    int safeTotal = rows * cols - bombCount;
    int totalCells = rows * cols;
    do {
        pickRow = readNumber("Row: ", 0, rows - 1);
        pickCol = readNumber("Column: ", 0, cols - 1);
        system("cls");

        if (board[pickRow][pickCol] == '*') {
            // hit a bomb: show all of them
            for (int i = 0; i < bombCount; i++) {
                view[bombs[i][0]][bombs[i][1]] = '*';
            }
        } else {
            if (board[pickRow][pickCol] == '0') {
                if (view[pickRow][pickCol] == '?') {
                    view[pickRow][pickCol] = '0';
                    revealed++;
                }
                revealed = revealed + revealArea(view, board, pickRow, pickCol, rows, cols);
            } else if (view[pickRow][pickCol] == '?') {
                view[pickRow][pickCol] = board[pickRow][pickCol];
                revealed++;
            }

            printMap(view, rows, cols);
            if (revealed != safeTotal) {
                cout << "Bombs: " << bombCount << " (on " << totalCells << " cells)" << endl;
                cout << "Safe cells revealed: " << revealed << endl;
                cout << "Safe cells left:     " << safeTotal - revealed << endl;
                cout << endl;
            }
        }
    } while (board[pickRow][pickCol] != '*' && revealed != safeTotal);

    if (board[pickRow][pickCol] == '*') {
        printMap(view, rows, cols);
        cout << "BOOM! You hit a bomb. Game over." << endl;
    } else {
        cout << "You won! All safe cells are revealed." << endl;
    }

    system("pause");  // keep the window open when started by double-click
    return 0;
}
