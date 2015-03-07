/*
I know the code is really stupid...but I try to find the bugs out..!!
*/


#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <istream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <set>


using namespace std;


// what will be stored in priority queue
class Pair
{
public:
    int weight;
    vector<int> Map;
    vector<int> Move;

    Pair(int weight, vector<int> Map, vector<int> Move)
        : weight(weight), Map(Map), Move(Move) {}

    
};



// comparison functor
class PairCompare
{
public:
    bool operator()(const Pair &t1, const Pair &t2) const
    {
        return t1.weight > t2.weight;
    }
};


void clear( priority_queue<Pair, vector<Pair>, PairCompare> &q)
{
   priority_queue<Pair, vector<Pair>, PairCompare> empty;
   swap( q, empty );
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
    //cout << endl;
}


int Where_is_zero(vector<int> Map) {

    int counter = 0;
    for (int i=0; i < Map.size(); i++) {
        if (Map[i] == 0) 
            break;

        counter++;
    }

    return counter;
    }

int Where_Are_You(int x, vector<int> Map) {
    
    int index = 0;
    int i = 0;
    while (Map[i] != x) {
        index++;
        i++;
    }

    return index;
}

// Always return 0 reguardless of input.
int Weight_1(vector<int> Map, vector<int> Goal) {
    int weight;
    weight = 0;
    return weight;
}

// Count of number of tiles out of place.
int Weight_2(vector<int> Map, vector<int> Goal) {
    int weight = 0;


    for (int i = 0; i < Map.size(); i++) {
        if (Map[i] != Goal[i])
            weight++;
    }
    return weight;
}


// Sum of the Manhatten distances to goal position for each tile.
int Weight_3(vector<int> Map, vector<int> Goal) {


    int x, Gx;
    int y, Gy;
    int distance = 0;
    int weight = 0;
    int Goal_position;
    int position;
    


    for (int i = 0; i < Map.size(); i++) {
        Goal_position = Where_Are_You(Map[i], Goal);
        
        Gx = Goal_position / 3;
        Gy = Goal_position % 3;

        position = Where_Are_You(Map[i], Map);
        x = position / 3;
        y = position % 3;
        
        distance = abs(Gx - x) + abs(Gy - y);
        weight = weight + distance; 
    }
    return weight;

}

// 2*max(distance out of place in the row, distance out of place in col) 
// <- this is not an optimistic estimator 
// (referred to as "not admissible" in AI terminology.)
int Weight_4(vector<int> Map, vector<int> Goal) {

    int x, Gx;
    int y, Gy;
    int distance = 0;
    int weight = 0;
    int Goal_position;
    int position;
    

    for (int i = 0; i < Map.size(); i++) {
        Goal_position = Where_Are_You(Map[i], Goal);

        Gx = Goal_position / 3;
        Gy = Goal_position % 3;

        position = Where_Are_You(Map[i], Map);
        x = position / 3;
        y = position % 3;

        distance = 2 * max(abs(Gx - x), abs(Gy - y));
        weight = weight + distance; 
    }
    return weight;

}

// 3*max(distance out of place in the row, distance out of place in col) 
// <- this is even worse.
int Weight_5(vector<int> Map, vector<int> Goal) {
    int x, Gx;
    int y, Gy;
    int distance = 0;
    int weight = 0;
    int Goal_position;
    int position;
    

    for (int i = 0; i < Map.size(); i++) {
        Goal_position = Where_Are_You(Map[i], Goal);

        Gx = Goal_position / 3;
        Gy = Goal_position % 3;

        position = Where_Are_You(Map[i], Map);
        x = position / 3;
        y = position % 3;
        
        distance = 3 * max(abs(Gx - x), abs(Gy - y));
        weight = weight + distance; 
    }
    return weight;

}

void Print_PQ(priority_queue<Pair, vector<Pair>, PairCompare> Q) {
    
    cout << "Here is my PQ: " << endl;
    while (!Q.empty()) {
        Print_Map(Q.top().Map);
        Q.pop();
    }

}

void Print_Weight(priority_queue<Pair, vector<Pair>, PairCompare> W) {
    cout << "Here is my WQ: " << endl;
    while (!W.empty()) {
        cout << W.top().weight << endl;
        W.pop();
    }

}


int Generate(
    int position, 
    vector<int> Curr_Map, 
    vector<int> Goal_Map, 
    priority_queue<Pair, vector<Pair>, PairCompare> &Queue, 
    set<vector<int> > &TheSet,
    vector<int> Curr_Move,
    int trys,
    int SIZE,
    int EST

    ) {
    

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
    temp_move = Curr_Move;
    int Cost;
    

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
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_1(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
       
        iter_swap(Curr_Map.begin() + down, Curr_Map.begin() + position);





    }


    if (Rleft == Row && Curr_Map[left] !=0){
        
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + left);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_1(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + left, Curr_Map.begin() + position);



    }


    if ((Rup == 0 || Rup == 1) && Curr_Map[up] != 0) {
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + up);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_1(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + up, Curr_Map.begin() + position);

 

    }


    if (Rright == Row && Curr_Map[right] != 0){
        
        
        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + right);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_1(Curr_Map, Goal_Map) + Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            

        iter_swap(Curr_Map.begin() + right, Curr_Map.begin() + position);




    }


    
    return 0;
}

