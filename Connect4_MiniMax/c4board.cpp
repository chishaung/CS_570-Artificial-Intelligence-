#include "c4board.h"

Board::Board(string nameArg)
{
    name = nameArg;

    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            board[r][c] = '.';
        }
    }
    check();
}


char Board::isWinner()
{
    if (isWinner('X')) return 'X';
    if (isWinner('O')) return 'O';
    return '\0';  // zero or false
}


bool Board::isWinner(char piece)
{
    Bit64 bits, tmp;
    
    bits = toBitstring(piece);

    // horizontal win
    tmp = (bits & (bits>>1));
    tmp = (tmp>>2) & tmp;
    if (tmp) return true;
//    tmp = tmp | (tmp<<2)   // for marking the win if you want
//    tmp = tmp | (tmp<<1)

    // vertial win
    tmp = (bits & (bits>>(width+1)));
    tmp = (tmp>>(2*(width+1))) & tmp;
    if (tmp) return true;

    // down diagonal win
    tmp = (bits & (bits>>(width+2)));
    tmp = (tmp>>(2*(width+2))) & tmp;
    if (tmp) return true;

    // up diagonal win
    tmp = (bits & (bits>>(width)));
    tmp = (tmp>>(2*(width))) & tmp;
    if (tmp) return true;

    return false;
}




Bit64 Board::toBitstring(char piece)
{
    Bit64 bits;

    if (height * (width+1)>64) {
        cout << "ERROR(toBitstring): board too large to be bit encoded.  height * (width+1) <= 64." << endl;
    }

    bits = 0ULL;
    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            bits = (bits<<1) | ((board[r][c]==piece) ? 1 : 0);
        }
        bits = (bits<<1);
    }

    return bits;
}


char Board::cleanChar(char c)
{
    char uc;

    uc = toupper((int)c);
    switch (uc) {
    case 'X' :
        uc = 'X';
        break;
    case 'O' :
        uc = 'O';
        break;
    case '.' :
        uc = '.';
        break;
    default:
        cout << "ERROR(read): invalid character '" <<  c << "' treated as a period." << endl;
        uc = '.';
    }

    return uc;
}

// return true if valid board.
// return false on invalid board and indicates time for termination
bool Board::read()
{
    string line[width+1];

    // get board
    int numlines;

    numlines = 0;
    for (; numlines<height; numlines++) {
        cin >> line[numlines];
        if (line[numlines]=="--" || cin.eof()) {
            return false;   // immediate termination signal
            break;
        }
        if (line[numlines]=="-") {
            break;
        }
        if (line[numlines].length()<width) {
            cout << "ERROR(read): input line '" << line[numlines] << "' is too short." << endl;
            return false;
        }
    }
    numlines--;

    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            if (numlines>=0) {
                board[r][c] = cleanChar((unsigned char)line[numlines][c]);
            }
            else {
                board[r][c] = '.';
            }
        }
        numlines--;
    }

    return check();
}

// print out board
void Board::print(char *spacing)
{
    for (int r=height-1; r>=0; r--) {
        for (int c=0; c<width; c++) {
            cout << board[r][c] << spacing;
        }
        cout << endl;
    }
}
    

// check board to see that it is legal
// and set whose move it is
bool Board::check()
{
    bool ok = true;

    x = o = 0;
    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            if (board[r][c]=='X') x++;
            else if (board[r][c]=='O') o++;
        }
    }
    if (x>o+1) {
        cout << "ERROR(board): there are too many X's on the board" << endl;
        ok = false;
    }
    else if (x<o) {
        cout << "ERROR(board): there are too many O's on the board" << endl;
        ok = false;
    }
    else if (x==o) {
        moveChar = 'X';
    }
    else {
        moveChar = 'O';
    }

    for (int c=0; c<width; c++) {
        int firstPeriod;

        firstPeriod = height;
        for (int r=0; r<height; r++) {
            if (board[r][c]=='.') {
                if (firstPeriod==height) firstPeriod=r;
            }
            else {
                if (firstPeriod<height) {
                    cout << "ERROR(board): board has a gap in column " << c+1 << endl;
                    ok = false;
                }
            }
        }
        top[c] = firstPeriod;
    }

    return ok;
}


// check if move OK.
// if c==-1 then there is no legal move and move is not OK
bool Board::moveOK(int c)
{
    return (c>=0 && top[c]<height && board[top[c]][c] == '.');
}


// is board full?
bool Board::isBoardFull()
{
    for (int i=0; i<width; i++) 
        if (top[i]<height) return false;
    return true;
}


