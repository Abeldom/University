// Minesweeper - clickable window version.
// The game logic (countBombsAround, checkSurroundings, revealArea, bomb placement,
// numbering and the click handling) is the same as Minesweeper_new.cpp.
// Only the console input/output was replaced by a Win32 window.
//
// Build:  g++ MinesweeperGUI.cpp -o MinesweeperGUI.exe -mwindows -static
//
// Controls: left click = pick a cell, menu "Game" = new game / difficulty / size (also F2 = new game)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

const int MAX_COLS = 50;
const int MAX_ROWS = 50;

// ---------------------------------------------------------------- game state
int rows = 9, cols = 9;
int mode = 1;                       // 1 easy, 2 medium, 3 hard
int bombCount = 0;
int revealed = 0;
int safeTotal = 0;
bool gameOver = false;
bool won = false;

char view[MAX_ROWS][MAX_COLS];      // what the player sees
char board[MAX_ROWS][MAX_COLS];     // the real board
int bombs[MAX_ROWS * MAX_COLS][2];
bool flagged[MAX_ROWS][MAX_COLS];   // flags are only a marker for the player, they do not touch the game logic
int flagCount = 0;

// ---------------------------------------------------------------- game logic
// (unchanged from Minesweeper_new.cpp)

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

// Sets up a new game: empty boards, random bombs, moves packed bombs, numbers the cells.
void newGame() {
    if (mode == 1) {
        bombCount = rows * cols * 20 / 100;
    } else if (mode == 2) {
        bombCount = rows * cols * 30 / 100;
    } else {
        bombCount = rows * cols * 40 / 100;
    }

    // --- Empty boards ---
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            view[r][c] = '?';
            board[r][c] = '0';
            flagged[r][c] = false;
        }
    }

    // --- Place bombs at random ---
    int cellNumber;
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

    revealed = 0;
    flagCount = 0;
    safeTotal = rows * cols - bombCount;
    gameOver = false;
    won = false;
}

// One turn of the game loop: the player picks (pickRow, pickCol).
void pickCell(int pickRow, int pickCol) {
    if (board[pickRow][pickCol] == '*') {
        // hit a bomb: show all of them
        for (int i = 0; i < bombCount; i++) {
            view[bombs[i][0]][bombs[i][1]] = '*';
        }
        gameOver = true;
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

        if (revealed == safeTotal) {
            gameOver = true;
            won = true;
        }
    }
}

// ---------------------------------------------------------------- window / layout
const int CELL = 30;            // size of one cell in pixels
const int MARGIN = 10;
const int STATUS_H = 82;        // status text area above the board

const COLORREF COLOR_BG      = RGB(24, 26, 31);
const COLORREF COLOR_HIDDEN  = RGB(70, 76, 90);
const COLORREF COLOR_OPEN    = RGB(38, 42, 52);
const COLORREF COLOR_FRAME   = RGB(0, 170, 190);     // cyan
const COLORREF COLOR_NUMBER  = RGB(80, 230, 110);    // green
const COLORREF COLOR_BOMB    = RGB(255, 210, 40);    // yellow
const COLORREF COLOR_TEXT    = RGB(235, 235, 235);
const COLORREF COLOR_LOSE    = RGB(255, 90, 90);

enum {
    ID_NEW = 100,
    ID_EASY, ID_MEDIUM, ID_HARD,
    ID_SIZE_9, ID_SIZE_12, ID_SIZE_16, ID_SIZE_20,
    ID_EXIT
};

HWND hMainWnd;
HFONT hFontCell, hFontSmall, hFontBig;

void resizeWindowToBoard() {
    int w = MARGIN * 2 + cols * CELL;
    int h = STATUS_H + MARGIN + rows * CELL + MARGIN;
    if (w < 340) w = 340;
    RECT rc = {0, 0, w, h};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, TRUE);
    SetWindowPos(hMainWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOMOVE | SWP_NOZORDER);
}

void updateMenuChecks() {
    HMENU menu = GetMenu(hMainWnd);
    CheckMenuRadioItem(menu, ID_EASY, ID_HARD, ID_EASY + mode - 1, MF_BYCOMMAND);
    int sizeId = ID_SIZE_9;
    if (rows == 12) sizeId = ID_SIZE_12;
    else if (rows == 16) sizeId = ID_SIZE_16;
    else if (rows == 20) sizeId = ID_SIZE_20;
    CheckMenuRadioItem(menu, ID_SIZE_9, ID_SIZE_20, sizeId, MF_BYCOMMAND);
}

