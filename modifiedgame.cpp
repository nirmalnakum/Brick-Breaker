// Same headers and initial defines
#include<iostream>
#include<conio.h>
#include<windows.h>

#define SCREEN_WIDTH 52
#define SCREEN_HEIGHT 20

#define MINX 2
#define MINY 2
#define MAXX 49
#define MAXY 19

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int bricks[24][2] = {
    {2,7},{2,12},{2,17},{2,22},{2,27},{2,32},{2,37},{2,42},
    {4,7},{4,12},{4,17},{4,22},{4,27},{4,32},{4,37},{4,42},
    {6,7},{6,12},{6,17},{6,22},{6,27},{6,32},{6,37},{6,42}
};

int visibleBricks[24];
int sliderPos[2];
int ballPos[2];
int startBall;
int dir;
int bricksLeft;
int win;
int lose;
int score;
int lives;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if(size == 0) size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setColor(int color) {
    SetConsoleTextAttribute(console, color);
}

void drawBorder() {
    gotoxy(0,0); cout<<"----------------------------------------------------";
    gotoxy(0,SCREEN_HEIGHT); cout<<"----------------------------------------------------";

    for(int i=0; i<SCREEN_HEIGHT; i++) {
        gotoxy(0,i); cout<<"|";
        gotoxy(SCREEN_WIDTH,i); cout<<"|";
    }
}

void drawBricks() {
    for(int i=0; i<24; i++) {
        if(visibleBricks[i] == 1) {
            int y = bricks[i][0];

            if(y == 2) setColor(12);     // Light Red
            else if(y == 4) setColor(14); // Light Yellow
            else if(y == 6) setColor(10); // Light Green

            gotoxy(bricks[i][1], y);
            cout<<"####";
        }
    }
    setColor(7); // Reset
}

void drawSlider() {
    gotoxy(sliderPos[1], sliderPos[0]);
    cout<<"=========";
}

void eraseSlider() {
    gotoxy(sliderPos[1], sliderPos[0]);
    cout<<"         ";
}

void drawBall() {
    gotoxy(ballPos[1], ballPos[0]);
    cout<<"O";
}

void eraseBall() {
    gotoxy(ballPos[1], ballPos[0]);
    cout<<" ";
}

void drawScore() {
    gotoxy(55, 2);
    setColor(11);
    cout<<"Score : "<<score;
    setColor(7);
}

void drawLives() {
    gotoxy(55, 4);
    setColor(14);
    cout<<"Lives : "<<lives;
    setColor(7);
}

void resetBallAndSlider() {
    sliderPos[0] = 18; sliderPos[1] = 22;
    ballPos[0] = 17; ballPos[1] = 26;
    startBall = 0;
    dir = 1;
    drawSlider();
    drawBall();
}

void ballHitSlider() {
    if(ballPos[0] == sliderPos[0]-1) {
        if(ballPos[1] >= sliderPos[1] && ballPos[1] <= sliderPos[1]+8) {
            if(dir == 3) dir = 2;
            else if(dir == 4) dir = 1;
        }
    }
}

void ballHitBrick() {
    for(int i=0; i<24; i++) {
        if(visibleBricks[i] == 1) {
            int brickX = bricks[i][0];
            int brickY = bricks[i][1];

            if(ballPos[0] == brickX && ballPos[1] >= brickY && ballPos[1] <= brickY + 3) {
                visibleBricks[i] = 0;
                bricksLeft--;
                score++;
                drawScore();

                // Reverse vertical direction only
                if(dir == 1) dir = 4;
                else if(dir == 2) dir = 3;
                else if(dir == 3) dir = 2;
                else if(dir == 4) dir = 1;

                break;
            }
        }
    }
}

