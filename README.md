GROUP 150

Group members:
1. Gupta Navya 3036344892
2. Kussainova Adel 3036385731
3. Khanna Prisha 3036344971
4. Chan Pak Tung 3036328173

Contribution:
1. Gupta Navya - Bone Memory Card Game, Tic Tac Toe Game
2. Kussainova Adel - Food Catcher game, Dog Surfers game
3. Khanna Prisha - Dog Quest Game, Simon Stays Game
4. Chan Pak Tung - Word Search Game, video
//Game description written by Adel Kussainova 3036385731

Game title: Doggie Day Care

Game description: 

Join your loyal pup on a tail-wagging journey full of fun, reflex, and puzzle challenges! In
PawQuest you’ll step into the paws of an adventurous dog navigating a world packed with
exciting mini-games. Whether it’s catching falling treats, leaping over obstacles, tic tac toe or 
connecting bones, each game is designed to test your speed, strategy and loyalty! With 8 mini games
of varying difficulty levels, you can immerse yourself in a vibrant world brimming with excitement, 
where every level brings new obstacles to overcome and treasures to sniff out. From fast-paced 
action to brain-teasing puzzles, PawQuest offers something for every type of player. Get ready
bark,bounce, and wag your way through an unforgettable dogventure!

There are 8 unique mini games containing different levels of difficulties. 
Bone Memory Game - a dog-themed memory game where players uncover hidden bones 🦴 on an 8x8 grid filled with colorful decorations like 🌼, 🐝, and 🍄. Each level briefly reveals bone locations before hiding them, challenging players to remember and find them using coordinates (e.g., A1, B4). With five levels from Easy to Impossible and limited-use hints, the game tests memory, accuracy, and strategy—ending with a rewarding reveal.
Tic Tac Toe Game - This is a dog-themed twist on classic Tic-Tac-Toe, where the player (🦴) faces off against a simple AI opponent (💀). Played in the terminal, the game features a friendly interface, emoji-based game pieces, and clear instructions. The first to align three bones or skulls in a row wins!
Food Catcher Game - In Dog Food Catcher, you control a bouncing pup  using 'A' and 'D' keys to move left and right. Your goal is to catch 15 good foods 🍗 while avoiding junk 🗑️ and deadly bombs 💣 (on hard mode). With three difficulty levels, animated instructions, and colorful emoji-based visuals, the game tests your reflexes and focus. Be careful—3 bad catches or one bomb ends the game!
Dog Surfers Game - In this side-scrolling runner, you guide a dog 🐕 across levels by jumping over bushes 🌿, dodging birds 🦅, and avoiding bombs 💣. Using the spacebar or 'J' key, you'll jump through three levels of increasing difficulty. Each level includes animated intros, energy and health tracking, and randomized obstacle spawns—offering a fast-paced and visually fun terminal experience.
Dog Quest Game - Guide your dog 🐶 across a grid full of obstacles to reach its toy 🧸! Avoid static 🚧 and moving 🚗 hazards using W/A/S/D keys. Choose from Easy, Medium, or Hard mode with increasing grid sizes and obstacle difficulty. A strategic and reflex-based puzzle adventure!
Simon Stays Game: Train your memory in this dog-themed Simon Says game! Watch a sequence of commands like “Sit”, “Roll”, “Stay”, and “Jump” 🐾—then repeat it using numbers. Choose from three difficulties and prove you're the ultimate dog trainer 🐕‍🦺.
Word Search Game: Oops, your mischievous dog has eaten your homework again! In this playful word search game, your goal is to find a hidden dog-related word buried in a grid of random letters.  The game features three difficulty levels (Easy, Medium, Hard), each increasing the size of the grid and the complexity of the word to be found.

Implemented features:

//written by  Gupta Navya 3036344892
1. Bone Memory Card game: 
    1. Multiple difficulty levels (Easy to impossible)
    2. Memory Game Mechanics(Memorize Bone Locations) 
    3. Hint System(Limited reveals of the board)
    4. Interactive Grid Interface(Coordinate-based input)
    5. Visual Feedback(Emoji-based UI)
    How coding requirements support features:
    1. Generation of random events : to randomly generate positions of bones and other emojis
    2. Data Structures for Storing Data: vector for game grids and array for level configurations.
    3. Dynamic Memory Management: vectors handle dynamic resizing

// written by Gupta Navya 3036344892
2. Tic Tac Toe Game: 
    1. Classic Tic-Tac-Toe Gameplay with emoji-based visuals(🦴 vs 💀)
    2. AI Opponent 
    3. Input Validation for moves(A1-C3 format) 
    4. Win/Tie Detection for all possible scenarios
    5. Replayability (play again option)
    How coding requirements support features:
    1. Generation of Random Events: to generate the skull at a random cell
    2. Data Structures for Storing Data: vector for 3x3 game board
    3. Dynamic Memory Management
 
