#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define RECT_WIDTH 11
#define RECT_HEIGHT 5
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 콘솔 화면 지우기 함수
void clearScreen() {
    system("cls");
}

// 화면 중앙에 회전된 사각형을 빈틈 없이 그리기
void drawFilledRotatedRectangle(float angle) {
    // 콘솔 화면 지우기
    clearScreen();

    // 화면에 출력할 캐릭터 배열 초기화
    char screen[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }

    // 화면 중심 좌표
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    // 각도에 따른 회전 변환
    float rad = angle * M_PI / 180.0f;
    float cosA = cos(rad);
    float sinA = sin(rad);

    // 회전된 사각형의 각 좌표를 계산하고, 내부 픽셀을 채우기
    for (float y = -RECT_HEIGHT / 2.0f; y <= RECT_HEIGHT / 2.0f; y += 0.25f) {
        for (float x = -RECT_WIDTH / 2.0f; x <= RECT_WIDTH / 2.0f; x += 0.5f) {
            int rotatedX = (int)(x * cosA - y * sinA + centerX);
            int rotatedY = (int)(x * sinA + y * cosA + centerY);

            // 화면 범위 내에 있는 좌표에 `*`로 채우기
            if (rotatedX >= 0 && rotatedX < WIDTH && rotatedY >= 0 && rotatedY < HEIGHT) {
                screen[rotatedY][rotatedX] = '*';
            }
        }
    }

    // 화면 출력
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

// 메인 함수
int main() {
    float angle = 0.0f;

    while (1) {
        drawFilledRotatedRectangle(angle);  // 현재 각도에 따라 회전된 사각형 그리기
        Sleep(100);  // 0.1초 대기
        angle += 6.0f;  // 각도를 6도씩 증가
        if (angle >= 360.0f) {
            angle = 0.0f;  // 360도 이상이면 0도로 초기화
        }
    }

    return 0;
}