void play() {
    for(int i=0; i<24; i++) visibleBricks[i] = 1;
    resetBallAndSlider();
    bricksLeft = 24;
    win = 0;
    lose = 0;
    score = 0;
    lives = 3;

    system("cls");
    drawBorder();
    drawBricks();
    drawSlider();
    drawBall();
    drawScore();
    drawLives();

    while(lives > 0 && win == 0) {
        eraseBall();
        eraseSlider();

        if(kbhit()) {
            char ch = getch();
            if(ch == 'd' || ch == 'D' || ch == 77) {
                if(sliderPos[1] < 40) sliderPos[1] += 2;
            }
            if(ch == 'a' || ch == 'A' || ch == 75) {
                if(sliderPos[1] > 2) sliderPos[1] -= 2;
            }
            if(ch == 32 && startBall == 0) {
                startBall = 1;
            }
            if(ch == 27) {
                break;
            }
        }

        if(startBall == 1) {
            if(dir == 1) { ballPos[0] -= 1; ballPos[1] += 1; }
            else if(dir == 2) { ballPos[0] -= 1; ballPos[1] -= 1; }
            else if(dir == 3) { ballPos[0] += 1; ballPos[1] -= 1; }
            else if(dir == 4) { ballPos[0] += 1; ballPos[1] += 1; }

            if(ballPos[1] >= MAXX) dir = (dir == 1) ? 2 : 3;
            if(ballPos[1] <= MINX) dir = (dir == 2) ? 1 : 4;
            if(ballPos[0] <= MINY) dir = (dir == 1) ? 4 : 3;
            if(ballPos[0] >= MAXY) {
                lives--;
                drawLives();
                startBall = 0;
                resetBallAndSlider();
                Sleep(1000); // Small delay before next life
                if (lives == 0) {
                    lose = 1;
                    break;
                }
                continue; // Skip ballHit checks for this frame
            }

            ballHitSlider();
            ballHitBrick();

            if(bricksLeft == 0) {
                win = 1;
                break;
            }
        }

        drawSlider();
        drawBall();

        Sleep(120);
    }

    system("cls");
    if(lose == 1) {
        gotoxy(10,5); cout<<" --------------------- ";
        gotoxy(10,6); cout<<" |     GAME OVER     | ";
        gotoxy(10,7); cout<<" --------------------- ";
    } else if(win == 1) {
        gotoxy(10,5); cout<<" --------------------- ";
        gotoxy(10,6); cout<<" |     YOU WIN       | ";
        gotoxy(10,7); cout<<" --------------------- ";
    }

    gotoxy(10,9);  cout<<" ------------------------ ";
    gotoxy(10,10); cout<<" |  Final Score : "<<score<<"    |";
    gotoxy(10,11); cout<<" ------------------------ ";

    gotoxy(10,13); cout<<"Press ESC key to go back to Menu.";
    while(true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) break; // ESC
        }
    }
}

void instructions() {
    system("cls");
    cout<<"Instructions";
    cout<<"\n----------------";
    cout<<"\n1. Use 'A' or Left Arrow key to move slider to left.";
    cout<<"\n2. Use 'D' or Right Arrow key to move slider to right.";
    cout<<"\n3. Press Spacebar to launch the ball.";
    cout<<"\n4. You have 3 lives.";
    cout<<"\n5. Lose a life if the ball goes below the slider.";
    cout<<"\n6. Press ESC to exit game.";
    cout<<"\n\nPress any key to go back to menu.";
    getch();
}

int main() {
    setcursor(0,0);

    while(1) {
        system("cls");
        gotoxy(10,5); cout<<" -------------------------- ";
        gotoxy(10,6); cout<<" |     BRICK BREAKER      | ";
        gotoxy(10,7); cout<<" --------------------------";
        gotoxy(10,9); cout<<"1. Start Game";
        gotoxy(10,10); cout<<"2. Instructions";
        gotoxy(10,11); cout<<"3. Quit";
        gotoxy(10,13); cout<<"Select option: ";
        char op = getche();

        if(op == '1') play();
        else if(op == '2') instructions();
        else if(op == '3') exit(0);
    }

    return 0;
}