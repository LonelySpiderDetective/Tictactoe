#include <iostream>
#include <windows.h>
#include "Tictactoe.h"

using namespace std;

int main() {
    // �����ʼ��
    srand(GetTickCount64());

    // ���微������Ϸ��ʵ��������tic
    Tictactoe tic;
    // ���о�������Ϸ
    tic.play();

    return 0;
}

