# PingPong Game

A simple 2D Ping Pong game built using **C++** and **Raylib**. This project demonstrates the use of game loops, user input handling, and 2D graphics rendering using the Raylib library.

## Features

- Player-vs-Player gameplay.
- Score tracking.
- Pause and resume functionality.
- Game over screen with restart and quit options.
- Smooth paddle and ball movement.
- Randomized ball speeds for dynamic gameplay.

## Requirements

- CMake 3.15 or later
- C++17 or later
- Raylib 5.0

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/PingPong.git
   cd PingPong
   ```

2. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run the executable:
   ```bash
   ./PingPong
   ```

## Controls

### Start Screen
- **Enter**: Start the game

### Gameplay
- **Up Arrow/Down Arrow**: Move Player 1's paddle
- **W/S**: Move Player 2's paddle
- **Space**: Pause/Resume the game
- **Q**: Quit the game

### Game Over Screen
- **Enter**: Restart the game
- **Q**: Quit the game

## File Structure

```
PingPong/
├── CMakeLists.txt      # Build configuration
├── main.cpp            # Game logic and rendering
├── res/                # Assets (e.g., fonts)
├── build/              # Build directory
└── README.md           # This file
```

## Game Preview

- **Start Screen**: Displays a "Press Enter to Start" message with animated elements.
- **Gameplay**: Classic Ping Pong with score tracking and dynamic ball behavior.
- **Game Over Screen**: Announces the winner or a draw and provides restart/quit options.

## Dependencies

- **Raylib**: A simple and easy-to-use library to learn programming games.

Raylib is automatically fetched and built via CMake's `FetchContent` mechanism.

## Configuration

The `CMakeLists.txt` file includes the following configurations:

- **C++ Standard**: Set to C++17.
- **Raylib Integration**: Automatically downloads and links Raylib.

## Acknowledgments

- [Raylib](https://www.raylib.com/) for the graphics library.
- [CMake](https://cmake.org/) for the build system.