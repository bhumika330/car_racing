#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 20;
const int height = 17;
int carX = width / 2;
int score = 0;
bool gameOver = false;
char road[height][width];

void initializeRoad() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0 || j == width - 1)
                road[i][j] = '|';
            else
                road[i][j] = ' ';  // Empty space for the car and obstacles
        }
    }
}

void displayRoad() {
    system("cls");
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << road[i][j];
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
    cout << "Controls: 'a' for Left, 'd' for Right" << endl;
}

void placeCar() {
    road[height - 2][carX] = 'A';  // 'A' is the player's car
}

void clearCar() {
    road[height - 2][carX] = ' ';  // Clear previous car position
}

void generateObstacles() {
    // Randomly generate obstacles at the top row
    int randomPos = rand() % (width - 2) + 1;  // Position within road bounds
    road[0][randomPos] = '*';  // '' represents an obstacle
}

void moveObstacles() {
    for (int i = height - 2; i >= 0; --i) {
        for (int j = 1; j < width - 1; ++j) {
            if (road[i][j] == '*') {
                road[i][j] = ' ';  // Clear the obstacle from the current position
                if (i + 1 < height - 1) {
                    road[i + 1][j] = '*';  // Move the obstacle one row down
                }
            }
        }
    }
}

bool checkCollision() {
    if (road[height - 2][carX] == '*') {
        return true;  // Collision detected
    }
    return false;
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        clearCar();  // Remove the car from its current position

        if (key == 'a' || key == 'A') {
            if (carX > 1) carX--;  // Move the car left
        } else if (key == 'd' || key == 'D') {
            if (carX < width - 2) carX++;  // Move the car right
        }

        placeCar();  // Place the car in its new position
    }
}

void updateGame() {
    moveObstacles();
    if (checkCollision()) {
        gameOver = true;
    } else {
        score++;
    }
}

int main() {
    initializeRoad();
    placeCar();

    while (!gameOver) {
        displayRoad();
        input();
        updateGame();

        if (rand() % 5 == 0) {  // Randomly generate obstacles with probability
            generateObstacles();
        }

        Sleep(100);  // Game speed control
    }

    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}
