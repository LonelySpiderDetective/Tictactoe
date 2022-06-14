#include "Tictactoe.h" 

#include "windows.h"

#include <iostream>
#include <random>

using namespace std;

Tictactoe::Tictactoe() {
    // 随机分配先手：true人先走，false电脑先走
    default_random_engine e;
    bernoulli_distribution b;
    m_flag = b(e);

    // 初始化棋盘
    reset();
}

void Tictactoe::play() {
    // res表示棋局的胜负结果，初始值为平局
    int res = Draw;
    // 一直刷新棋盘，直到分出胜负或结束游戏
    while (true) {
        // 刷新棋盘
        drawGrid();
        // 一直轮流下棋子，直至分出胜负或平局
        while (true) {
            if (m_flag) {   // 轮到人下
                getHumanMove();
            }
            else {  // 轮到电脑下
                getComputerMove();
            }
            // 刷新棋盘
            drawGrid();
            // 判断胜负
            res = checkVictory();
            if (res != None) {  // 如果胜负已分或平局，则跳出循环
                break;
            }

            // 标识符置反，轮到另一方下
            m_flag = !m_flag;
        }

        if (res == Human) { // 如果res == Human，那么人赢了
            cout << "恭喜您，取得了游戏胜利！";
        }
        else if (res == Computer) { // 如果res == Computer，那么人输了
            cout << "很遗憾，您被电脑击败了。";
        }
        else {  // 平局
            cout << "平局。";
        }
        cout << endl << endl;

        // 确定是否再来一局
        cout << "再来一局？( Y / N ) ";
        string r;
        cin >> r;
        if (r != "Y" && r != "y") { // 当选择不玩下一局，即退出游戏，跳出外层死循环
            return;
        }

        // 标识符置反，轮到另一方下
        m_flag = !m_flag;
        // 重新初始化棋盘
        reset();
    }
}

void Tictactoe::reset() {
    for (int x = 0; x < 9; x++) {
        m_field[x] = None;
    }
}

void Tictactoe::drawGrid() {
    // 清空屏幕
    system("cls");

    // 设置屏幕初始坐标，即棋盘左上角位置
    COORD coord = { 0, 2 };
    // 移动控制台光标位置
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // 输出默认棋盘
    cout << " 1 | 2 | 3 " << endl;
    cout << "---+---+---" << endl;
    cout << " 4 | 5 | 6 " << endl;
    cout << "---+---+---" << endl;
    cout << " 7 | 8 | 9 " << endl << endl << endl;

    // 棋盘格子序号
    int serial = 0;
    for (int y = 0; y < 5; y += 2) {    // 纵坐标
        for (int x = 1; x < 11; x += 4) {   // 横坐标
            if (m_field[serial] != None) {  // 如果该格子已经有棋子
                // 设置光标坐标
                COORD coord = { x, 2 + y };
                // 移动控制台光标位置
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                // 判断当前下棋的人还是电脑，如果是人输出○，如果电脑输出×
                string chess = (m_field[serial] == Human) ? "○" : "×";
                cout << chess;
            }

            //棋子个数+1
            serial++;
        }
    }

    coord.Y = 9;    
    // 移动控制台光标位置
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Tictactoe::getHumanMove() {
    // 定义一个人想要下的棋盘格子编号
    int move = 0;
    cout << "请输入你的下一步棋 ( 1 - 9 ) ";
    // 输入格子编号，直至该格子为空
    while (true) {
        cin >> move;
        if (m_field[move - 1] != None) {    // 如果该已经有棋子，则是无效输入需重新输入编号
            cout << "该格子已被占有，请重新选择！" << endl;
        }
        else {  // 如果没有棋子则为有效输入，跳出循环
            break;
        }
    }

    //将输入的编号所对应格子标记为已有人下的棋子
    m_field[move - 1] = Human;
}

void Tictactoe::getComputerMove() {
    // 定义一个电脑想要下的棋盘格子编号
    int move = 0;
    // 随机取得一个编号,只要这个格子里没有棋子
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 8);
    do {
        move = u(e);
    }
    while (m_field[move] != None);

    // 对赢的状态进行枚举
    for (int i = 0; i < 8; i++) {
        // try1、try2和try3表示可能赢的3个格子编号
        int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];

        // 如果try1和try2已经有棋子，并且下棋子的玩家是同一方，而且try3没有棋子
        if (m_field[try1] != None && m_field[try1] == m_field[try2] && m_field[try3] == None) {
            // 电脑会将棋子下在try3这个格子上
            move = try3;
            // 如果try1这个格子的棋子是电脑，那么电脑赢了，游戏结束
            if (m_field[try1] == Computer) {
                break;
            }
        }

        // 如果try1和try3已经有棋子，并且下棋子的玩家是同一方，而且try2没有棋子
        if (m_field[try1] != None && m_field[try1] == m_field[try3] && m_field[try2] == None) {
            // 电脑会将棋子下在try2这个格子上
            move = try2;
            // 如果try1这个格子的棋子是电脑，那么电脑赢了，游戏结束
            if (m_field[try1] == Computer) {
                break;
            }
        }

        // 如果try2和try3已经有棋子，并且下棋子的玩家是同一方，而且try1没有棋子
        if (m_field[try2] != None && m_field[try2] == m_field[try3] && m_field[try1] == None)
        {
            // 电脑会将棋子下在try1这个格子上
            move = try1;
            //如果try2这个格子的棋子是电脑，那么电脑赢了，游戏结束
            if (m_field[try1] == Computer) {
                break;
            }
        }
    }

    //将第move个格子标记为电脑下的棋子
    m_field[move] = Computer;
}

int Tictactoe::checkVictory() {
    // 如果有一行或一列或者对角的三个格子都非空且相等，那么就表示胜负已分
    for (int i = 0; i < 8; i++) {
        if (m_field[iWin[i][0]] != None &&
            m_field[iWin[i][0]] == m_field[iWin[i][1]] && m_field[iWin[i][1]] == m_field[iWin[i][2]]) {
            // 返回赢得一方
            return m_field[iWin[i][0]];
        }
    }

    // i表示棋子个数
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (m_field[i] != None) {
            cnt++;
        }
    }
    // 如果9个格子都有了棋子，那么就是一个平局状态
    if (cnt == 9) {
        return Draw;
    }

    // 否则棋局未完
    return None;
}