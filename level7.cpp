// level7.cpp - Fixed version
// written by CHAN Pak Tung, UID:303632817
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

// Define a constant vector of dog-related words for the word search game
const vector<string> dogWords = {"BARK", "SIT", "STAY", "PAW", "FETCH", "ROLL", "BONE", "LEASH", "TREAT", "WOOF"};

// Class representing a word search puzzle
class WordSearch {
private:
    // 2D vector representing the word search grid
    vector<vector<char>> grid;
    // 2D vector to mark the positions of the target word for highlighting
    vector<vector<bool>> highlight;
    // The word that the player needs to find in the grid
    string targetWord;
    // The size of the word search grid
    int size;
    // The difficulty level of the puzzle (easy, medium, hard)
    string difficulty;
    // The starting row of the target word in the grid
    int startRow, startCol;
    // Flag indicating whether the word is placed horizontally (true) or vertically (false)
    bool isHorizontal;

    // Fill the empty cells in the grid with random letters
    void fillRandomLetters() {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (grid[i][j] == ' ')
                    grid[i][j] = 'A' + rand() % 26;
    }

    // Try to place the given word in the grid either horizontally or vertically
    bool placeWord(string word) {
        // Randomly choose a direction (0 = horizontal, 1 = vertical)
        int direction = rand() % 2; 
        int row, col;

        if (direction == 0) { // Horizontal placement
            // Randomly select a row
            row = rand() % size;
            // Randomly select a starting column such that the word fits horizontally
            col = rand() % (size - word.length() + 1);
            // Check if the word can be placed horizontally without overlapping with existing letters
            for (size_t i = 0; i < word.length(); ++i) 
                if (grid[row][col + i] != ' ' && grid[row][col + i] != word[i])
                    return false;
            // Place the word horizontally and mark the cells for highlighting
            for (size_t i = 0; i < word.length(); ++i) { 
                grid[row][col + i] = word[i];
                highlight[row][col + i] = true;
            }
            // Record the starting position and direction
            startRow = row;
            startCol = col;
            isHorizontal = true;
        } else { // Vertical placement
            // Randomly select a starting row such that the word fits vertically
            row = rand() % (size - word.length() + 1);
            // Randomly select a column
            col = rand() % size;
            // Check if the word can be placed vertically without overlapping with existing letters
            for (size_t i = 0; i < word.length(); ++i) 
                if (grid[row + i][col] != ' ' && grid[row + i][col] != word[i])
                    return false;
            // Place the word vertically and mark the cells for highlighting
            for (size_t i = 0; i < word.length(); ++i) { 
                grid[row + i][col] = word[i];
                highlight[row + i][col] = true;
            }
            // Record the starting position and direction
            startRow = row;
            startCol = col;
            isHorizontal = false;
        }

        return true;
    }

public:
    // Constructor to initialize the word search puzzle based on the given difficulty level
    WordSearch(string diff) : difficulty(diff) {
        // Seed the random number generator with the current time
        srand(time(0));
        if (difficulty == "easy") {
            // Set the grid size for easy difficulty
            size = 8;
            // Randomly select a word from the first three words in the dogWords list
            targetWord = dogWords[rand() % 3];
        } else if (difficulty == "medium") {
            // Set the grid size for medium difficulty
            size = 12;
            // Randomly select a word from the middle three words in the dogWords list
            targetWord = dogWords[3 + rand() % 3];
        } else {
            // Set the grid size for hard difficulty
            size = 16;
            // Randomly select a word from the last four words in the dogWords list
            targetWord = dogWords[6 + rand() % 4];
        }

        // Resize the grid and highlight vectors to the appropriate size
        grid.resize(size, vector<char>(size, ' '));
        highlight.resize(size, vector<bool>(size, false));

        // Try to place the target word in the grid up to 100 times
        for (int attempt = 0; attempt < 100; ++attempt)
            if (placeWord(targetWord)) break;

        // Fill the remaining empty cells with random letters
        fillRandomLetters();
    }

