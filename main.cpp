#include <iostream>
#include <tuple>


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
    char board_state[3][3]{};
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


class MinMax {
public:
    char (&board)[3][3];
    char computer;
    char player;
    MinMax(char (&board1)[3][3], char comp_sign) : board(board1) {
        computer = comp_sign;
        comp_sign == 'X' ? player = 'O': player = 'X';
    }
    bool isFreePlace() {
        for (auto & i : board)
            for (char j : i)
                if (j==' ')
                    return true;
        return false;
    };

    int rowCheck() {
        for (auto & i : board) {
            if (i[0]==i[1] &&
                i[1]==i[2])
            {
                if (i[0]==player)
                    return +10;
                else if (i[0]==computer)
                    return -10;
            }
        }
        return 0;
    };

    int colCheck() {
        for (int i = 0; i<3; i++)
        {
            if (board[0][i]==board[1][i] &&
                board[1][i]==board[2][i])
            {
                if (board[0][i]==player)
                    return +10;

                else if (board[0][i]==computer)
                    return -10;
            }
        }
        return 0;
    };

    int diagCheck() {
        if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
        {
            if (board[0][0]==player)
                return +10;
            else if (board[0][0]==computer)
                return -10;
        }

        if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
        {
            if (board[0][2]==player)
                return +10;
            else if (board[0][2]==computer)
                return -10;
        }

        return 0;
    }

    int evaluate() {
        int res = rowCheck();
        if (res == 0){
            res = colCheck();
            if (res == 0) {
                res = diagCheck();
            }
        }
        return res;
    };

    int minimax(int depth, bool isMax) {
        int score = evaluate();
        if (score == 10)
            return score;
        if (score == -10)
            return score;
        if (!isFreePlace())
            return 0;
        if (isMax) {
            int best = -1000;
            for (auto & i : board) {
                for (char & j : i) {
                    if (j==' ') {
                        j = player;
                        best = std::max( best, minimax(depth+1, !isMax) );
                        j = ' ';
                    }
                }
            }
            return best;
        }
        else {
            int best = 1000;
            for (auto & i : board) {
                for (char & j : i) {
                    if (j==' ') {
                        j = computer;
                        best = std::min(best, minimax(depth+1, !isMax));
                        j = ' ';
                    }
                }
            }
            return best;
        }
    };

    std::tuple<int, int> findBestMove()
    {
        int bestVal = -1000;
        int row = -1;
        int col = -1;

        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                if (board[i][j]==' ') {
                    board[i][j] = player;
                    int moveVal = minimax(0, false);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        return std::make_tuple(row, col);
    }

};



int main() {
//    Board board(3);
//    board.set_X(0, 2);
//    board.set_O(1, 1);
//    board.set_X(1, 2);
//    board.draw();
//    MinMax alg(board.board_state, 'X');
//    int row, col;
//    std::tie(row, col) = alg.findBestMove();
//    board.set_O(row, col);
//    board.draw();
//    std::tie(row, col) = alg.findBestMove();
//    board.set_O(row, col);
//    board.draw();
    Board board(3);
    board.set_X(0, 2);
    board.set_O(0, 0);
    board.set_X(1, 2);
//    board.set_O(1, 0);
    board.draw();
    MinMax alg(board.board_state, 'O');
    int row, col;
    std::tie(row, col) = alg.findBestMove();
    board.set_O(row, col);
    board.draw();
    return 0;
}