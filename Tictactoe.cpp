#include "Tictactoe.h" 

#include "windows.h"

#include <iostream>
#include <random>

using namespace std;

Tictactoe::Tictactoe() {
    // ����������֣�true�����ߣ�false��������
    default_random_engine e;
    bernoulli_distribution b;
    m_flag = b(e);

    // ��ʼ������
    reset();
}

void Tictactoe::play() {
    // res��ʾ��ֵ�ʤ���������ʼֵΪƽ��
    int res = Draw;
    // һֱˢ�����̣�ֱ���ֳ�ʤ���������Ϸ
    while (true) {
        // ˢ������
        drawGrid();
        // һֱ���������ӣ�ֱ���ֳ�ʤ����ƽ��
        while (true) {
            if (m_flag) {   // �ֵ�����
                getHumanMove();
            }
            else {  // �ֵ�������
                getComputerMove();
            }
            // ˢ������
            drawGrid();
            // �ж�ʤ��
            res = checkVictory();
            if (res != None) {  // ���ʤ���ѷֻ�ƽ�֣�������ѭ��
                break;
            }

            // ��ʶ���÷����ֵ���һ����
            m_flag = !m_flag;
        }

        if (res == Human) { // ���res == Human����ô��Ӯ��
            cout << "��ϲ����ȡ������Ϸʤ����";
        }
        else if (res == Computer) { // ���res == Computer����ô������
            cout << "���ź����������Ի����ˡ�";
        }
        else {  // ƽ��
            cout << "ƽ�֡�";
        }
        cout << endl << endl;

        // ȷ���Ƿ�����һ��
        cout << "����һ�֣�( Y / N ) ";
        string r;
        cin >> r;
        if (r != "Y" && r != "y") { // ��ѡ������һ�֣����˳���Ϸ�����������ѭ��
            return;
        }

        // ��ʶ���÷����ֵ���һ����
        m_flag = !m_flag;
        // ���³�ʼ������
        reset();
    }
}

void Tictactoe::reset() {
    for (int x = 0; x < 9; x++) {
        m_field[x] = None;
    }
}

void Tictactoe::drawGrid() {
    // �����Ļ
    system("cls");

    // ������Ļ��ʼ���꣬���������Ͻ�λ��
    COORD coord = { 0, 2 };
    // �ƶ�����̨���λ��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // ���Ĭ������
    cout << " 1 | 2 | 3 " << endl;
    cout << "---+---+---" << endl;
    cout << " 4 | 5 | 6 " << endl;
    cout << "---+---+---" << endl;
    cout << " 7 | 8 | 9 " << endl << endl << endl;

    // ���̸������
    int serial = 0;
    for (int y = 0; y < 5; y += 2) {    // ������
        for (int x = 1; x < 11; x += 4) {   // ������
            if (m_field[serial] != None) {  // ����ø����Ѿ�������
                // ���ù������
                COORD coord = { x, 2 + y };
                // �ƶ�����̨���λ��
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                // �жϵ�ǰ������˻��ǵ��ԣ�������������������������
                string chess = (m_field[serial] == Human) ? "��" : "��";
                cout << chess;
            }

            //���Ӹ���+1
            serial++;
        }
    }

    coord.Y = 9;    
    // �ƶ�����̨���λ��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Tictactoe::getHumanMove() {
    // ����һ������Ҫ�µ����̸��ӱ��
    int move = 0;
    cout << "�����������һ���� ( 1 - 9 ) ";
    // ������ӱ�ţ�ֱ���ø���Ϊ��
    while (true) {
        cin >> move;
        if (m_field[move - 1] != None) {    // ������Ѿ������ӣ�������Ч����������������
            cout << "�ø����ѱ�ռ�У�������ѡ��" << endl;
        }
        else {  // ���û��������Ϊ��Ч���룬����ѭ��
            break;
        }
    }

    //������ı������Ӧ���ӱ��Ϊ�������µ�����
    m_field[move - 1] = Human;
}

void Tictactoe::getComputerMove() {
    // ����һ��������Ҫ�µ����̸��ӱ��
    int move = 0;
    // ���ȡ��һ�����,ֻҪ���������û������
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 8);
    do {
        move = u(e);
    }
    while (m_field[move] != None);

    // ��Ӯ��״̬����ö��
    for (int i = 0; i < 8; i++) {
        // try1��try2��try3��ʾ����Ӯ��3�����ӱ��
        int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];

        // ���try1��try2�Ѿ������ӣ����������ӵ������ͬһ��������try3û������
        if (m_field[try1] != None && m_field[try1] == m_field[try2] && m_field[try3] == None) {
            // ���ԻὫ��������try3���������
            move = try3;
            // ���try1������ӵ������ǵ��ԣ���ô����Ӯ�ˣ���Ϸ����
            if (m_field[try1] == Computer) {
                break;
            }
        }

        // ���try1��try3�Ѿ������ӣ����������ӵ������ͬһ��������try2û������
        if (m_field[try1] != None && m_field[try1] == m_field[try3] && m_field[try2] == None) {
            // ���ԻὫ��������try2���������
            move = try2;
            // ���try1������ӵ������ǵ��ԣ���ô����Ӯ�ˣ���Ϸ����
            if (m_field[try1] == Computer) {
                break;
            }
        }

        // ���try2��try3�Ѿ������ӣ����������ӵ������ͬһ��������try1û������
        if (m_field[try2] != None && m_field[try2] == m_field[try3] && m_field[try1] == None)
        {
            // ���ԻὫ��������try1���������
            move = try1;
            //���try2������ӵ������ǵ��ԣ���ô����Ӯ�ˣ���Ϸ����
            if (m_field[try1] == Computer) {
                break;
            }
        }
    }

    //����move�����ӱ��Ϊ�����µ�����
    m_field[move] = Computer;
}

int Tictactoe::checkVictory() {
    // �����һ�л�һ�л��߶Խǵ��������Ӷ��ǿ�����ȣ���ô�ͱ�ʾʤ���ѷ�
    for (int i = 0; i < 8; i++) {
        if (m_field[iWin[i][0]] != None &&
            m_field[iWin[i][0]] == m_field[iWin[i][1]] && m_field[iWin[i][1]] == m_field[iWin[i][2]]) {
            // ����Ӯ��һ��
            return m_field[iWin[i][0]];
        }
    }

    // i��ʾ���Ӹ���
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (m_field[i] != None) {
            cnt++;
        }
    }
    // ���9�����Ӷ��������ӣ���ô����һ��ƽ��״̬
    if (cnt == 9) {
        return Draw;
    }

    // �������δ��
    return None;
}