//Written by Adel Kussainova 3036385731
3. Food Catcher Game
    1. Multiple difficulty levels (Easy, Medium, Hard): pace becomes faster,
    2. Generation of Random events: random placement of good and bad food falling from the sky
    3. Animation: win/lose animation, animation of instructions before each level, countdown
    4. Interface: the use of emojis, different colors for text, frames, shows score of bad and good food caught 
    5. Keyboard input: A/D for movement, after each level press any button to exit or play level again
    6. Scoring system: the number of good and bad food is shown and updated throughout the whole game
    How coding requirements support features:
    1. Generation of random events: food and trash are randomly generated and fall from sky
    2. Dynamic memory management: use of vector to create a 2D food grid that allocates and manages memory for food items at runtime
    3. Data Structures for Storing data: vector to store data

//Written by Adel Kussainova 3036385731
4. Running Obstacles Game
    1. Multiple difficulty levels(Easy, Medium, Hard): pace becomes faster, more obstacles of different types each level
    2. Animation: moving objects, smooth jump animation, variable jump height, instructions animation, victory/loss animation
    3. Keyboard input: press space or J to jump, after the game to exit press any button
    4. Scoring system and Health: score is shown, health is shown, if dog touches the obstacle health decrements, if jumps over it increments
    5.Movement detection: checks whether the player has hit an obstacle or jumped over it, based on that increments or decrements score and health
    How coding requirements support features:
    1. Generation of random events: obstacles  appear randomly
    2. Data Structures: use of vector or arrays to store obstacle positions and types
    3. Dynamic memory management

//Written by Prisha Khanna 3036344971
5. Dog Quest Game
    1. Multiple Difficulty Levels (Easy, Medium, Hard)
    2. 2D Grid Movement (Navigate using arrow keys)
    3. Static and Moving Obstacles (Different for each level)
    4. Randomized Placement (Dog, Toy, and Obstacles)
    5. Emoji-Based Visual Grid (Dog 🐶, Toy 🧸, Obstacles 🧱)
    How coding requirements support features:
    1. Generation of Random Events: Random placement of the dog, toy, and obstacles at the start of the game.
    2. Data Structures for Storing Data: Vectors are used to store obstacle positions and moving obstacle paths.
    3. Dynamic Memory Management: Vectors handle dynamic resizing during obstacle setup.
    4. Multiple Difficulty Levels: Player can choose different levels which adjust grid size, obstacle count, and moving obstacle behavior.

//Written by Prisha Khanna 3036344971
6. Simon Stays Game
    1. Multiple Difficulty Levels (Easy, Medium, Hard)
    2. Memory Challenge (Repeat growing command sequence)
    3. Random Command Generation (Commands like sit, roll, stay)
    4. Interactive Input System (Select by numbered options)
    5. Emoji and Menu-Based UI for Commands
    How coding requirements support features:
    1. Generation of Random Events: Random generation of the command sequence that the player must memorize.
    2. Data Structures for Storing Data: Vectors are used to store the sequence of commands and player's responses.
    3. Dynamic Memory Management: Vectors allow dynamic resizing as sequences grow longer.
    4. Multiple Difficulty Levels: Player chooses Easy (4 commands), Medium (6 commands), or Difficult (8 commands) at the start.

//written by Adel Kussainova 3036385731
7. Word Search Game: 7. Dog Ate My Homework – Word Search Game
    1. Multiple Difficulty Levels (Easy, Medium, Hard): grid size and word complexity increase
    2. Word Search Gameplay: a single dog-themed word is hidden in the grid (horizontally or vertically)
    3. Puzzle Generation: new randomized puzzle is generated on each play
    4. Hint System: option to reveal the word’s location and direction
    5. Interactive UI: grid displayed with emojis and colored highlights for answers
    6. Input Handling: interactive menu for difficulty and actions (e.g., "Show Answer", "New Puzzle", etc.)
    
    How coding requirements support features:
    1. Generation of Random Events: random selection of dog words and placement direction/position
    2. Data Structures for Storing Data: 2D vectors for grid and boolean highlight overlay
    3. Dynamic Memory Management: grid size dynamically adjusts with selected difficulty
    4. Interactive Text UI: console output uses colors and formatted spacing for clarity
    

// written by Adel Kussainova 3036385731
7. Dog Ate My Homework – Word Search Game
    1. Multiple Difficulty Levels (Easy, Medium, Hard): grid size and word complexity increase
    2. Word Search Gameplay: a single dog-themed word is hidden in the grid (horizontally or vertically)
    3. Puzzle Generation: new randomized puzzle is generated on each play
    4. Hint System: option to reveal the word’s location and direction
    5. Interactive UI: grid displayed with emojis and colored highlights for answers
    6. Input Handling: interactive menu for difficulty and actions (e.g., "Show Answer", "New Puzzle", etc.)
    
    How coding requirements support features:
    1. Generation of Random Events: random selection of dog words and placement direction/position
    2. Data Structures for Storing Data: 2D vectors for grid and boolean highlight overlay
    3. Dynamic Memory Management: grid size dynamically adjusts with selected difficulty
    4. Interactive Text UI: console output uses colors and formatted spacing for clarity
    
    

Non-standard libraries used:
Used in Food Catcher game and Running Obstacles game
1. <ncurses.h> - used for handling graphics in the terminal(drawing borders, color, characters, movement)
2. <unistd.h>  - used for controlling game timing and delays using sleep() and usleep(), supporting frame-rate pacing and animation timing




Compilation and execution instructions:
    download all files into one folder
    open the folder on your terminal
    write command: make
    write command: ./finalgame
    have fun playing!
    


