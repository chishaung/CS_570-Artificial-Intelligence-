#ifndef LANDER_H
#define LANDER_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <cmath>
#include "Fuzzy.h"

using namespace std;

float ACCELERATION;
float WIND;
const float MAX_SAFE_LANDING_SPEED = 4.0;
const float MIN_SAFE_X = -0.2;
const float MAX_SAFE_X = 0.2;


//float lrand(){
//    return(rand()/float(RAND_MAX));
//}

float lrand(void){
	srand(time(NULL));
	int tmp=rand()%10000;
    float f=tmp*0.0001;
    return f;
    //return(rand()/float(RAND_MAX));
}


class lander{

public:
    lander(void);
    bool landed_test(void){return landed;}
    void update(void);
    void print(void);
    void test(void);
    void control();
    int get_land();
private:
    float height;
    float xPosition;
    float Yvelocity;
    float Xvelocity;
    int landed;  // 0- no, 1- yes, 2- crashed
    float fuel;
    float burn;
    float thrust;
};

lander::lander(void){
    height = 100.0;  // starting height
    Yvelocity = 10.0 * lrand();  // random starting velocity
    //Yvelocity = 0.001;
    landed = 0;  // haven't landed yet
    fuel = 100.0;   // starting fuel
    ACCELERATION = 2.0;  // but should be changed
    xPosition = 0;
    Xvelocity = 0;
    WIND = 0.2 * (lrand()-0.5);  // random wind
    //WIND = 0;
}


int lander::get_land() {

    return landed;
}

void lander::control(){
    // calculates the burn - vertical adjustments
    // and the thrust - horizontal adjustments
    // both use fuel
    
    
    

    fuzzy Y;
    Y.get_fuzzy_height(height);
    Y.get_fuzzy_speed(Yvelocity);
    Y.fuzzy_set_Y();
    burn = Y.defuzzy_Y();

    
    fuzzy X;
    X.get_fuzzy_far(xPosition);
    X.get_fuzzy_height(height);
    X.fuzzy_set_X();
    thrust = X.defuzzy_X();
    
    // Define how is 

}


void lander::test(void){
    // Test for landing
    if(height > 0) // haven't landed yet
        return;
    if(Yvelocity > MAX_SAFE_LANDING_SPEED || xPosition < MIN_SAFE_X || xPosition > MAX_SAFE_X)
        landed = 2;
    else
        landed = 1;
}



void lander::update(void){
    // update the lander's altitude
    Yvelocity+=ACCELERATION;  // apply acceleration
    control();  // calculate burn and thrust
    
    
    
    if(fuel < burn)   // if insuficient fuel, use the rest for burn
        burn = fuel;
    fuel -= fabs(burn);  // subtract fuel
    Yvelocity-=burn;  // apply burn
   
    
    if(fuel < thrust)   // if insuficient fuel, use the rest for thrust
        thrust = fuel;
    fuel -= fabs(thrust);  // subtract fuel
    Xvelocity-=thrust;    // apply thrust
    
    
    height -= (Yvelocity);  //  subtract because moving down
    xPosition += (Xvelocity + WIND);  //  wind
}

void lander::print(void){
    /*  For command line version */
     cout << "Height: " << height << "  ";
     cout << "Y-Velocity: " << Yvelocity << "  ";
     cout << "Position: " << xPosition << "  ";
     cout << "Thurst: " << thrust << "   ";
     cout << "Fuel: " << fuel<< endl;
     
     
}

#endif