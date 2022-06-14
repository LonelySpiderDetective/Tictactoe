#ifndef TICTACTOE_H
#define TICTACTOE_H

// 定义四种情况 人机进行对弈
enum statas { 
    Computer,   // 电脑
    Human,  // 人
    None,   // 空
    Draw   // 平局
};

// 可能赢的情况，一行一列或者是对角非空且相等
const int iWin[8][3] = { 
    { 0, 1, 2 },
    { 3, 4, 5 },
    { 6, 7, 8 },
    { 0, 3, 6 },
    { 1, 4, 7 },
    { 2, 5, 8 },
    { 0, 4, 8 },
    { 2, 4, 6 }
};

class Tictactoe {
public:
    // 构造函数
    Tictactoe();

    // 成员函数
    // 游戏函数
    void play();
//private:
    // 成员函数
    // 初始化棋盘
    void reset();
    // 刷新棋盘
    void drawGrid();
    // 人下棋子
    void getHumanMove();
    // 电脑下棋子
    void getComputerMove();
    // 判断是否已经分出胜负
    int checkVictory();

    // 成员变量
    // 标识符，true表示轮到人，false表示轮到电脑
    bool m_flag;
    // 各个格子的状态：Computer(电脑下的棋子), Human(人下的棋子), None(没有棋子)
    int m_field[9];
};

#endif
