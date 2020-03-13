//
// Created by taras on 13.03.20.
//

#include <iostream>
#include "board.h"

using std::cout;
using std::endl;

class Board {
public:
    int size;
    char board_state[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
//    void change_state(int x, int y, char tic) {
//        board_state[x-1][y-1] = tic;
//    };
    void set_cross(int i, int j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            board_state[i][j] = 'X';
        }
    }

    void set_zero(int i, int j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            board_state[i][j] = 'O';
        }
    }
    void draw() {
//        cout << endl;
//        cout << "     |     |     " << endl;
//        cout << "  " << board_state[1][] << "  |  " << square[2] << "  |  " << square[3] << endl;
//
//        cout << "_____|_____|_____" << endl;
//        cout << "     |     |     " << endl;
//
//        cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;
//
//        cout << "_____|_____|_____" << endl;
//        cout << "     |     |     " << endl;
//
//        cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;
//
//        cout << "     |     |     " << endl << endl;

        for (int i = 0; i < size; ++i) {
//            cout << "     |     |     " << endl;
            for (int j = 0; j < size; ++j) {

                cout << "  " << board_state[i][j] << "  |  ";
            }
            cout << "_____|_____|_____" << endl;
            cout << "     |     |     " << endl;

        }
    };
    explicit Board(int s) {
        size = s;
    }

};



