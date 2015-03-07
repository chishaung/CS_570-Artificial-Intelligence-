#include <iostream>
#include "rand.h"
#include <algorithm>
#define INFINITY 99999



typedef unsigned long long int Bit64;

using namespace std;

// input/output:
// .......
// .......
// .......
// .......
// .......
// .......
//
// ...O...
// ..XX...
// -
// --  is the end of game signal
//
class Board {
private:
    static const int height = 6;
    static const int width = 7;

private:
    string name;                // name of player
    char board[height][width];  // full board
    int top[width];             // location of first empty cell in column
    char moveChar;              // character for next play
    int x, o;                   // number of x's and number of o's
    
    

// methods
private:
    char cleanChar(char c);

public:
    Board(string nameArg);
    bool read();
    bool check();
    void print(char *spacing="");
    bool moveOK(int c);
    bool isBoardFull();
    int pickRandomMove();
    int PlayBestMove(int depth);
    int PickBestMove(int depth);
    void placeMove(int c);
    void playRandomMove();
    char isWinner();
    bool isWinner(char c);
    Bit64 toBitstring(char piece);
    int check_2(char player) ;
    int check_3(char player) ;
    int evaluating(int, int);
    int Search_Min(int depth, int, int, int, int);
    int Search_Max(int depth, int, int, int, int);
    int checkboard();
    int Distance();
};
