// Dog Jump game with obstacles and levels
// Made by: Adel Kussainova 3036385731

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <locale.h>
#include <cstring>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>
#include <algorithm>

using namespace std;

// Constants
const int WIDTH = 60;
const int HEIGHT = 20;
const int DOG_X = 5;
const int JUMP_HEIGHT = 4;  
const int GROUND_OFFSET = 3;
const int MAX_ENERGY = 5;
const int MAX_HEALTH = 3;

// Emojis
const string DOG_EMOJI = "🐕";
const string BUSH_EMOJI = "🌿";
const string BIRD_EMOJI = "🦅";
const string BOMB_EMOJI = "💣";

// Difficulty levels
enum GameLevel { EASY, MEDIUM, HARD };

// Obstacle structure
struct Obstacle {
    int x, y;
    string emoji;
    bool scored;
    bool isActive;
    Obstacle(int px, int py, string e) {
        x = px;
        y = py;
        emoji = e;
        scored = false;
        isActive = true;
    }
};

// Custom clear screen for Level4
void customClearLevel4() {
    cout << "\033[2J\033[1;1H";
}

// Cross-platform input handling
void enableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

bool keyPressed() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) > 0;
}

// Draws the game frame
void drawFrame() {
    cout << "\033[0;0H";
    for (int x = 0; x < WIDTH; ++x) cout << "▔";
    cout << "\n";
    
    for (int y = 1; y < HEIGHT; ++y) {
        cout << "┃";
        for (int x = 1; x < WIDTH-1; ++x) cout << " ";
        cout << "┃\n";
    }
    
    for (int x = 0; x < WIDTH; ++x) cout << "▁";
}

// Draws the ground
void drawGround(int y) {
    cout << "\033[" << y << ";0H";
    for (int x = 0; x < WIDTH; x++) cout << "▔";
}

// Shows the instructions for the game
void showInstructions(GameLevel level) {
    customClearLevel4();
    string title = level == EASY ? "🐾 LEVEL 1: EASY - JUMP OVER 🌿" :
                    level == MEDIUM ? "🟡 LEVEL 2: MEDIUM - AVOID 🌿 & 🦅" :
                                       "🔴 LEVEL 3: HARD - AVOID 🌿, 🦅 & 💣";

    vector<string> lines;
    lines.push_back("INSTRUCTIONS:");
    lines.push_back("You are a dog 🐕. Use SPACE or J to jump.");
    lines.push_back("Avoid 🌿 (bushes) on the ground.");
    if (level >= MEDIUM) lines.push_back("Avoid 🦅 (birds) in the air.");
    if (level == HARD) lines.push_back("Avoid 💣 (bombs) - instant loss.");
    lines.push_back("You gain +1 point for jumping OVER any obstacle.");
    lines.push_back("Game starts in:");

    cout << "\033[2;0H" << title << endl;
    for (int i = 0; i < (int)lines.size(); ++i) {
        cout << "\033[" << (4 + i) << ";0H" << lines[i];
        cout.flush();
        usleep(500000);
    }

    for (int i = 3; i >= 1; --i) {
        cout << "\033[13;0H" << i;
        cout.flush();
        sleep(1);
    }
    cout << "\033[14;0HGO";
    cout.flush();
    sleep(1);
    customClearLevel4();
}

// Draws the game screen
void drawGame(int dogY, const vector<Obstacle>& obs, int groundY, int score, int health, int energy, GameLevel level, int target) {
    customClearLevel4();
    drawFrame();
    
    // Draw dog
    cout << "\033[" << dogY << ";" << DOG_X << "H" << DOG_EMOJI;
    
    // Draw obstacles
    for (const auto& o : obs) {
        if (o.x >= 0 && o.x < WIDTH && o.isActive)
            cout << "\033[" << o.y << ";" << o.x << "H" << o.emoji;
    }

    drawGround(groundY + 1);

    // Draw HUD
    cout << "\033[0;0H";
    cout << "Health: " << health << " Energy: " << energy << "\n";
    cout << "Score: " << score << "/" << target << " Level: " 
         << (level == EASY ? "Easy" : level == MEDIUM ? "Medium" : "Hard") << "\n";
    cout << "Jump using SPACE or J. Avoid all obstacles.";
    cout.flush();
}

