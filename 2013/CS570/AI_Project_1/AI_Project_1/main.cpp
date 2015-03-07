//
//  main.cpp
//  AI_Project_1
//
//  Created by Shaung on 6/2/14.
//  Copyright (c) 2014 Shaung. All rights reserved.
//

#include <iostream>
#include "Map.h"

using namespace std;


int main(int argc, const char * argv[])
{
    char Map[LENGTH][WIDTH];
    //create_Map(Map[LENGTH][WIDTH]);
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Map[j][i] = '+';
        }
    }

    
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout <<Map[j][i];
        }
        cout << endl;
    }
    
    return 0;
}

