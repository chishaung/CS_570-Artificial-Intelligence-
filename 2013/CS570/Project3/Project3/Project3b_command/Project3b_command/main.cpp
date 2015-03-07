#include"lander.h"
#include<ctime>
#include<cmath>
#include<iostream>
using namespace std;



int main()
{
    
    
    int land;
    int successful = 0;
    int crashed = 0;
    bool bQuit = false;


for (int i = 0; i < 10000; i++) {
    lander *l = new lander;
    bQuit = false;
    /* program main loop */
    while (!bQuit)
    {
        
        /* OpenGL animation code goes here */
        if(!l->landed_test()){  // if it hasn't landed
            
            l->update();  // update position and velocity
            //l->print();
            l->test();    // test for landing/crash
        }
        
        
        else {
            land = l->get_land();
            
            if (land  == 1) {
                //cout << "Successful!" << endl;
                successful++;
            }
            
            else if (land == 2) {
                //cout << "Crashed!" << endl;
                crashed++;
            }
            bQuit = true;
        }
        
    
    }
    
    delete l;
    
}
    cout << "Successful: " << successful << endl;
    cout << "Crashed: " << crashed << endl;
    return 0;
    
}


