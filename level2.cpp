#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// Game symbols
const string BONE = "🦴";   // Player uses bone symbol
const string SKULL = "💀";  // AI uses skull symbol
const string EMPTY = "  ";  // Empty space on board

// Shows the current game board with rows A-C and columns 1-3
void customPrintBoard(const vector<vector<string> > &board) {
    cout << "\n    1   2   3\n";
    cout << "  +---+---+---+\n";
    for (int i = 0; i < 3; ++i) {
        cout << char('A' + i) << " |";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << "|";
        }
        cout << "\n  +---+---+---+\n";
    }
}

// Checks if the given player (BONE or SKULL) has 3 in a row
bool customCheckWin(const vector<vector<string> > &board, string player) {
    // Check all rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Check both diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Returns true if all spaces on board are filled
bool customIsBoardFull(const vector<vector<string> > &board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}

// AI picks first empty spot and marks it with skull
void customMakeAIMove(vector<vector<string> > &board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = SKULL;
                return;
            }
        }
    }
}

// Displays game instructions at start
void customShowInstruction() {
    cout << "\n🐕 BONE vs SKULL TIC-TAC-TOE 🐕\n";
    cout << "HOW TO PLAY:\n";
    cout << "1. Enter moves like A1, B2, C3\n";
    cout << "2. Get 3 in a row to win\n";
    cout << "3. Type 'quit' to exit\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Main game loop - handles turns, wins, and replay
void startLevel2() {
    char playAgain;
    do {
        vector<vector<string> > board(3, vector<string>(3, EMPTY));
        srand(time(0));

        customShowInstruction();
        cout << "🐕 BONE vs SKULL TIC-TAC-TOE 🐕\n";

        while (true) {
            customPrintBoard(board);
            string input;
            cout << "\nYour move (🦴): ";
            cin >> input;

            if (input == "quit") return;

            if (input.length() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
                cout << "Invalid move! Use format like A1\n";
                continue;
            }

            int row = toupper(input[0]) - 'A';
            int col = input[1] - '1';

            if (row < 0 || row > 2 || col < 0 || col > 2) {
                cout << "Invalid position! Use A1-C3\n";
                continue;
            }

            if (board[row][col] != EMPTY) {
                cout << "Spot taken!\n";
                continue;
            }

            board[row][col] = BONE;

            if (customCheckWin(board, BONE)) {
                customPrintBoard(board);
                cout << "🎉 YOU WON!\n";
                break;
            }

            if (customIsBoardFull(board)) {
                customPrintBoard(board);
                cout << "😐 TIE!\n";
                break;
            }

            customMakeAIMove(board);

            if (customCheckWin(board, SKULL)) {
                customPrintBoard(board);
                cout << "💀 SKULLS WON!\n";
                break;
            }

            if (customIsBoardFull(board)) {
                customPrintBoard(board);
                cout << "😐 TIE!\n";
                break;
            }
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
}
