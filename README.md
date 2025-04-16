# 🎮 Brick Breaker (Console Game in C++)

A simple retro-style **Brick Breaker** game built in C++ for the Windows console using ASCII characters. Destroy all the bricks using a bouncing ball while controlling a slider. Avoid missing the ball or you'll lose a life!

---

## Team Members

* Nirmal Nakum - 202401022
* Ayush Donga - 202401052
* Rajveersinh Gohil - 202401057

 ## Files
 game code :- [modifiedgame.cpp](./modifiedgame.cpp)

 ## Game Photoes And Videos

![Screenshot 2025-04-17 000854](https://github.com/user-attachments/assets/e4166e64-bd24-4329-809b-d647de9fe8fc)

![Screenshot 2025-04-17 000944](https://github.com/user-attachments/assets/6b7d7279-eba7-4f1a-b823-87ac0d701804)

![Screenshot 2025-04-17 001037](https://github.com/user-attachments/assets/e7055db9-37bf-492f-b706-fdd186589144)




## 📌 Features

- Colored bricks in rows
- Real-time ball movement and collision
- Paddle (slider) control with keyboard
- Score tracking
- Lives system (3 chances)
- Win and Game Over screens
- Clean menu with game instructions

---

## 🛠️ Technologies Used

- **C++**
- Windows Console API (`windows.h`, `conio.h`)
- ASCII graphics

---

## Code Structure

The code is organized into several functions:

-   `gotoxy(int x, int y)`: Sets the cursor position in the console.
-   `setcursor(bool visible, DWORD size)`: Controls the visibility and size of the console cursor.
-   `setColor(int color)`: Sets the text color in the console.
-   `drawBorder()`: Draws the game boundaries.
-   `drawBricks()`: Draws the initial set of bricks.
-   `drawSlider()`: Draws the player's slider.
-   `eraseSlider()`: Erases the slider from its previous position.
-   `drawBall()`: Draws the game ball.
-   `eraseBall()`: Erases the ball from its previous position.
-   `drawScore()`: Displays the current score.
-   `drawLives()`: Displays the remaining lives.
-   `resetBallAndSlider()`: Resets the ball and slider to their starting positions.
-   `ballHitSlider()`: Handles ball collision with the slider.
-   `ballHitBrick()`: Handles ball collision with the bricks.
-   `play()`: Contains the main game loop.
-   `instructions()`: Displays the game instructions.
-   `main()`: The entry point of the program, handles the main menu.

## 🎮 Controls

| Key        | Action                         |
|------------|--------------------------------|
| `A` / ←    | Move slider to the left        |
| `D` / →    | Move slider to the right       |
| `Spacebar` | Launch the ball                |
| `ESC`      | Exit game / go to menu         |

---

## 🧱 Bricks

- **3 rows** of colored bricks:
  - Top row: Light Red
  - Middle row: Light Yellow
  - Bottom row: Light Green
- Bricks are removed upon collision with the ball
- Ball reflects vertically after hitting a brick

---

## ❤️ Lives System

- Player starts with **3 lives**
- Lose 1 life if the ball falls below the slider
- Game Over once all lives are lost
- Victory if all bricks are destroyed

---

## 🧠 How It Works (Logic Overview)

- The game initializes a 52×20 console screen with borders.
- Bricks are placed in a grid and tracked using a visibility array.
- Ball and slider positions are managed in a loop with collision checks.
- The ball moves in 4 diagonal directions (`dir` from 1 to 4).
- If the ball hits the slider, bricks, or wall, direction changes accordingly.
- Score and lives are updated dynamically.

---

## 🚀 How to Run

1. **Compile the code** using any Windows-compatible C++ compiler:
   ```bash
   g++ brick_breaker.cpp -o brick_breaker
