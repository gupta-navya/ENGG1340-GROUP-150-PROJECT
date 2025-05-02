#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <limits>

using namespace std;

// Emojis
const string DOG = "🐶";
const string TOY = "🧸";
const string OBSTACLE = "🚧";         // Static
const string MOVING_OBSTACLE = "🚗"; // Moving
const string EMPTY = "⬜";

int rows, cols, staticObstacleCount, movingObstacleCount;
int dogX, dogY;
int toyX, toyY;
vector<vector<string>> grid;
vector<pair<int, int>> movingObstacles;

// Input without Enter
char getInput() {
    termios oldt{}, newt{};
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Non-blocking key press
bool kbhit() {
    termios oldt{}, newt{};
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

// Clear terminal
void clearScreens() {
    cout << "\033[2J\033[1;1H";
}

// Wait for Enter
void waitForEnter() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Show instructions
void showInstructions() {
    clearScreens();
    cout << "+----------------------------------------------+\n";
    cout << "|         🐶 Welcome to Dog's Quest!           |\n";
    cout << "+----------------------------------------------+\n";
    cout << "| OBJECTIVE:                                   |\n";
    cout << "| 🧸 Reach the toy without touching obstacles! |\n";
    cout << "|                                              |\n";
    cout << "| CONTROLS:                                    |\n";
    cout << "|   W = Up   S = Down   A = Left   D = Right   |\n";
    cout << "|                                              |\n";
    cout << "| OBSTACLES:                                   |\n";
    cout << "|   🚧 Static obstacles (don't move)            |\n";
    cout << "|   🚗 Moving obstacles (move around!)          |\n";
    cout << "|                                              |\n";
    cout << "| DIFFICULTIES:                                |\n";
    cout << "|  Easy: Static obstacles only                 |\n";
    cout << "|  Medium: 2 moving obstacles                  |\n";
    cout << "|  Hard: 4 moving obstacles                    |\n";
    cout << "|                                              |\n";
    cout << "| Press ENTER to start...                      |\n";
    cout << "+----------------------------------------------+\n";
    waitForEnter();
}

// Choose difficulty
void chooseDifficulty() {
    int choice;
    cout << "\nChoose difficulty: 1/2/3\n";
    cout << "1. Easy\n2. Medium\n3. Hard\n> ";
    cin >> choice;

    switch (choice) {
        case 1:
            rows = 8; cols = 12; staticObstacleCount = 10; movingObstacleCount = 0;
            break;
        case 2:
            rows = 12; cols = 18; staticObstacleCount = 20; movingObstacleCount = 2;
            break;
        case 3:
            rows = 16; cols = 24; staticObstacleCount = 30; movingObstacleCount = 4;
            break;
        default:
            cout << "Invalid choice. Defaulting to Easy.\n";
            rows = 8; cols = 12; staticObstacleCount = 10; movingObstacleCount = 0;
            break;
    }
}

// Initialize grid
void initializeGrid() {
    grid = vector<vector<string>>(rows, vector<string>(cols, EMPTY));
    movingObstacles.clear();
    srand(time(0));

    dogX = rand() % rows;
    dogY = rand() % cols;
    grid[dogX][dogY] = DOG;

    do {
        toyX = rand() % rows;
        toyY = rand() % cols;
    } while (grid[toyX][toyY] != EMPTY);
    grid[toyX][toyY] = TOY;

    for (int i = 0; i < staticObstacleCount; ++i) {
        int x, y;
        do {
            x = rand() % rows;
            y = rand() % cols;
        } while (grid[x][y] != EMPTY);
        grid[x][y] = OBSTACLE;
    }

    for (int i = 0; i < movingObstacleCount; ++i) {
        int x, y;
        do {
            x = rand() % rows;
            y = rand() % cols;
        } while (grid[x][y] != EMPTY);
        grid[x][y] = MOVING_OBSTACLE;
        movingObstacles.push_back(make_pair(x, y));
    }
}

// Draw grid
void drawGrid() {
    clearScreens();
    for (int i = 0; i < cols + 2; ++i) cout << "⬛";
    cout << endl;

    for (int i = 0; i < rows; ++i) {
        cout << "⬛";
        for (int j = 0; j < cols; ++j) {
            cout << grid[i][j];
        }
        cout << "⬛\n";
    }

    for (int i = 0; i < cols + 2; ++i) cout << "⬛";
    cout << endl;
}

// Move dog
bool moveDog(char input, bool &hitObstacle) {
    int dx = 0, dy = 0;
    if (input == 'w' || input == 'W') dx = -1;
    if (input == 's' || input == 'S') dx = 1;
    if (input == 'a' || input == 'A') dy = -1;
    if (input == 'd' || input == 'D') dy = 1;

    int newX = dogX + dx;
    int newY = dogY + dy;

    if (newX < 0 || newX >= rows || newY < 0 || newY >= cols) return false;

    if (grid[newX][newY] == OBSTACLE || grid[newX][newY] == MOVING_OBSTACLE) {
        hitObstacle = true;
        return false; // Don't declare a win
    }

    grid[dogX][dogY] = EMPTY;
    dogX = newX;
    dogY = newY;
    grid[dogX][dogY] = DOG;

    return (dogX == toyX && dogY == toyY);
}

// Game loop
void playGame() {
    bool won = false;
    bool hitObstacle = false;
    int tick = 0;

    while (!won && !hitObstacle) {
        drawGrid();
        if (kbhit()) {
            char input = getInput();
            won = moveDog(input, hitObstacle);
        }

        usleep(150000);

        if (tick++ % 10 == 0 && movingObstacleCount > 0) {
            vector<pair<int, int>> newPositions;
            for (auto &obs : movingObstacles) {
                int x = obs.first, y = obs.second;
                grid[x][y] = EMPTY;
                int dir = rand() % 4;
                int nx = x, ny = y;
                if (dir == 0 && x > 0) nx--;
                if (dir == 1 && x < rows - 1) nx++;
                if (dir == 2 && y > 0) ny--;
                if (dir == 3 && y < cols - 1) ny++;

                if (grid[nx][ny] == DOG) {
                    hitObstacle = true;
                    grid[nx][ny] = MOVING_OBSTACLE;
                    newPositions.push_back({nx, ny});
                    continue;
                }

                if (grid[nx][ny] == EMPTY) {
                    grid[nx][ny] = MOVING_OBSTACLE;
                    newPositions.push_back({nx, ny});
                } else {
                    grid[x][y] = MOVING_OBSTACLE;
                    newPositions.push_back({x, y});
                }
            }
            movingObstacles = newPositions;
        }
    }

    drawGrid();
    if (won)
        cout << "\n🎉 You found the toy! You win! 🧸🐾\n";
    else
        cout << "\n💥 You hit an obstacle! Game Over!\n";

    cout << "Return to main menu? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') return;
    else {
        initializeGrid();
        playGame();
    }
}

// Level 5 entry point
void startLevel5() {
    showInstructions();
    chooseDifficulty();
    initializeGrid();
    playGame();
}