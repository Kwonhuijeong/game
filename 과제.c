#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w; // 3D 벡터
} vec3;

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 3x3 행렬 초기화
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx; // X축 이동
    mat.m[1][2] = ty; // Y축 이동
    return mat;
}

// 회전 행렬 생성
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian); // cos(θ)
    mat.m[0][1] = -sin(radian); // -sin(θ)
    mat.m[1][0] = sin(radian); // sin(θ)
    mat.m[1][1] = cos(radian); // cos(θ)
    return mat;
}

// 행렬 곱셈
Matrix3x3 Mul(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// 점을 변환
vec3 MulVec(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = a.x * b.m[0][0] + a.y * b.m[0][1] + a.w * b.m[0][2];
    result.y = a.x * b.m[1][0] + a.y * b.m[1][1] + a.w * b.m[1][2];
    result.w = a.w; // w는 그대로
    return result;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(int earthAngle, int moonAngle) {
    clearScreen();
    int pX = WIDTH / 2; // 태양 위치
    int pY = HEIGHT / 2;

    // 지구와 달 초기 위치 (비율을 줄임)
    vec3 earthPos = { 8.0f, 0.0f, 1.0f }; // 지구 위치
    vec3 moonPos = { 2.0f, 0.0f, 1.0f };  // 달 상대 위치

    // 태양 주위의 지구 회전
    Matrix3x3 earthRotation = createRotationMatrix(earthAngle);
    Matrix3x3 earthTranslation = createTranslationMatrix(pX, pY);
    Matrix3x3 combinedEarth = Mul(earthTranslation, earthRotation);
    earthPos = MulVec(earthPos, combinedEarth);

    // 지구 주위의 달 회전
    Matrix3x3 moonRotation = createRotationMatrix(moonAngle);
    Matrix3x3 moonTranslation = createTranslationMatrix(earthPos.x, earthPos.y);
    Matrix3x3 combinedMoon = Mul(moonTranslation, moonRotation);
    moonPos = MulVec(moonPos, moonRotation);

    // 화면 그리기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("S"); // 태양 출력
            }
            else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // 지구 출력
            }
            else if ((int)(earthPos.x + moonPos.x) == x && (int)(earthPos.y + moonPos.y) == y) {
                printf("M"); // 달 출력
            }
            else {
                printf(" "); // 빈 공간 출력
            }
        }
        printf("\n");
    }
}

int main() {
    for (int angle = 0; angle < 360; angle += 5) {
        draw(angle, angle * 5); // 회전 각도에 따라 그리기
        Sleep(100); // 0.1초 대기
    }
    return 0;
}
