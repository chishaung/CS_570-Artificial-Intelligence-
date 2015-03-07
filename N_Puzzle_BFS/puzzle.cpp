/*
CS411 Assignment#1 BFS for the 8 Puzzle Game
Chihsiang Wang
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <istream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int Where_is_zero(vector<int> Map) {

	int counter = 0;
	for (int i=0; i < Map.size(); i++) {
		if (Map[i] == 0) 
			break;

		counter++;
	}

	return counter;
	}

void Print_Map(vector<int> Map) {
    for (int i =0; i < Map.size(); i++) {

        
        if (Map[i] == 0)
            cout << ". ";
        else
        cout << Map[i] <<" ";

        if ((i+1)%3 == 0)
            cout << endl;
    }
    cout << endl;
}

void Print_Move(vector<int> Move) {
    for (int i =0; i < Move.size(); i++) {

        cout << Move[i] << " ";
    }
    cout << endl;
}


int Generate(int position, vector<int> Curr_Map, vector<int> Goal_Map, queue<vector<int> > &Queue, queue<vector<int> > &Move, vector<int> Curr_Move) {
	int Row = position / 3; 
    int up = position - 3;
    int down = position + 3;
    int left = position - 1;
    int right = position + 1;
    int Rup = up / 3;
    int Rdown = down / 3;
    int Rleft = left / 3;
    int Rright = right / 3;
    vector<int> temp_move;



    if (up < 0)
    	Rup = -1;
    if (down > 8)
    	Rdown = 4;
    if (left < 0)
    	Rleft = -1;
    if (right >8)
    	Rright = -1;




    if ((Rdown == 2 || Rdown == 1) && Curr_Map[down] != 0){

        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + down);
        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            Move.push(Curr_Move);
            Print_Map(Curr_Map);
            Print_Move(Curr_Move);
            return 1;
        }
        Queue.push(Curr_Map);
        iter_swap(Curr_Map.begin() + down, Curr_Map.begin() + position);

        Curr_Move.push_back(Curr_Map[down]);
        Move.push(Curr_Move);
        Curr_Move.pop_back();


    }


    if (Rleft == Row && Curr_Map[left] !=0){


        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + left);
        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            Move.push(Curr_Move);
            Print_Map(Curr_Map);
            Print_Move(Curr_Move);
            return 1;
        }
        Queue.push(Curr_Map);
        iter_swap(Curr_Map.begin() + left, Curr_Map.begin() + position);

        Curr_Move.push_back(Curr_Map[left]);
        Move.push(Curr_Move);
        Curr_Move.pop_back();

    }


    if ((Rup == 0 || Rup == 1) && Curr_Map[up] != 0) {

        

		iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + up);
        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            Move.push(Curr_Move);
            Print_Map(Curr_Map);
            Print_Move(Curr_Move);
        	return 1;
        }
        Queue.push(Curr_Map);
        iter_swap(Curr_Map.begin() + up, Curr_Map.begin() + position);

        Curr_Move.push_back(Curr_Map[up]);
        Move.push(Curr_Move);
        Curr_Move.pop_back();  

    }


    if (Rright == Row && Curr_Map[right] != 0){

        
    	iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + right);
        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            Move.push(Curr_Move);
            Print_Map(Curr_Map);
            Print_Move(Curr_Move);
            return 1;
        }
        Queue.push(Curr_Map);
        iter_swap(Curr_Map.begin() + right, Curr_Map.begin() + position);

        Curr_Move.push_back(Curr_Map[right]);
        Move.push(Curr_Move);
        Curr_Move.pop_back();



    }



	return 0;
}

int main (int argc, char* argv[]) {
	string line;
	string line2;
	getline(cin, line);
	getline(cin, line2);

	vector<int> Start_Map;
	vector<int> Goal_Map;
	vector<int> Curr_Map;
    vector<int> Curr_Move;
	queue<vector<int> > Queue;
    queue<vector<int> > Move;
	
	int position;
	

	/******************************************/
	/****** Analyzing external file here ******/
	/******************************************/

	char start[100];
	char goal[100];
	strcpy(start, line.c_str());
	strcpy(goal, line2.c_str());

	for (int i = 0; i < 18; i+=2) {
		Start_Map.insert(Start_Map.end(), (int)start[i]-48);
		Goal_Map.insert(Goal_Map.end(), (int)goal[i]-48);
	}

    cout << "START: " << endl;
    Print_Map(Start_Map);
    cout << "GOAL: " << endl;
    Print_Map(Goal_Map); 

	Curr_Map = Start_Map;
    //Curr_Move.push_back(0);
    Move.push(Curr_Move);
	Queue.push(Start_Map);




	while (1) {
	   Curr_Map = Queue.front();
       Curr_Move = Move.front();

	   position = Where_is_zero(Curr_Map);
	   if (Generate(position, Curr_Map, Goal_Map, Queue, Move, Curr_Move) == 1) {
	       cout << "Find answer!" << endl;
		   break;
	   }

	   else {
		  // Keep looping for answer
		  Queue.pop(); 
          Move.pop();
	   }

    }// End While



    cout << "Length of Queue: " << Queue.size() << endl;
    cout << "Moves..." << endl;
    cout << "L: " << Move.size() << endl;


}

