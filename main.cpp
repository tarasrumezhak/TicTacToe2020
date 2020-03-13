#include <iostream>


using std::cout;
using std::endl;

class Board {
public:
    int size;
    char board_state[3][3]{};             //= {{' ', ' ', ' '}, {' ', 'X', ' '}, {' ', ' ', ' '}};
    void change_state(int x, int y, char tic) {
        board_state[x][y] = tic;
    };

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
    board.change_state(0, 2, 'X');
    board.draw();
    return 0;
}