int Generate2(
    int position, 
    vector<int> Curr_Map, 
    vector<int> Goal_Map, 
    priority_queue<Pair, vector<Pair>, PairCompare> &Queue, 
    set<vector<int> > &TheSet,
    vector<int> Curr_Move,
    int trys,
    int SIZE,
    int EST
    ) {
    

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
    temp_move = Curr_Move;
    int Cost;

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
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_2(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
       
        iter_swap(Curr_Map.begin() + down, Curr_Map.begin() + position);





    }


    if (Rleft == Row && Curr_Map[left] !=0){
        
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + left);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_2(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + left, Curr_Map.begin() + position);



    }


    if ((Rup == 0 || Rup == 1) && Curr_Map[up] != 0) {
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + up);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_2(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + up, Curr_Map.begin() + position);

 

    }


    if (Rright == Row && Curr_Map[right] != 0){
        
        
        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + right);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_2(Curr_Map, Goal_Map) + Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            

        iter_swap(Curr_Map.begin() + right, Curr_Map.begin() + position);




    }


    
    return 0;
}

int Generate3(
    int position, 
    vector<int> Curr_Map, 
    vector<int> Goal_Map, 
    priority_queue<Pair, vector<Pair>, PairCompare> &Queue, 
    set<vector<int> > &TheSet,
    vector<int> Curr_Move,
    int trys,
    int SIZE,
    int EST
    ) {
    

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
    temp_move = Curr_Move;
    int Cost;

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
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_3(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
       
        iter_swap(Curr_Map.begin() + down, Curr_Map.begin() + position);





    }


    if (Rleft == Row && Curr_Map[left] !=0){
        
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + left);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_3(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + left, Curr_Map.begin() + position);



    }


    if ((Rup == 0 || Rup == 1) && Curr_Map[up] != 0) {
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + up);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_3(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + up, Curr_Map.begin() + position);

 

    }


    if (Rright == Row && Curr_Map[right] != 0){
        
        
        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + right);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_3(Curr_Map, Goal_Map) + Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            

        iter_swap(Curr_Map.begin() + right, Curr_Map.begin() + position);




    }


    
    return 0;
}

int Generate4(
    int position, 
    vector<int> Curr_Map, 
    vector<int> Goal_Map, 
    priority_queue<Pair, vector<Pair>, PairCompare> &Queue, 
    set<vector<int> > &TheSet,
    vector<int> Curr_Move,
    int trys,
    int SIZE,
    int EST
    ) {
    

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
    temp_move = Curr_Move;
    int Cost;

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
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_4(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
       
        iter_swap(Curr_Map.begin() + down, Curr_Map.begin() + position);





    }


    if (Rleft == Row && Curr_Map[left] !=0){
        
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + left);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_4(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + left, Curr_Map.begin() + position);



    }


    if ((Rup == 0 || Rup == 1) && Curr_Map[up] != 0) {
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + up);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_4(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + up, Curr_Map.begin() + position);

 

    }


    if (Rright == Row && Curr_Map[right] != 0){
        
        
        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + right);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_4(Curr_Map, Goal_Map) + Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            

        iter_swap(Curr_Map.begin() + right, Curr_Map.begin() + position);




    }


    
    return 0;
}

int Generate5(
    int position, 
    vector<int> Curr_Map, 
    vector<int> Goal_Map, 
    priority_queue<Pair, vector<Pair>, PairCompare> &Queue, 
    set<vector<int> > &TheSet,
    vector<int> Curr_Move,
    int trys,
    int SIZE,
    int EST
    ) {
    

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
    temp_move = Curr_Move;
    int Cost;

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
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_5(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
       
        iter_swap(Curr_Map.begin() + down, Curr_Map.begin() + position);





    }


    if (Rleft == Row && Curr_Map[left] !=0){
        
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + left);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_5(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + left, Curr_Map.begin() + position);



    }


    if ((Rup == 0 || Rup == 1) && Curr_Map[up] != 0) {
        

        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + up);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_5(Curr_Map, Goal_Map)+Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            
 
        iter_swap(Curr_Map.begin() + up, Curr_Map.begin() + position);

 

    }


    if (Rright == Row && Curr_Map[right] != 0){
        
        
        iter_swap(Curr_Map.begin() + position, Curr_Map.begin() + right);

        if (Curr_Map == Goal_Map) {
            Curr_Move.push_back(Curr_Map[position]);
            //cout << "Find Answer!" << endl;
            cout << "TRIES: " << trys << endl;
            cout << "COST: " << Curr_Move.size() <<endl;
            cout << "EST. DIST. START TO GOAL: " << EST << endl;
            cout << "SOLUTION: ";
            Print_Move(Curr_Move);
            cout << "    QUEUE LEN:  " << SIZE << endl;
            Print_Map(Curr_Map);
            return 1;
        }
            
            if (TheSet.count(Curr_Map) == 0) {
                TheSet.insert(Curr_Map);
                Curr_Move.push_back(Curr_Map[position]);
                Cost = Curr_Move.size();
                Queue.push(Pair(Weight_5(Curr_Map, Goal_Map) + Cost, Curr_Map, Curr_Move));
                
                
                Curr_Move.pop_back();
            }
            

        iter_swap(Curr_Map.begin() + right, Curr_Map.begin() + position);




    }


    
    return 0;
}



