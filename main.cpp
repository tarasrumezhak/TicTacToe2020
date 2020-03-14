#include <iostream>
#include <map>
#include <tuple>

using std::cout;
using std::cin;
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
    char board_state[100][100]{};

    bool is_free(int row, int col){
        if (board_state[row][col] == ' ' && 0 < row < size && 0 < col < size)
            return true;
        else
            return false;
    }

    char get(int row, int col){
        return board_state[row][col];
    }


    void set_X(int i, int j) {
        change_state(i, j, 'X');
    }

    void set_O(int i, int j) {
        change_state(i, j, 'O');
    }

    void draw() {
        cout << "  ";
        for (int l = 0; l < size; ++l) {
            cout << "  " << l << " ";
        }
        cout << endl << "  ";
        for (int l = 0; l < size; ++l) {
            cout << "+---";
        }
        cout << '+' << endl;
        for (int i = 0; i < size; ++i) {
            cout << i << " |";
            for (int j = 0; j < size; ++j) {

                cout << " " << board_state[i][j] << " |";
            }
            cout << endl << "  ";
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


class Player{
public:
    virtual std::tuple<int, int> make_move(Board board)=0;
};


class Human : public Player {
public:
    std::tuple<int, int> make_move(Board board) override{
        std::string row, col;
        cout << "enter coordinates of your mark(row and column): ";
        cin >> row >> col;
        while (!board.is_free(std::stoi(row), std::stoi(col))){
            cout << "You cannot put mark in this cell. Enter coordinates of your mark(row and column): ";
            cin >> row >> col;
        };
        return std::make_tuple(std::stoi(row), std::stoi(col));
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


class Game {
private:

    Board board;
    Player* player1;
    Player* player2;
    int size;
    int moves_cntr = 0;

    void player1_make_move(){
        int row, col;
        cout << "Player 1, ";
        std::tie(row, col) = player1->make_move(board);
        board.set_X(row, col);
        moves_cntr += 1;
    }

    void player2_make_move(){
        int row, col;
        cout << "Player 2, ";
        std::tie(row, col) = player2->make_move(board);
        board.set_O(row, col);
        moves_cntr += 1;
    }

    int is_game_over(){

        if (moves_cntr >= (size + size - 1)) {
            for (int i = 0; i < size; i++) {
                char value = board.get(i, 0);
                if (value == ' ')
                    continue;
                bool equal = true;
                for (int j = 1; j < size; j++)
                    if (board.get(i, j) != value) {
                        equal = false;
                        break;
                    }

                if (equal)
                    if (board.get(i, 0) == 'X')
                        return 1;
                    else
                        return 2;
            }

            for (int i = 0; i < size; i++) {
                char value = board.get(0, i);
                if (value == ' ')
                    continue;
                bool equal = true;
                for (int j = 1; j < size; j++)
                    if (board.get(j, i) != value) {
                        equal = false;
                        break;
                    }

                if (equal)
                    if (board.get(0, i) == 'X')
                        return 1;
                    else
                        return 2;
            }

            char value = board.get(0, 0);
            if (value != ' ') {
                bool equal = true;
                for (int j = 1; j < size; j++)
                    if (board.get(j, j) != value) {
                        equal = false;
                        break;
                    }
                if (equal)
                    if (board.get(0, 0) == 'X')
                        return 1;
                    else
                        return 2;

            }
        }

        if (moves_cntr >= size * size){
            return 3;
        }
        return 0;
    }

public:

    Game(int s = 3): board(s), size(s){

        std::map<std::string, Player*> input_map;
        input_map.insert(std::make_pair("h", new Human()));
//        input_map.insert(std::make_pair("cr", new ComputerRandom()));
//        input_map.insert(std::make_pair("cb", new MinMax()));

        std::string p1;
        std::string p2;
        cout << "Choose first player [h/cr/cb]: ";
        cin >> p1;
        cout << "Choose second player [h/cr/cb]: ";
        cin >> p2;
        player1 = input_map[p1];
        player2 = input_map[p2];

    }

    void play(){
    int res = this->is_game_over();
        while (res == 0){
            board.draw();
            player1_make_move();
            res = this->is_game_over();
            if (res != 0)
                break;
            board.draw();
            player2_make_move();
            res = this->is_game_over();
        }

        board.draw();
        if (res == 1){
            cout << "Game over. Player 1 won." << endl;
        } else if (res == 2){
            cout << "Game over. Player 2 won." << endl;
        } else {
            cout << "Game over. Draw." << endl;
        }

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
//    Board board(3);
//    board.set_X(0, 2);
//    board.set_O(0, 0);
//    board.set_X(1, 2);
////    board.set_O(1, 0);
//    board.draw();
//    MinMax alg(board.board_state, 'O');
//    int row, col;
//    std::tie(row, col) = alg.findBestMove();
//    board.set_O(row, col);
//    board.draw();

    Game game;
    game.play();
    return 0;
}