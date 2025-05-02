// Game Name: Dog Food Catcher
// Description: A fun game where you control a dog to catch good food and avoid bad food.
// Made by: Adel Kussainova 3036385731

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring>
#include <locale.h>
#include <termios.h>
#include <sys/select.h>

using namespace std;

// Constants for game settings
const int WIDTH = 60;
const int HEIGHT = 18;
const int BORDER_PADDING = 1;
const int WIN_GOOD_FOOD_COUNT = 15;
const int LOSE_BAD_FOOD_COUNT = 3;
const int INSTRUCTION_DELAY = 800000;

// Game variables
int dogPos = WIDTH / 2;
int goodFoodEaten = 0;
int badFoodEaten = 0;
int frame = 0;
bool dogBounce = false;
bool caughtBomb = false;

// Difficulty levels
enum Difficulty { EASY = 1, MEDIUM, HARD };

// ANSI Color Codes
const string COLOR_RESET = "\033[0m";
const string COLOR_DOG = "\033[38;5;208m";
const string COLOR_GOOD = "\033[92m";
const string COLOR_BAD = "\033[91m";
const string COLOR_BOMB = "\033[95m";
const string COLOR_TEXT = "\033[96m";
const string COLOR_BORDER = "\033[38;5;118m";

// Food item structure
struct FoodItem {
    string type;
    int delay;
    FoodItem(const string& t = " ", int d = 0) : type(t), delay(d) {}
};

vector<vector<FoodItem>> food(HEIGHT, vector<FoodItem>(WIDTH));

// Level3-specific terminal functions
void enableRawModeLevel3() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disableRawModeLevel3() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

bool keyPressedLevel3() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) > 0;
}

void customClearLevel3() {
    cout << "\033[2J\033[1;1H";
}

int getGameSpeed(Difficulty level) {
    if (level == EASY) return 150000;
    if (level == MEDIUM) return 100000;
    return 60000;
}

void resetGame() {
    goodFoodEaten = 0;
    badFoodEaten = 0;
    frame = 0;
    caughtBomb = false;
    dogPos = WIDTH / 2;
    food.assign(HEIGHT, vector<FoodItem>(WIDTH));
}

void drawBorder() {
    cout << COLOR_BORDER;
    cout << "╔";
    for (int x = 0; x < WIDTH; x++) cout << "═";
    cout << "╗\n";
    
    for (int y = 0; y < HEIGHT; y++) {
        cout << "║";
        for (int x = 0; x < WIDTH; x++) cout << " ";
        cout << "║\n";
    }
    
    cout << "╚";
    for (int x = 0; x < WIDTH; x++) cout << "═";
    cout << "╝" << COLOR_RESET << "\n";
}

void instructions(Difficulty level) {
    customClearLevel3();
    cout << COLOR_TEXT;
    
    string header = level == EASY ? "🐶 WELCOME TO DOG FOOD CATCHER 🐶" :
                    level == MEDIUM ? "🟡 LEVEL 2: MEDIUM MODE 🟡" :
                                      "🔴 LEVEL 3: HARD MODE 🔴";

    vector<string> lines = {
        "Instructions:",
        "- Use 'a' to move left, 'd' to move right.",
        "- Catch 🍗 (good food), avoid 🗑️ (junk food).",
        "- Eat 15 good food to win.",
        "- Avoid eating 3 bad food, or you lose.",
        (level == HARD ? "- Avoid bombs (💣) or game over!" : ""),
        "Game starting in:"
    };

    cout << "\033[2;0H" << header << "\n";
    for (size_t i = 0; i < lines.size(); i++) {
        cout << "\033[" << (4 + i) << ";0H" << lines[i];
        cout.flush();
        usleep(INSTRUCTION_DELAY);
    }

    for (int i = 3; i >= 1; i--) {
        cout << "\033[11;0H" << i;
        cout.flush();
        sleep(1);
    }
    cout << "\033[13;0HGO!";
    cout.flush();
    sleep(1);
    customClearLevel3();
}