int main(int argc, char ** argv)
{

    priority_queue<Pair, vector<Pair>, PairCompare> Queue;
    
    set<vector<int> > TheSet;

    vector<int> Start_Map;
    vector<int> Goal_Map;
    vector<int> Curr_Map;
    vector<int> Curr_Move;
    string line;
    string line2;
    getline(cin, line);
    getline(cin, line2);
    int weight;
    int position;
    int EST;

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




    /*****************************************/
    /****** Print Out first information ******/
    /*****************************************/
    cout << "START: " << endl;
    Print_Map(Start_Map);
    cout << "GOAL: " << endl;
    Print_Map(Goal_Map); 



    /*********************************************/
    /****** Start to do A* Search from here ******/
    /*********************************************/

    Curr_Map = Start_Map;
    TheSet.insert(Start_Map);
    int Cost = Curr_Move.size();
    Queue.push(Pair(Weight_1(Start_Map, Goal_Map) + Cost, Start_Map, Curr_Move));
    Pair p = Queue.top();
    EST = Weight_1(Start_Map, Goal_Map);

    int trys = 0;

while (1) {
        trys++;
        p = Queue.top();
        Curr_Map = p.Map;
        Curr_Move = p.Move;

        Queue.pop();
        

        position = Where_is_zero(Curr_Map);
        if (Generate(position, Curr_Map, Goal_Map, Queue, TheSet, Curr_Move, trys, Queue.size(), EST) == 1) {
           break;
        }
}




/****************************************************************************/

clear(Queue);
TheSet.clear();
Curr_Move.clear();

Curr_Map = Start_Map;
TheSet.insert(Start_Map);
Cost = Curr_Move.size();
Queue.push(Pair(Weight_2(Start_Map, Goal_Map) + Cost, Start_Map, Curr_Move));
p = Queue.top();
trys = 0;
EST = Weight_2(Start_Map, Goal_Map);


while (1) {
        trys++;
        p = Queue.top();
        Curr_Map = p.Map;
        Curr_Move = p.Move;

        Queue.pop();
        

        position = Where_is_zero(Curr_Map);
        if (Generate2(position, Curr_Map, Goal_Map, Queue, TheSet, Curr_Move, trys, Queue.size(), EST) == 1) {
           break;
        }
}
//cout << "Size::: " << Queue.size() << endl;
//cout << "Trys::: " << trys << endl; 

/****************************************************************************/

clear(Queue);
TheSet.clear();
Curr_Move.clear();

Curr_Map = Start_Map;
TheSet.insert(Start_Map);
Cost = Curr_Move.size();
Queue.push(Pair(Weight_3(Start_Map, Goal_Map) + Cost, Start_Map, Curr_Move));
p = Queue.top();
trys = 0;
EST = Weight_3(Start_Map, Goal_Map);


while (1) {
        trys++;
        p = Queue.top();
        Curr_Map = p.Map;
        Curr_Move = p.Move;

        Queue.pop();
        

        position = Where_is_zero(Curr_Map);
        if (Generate3(position, Curr_Map, Goal_Map, Queue, TheSet, Curr_Move, trys, Queue.size(), EST) == 1) {
           break;
        }
}


/****************************************************************************/

clear(Queue);
TheSet.clear();
Curr_Move.clear();

Curr_Map = Start_Map;
TheSet.insert(Start_Map);
Cost = Curr_Move.size();
Queue.push(Pair(Weight_4(Start_Map, Goal_Map) + Cost, Start_Map, Curr_Move));
p = Queue.top();
trys = 0;
EST = Weight_4(Start_Map, Goal_Map);


while (1) {
        trys++;
        p = Queue.top();
        Curr_Map = p.Map;
        Curr_Move = p.Move;

        Queue.pop();
        

        position = Where_is_zero(Curr_Map);
        if (Generate4(position, Curr_Map, Goal_Map, Queue, TheSet, Curr_Move, trys, Queue.size(), EST) == 1) {
           break;
        }
}



/****************************************************************************/

clear(Queue);
TheSet.clear();
Curr_Move.clear();

Curr_Map = Start_Map;
TheSet.insert(Start_Map);
Cost = Curr_Move.size();
Queue.push(Pair(Weight_5(Start_Map, Goal_Map) + Cost, Start_Map, Curr_Move));
p = Queue.top();
trys = 0;
EST = Weight_5(Start_Map, Goal_Map);


while (1) {
        trys++;
        p = Queue.top();
        Curr_Map = p.Map;
        Curr_Move = p.Move;

        Queue.pop();
        

        position = Where_is_zero(Curr_Map);
        if (Generate5(position, Curr_Map, Goal_Map, Queue, TheSet, Curr_Move, trys, Queue.size(), EST) == 1) {
           break;
        }
}





    return 0;
}

