#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 3D 벡터 구조체 정의
typedef struct {
    float x, y, w; // x, y 좌표 및 w 값
} vec3;

// 3x3 행렬 구조체 정의
typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 3x3 행렬 초기화 함수
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1.0f : 0.0f; // 대각선은 1, 나머지는 0
        }
    }
}

// 이동 행렬 생성 함수
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat); // 단위 행렬로 초기화
    mat.m[0][2] = tx; // X축 이동
    mat.m[1][2] = ty; // Y축 이동
    return mat;
}

// 회전 행렬 생성 함수
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat); // 단위 행렬로 초기화
    float radian = angle * M_PI / 180; // 각도를 라디안으로 변환
    mat.m[0][0] = cos(radian); // cos(θ)
    mat.m[0][1] = -sin(radian); // -sin(θ)
    mat.m[1][0] = sin(radian); // sin(θ)
    mat.m[1][1] = cos(radian); // cos(θ)
    return mat;
}

// 행렬 곱셈 함수
Matrix3x3 Mul(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // 행렬 곱셈 계산
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// 벡터 변환 함수
vec3 MulVec(vec3 a, Matrix3x3 b) {
    vec3 result;
    // 변환된 좌표 계산
    result.x = a.x * b.m[0][0] + a.y * b.m[0][1] + a.w * b.m[0][2];
    result.y = a.x * b.m[1][0] + a.y * b.m[1][1] + a.w * b.m[1][2];
    result.w = a.w; // w 값은 그대로 유지
    return result;
}

// 콘솔 화면 지우기 함수
void clearScreen() {
    system("cls"); // 콘솔 화면 지우기
}

// 화면 그리기 함수
void draw(int earthAngle, int moonAngle) {
    clearScreen(); // 화면 지우기
    int pX = WIDTH / 2; // 태양 위치 (중앙)
    int pY = HEIGHT / 2;

    // 지구와 달의 초기 위치 (스케일 조정)
    vec3 earthPos = { 8.0f, 0.0f, 1.0f }; // 지구 위치
    vec3 moonPos = { 2.0f, 0.0f, 1.0f };  // 달의 상대 위치

    // 태양 주위의 지구 회전
    Matrix3x3 earthRotation = createRotationMatrix(earthAngle); // 지구 회전 행렬 생성
    Matrix3x3 earthTranslation = createTranslationMatrix(pX, pY); // 태양 위치로 이동
    Matrix3x3 combinedEarth = Mul(earthTranslation, earthRotation); // 이동과 회전 결합
    earthPos = MulVec(earthPos, combinedEarth); // 변환된 지구 위치

    // 지구 주위의 달 회전
    Matrix3x3 moonRotation = createRotationMatrix(moonAngle); // 달 회전 행렬 생성
    Matrix3x3 moonTranslation = createTranslationMatrix(earthPos.x, earthPos.y); // 지구 위치로 이동
    Matrix3x3 combinedMoon = Mul(moonTranslation, moonRotation); // 이동과 회전 결합
    moonPos = MulVec(moonPos, combinedMoon); // 변환된 달 위치

    // 화면 그리기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // 각 천체의 위치에 따라 출력
            if (x == pX && y == pY) {
                printf("S"); // 태양 출력
            } else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // 지구 출력
            } else if ((int)(earthPos.x + moonPos.x) == x && (int)(earthPos.y + moonPos.y) == y) {
                printf("M"); // 달 출력
            } else {
                printf(" "); // 빈 공간 출력
            }
        }
        printf("\n"); // 다음 줄로 이동
    }
}

// 메인 함수
int main() {
    for (int angle = 0; angle < 360; angle += 5) { // 각도 0부터 360도까지 5도씩 증가
        draw(angle, angle * 5); // 현재 각도에 따라 화면 그리기
        Sleep(100); // 0.1초 대기
    }
    return 0;
}