// pick a random place to move
int Board::pickRandomMove()
{
    int c;

    if (isBoardFull()) {
        cout << "ERROR(pickRandomMove): Can't move.  The board is full" << endl;
        return -1;
    }

    c = randMod(width);
    while (! moveOK(c)) {
        c = randMod(width);
    }
    return c;
}

// pick and place a random move
void Board::playRandomMove()
{
    int c;

    c = pickRandomMove();
    placeMove(c);
//    cout << moveChar << ": Player " << name << " plays in column " << c+1 << endl;
}


// put the piece on the board in column c
void Board::placeMove(int c)
{
    if (moveOK(c)) {
        board[top[c]][c] = moveChar;
        top[c]++;
    }
}





/************************
For the Minimax algorithm
*************************/


// pick and place a move by MinMax algorithm
int Board::PlayBestMove(int depth) 
{

    int c;
    

    c = PickBestMove(depth);
    placeMove(c);
}



int Board::Search_Max(int depth, int alpha, int beta, int h, int w) {

    int evalValue = evaluating(h,w);
    if (beta >= alpha){
        return evalValue;
    }

    if (isWinner() == 'O' || isWinner() == 'X' || depth == 0) {
        //cout << "Depth: " << depth << endl;
        /*
        if (isWinner() == 'O')
            cout << "O win" << endl;
        if (isWinner() == 'X')
            cout << "X win" << endl;
        */
        return evalValue;
    }

    int bestValue = - INFINITY;
    for (int pos = 0; pos < 7; pos++) {

        if (moveOK(pos)) {
            int w, h;
            w = pos;
            h = top[pos];
            //placeMove(pos);
            board[h][w] = 'X';
            top[w]++;
            //print();
            //bestValue = max(bestValue, Search_Min(depth-1));
            bestValue = max(bestValue, Search_Min(depth-1, max(bestValue, alpha), beta, h, w)); 
            board[h][w] = '.';
            top[w]--;
        }

    }
    return bestValue;
}



int Board::Search_Min(int depth, int alpha, int beta, int h, int w) {

    int evalValue = evaluating(h,w);
    

    if (alpha >= beta){
        return evalValue;
    }

    if (isWinner() == 'O' || isWinner() == 'X' || depth == 0) {
        //cout << "Find winner" << endl;
        //cout << "Depth: " << depth << endl;
        /*
        if (isWinner() == 'O')
            cout << "O win" << endl;
        if (isWinner() == 'X')
            cout << "X win" << endl;
            */
        return evalValue;
    }

    int bestValue = INFINITY;
    for (int pos = 0; pos < 7; pos++) {

        if (moveOK(pos)) {
            int w, h;
            w = pos;
            h = top[pos];
            //placeMove(pos);
            board[h][w] = 'O';
            top[w]++;
            //print();
            //bestValue = min(bestValue, Search_Max(depth-1));
            bestValue = min(bestValue, Search_Max(depth-1, alpha, min(bestValue, beta), h, w)); 
            board[h][w] = '.';
            top[w]--;
        }

    }
    return bestValue;
}

// MiniMax Algorithm
int Board::PickBestMove(int depth) 
{

    int c;
    if (isBoardFull()) {
        cout << "ERROR(pickRandomMove): Can't move.  The board is full" << endl;
        return -1;
    }


    int bestMoves[7];      
    int index = 0;      
    int bestValue = - INFINITY ;  
       
    for (int pos = 0; pos < 7; pos++){  


        if (moveOK(pos)) {
            int w, h;
            w = pos;
            h = top[pos];
            //placeMove(pos);
            board[h][w] = 'X';
            top[w]++;
            //print();
            int value = Search_Min(depth, - INFINITY, INFINITY, h, w);


            if (value > bestValue) {
                bestValue = value;
                index = 0;
                bestMoves[index] = pos;
            }

            else if (value == bestValue) {
                index++;
                bestMoves[index] = pos;
            }

            board[h][w] = '.';
            top[w]--;

        }    
    }  
      
    //index = 2;
    //cout << "index: " << index << endl;
    if (index > 1){  
        //cout << "random pick?" << endl;
        return pickRandomMove(); 
    }

    c = bestMoves[index]; 
    //c = bestMoves[3];
    return c;

}



