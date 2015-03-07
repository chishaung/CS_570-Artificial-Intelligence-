//
//  main.cpp
//  Ryu
//
//  Created by Shaung on 13/3/4.
//  Copyright (c) 2013年 Shaung. All rights reserved.
//

#include <iostream>

using namespace std;


float cosine() {

    return 0;
}

int fac(int x, int result = 1) {
    if (x == 1) return result;
    
    else
        return fac(x - 1, x * result);
}


int main(int argc, const char * argv[])
{
    cout << fac(3);
    

    return 0;
    
}

