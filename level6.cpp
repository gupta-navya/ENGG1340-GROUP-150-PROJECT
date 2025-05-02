#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

vector<string> commands = {"🐶 Sit", "🦴 Roll", "🐾 Stay", "🎾 Fetch", "🛏️ Sleep", "🚶 Walk"};

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayInstructions() {
    cout << "🐕‍🦺 Welcome to the Simon Stays Memory Game 🧠" << endl;
    cout << "------------------------------------------" << endl;
    cout << "👉 You will be shown a sequence of dog commands (emojis included)." << endl;
    cout << "👉 Memorize the command order. It will disappear in a few seconds." << endl;
    cout << "👉 You'll then select the correct sequence using numbers from the list below." << endl;
    cout << "👉 Each level changes how many commands you need to remember:" << endl;
    cout << "   🟢 Easy: 4 Commands" << endl;
    cout << "   🟡 Medium: 6 Commands" << endl;
    cout << "   🔴 Difficult: 8 Commands" << endl;
    cout << "\nPress ENTER to continue..." << endl;
    cin.ignore();
}

void displayMenu() {
    cout << "\n📋 Command List:\n";
    for (size_t i = 0; i < commands.size(); ++i) {
        cout << " " << i + 1 << ") " << commands[i] << endl;
    }
}

void showSequence(const vector<int>& sequence) {
    cout << "\n🧠 Memorize This Command Sequence:\n";
    for (int idx : sequence) {
        cout << commands[idx] << "  ";
    }
    cout << "\n";
    this_thread::sleep_for(chrono::seconds(5));
    clearConsole();
}

bool getPlayerInput(const vector<int>& sequence) {
    cout << "📥 Enter the sequence using numbers (e.g., 1231): ";
    string input;
    cin >> input;

    if (input.length() != sequence.size()) {
        cout << "❌ Wrong number of commands.\n";
        return false;
    }

    for (size_t i = 0; i < input.length(); ++i) {
        int entered = input[i] - '1';
        if (entered != sequence[i]) {
            cout << "❌ Incorrect sequence at position " << i + 1 << ".\n";
            return false;
        }
    }

    return true;
}

void startSimonLevel(int levelLength) {
    srand(time(0));
    vector<int> sequence;

    for (int i = 0; i < levelLength; ++i) {
        sequence.push_back(rand() % commands.size());
    }

    showSequence(sequence);
    displayMenu();

    bool success = getPlayerInput(sequence);
    if (success) {
        cout << "✅ Well done! You got the sequence right! 🎉" << endl;
    } else {
        cout << "💥 Oops! Better luck next time!" << endl;
    }
}

void startLevel6() {
    clearConsole();
    displayInstructions();

    int level = 1;
    while (level <= 3) {
        if (level == 1) {
            cout << "\nStarting Easy Level (4 commands)...\n";
            startSimonLevel(4);
        } else if (level == 2) {
            cout << "\nStarting Medium Level (6 commands)...\n";
            startSimonLevel(6);
        } else if (level == 3) {
            cout << "\nStarting Hard Level (8 commands)...\n";
            startSimonLevel(8);
        }

        level++;
    }

    cout << "\n🎉 All levels completed! Returning to the Main Menu...\n";
    this_thread::sleep_for(chrono::seconds(2));
    clearConsole();
}
