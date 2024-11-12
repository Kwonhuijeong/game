#include <stdio.h>
#include <math.h>
#include <windows.h>

// 화면 크기와 사각형 크기 정의
#define WIDTH 40           // 콘솔 창 너비
#define HEIGHT 20          // 콘솔 창 높이
#define RECT_WIDTH 11      // 사각형 너비
#define RECT_HEIGHT 5      // 사각형 높이

// M_PI가 정의되지 않은 경우 수동으로 정의
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 콘솔 화면 지우기 함수
void clearScreen() {
    system("cls");  // Windows에서 화면을 지우는 명령어
}

// 화면 중앙에 회전된 사각형을 그리는 함수
void drawFilledRotatedRectangle(float angle) {
    // 현재 각도에 따라 회전된 사각형을 그리기 전 콘솔 화면을 지움
    clearScreen();

    // 출력할 화면을 초기화할 문자 배열 생성
    char screen[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';  // 빈 화면을 공백 문자로 초기화
        }
    }

    // 화면 중심 좌표
    int centerX = WIDTH / 2;  // X축 중심 좌표
    int centerY = HEIGHT / 2; // Y축 중심 좌표

    // 각도(도 단위)를 라디안으로 변환
    float rad = angle * M_PI / 180.0f;
    float cosA = cos(rad);  // 각도의 코사인 값 계산
    float sinA = sin(rad);  // 각도의 사인 값 계산

    // 회전된 사각형의 각 좌표를 계산하고, 내부를 '*'로 채우기
    for (float y = -RECT_HEIGHT / 2.0f; y <= RECT_HEIGHT / 2.0f; y += 0.25f) {
        for (float x = -RECT_WIDTH / 2.0f; x <= RECT_WIDTH / 2.0f; x += 0.5f) {
            // 회전 변환 공식을 사용해 회전 후 좌표 계산
            int rotatedX = (int)(x * cosA - y * sinA + centerX);  // 회전된 X 좌표
            int rotatedY = (int)(x * sinA + y * cosA + centerY);  // 회전된 Y 좌표

            // 화면 범위 내에 있는 경우만 '*'를 넣어 채우기
            if (rotatedX >= 0 && rotatedX < WIDTH && rotatedY >= 0 && rotatedY < HEIGHT) {
                screen[rotatedY][rotatedX] = '*';  // 사각형 영역을 '*'로 채우기
            }
        }
    }

    // 완성된 화면 배열을 콘솔에 출력
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);  // 화면 배열을 출력
        }
        printf("\n");  // 줄바꿈
    }
}

// 메인 함수
int main() {
    float angle = 0.0f;  // 초기 각도 설정

    // 무한 루프를 돌면서 화면을 계속해서 갱신하여 회전 애니메이션 구현
    while (1) {
        drawFilledRotatedRectangle(angle);  // 현재 각도에 따라 회전된 사각형을 그림
        Sleep(100);  // 0.1초 대기 (회전 속도 조절)
        
        angle += 6.0f;  // 각도를 6도씩 증가
        if (angle >= 360.0f) {
            angle = 0.0f;  // 360도 이상이 되면 0도로 초기화 (한 바퀴 완료)
        }
    }

    return 0;  // 프로그램 종료
}
