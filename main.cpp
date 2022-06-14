#include <iostream>
#include <windows.h>
#include "Tictactoe.h"

using namespace std;

int main() {
    // 随机初始化
    srand(GetTickCount64());

    // 定义井字棋游戏的实例化对象tic
    Tictactoe tic;
    // 运行井字棋游戏
    tic.play();

    return 0;
}

