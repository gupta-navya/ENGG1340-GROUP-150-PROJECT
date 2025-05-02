#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <unistd.h>
using namespace std;

// Game configuration structure
struct Level {
    string name;    // Difficulty level name
    int bones;      // Number of bones to find
    int hints;      // Available hints
};

// Predefined difficulty levels
const Level LEVELS[] = {
    {"Easy", 3, 1},
    {"Medium", 5, 2},
    {"Difficult", 7, 3},
    {"Master", 10, 3},
    {"Impossible", 15, 2}
};

// Clears terminal screen (cross-platform)
void customClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Displays game instructions and level info
void customShowInstructions() {
    customClearScreen();
    cout << "🐕 BONE FINDER GAME - INSTRUCTIONS 🦴\n\n";
    cout << "1. You'll see a grid with hidden bones (🦴) and decorations\n";
    cout << "2. Memorize bone locations within 5 seconds\n";
    cout << "3. Enter coordinates (like A1, B2) to find bones\n";
    cout << "   - or type 'quit' to exit to main menu\n";
    cout << "4. Use 'hint' to reveal the board temporarily (limited uses)\n";
    cout << "5. Find all bones to complete the level\n\n";
    cout << "LEVELS:\n";
    for (size_t i = 0; i < sizeof(LEVELS)/sizeof(LEVELS[0]); i++) {
        cout << "- " << LEVELS[i].name << ": " << LEVELS[i].bones 
             << " bones, " << LEVELS[i].hints << " hints\n";
    }
    cout << "\nPress Enter to begin...";
    cin.ignore();
    cin.get();
}

// Displays the current game grid
void customShowGrid(const vector<vector<string> >& grid) {
    cout << "   ";
    for (char c = 'A'; c <= 'H'; c++) {
        cout << " " << c << "  ";
    }
    cout << "\n";
    
    for (int i = 0; i < 8; ++i) {
        cout << i+1 << " ";
        for (int j = 0; j < 8; ++j) {
            cout << " " << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

// Handles gameplay for a single level
bool playLevel(const Level& level) {
    // Hidden grid shows player progress
    vector<vector<string> > hiddenGrid(8, vector<string>(8, "❓"));
    // Visible grid contains actual bone locations
    vector<vector<string> > visibleGrid(8, vector<string>(8, "🟩"));
    int hintsLeft = level.hints;
    int bonesFound = 0;

    // Randomly place bones on grid
    for (int i = 0; i < level.bones; ) {
        int x = rand() % 8, y = rand() % 8;
        if (visibleGrid[x][y] == "🟩") {
            visibleGrid[x][y] = "🦴";
            i++;
        }
    }

    // Fill remaining spaces with decorations
    const char* decor_array[] = {"🌼","🐝","🦋","🍄","🌻","🐞","🌷","🪴"};
    vector<string> decorations(decor_array, decor_array + sizeof(decor_array)/sizeof(decor_array[0]));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (visibleGrid[i][j] == "🟩") {
                visibleGrid[i][j] = decorations[rand() % 8];
            }
        }
    }

    // Show initial board for memorization
    customClearScreen();
    cout << "🐕 LEVEL: " << level.name << " 🦴\n";
    cout << "Find " << level.bones << " bones | " << level.hints << " hints available\n\n";
    cout << "Memorize the bone locations (5 seconds):\n";
    customShowGrid(visibleGrid);
    sleep(5);
    customClearScreen();

    // Main game loop
    while (bonesFound < level.bones) {
        cout << "🐕 LEVEL: " << level.name << " 🦴\n";
        customShowGrid(hiddenGrid);
        cout << "\n🦴 Bones: " << bonesFound << "/" << level.bones;
        cout << " | 💡 Hints: " << hintsLeft << "/" << level.hints << "\n";
        cout << "Enter (A1-H8), 'hint', or 'quit': ";
        
        string input;
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        // Handle quit command
        if (input == "quit") {
            cout << "Returning to main menu...\n";
            sleep(1);
            return false;
        }

        // Handle hint command
        if (input == "hint") {
            if (hintsLeft > 0) {
                hintsLeft--;
                cout << "💡 Showing board for 3 seconds...\n";
                customShowGrid(visibleGrid);
                sleep(3);
            } else {
                cout << "🚫 NO MORE HINTS AVAILABLE!\n";
                sleep(1);
            }
            customClearScreen();
            continue;
        }

        // Validate input format
        if (input.length() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
            cout << "❌ Invalid input! Use format like A1\n";
            sleep(1);
            customClearScreen();
            continue;
        }

        // Convert input to coordinates
        char col = toupper(input[0]);
        int row = input[1] - '0';
        if (col < 'A' || col > 'H' || row < 1 || row > 8) {
            cout << "❌ Invalid coordinates! Use A1-H8\n";
            sleep(1);
            customClearScreen();
            continue;
        }

        // Check if position was already revealed
        int x = row - 1;
        int y = col - 'A';
        if (hiddenGrid[x][y] != "❓") {
            cout << "⏳ Already checked this spot!\n";
            sleep(1);
            customClearScreen();
            continue;
        }

        // Reveal position and check for bone
        hiddenGrid[x][y] = visibleGrid[x][y];
        if (visibleGrid[x][y] == "🦴") {
            bonesFound++;
            cout << "🎉 BONE FOUND! (" << bonesFound << "/" << level.bones << ")\n";
        } else {
            cout << "Found " << visibleGrid[x][y] << " (not a bone)\n";
        }
        sleep(1);
        customClearScreen();
    }

    // Level completion message
    cout << "🎊 LEVEL " << level.name << " COMPLETED! 🐶\n";
    cout << "Final board:\n";
    customShowGrid(visibleGrid);
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    return true;
}

// Main game function - handles level progression
void startLevel1() {
    srand(time(0));
    customShowInstructions();

    for (size_t i = 0; i < sizeof(LEVELS)/sizeof(LEVELS[0]); ++i) {
        customClearScreen();
        cout << "🚀 STARTING LEVEL " << (i+1) << ": " << LEVELS[i].name << "\n";
        cout << "Find " << LEVELS[i].bones << " bones | " << LEVELS[i].hints << " hints available\n";
        cout << "Press Enter to begin...";
        cin.ignore();
        cin.get();

        if (!playLevel(LEVELS[i])) {
            cout << "Exiting to main menu...\n";
            return;
        }
    }

    cout << "\n🎉 CONGRATULATIONS! YOU BEAT ALL LEVELS! 🏆\n";
    cout << "🐶 Your dog is proud of you! 🦴\n";
    cout << "Press Enter to return to main menu...\n";
    cin.ignore();
    cin.get();
}
