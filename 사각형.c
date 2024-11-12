#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40           // 콘솔 창 너비
#define HEIGHT 20          // 콘솔 창 높이
#define RECT_WIDTH 11      // 사각형 너비
#define RECT_HEIGHT 5      // 사각형 높이

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void clearScreen() {
    system("cls");
}

void drawFilledRotatedRectangle(float angle) {
    clearScreen();

    char screen[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }

    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    float rad = angle * M_PI / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);

    for (float y = -RECT_HEIGHT / 2.0f; y <= RECT_HEIGHT / 2.0f; y += 0.25f) {
        for (float x = -RECT_WIDTH / 2.0f; x <= RECT_WIDTH / 2.0f; x += 0.5f) {
            int rotatedX = (int)(x * cosA - y * sinA + centerX);
            int rotatedY = (int)(x * sinA + y * cosA + centerY);

            if (rotatedX >= 0 && rotatedX < WIDTH && rotatedY >= 0 && rotatedY < HEIGHT) {
                screen[rotatedY][rotatedX] = '*';
            }
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

int main() {
    float angle = 0.0f;

    while (1) {
        drawFilledRotatedRectangle(angle);
        Sleep(100);      // 0.1초 대기
        angle += 12.0f;  // 각도를 12도씩 증가시켜 3초에 1바퀴 회전

        if (angle >= 360.0f) {
            angle = 0.0f;
        }
    }

    return 0;
}