    // Print the word search grid, optionally showing the answer
    void printGrid(bool showAnswer = false) {
        // Print the difficulty level and the target word
        cout << "\nDifficulty: " << difficulty << endl;
        cout << "Find the word: " << targetWord << "\n\n";
        // Iterate through each cell in the grid
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (showAnswer && highlight[i][j])
                    // If showing the answer and the cell is part of the target word, highlight it in red
                    cout << "\033[1;31m" << setw(2) << grid[i][j] << "\033[0m" << " ";
                else
                    // Otherwise, print the cell as normal
                    cout << setw(2) << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        if (showAnswer) {
            // If showing the answer, print the starting position and direction of the target word
            cout << "The word starts at row " << startRow + 1 << ", column " << startCol + 1
                 << " and goes " << (isHorizontal ? "horizontally" : "vertically") << ".\n";
        }
    }
};

// Function to clear the console screen
void customclearlevel7() {  
    cout << "\033[2J\033[1;1H";
}

// Function to display the instructions for the level 7 game
void showLevel7Instructions() {  
    // Clear the console screen
    customclearlevel7();
    cout << "+--------------------------------------------------+\n";
    cout << "|              🐾 DOG ATE MY HOMEWORK 🐾            |\n";
    cout << "+--------------------------------------------------+\n";
    cout << "|                                                  |\n";
    cout << "|  Uh oh! Your dog ate your homework again!        |\n";
    cout << "|  But wait... Can you find the missing word?      |\n";
    cout << "|                                                  |\n";
    cout << "|  Use your eyes and spot the hidden doggy term!   |\n";
    cout << "|                                                  |\n";
    cout << "|              Press ENTER to continue             |\n";
    cout << "+--------------------------------------------------+\n";
    // Wait for the user to press Enter
    cin.ignore();
    cin.get();
}

// Function to ask the user if they want to return to the main menu
bool askReturnToMenu() {
    string input;
    cout << "\nWould you like to go back to the main menu? (yes/no): ";
    cin >> input;
    // Convert the input to lowercase
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    // Return true if the user wants to go back to the main menu
    return (input == "yes" || input == "y");
}

// Function to start the level 7 game
void startLevel7() {
    // Seed the random number generator with the current time
    srand(time(0));
    // Display the game instructions
    showLevel7Instructions();  

    while (true) {
        // Clear the console screen
        customclearlevel7();  
        cout << "WORD SEARCH: DOG ATE MY HOMEWORK - FIND THE MISSING WORD\n";
        cout << "=======================================================\n";
        cout << "Choose difficulty level:\n";
        cout << "1. Easy (8x8 grid)\n";
        cout << "2. Medium (12x12 grid)\n";
        cout << "3. Hard (16x16 grid)\n";
        cout << "Enter your choice (1-3): ";

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            // If the input is invalid, clear the input buffer and prompt the user to try again
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        // Determine the difficulty level based on the user's choice
        string difficulty = (choice == 1) ? "easy" : (choice == 2) ? "medium" : "hard";

        while (true) {
            // Create a new word search puzzle with the selected difficulty level
            WordSearch puzzle(difficulty);
            // Clear the console screen
            customclearlevel7();  
            // Print the puzzle grid
            puzzle.printGrid();

            cout << "Options:\n";
            cout << "1. Show answer\n";
            cout << "2. Try another puzzle\n";
            cout << "3. Choose different difficulty\n";
            cout << "Enter your choice (1-3): ";

            int option;
            cin >> option;

            if (cin.fail()) {
                // If the input is invalid, clear the input buffer and prompt the user to try again
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
                continue;
            }

            if (option == 1) {
                // If the user wants to see the answer, clear the screen and print the grid with the answer
                customclearlevel7();  
                puzzle.printGrid(true);
                cout << "Press enter to continue...";
                // Wait for the user to press Enter
                cin.ignore();
                cin.get();
            } else if (option == 2) {
                // If the user wants to try another puzzle, continue with the same difficulty level
                continue; 
            } else if (option == 3) {
                // If the user wants to change the difficulty level, break out of the inner loop
                break; 
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }

        if (askReturnToMenu()) {
            // If the user wants to return to the main menu, exit the function
            return; 
        }
    }
}