// Displays a winning animation
void winAnimation(GameLevel level) {
    string msg = "🎉 YOU WON LEVEL " + to_string(level + 1) + "! 🎉";
    for (int i = 0; i < 4; ++i) {
        customClearLevel4();
        cout << msg << endl;
        cout.flush();
        usleep(300000);
    }
    sleep(1);
}

// Displays a losing animation
bool loseAnimation(GameLevel level) {
    string msg = level == HARD ? "💣 You hit a bomb! GAME OVER!" : "💀 You lost Level " + to_string(level + 1);
    customClearLevel4();
    cout << msg << endl;
    cout << "Press any key to retry Level " << (level + 1);
    cout.flush();
    disableRawMode();
    getchar();
    return false;
}

// Main game loop for each level
bool playLevel(GameLevel level) {
    enableRawMode();
    int groundY = HEIGHT - GROUND_OFFSET;
    int dogY = groundY, jumpCounter = 0, score = 0, health = MAX_HEALTH, energy = MAX_ENERGY;
    int energyFrameCounter = 0;
    int target = 10 + 5 * level;
    int obstacleSpeed = 1 + (level == HARD ? 1 : 0);

    vector<Obstacle> obstacles;
    obstacles.push_back(Obstacle(WIDTH, groundY, BUSH_EMOJI));
    if (level >= MEDIUM)
        obstacles.push_back(Obstacle(WIDTH + 20, groundY - 2, BIRD_EMOJI));
    if (level == HARD)
        obstacles.push_back(Obstacle(WIDTH + 40, groundY - 1, BOMB_EMOJI));

    showInstructions(level);

    int frameCount = 0;
    while (true) {
        frameCount++;
        
        char ch = ' ';
        if (keyPressed()) {
            read(STDIN_FILENO, &ch, 1);
            if ((ch == ' ' || ch == 'j' || ch == 'J') && jumpCounter == 0 && energy > 0) {
                jumpCounter = JUMP_HEIGHT * 2;
                energy--;
            }
        }

        if (jumpCounter > 0) {
            dogY = (jumpCounter > JUMP_HEIGHT) ? (groundY - (2 * JUMP_HEIGHT - jumpCounter + 1)) : (groundY - jumpCounter);
            jumpCounter--;
        } else {
            dogY = groundY;
        }

        if (frameCount % (30 - 5 * level) == 0) {
            int type = rand() % (level == EASY ? 1 : (level == MEDIUM ? 2 : 3));
            int yPos = groundY;
            string emoji = BUSH_EMOJI;
            
            if (type == 1 && level >= MEDIUM) {
                yPos = groundY - 2;
                emoji = BIRD_EMOJI;
            } else if (type == 2 && level == HARD) {
                yPos = groundY - 1;
                emoji = BOMB_EMOJI;
            }
            
            obstacles.push_back(Obstacle(WIDTH + rand() % 10, yPos, emoji));
        }

        for (auto& o : obstacles) {
            if (!o.isActive) continue;
            
            o.x -= obstacleSpeed;

            bool isColliding = abs(o.x - DOG_X) <= 1 && dogY == o.y;
            bool isAbove = dogY < o.y && o.x >= DOG_X - 2 && o.x <= DOG_X + 2;

            if (isAbove && !o.scored) {
                score++;
                o.scored = true;
            }
            else if (isColliding && !o.scored) {
                if (o.emoji == BOMB_EMOJI) {
                    disableRawMode();
                    return false;
                }
                health--;
                o.scored = true;
                o.isActive = false;
            }

            if (o.x < -5) o.isActive = false;
        }

        obstacles.erase(remove_if(obstacles.begin(), obstacles.end(), 
            [](const Obstacle& o) { return !o.isActive; }), obstacles.end());

        if (health <= 0) return loseAnimation(level);
        if (score >= target) {
            winAnimation(level);
            return true;
        }

        if (++energyFrameCounter >= 10 && energy < MAX_ENERGY) {
            energy++;
            energyFrameCounter = 0;
        }

        drawGame(dogY, obstacles, groundY, score, health, energy, level, target);
        usleep(50000);
    }
}

// MAIN FUNCTION - PRESERVED EXACTLY AS YOU WROTE IT
void startLevel4() {
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(0));

    for (int lvl = EASY; lvl <= HARD; ++lvl) {
        while (!playLevel(static_cast<GameLevel>(lvl))) {}
    }

    customClearLevel4();
    cout << "🏆 CONGRATS! YOU BEAT ALL LEVELS! 🏆\n";
    cout << "Press any key to finish.\n";
    getchar();
}