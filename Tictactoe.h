#ifndef TICTACTOE_H
#define TICTACTOE_H

// ����������� �˻����ж���
enum statas { 
    Computer,   // ����
    Human,  // ��
    None,   // ��
    Draw   // ƽ��
};

// ����Ӯ�������һ��һ�л����ǶԽǷǿ������
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
    // ���캯��
    Tictactoe();

    // ��Ա����
    // ��Ϸ����
    void play();
//private:
    // ��Ա����
    // ��ʼ������
    void reset();
    // ˢ������
    void drawGrid();
    // ��������
    void getHumanMove();
    // ����������
    void getComputerMove();
    // �ж��Ƿ��Ѿ��ֳ�ʤ��
    int checkVictory();

    // ��Ա����
    // ��ʶ����true��ʾ�ֵ��ˣ�false��ʾ�ֵ�����
    bool m_flag;
    // �������ӵ�״̬��Computer(�����µ�����), Human(���µ�����), None(û������)
    int m_field[9];
};

#endif
