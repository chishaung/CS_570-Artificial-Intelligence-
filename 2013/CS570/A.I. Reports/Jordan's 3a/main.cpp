#include "lander.h"
#include "ann.h"
#include <ctime>
#include <cmath>
//#include <iostream>

using namespace std;

float lrand(void){
      return(rand()/float(RAND_MAX));
}

void targetControl(float y_pos, float y_vel, float x_pos, float x_vel, float wind, float Fuel, float acceleration, float *targetBurn, float *targetThrust){
	if((y_vel + acceleration) > 3){
		*targetBurn = -(3 - (y_vel + acceleration));
	}
	else{
		*targetBurn = 0.0;
	}
	//*targetBurn = acceleration + (y_vel - 4 - acceleration);
	if(x_pos < -0.2){
		*targetThrust = -0.2;
	}
	else if(x_pos > 0.2){
		*targetThrust = 0.2;
	}
	else{
		*targetThrust = 0.0;
	}
}

int main(){

	int numLanded = 0;
	int numCrashed = 0;
	srand(time(NULL));
	int bQuit = 1;
	int retval;
	float thrust = 0.0;
	float burn = 0.0;
	float learning_rate = 0.5;
	float momentum = 0.1;
	cout << "test" << endl;
	ann *Brain = new ann(7, 7, 2);
	float input[7];
	float targets[2];
	float height;
	float Yvelocity;
	float landed;
	float fuel;
	float ACCELERATION;
	float xPosition;
	float Xvelocity;
	float WIND;
	float standard_error = 1.0;

	//while(standard_error > 0.00001){
	for(int i = 0; i < 100; i++){
		lander *l = new lander;
		cout << i << endl;
		
		 /* program main loop */
		while (bQuit)
		{
				input[0] = l->getHeight();
				input[1] = l->getYVel();
				input[2] = l->getXPos();
				input[3] = l->getXVel();
				input[4] = l->getWind();
				input[5] = l->getFuel();
				input[6] = l->getAccel();


				targetControl(l->getHeight(), l->getYVel(), l->getXPos(), l->getXVel(), l->getWind(), l->getFuel(), l->getAccel(), &burn, &thrust);
				
				targets[0] = burn;
				targets[1] = thrust;
        
				/* OpenGL animation code goes here */
				if(!l->landed_test()){  // if it hasn't landed
				   
					//Brain->printWeight();
				   Brain->update(input, &burn, &thrust);
				   standard_error = Brain->backPropogate(targets, learning_rate, momentum);
                    //Brain->printWeight();
                    //cout << "STD: " << standard_error << endl;
				   l->update(burn, thrust);  // update position and velocity
				  
				   l->test();    // test for landing/crash

				}
				else {
				   //glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
				   //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the screen
				   //l.print(); // draw crash or landing
				   bQuit = 0;
				   //if(l.landed_test() == 1)	numLanded++;
				   //else if(l.landed_test() == 2) numCrashed++;
				   //SwapBuffers(hDC);
				}
				//Sleep (200);
        
		}
		delete l;
		bQuit = 1;
		//cin >> bQuit;
	}

	bQuit = 1;
	
    //for(int i = 0; i < 1000; i++){
		lander *l = new lander;
		
		 /* program main loop */
		while (bQuit)
		{
				input[0] = l->getHeight();
				input[1] = l->getYVel();
				input[2] = l->getXPos();
				input[3] = l->getXVel();
				input[4] = l->getWind();
				input[5] = l->getFuel();
				input[6] = l->getAccel();

				targetControl(l->getHeight(), l->getYVel(), l->getXPos(), l->getXVel(), l->getWind(), l->getFuel(), l->getAccel(), &burn, &thrust);
				
				targets[0] = burn;
				targets[1] = thrust;
        
				/* OpenGL animation code goes here */
				if(!l->landed_test()){  // if it hasn't landed
				   
				   Brain->update(input, &burn, &thrust);
				   //standard_error = Brain->backPropogate(targets, learning_rate, momentum);
                   
                   //l->print();
                    
				   l->update(burn, thrust);  // update position and velocity
				   //l.print();   // draw/print position
				   l->test();    // test for landing/crash
				   //cout << "burn:: " << burn << " thrust:: " << thrust << endl;

				}
				else {
				   //glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
				   //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the screen
					//l->print(); // draw crash or landing
				   bQuit = 0;
				   if(l->landed_test() == 1)	numLanded++;
				   else if(l->landed_test() == 2) numCrashed++;
				   //SwapBuffers(hDC);
				}
				//Sleep (200);
        
		}
		delete l;
		bQuit = 1;
		//cin >> bQuit;
	//}

	cout << "Landed " << numLanded << " times!" << endl;
	cout << "Crashed " << numCrashed << " times!" << endl;
	cin >> retval;
	return 0;
}