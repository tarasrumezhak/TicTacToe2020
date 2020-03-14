#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>

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
    char board_state[3][3]{};

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
        cout << "\n  ";
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
    char (&board)[3][3];
    char sign;
    Player(char (&input_board)[3][3]):board(input_board){};
    virtual std::tuple<int, int> make_move()=0;
};


class Human : public Player {
public:
    Human(char (&input_board)[3][3]):Player(input_board){};
    std::tuple<int, int> make_move() override{
        std::string row, col;
        cout << "enter coordinates of your mark(row and column): ";
        cin >> row >> col;
        while (board[std::stoi(row)][std::stoi(col)]  != ' ' || 0 > std::stoi(row) || std::stoi(row) > 3 || 0 > std::stoi(col) || std::stoi(col) > 3 ||
               std::find_if(row.begin(), row.end(), [](unsigned char c) { return !std::isdigit(c); }) != row.end() ||
               std::find_if(col.begin(), col.end(), [](unsigned char c) { return !std::isdigit(c); }) != col.end()
               ){
            cout << "You cannot put mark in this cell. Enter coordinates of your mark(row and column): ";
            cin >> row >> col;
        };
        return std::make_tuple(std::stoi(row), std::stoi(col));
    }
};


class MiniMaxAI : public Player {
public:
    char player;
    int board_1d[9]={0};
    MiniMaxAI(char (&input_board)[3][3], char comp_sign) : Player(input_board) {
        sign = 'X';
    }
    
    int win() {
        unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
        int i;
        for(i = 0; i < 8; ++i) {
            if(board_1d[wins[i][0]] != 0 &&
                board_1d[wins[i][0]] == board_1d[wins[i][1]] && board_1d[wins[i][1]] == board_1d[wins[i][2]])
                return board_1d[wins[i][2]];
        }
        return 0;
    }
    
    int minimax(int p) {
        int winner = win();
        if(winner != 0)
            return winner*p;
        int move = -1;
        int score = -2;
        for(int i = 0; i < 9; i++) {
            if(board_1d[i] == 0) {
                board_1d[i] = p;
                int thisScore = -minimax(p*-1);
                if(thisScore > score) {
                    score = thisScore;
                    move = i;
                }
                board_1d[i] = 0;
            }
        }
        if(move == -1)
         return 0;
        return score;
    }
    
    std::tuple<int, int> make_move() {
        player = sign == 'X' ? 'O': 'X';
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j] == sign)
                    board_1d[i*3+j] = 1;
                else if (board[i][j] == player)
                    board_1d[i*3+j] = -1;
            }
        }
        int move = -1;
        int score = -2;
        for(int i = 0; i < 9; ++i) {
            if(board_1d[i] == 0) {
                board_1d[i] = 1;
                int tempScore = -minimax(-1);
                board_1d[i] = 0;
                if(tempScore > score) {
                    score = tempScore;
                    move = i;
                }
            }
        }
        return std::make_tuple((int)move/3, move%3);
    }
};


class RandomAI : public Player {
public:
    char player;
    RandomAI(char (&input_board)[3][3]) : Player(input_board) {
        sign = 'X';
        player = 'O';
        srand(time(NULL));
    }

    std::tuple<int, int> make_move() override{
        int row, col;
        row = (rand() % 3);
        col = (rand() % 3);
        while (board[row][col] != ' '){
            row = (rand() % 3);
            col = (rand() % 3);
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
    char sign = 'X';

    void player1_make_move(){
        int row, col;
        cout << "Player 1, ";
        std::tie(row, col) = player1->make_move();
        board.set_X(row, col);
        moves_cntr += 1;
    }

    void player2_make_move(){
        int row, col;
        cout << "Player 2, ";
        std::tie(row, col) = player2->make_move();
        board.set_O(row, col);
        moves_cntr += 1;
    }

    int is_game_over(){
        unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
        int i;
        for(i = 0; i < 8; ++i) {
            if(board.get((int)(wins[i][0]/3),wins[i][0]%3) != ' ' &&
               board.get((int)(wins[i][0]/3),wins[i][0]%3) == board.get((int)(wins[i][1]/3),wins[i][1]%3) &&
               board.get((int)(wins[i][1]/3),wins[i][1]%3) == board.get((int)(wins[i][2]/3),wins[i][2]%3)){
                if (board.get((int)wins[i][0]/3,wins[i][0]%3) == 'X'){
                    cout << board.get((int)(wins[i][0]/3),wins[i][0]%3) << " " << board.get((int)(wins[i][1]/3),wins[i][1]%3) << " " << board.get((int)(wins[i][2]/3),wins[i][2]%3);
                    return 1;}
                else if ((board.get((int)wins[i][0]/3,wins[i][0]%3) == '0'))
                    return 2;
            }
        }
        if (moves_cntr >= size * size)
            return 3;
        return 0;
    }

public:

    Game(int s = 3): board(s), size(s){

        std::map<std::string, Player*> input_map;
        input_map.insert(std::make_pair("h", new Human(board.board_state)));
        input_map.insert(std::make_pair("cmm", new MiniMaxAI(board.board_state, sign)));
        input_map.insert(std::make_pair("cr", new RandomAI(board.board_state)));

        std::string p1;
        std::string p2;
        cout << "h - Human; cmm - computer using minimax algorithm; cr - computer using random;" << endl;
        cout << "Choose first player [h/cmm/cr]: ";
        cin >> p1;
        while(input_map.find(p1) == input_map.end()){
            cout << "Please, type proper player type. Choose first player [h/cmm/cr]: ";
            cin >> p1;
        }
        cout << "Choose second player [h/cmm/cr]: ";
        cin >> p2;
        while(input_map.find(p2) == input_map.end()){
            cout << "Please, type proper player type. Choose second player [h/cmm/cr]: ";
            cin >> p2;
        }
        player1 = input_map[p1];
        player2 = input_map[p2];
        player2->sign = 'O';

    }

    void play(){
    int res = 0;
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

    Game game;
    game.play();
    return 0;
}