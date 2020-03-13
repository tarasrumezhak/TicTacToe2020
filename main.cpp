#include <iostream>


using std::cout;
using std::endl;

class Board {
private:
    void change_state(int i, int j, char tic) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            board_state[i][j] = tic;
        }
    };
public:
    int size;
    char board_state[3][3]{};             //= {{' ', ' ', ' '}, {' ', 'X', ' '}, {' ', ' ', ' '}};
    void set_X(int i, int j) {
        change_state(i, j, 'X');
    }

    void set_O(int i, int j) {
        change_state(i, j, 'O');
    }

    void draw() {
        for (int l = 0; l < size; ++l) {
            cout << "+---";
        }
        cout << '+' << endl;
        for (int i = 0; i < size; ++i) {
            cout << "|";
            for (int j = 0; j < size; ++j) {

                cout << " " << board_state[i][j] << " |";
            }
            cout << endl;
            for (int k = 0; k < size; ++k) {
                cout << "+---";
            }
            cout << '+' << endl;


        }
    };
    explicit Board(int s) {
        size = s;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board_state[i][j] = ' ';
            }
        }
    }

};
int main() {
    Board board(3);
    board.draw();
    board.set_X(0, 2);
    board.draw();
    return 0;
}