void draw() {
    customClearLevel3();
    drawBorder();
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (food[i][j].type != " ") {
                cout << "\033[" << (i + 1) << ";" << (j + 1) << "H";
                if (food[i][j].type == "🍗") cout << COLOR_GOOD;
                else if (food[i][j].type == "🗑️") cout << COLOR_BAD;
                else if (food[i][j].type == "💣") cout << COLOR_BOMB;
                cout << food[i][j].type << COLOR_RESET;
            }
        }
    }
    
    cout << "\033[" << HEIGHT << ";" << (dogPos + 1) << "H" 
         << COLOR_DOG << (dogBounce ? "🐶" : "🐕") << COLOR_RESET;
    
    cout << "\033[" << (HEIGHT + 3) << ";0H" << COLOR_TEXT
         << "Good Food (🍗): " << goodFoodEaten << "\n"
         << "Bad Food (🗑️): " << badFoodEaten << COLOR_RESET;
    cout.flush();
}

void updateFood(Difficulty level) {
    for (int i = HEIGHT - 2; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            if (food[i][j].type != " " && food[i][j].delay <= 0 && food[i + 1][j].type == " ") {
                food[i + 1][j] = food[i][j];
                food[i][j] = FoodItem(" ", 0);
            } else if (food[i][j].type != " ") {
                food[i][j].delay--;
            }
        }
    }

    for (int j = 0; j < WIDTH; j++) {
        if (food[HEIGHT - 1][j].type != " " && abs(j - dogPos) > 1) {
            food[HEIGHT - 1][j] = FoodItem(" ", 0);
        }
    }

    if (frame % 5 == 0) {
        int col = rand() % WIDTH;
        int randNum = rand() % 10;
        string type = "🍗";
        if (randNum < 2) type = "🗑️";
        else if (level == HARD && randNum == 9) type = "💣";
        food[0][col] = FoodItem(type, 2);
    }
}

void moveDog(int ch) {
    if (ch == 'a' && dogPos > BORDER_PADDING) dogPos--;
    else if (ch == 'd' && dogPos < WIDTH - BORDER_PADDING - 1) dogPos++;
    dogBounce = !dogBounce;
}

void checkCatch() {
    for (int dx = -1; dx <= 1; dx++) {
        int pos = dogPos + dx;
        if (pos >= 0 && pos < WIDTH) {
            string item = food[HEIGHT - 1][pos].type;
            if (item == "🍗") { goodFoodEaten++; food[HEIGHT - 1][pos] = FoodItem(" ", 0); }
            else if (item == "🗑️") { badFoodEaten++; food[HEIGHT - 1][pos] = FoodItem(" ", 0); }
            else if (item == "💣") { caughtBomb = true; food[HEIGHT - 1][pos] = FoodItem(" ", 0); }
        }
    }
}

void winAnimation() {
    string msg = "🎉 LEVEL COMPLETE! 🎉";
    for (int i = 0; i < 10; i++) {
        customClearLevel3();
        cout << COLOR_TEXT << msg << COLOR_RESET << endl;
        cout.flush();
        usleep(200000);
    }
}

bool loseAnimationWithRetry(Difficulty level) {
    string msg = caughtBomb ? "💣 You caught a bomb! GAME OVER 💣" :
                             "💀 TOO MUCH JUNK FOOD! 💀";
    customClearLevel3();
    cout << COLOR_TEXT << msg << "\nPress any key to retry Level " << level << "..." << COLOR_RESET;
    cout.flush();
    disableRawModeLevel3();
    getchar();
    return false;
}

bool playLevel(Difficulty level) {
    instructions(level);
    resetGame();
    enableRawModeLevel3();

    while (goodFoodEaten < WIN_GOOD_FOOD_COUNT && 
           badFoodEaten < LOSE_BAD_FOOD_COUNT && 
           !caughtBomb) {
        int ch = 0;
        if (keyPressedLevel3()) {
            read(STDIN_FILENO, &ch, 1);
            if (isalpha(ch)) ch = tolower(ch);
            if (ch == 'a' || ch == 'd') moveDog(ch);
        }
        
        updateFood(level);
        checkCatch();
        draw();
        usleep(getGameSpeed(level));
        frame++;
    }

    disableRawModeLevel3();
    
    if (caughtBomb || badFoodEaten >= LOSE_BAD_FOOD_COUNT)
        return loseAnimationWithRetry(level);

    winAnimation();
    return true;
}

void startLevel3() {
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(0));

    for (int lvl = EASY; lvl <= HARD; lvl++) {
        while (!playLevel(static_cast<Difficulty>(lvl))) {}
    }

    customClearLevel3();
    cout << COLOR_TEXT << "🏆 YOU COMPLETED ALL LEVELS! 🏆\n" 
         << "Press any key to continue..." << COLOR_RESET;
    getchar();
}