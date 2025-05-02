#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

// Forward declarations of game levels
void startLevel1();
void startLevel2();
void startLevel3();
void startLevel4();
void startLevel5();
void startLevel6();
void startLevel7();

const string GAME_NAMES[] = {
    "Memory Bone Match 🦴",
    "Tic-Tac-Bone 🐾",
    "Hungry Pup Feeder 🍖",
    "Dog Jump Challenge 🐕",
    "Obstacle Course 🚧",
    "Simon Barks 🎵",
    "Word Search 🏁"
};
const int NUM_GAMES = 7;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
    cout.flush();
}

void printBorderedBox(const vector<string>& content) {
    const int BOX_WIDTH = 60;
    string topLeft = u8"╭";
    string topRight = u8"╮";
    string bottomLeft = u8"╰";
    string bottomRight = u8"╯";
    string horizontal = u8"─";
    string vertical = u8"│";

    string borderTop = topLeft + string(BOX_WIDTH - 2, ' ') + topRight;
    string borderBottom = bottomLeft + string(BOX_WIDTH - 2, ' ') + bottomRight;

    // Replace spaces with repeated dashes
    borderTop = topLeft + string(BOX_WIDTH - 2, '-') + topRight;
    borderBottom = bottomLeft + string(BOX_WIDTH - 2, '-') + bottomRight;

    cout << "\033[36m" << borderTop << "\033[0m" << endl;

    for (const string& line : content) {
        // Calculate visual length (skip escape sequences and handle multibyte UTF-8)
        size_t visibleLen = 0;
        bool inEscape = false;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '\033' && i + 1 < line.size() && line[i + 1] == '[') {
                inEscape = true;
                i += 2;
                while (i < line.size() && line[i] != 'm') i++;
                continue;
            }
            if (!inEscape && (line[i] & 0xC0) != 0x80) {
                visibleLen++;
            }
            if (inEscape && line[i] == 'm') inEscape = false;
        }

        int padding = BOX_WIDTH - 2 - visibleLen;
        int leftPad = padding / 2;
        int rightPad = padding - leftPad;

        cout << "\033[36m" << vertical << "\033[0m"
             << string(leftPad, ' ') << line << string(rightPad, ' ')
             << "\033[36m" << vertical << "\033[0m" << endl;
    }

    cout << "\033[36m" << borderBottom << "\033[0m" << endl;
    cout.flush();
}

int main() {
    // Enable UTF-8 mode on Windows
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    int choice = 0;
    bool quit = false;

    while (!quit) {
        clearScreen();

        vector<string> intro = {
            "\033[1;33m🐶  Welcome to Doggie Day Care!  🐶\033[0m",
            "",
            "\033[3mYou work at a dog daycare center!",
            "Play games with the pups to keep them happy and healthy.\033[0m",
            "",
            "\033[1mChoose a game to start:\033[0m"
        };

        printBorderedBox(intro);

        for (int i = 0; i < NUM_GAMES; ++i) {
            cout << "  \033[35m" << (i + 1) << ".\033[0m " << GAME_NAMES[i] << "\n";
        }
        cout << "\n  \033[35m8.\033[0m Exit Game\n\n";

        cout << "  \033[1mEnter your choice (1-8): \033[0m";
        cin >> choice;

        if (choice == 8) {
            clearScreen();
            cout << "\n  \033[32mGoodbye! Woof woof! 🐾\033[0m\n";
            usleep(1500000);
            quit = true;
            continue;
        }

        if (choice >= 1 && choice <= NUM_GAMES) {
            clearScreen();
            cout << "\n  \033[33mStarting " << GAME_NAMES[choice - 1] << "...\033[0m\n";
            usleep(1000000);

            switch (choice) {
                case 1: startLevel1(); break;
                case 2: startLevel2(); break;
                case 3: startLevel3(); break;
                case 4: startLevel4(); break;
                case 5: startLevel5(); break;
                case 6: startLevel6(); break;
                case 7: startLevel7(); break;
            }
        } else {
            cout << "  \033[31mInvalid choice! Please try again.\033[0m\n";
            usleep(1000000);
        }
    }

    return 0;
}