// Chekc how many 2 connection
int Board::check_2(char player)
{
    int countO = 0;
    int countX = 0;

/*
BOARD STATUS:
(5,0) (5,1) (5,2) (5,3) (5,4) (5,5) (5,6)
(4,0) (4,1) (4,2) (4,3) (4,4) (4,5) (4,6)
(3,0) (3,1) (3,2) (3,3) (3,4) (3,5) (3,6)
(2,0) (2,1) (2,2) (2,3) (2,4) (2,5) (2,6)
(1,0) (1,1) (1,2) (1,3) (1,4) (1,5) (1,6)
(0,0) (0,1) (0,2) (0,3) (0,4) (0,5) (0,6)
*/

    for (int h = 0; h < 6; h++) {
        for (int w = 0; w < 7; w++) {
            if (board[h][w] == 'X' && board[h+1][w+1] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h+1][w+1] == 'O')
                countO++;

            if (board[h][w] == 'X' && board[h-1][w+1] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h-1][w+1] == 'O')
                countO++;

            if (board[h][w] == 'X' && board[h+1][w-1] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h+1][w-1] == 'O')
                countO++;

            if (board[h][w] == 'X' && board[h-1][w-1] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h-1][w-1] == 'O')
                countO++;
        }
    }
   

    // check horizontal
    for (int h = 0; h < 6; h++) {
        for (int w = 0; w < 7; w++) {
            if (board[h][w] == 'X' && board[h][w+1] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h][w+1] == 'O')
                countO++;
        }
    }
    
    // check vertical
    for (int w = 0; w < 7; w++) {
        for (int h = 0; h < 6; h++) {
            if (board[h][w] == 'X' && board[h+1][w] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h+1][w] == 'O')
                countO++;
        }
    }

    if (player == 'X')
        return countX;

    else 
        return -countO;

}

// Chekc how many 3 connection
int Board::check_3(char player)
{
    int countO = 0;
    int countX = 0;

/*
BOARD STATUS:
(5,0) (5,1) (5,2) (5,3) (5,4) (5,5) (5,6)
(4,0) (4,1) (4,2) (4,3) (4,4) (4,5) (4,6)
(3,0) (3,1) (3,2) (3,3) (3,4) (3,5) (3,6)
(2,0) (2,1) (2,2) (2,3) (2,4) (2,5) (2,6)
(1,0) (1,1) (1,2) (1,3) (1,4) (1,5) (1,6)
(0,0) (0,1) (0,2) (0,3) (0,4) (0,5) (0,6)
*/

    for (int h = 0; h < 6; h++) {
        for (int w = 0; w < 7; w++) {
            if (board[h][w] == 'X' && board[h+1][w+1] == 'X' && board[h+2][w+2] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h+1][w+1] == 'O' && board[h+2][w+2] == 'O')
                countO++;

            if (board[h][w] == 'X' && board[h-1][w+1] == 'X' && board[h-2][w+2] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h-1][w+1] == 'O' && board[h-2][w+2] == 'O')
                countO++;

            if (board[h][w] == 'X' && board[h+1][w-1] == 'X' && board[h+2][w-2] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h+1][w-1] == 'O' && board[h+2][w-2] == 'O')
                countO++;

            if (board[h][w] == 'X' && board[h-1][w-1] == 'X' && board[h-2][w-2] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h-1][w-1] == 'O' && board[h-2][w-2] == 'O')
                countO++;
        }
    }
   

    // check horizontal
    for (int h = 0; h < 6; h++) {
        for (int w = 0; w < 5; w++) {
            if (board[h][w] == 'X' && board[h][w+1] == 'X' && board[h][w+2] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h][w+1] == 'O' && board[h][w+2] == 'O')
                countO++;
        }
    }
    
    // check vertical
    for (int w = 0; w < 7; w++) {
        for (int h = 0; h < 4; h++) {
            if (board[h][w] == 'X' && board[h+1][w] == 'X' && board[h+2][w] == 'X')
                countX++;
            if (board[h][w] == 'O' && board[h+1][w] == 'O' && board[h+2][w] == 'O')
                countO++;
        }
    }

    if (player == 'X')
        return countX;

    else 
        return -countO;

}

int Board::checkboard() {
    //height width
    //cout << "is: " << board[1][0] << endl;
    //cout << "X: " << check_4('X') << endl;
    //cout << board[0][3] << board[0][4] << board[0][5] << board[0][6] << endl;
}

int Board::Distance() {

    int distance;

    return distance;
}

// Heuristic function for minimax algorithm
int Board::evaluating(int h, int w)
{
    
    int value = 0;
    int distance = 0;

    //value = check_4('X') + check_3('X') + check_2('X') - 
    //       check_3('O') - check_2('O');

    
    if (isWinner() == 'O')           
        return -INFINITY;
    if (isWinner() == 'X')           
        return INFINITY;
    distance = sqrt((3-h)*(3-h) + (3-w)*(3-w));
    
    //cout << "#: " << check_4('X') << endl;
    value = 6*check_3('X') - 5*check_3('O') + 4*check_2('X') - 2*check_2('O') + distance;

    return value;
}







