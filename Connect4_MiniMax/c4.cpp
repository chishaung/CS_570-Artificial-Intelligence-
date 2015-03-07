#define DEPTH 30
#include "c4board.h"
#include <time.h>
// a simple player
int main()
{

    clock_t tStart = clock();
    Board b("Simplton");

    initRand();


    while (b.read() && ! b.isBoardFull()) {
        //b.playRandomMove();
        //b.playRandomMove();
        //b.print();
        b.PlayBestMove(DEPTH);
        //b.PickBestMove(1);
        b.print();
        //b.checkboard();
    }



    if (b.isWinner()) {

    	cout << "Win" << endl;
    }
//    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