void startNewGame() {
    newGame();
    resizeWindowToBoard();
    updateMenuChecks();
    InvalidateRect(hMainWnd, NULL, TRUE);
}

void drawText(HDC dc, const char *text, int x, int y, COLORREF color, HFONT font) {
    SelectObject(dc, font);
    SetTextColor(dc, color);
    TextOutA(dc, x, y, text, (int)strlen(text));
}

void paintGame(HDC dc, int width, int height) {
    HBRUSH bg = CreateSolidBrush(COLOR_BG);
    RECT all = {0, 0, width, height};
    FillRect(dc, &all, bg);
    DeleteObject(bg);
    SetBkMode(dc, TRANSPARENT);

    // status text
    char line[200];
    if (gameOver && won) {
        drawText(dc, "You won! All cells found.", MARGIN, 6, COLOR_NUMBER, hFontBig);
    } else if (gameOver) {
        drawText(dc, "BOOM! You hit a bomb.", MARGIN, 6, COLOR_LOSE, hFontBig);
    } else {
        sprintf(line, "Bombs: %d   Flags: %d", bombCount, flagCount);
        drawText(dc, line, MARGIN, 6, COLOR_TEXT, hFontBig);
    }
    sprintf(line, "Revealed: %d   Left: %d", revealed, safeTotal - revealed);
    drawText(dc, line, MARGIN, 32, COLOR_FRAME, hFontSmall);
    drawText(dc, "Right click = flag | F2 = new", MARGIN, 54, COLOR_FRAME, hFontSmall);

    // board
    int left = MARGIN;
    int top = STATUS_H;
    HBRUSH hiddenBrush = CreateSolidBrush(COLOR_HIDDEN);
    HBRUSH openBrush = CreateSolidBrush(COLOR_OPEN);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            char cell = view[r][c];
            RECT rc = {left + c * CELL, top + r * CELL,
                       left + c * CELL + CELL - 2, top + r * CELL + CELL - 2};
            FillRect(dc, &rc, cell == '?' ? hiddenBrush : openBrush);

            if (cell == '?') {
                if (flagged[r][c]) {
                    // flag: pole + red triangle
                    int px = rc.left + CELL / 2 - 3;
                    HPEN pen = CreatePen(PS_SOLID, 2, COLOR_TEXT);
                    HGDIOBJ oldPen = SelectObject(dc, pen);
                    MoveToEx(dc, px, rc.top + 5, NULL);
                    LineTo(dc, px, rc.bottom - 5);
                    MoveToEx(dc, px - 5, rc.bottom - 5, NULL);
                    LineTo(dc, px + 6, rc.bottom - 5);
                    SelectObject(dc, oldPen);
                    DeleteObject(pen);
                    HBRUSH red = CreateSolidBrush(COLOR_LOSE);
                    HGDIOBJ oldBrush = SelectObject(dc, red);
                    HPEN none = (HPEN)GetStockObject(NULL_PEN);
                    HGDIOBJ oldPen2 = SelectObject(dc, none);
                    POINT tri[3] = {{px + 1, rc.top + 5}, {px + 1, rc.top + 15}, {px + 12, rc.top + 10}};
                    Polygon(dc, tri, 3);
                    SelectObject(dc, oldPen2);
                    SelectObject(dc, oldBrush);
                    DeleteObject(red);
                }
                continue;
            }

            char text[2] = {cell, 0};
            COLORREF color = COLOR_TEXT;
            if (cell == '*') color = COLOR_BOMB;
            else if (cell >= '0' && cell < '9') color = COLOR_NUMBER;
            if (cell == '0') continue;   // empty revealed cell: no number shown
            SelectObject(dc, hFontCell);
            SetTextColor(dc, color);
            DrawTextA(dc, text, 1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }
    DeleteObject(hiddenBrush);
    DeleteObject(openBrush);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        hFontCell  = CreateFontA(22, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                                 CLEARTYPE_QUALITY, 0, "Consolas");
        hFontSmall = CreateFontA(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                                 CLEARTYPE_QUALITY, 0, "Consolas");
        hFontBig   = CreateFontA(22, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                                 CLEARTYPE_QUALITY, 0, "Consolas");
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_NEW:     startNewGame(); break;
        case ID_EASY:    mode = 1; startNewGame(); break;
        case ID_MEDIUM:  mode = 2; startNewGame(); break;
        case ID_HARD:    mode = 3; startNewGame(); break;
        case ID_SIZE_9:  rows = cols = 9;  startNewGame(); break;
        case ID_SIZE_12: rows = cols = 12; startNewGame(); break;
        case ID_SIZE_16: rows = cols = 16; startNewGame(); break;
        case ID_SIZE_20: rows = cols = 20; startNewGame(); break;
        case ID_EXIT:    DestroyWindow(hwnd); break;
        }
        return 0;

    case WM_KEYDOWN:
        if (wParam == VK_F2) startNewGame();
        return 0;

    case WM_LBUTTONDOWN: {
        if (gameOver) return 0;
        int x = LOWORD(lParam) - MARGIN;
        int y = HIWORD(lParam) - STATUS_H;
        if (x < 0 || y < 0) return 0;
        int c = x / CELL;
        int r = y / CELL;
        if (r >= rows || c >= cols) return 0;
        if (flagged[r][c]) return 0;   // a flagged cell is protected from clicks
        pickCell(r, c);
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }

    case WM_RBUTTONDOWN: {
        if (gameOver) return 0;
        int x = LOWORD(lParam) - MARGIN;
        int y = HIWORD(lParam) - STATUS_H;
        if (x < 0 || y < 0) return 0;
        int c = x / CELL;
        int r = y / CELL;
        if (r >= rows || c >= cols) return 0;
        if (view[r][c] != '?') return 0;   // only hidden cells can be flagged
        flagged[r][c] = !flagged[r][c];
        flagCount += flagged[r][c] ? 1 : -1;
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }

    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        RECT rc;
        GetClientRect(hwnd, &rc);
        // draw into a memory bitmap first, so there is no flicker
        HDC mem = CreateCompatibleDC(dc);
        HBITMAP bmp = CreateCompatibleBitmap(dc, rc.right, rc.bottom);
        HGDIOBJ old = SelectObject(mem, bmp);
        paintGame(mem, rc.right, rc.bottom);
        BitBlt(dc, 0, 0, rc.right, rc.bottom, mem, 0, 0, SRCCOPY);
        SelectObject(mem, old);
        DeleteObject(bmp);
        DeleteDC(mem);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        DeleteObject(hFontCell);
        DeleteObject(hFontSmall);
        DeleteObject(hFontBig);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nShow) {
    srand((unsigned)time(NULL));

    // menu
    HMENU menu = CreateMenu();
    HMENU game = CreatePopupMenu();
    HMENU diff = CreatePopupMenu();
    HMENU size = CreatePopupMenu();
    AppendMenuA(diff, MF_STRING, ID_EASY,   "Easy (20% bombs)");
    AppendMenuA(diff, MF_STRING, ID_MEDIUM, "Medium (30% bombs)");
    AppendMenuA(diff, MF_STRING, ID_HARD,   "Hard (40% bombs)");
    AppendMenuA(size, MF_STRING, ID_SIZE_9,  "9 x 9");
    AppendMenuA(size, MF_STRING, ID_SIZE_12, "12 x 12");
    AppendMenuA(size, MF_STRING, ID_SIZE_16, "16 x 16");
    AppendMenuA(size, MF_STRING, ID_SIZE_20, "20 x 20");
    AppendMenuA(game, MF_STRING, ID_NEW, "New game\tF2");
    AppendMenuA(game, MF_POPUP, (UINT_PTR)diff, "Difficulty");
    AppendMenuA(game, MF_POPUP, (UINT_PTR)size, "Map size");
    AppendMenuA(game, MF_SEPARATOR, 0, NULL);
    AppendMenuA(game, MF_STRING, ID_EXIT, "Exit");
    AppendMenuA(menu, MF_POPUP, (UINT_PTR)game, "Game");

    WNDCLASSA wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "MinesweeperWnd";
    RegisterClassA(&wc);

    hMainWnd = CreateWindowA("MinesweeperWnd", "Minesweeper",
                             WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
                             CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
                             NULL, menu, hInst, NULL);

    startNewGame();
    ShowWindow(hMainWnd, nShow);
    UpdateWindow(hMainWnd);

    MSG m;
    while (GetMessage(&m, NULL, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    return 0;
}
