#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

#define alpha 0.1
#define E 2.718
#define Training 150000


using namespace std;

// Giving Matrix A and B, return A x B
vector <vector<float> > Mutiply(vector <vector<float> > A, vector <vector<float> > B) {
  vector <vector<float> > Result;

  int A_Row, A_Column, B_Row, B_Column;
  A_Row = A.size();
  A_Column = A[0].size();
  B_Row = B.size();
  B_Column = B[0].size();
  vector<float> temp;


  if(A_Column != B_Row) {
    cout << "Warning!!!!! Mutiply Error!!!" << endl;
  }

  // Result is a A_Row x B_Column Matrix
  for (int i = 0; i < A_Row; i++) {
    for (int j = 0; j < B_Column; j++) {
      temp.push_back(0);
    }
    Result.push_back(temp);
    temp.clear();
  }
  // x denotes number rows in matrix A
  // y denotes number columns in matrix A
  // m denotes number rows in matrix B
  // n denotes number columns in matrix B
  int x, y, m, n, i, j;
  x = A_Row;
  y = A_Column;
  m = B_Row;
  n = B_Column;

  for(i = 0; i < x; i++)
        {
            for(j = 0; j < n; j++)
            {
                Result[i][j]=0;
                for(int k=0;k<m;k++)
                {
                    Result[i][j] = Result[i][j] + A[i][k] * B[k][j];
                }
            }
        }
  return Result;
}


float Sigmoid(float x) {

  float value;
  value = 1 / (1 + pow(E, (-4 * x)));
  return value;
}

// Randomly pick 0.1~0.7 or -0.1~-0.7
float RandomFloat(float lower, float upper)
{ 
  float temp;
  do{
  temp = rand() * (upper-lower) / RAND_MAX + lower;
  } while (temp > -0.0010 && temp < 0.0010);

  return temp;
}


/*************
Split Function
*************/
struct split
{
  enum empties_t { empties_ok, no_empties };
};

template <typename Container>
Container& split(
  Container&                                 result,
  const typename Container::value_type&      s,
  typename Container::value_type::value_type delimiter,
  split::empties_t                           empties = split::empties_ok )
{
  result.clear();
  std::istringstream ss( s );
  while (!ss.eof())
  {
    typename Container::value_type field;
    getline( ss, field, delimiter );
    if ((empties == split::no_empties) && field.empty()) continue;
    result.push_back( field );
  }
  return result;
}

void print( vector <vector<float> > M)
{
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M[0].size(); j++) {
      cout << M[i][j] << "  ";
    }
    cout << endl;
  }
}


vector <vector<float> > Transpose(vector <vector<float> > M) {

  vector <vector<float> > New;

  int height = M.size();
  int width = M[0].size();

 
  vector<float> Temp;

  for (int j = 0; j < width; j++) {
    for (int i = 0; i < height; i ++) {
      Temp.push_back(M[i][j]);
    }
    New.push_back(Temp);
    Temp.clear();
  }


  return New;
}

void intiWeight(int inSize, int outSize, int hiddenSize, 
  vector <vector<float> > &v,vector <vector<float> > &w) {


  vector<float> temp;
  // Set up the Weight Range
  float weightRange = 1 / sqrt(2); 
  // Fill up 5 x 3 matrix 'v'
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      temp.push_back(RandomFloat(-weightRange, weightRange));
    }
    v.push_back(temp);
    temp.clear();
  }

  // Fill up 4 x 3 matrix 'w'
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      temp.push_back(RandomFloat(-weightRange, weightRange));
    }
    w.push_back(temp);
    temp.clear();
  }

}

vector<vector<float> > Forward(vector<vector<float> > x, 
  vector <vector<float> > v,vector <vector<float> > w) {



  vector <vector<float> > delta1;
  vector <vector<float> > delta2;
  vector<float> t;
  vector <vector<float> > layer1;
  vector <vector<float> > layer2;
  vector <vector<float> > y;
  x[0].insert(x[0].begin(), -1);
  
  layer1 = Mutiply(x, v);
  layer1[0].insert(layer1[0].begin(), -1);

  for (int i = 0; i < layer1.size(); i++) {
    for (int j = 0; j < layer1[0].size(); j++) {
      layer1[i][j] = Sigmoid(layer1[i][j]); 
    }
  }
  //layer1[0].insert(layer1[0].begin(), -1);


  layer2 = Mutiply(layer1, w);

  for (int i = 0; i < layer2.size(); i++) {
    for (int j = 0; j < layer2[0].size(); j++) {
      layer2[i][j] = Sigmoid(layer2[i][j]); 
    }
  }
  

  return layer2;
}

void Adjust(vector <vector<float> > &v,vector <vector<float> > &w, int result, vector<vector <float> > x) {

  vector <vector<float> > delta1;
  vector <vector<float> > delta2;
  vector<float> t;
  vector <vector<float> > layer1;
  vector <vector<float> > layer2;
  vector <vector<float> > y;
  x[0].insert(x[0].begin(), -1);
  
  layer1 = Mutiply(x, v);
  layer1[0].insert(layer1[0].begin(), -1);

  for (int i = 0; i < layer1.size(); i++) {
    for (int j = 0; j < layer1[0].size(); j++) {
      layer1[i][j] = Sigmoid(layer1[i][j]); 
    }
  }
  //layer1[0].insert(layer1[0].begin(), -1);


  layer2 = Mutiply(layer1, w);

  for (int i = 0; i < layer2.size(); i++) {
    for (int j = 0; j < layer2[0].size(); j++) {
      layer2[i][j] = Sigmoid(layer2[i][j]); 
    }
  }
  

  switch (result) {
    case 0:
      t.push_back(1);
      t.push_back(0);
      t.push_back(0);
    break;

    case 1:
      t.push_back(0);
      t.push_back(1);
      t.push_back(0);
    break;

    case 2:
      t.push_back(0);
      t.push_back(0);
      t.push_back(1);
    break;
  }


  y = layer2;

  


  // To get Dealta 2:
  // Delta2 is 1 x 3
  vector<float> delta_temp;
  float value;
  for (int i = 0; i < 3; i++) {
    value = (t[i] - y[0][i]) * y[0][i] * (1 - y[0][i]);
    delta_temp.push_back(value);
  }
  delta2.push_back(delta_temp);
  delta_temp.clear();

  vector <vector<float> > trans_w;
  trans_w = Transpose(w);
  // To get Delta 1:
  // delta1 =( layer1 (1 - layer1)) ( delta2 . Transpose[w]);
  // w is 4 x 3, trans(w) is 3 x 4
  // delta2 . trans(w) is 1 x 4 
  
  vector <vector<float> > delta1_part;

  delta1_part = Mutiply(delta2, Transpose(w));
//////////////////////////////////////////////////////////////
  vector<float> temp_delta1;
  for (int i = 0; i < layer1[0].size(); i++) {
    temp_delta1.push_back((layer1[0][i] * (1 - layer1[0][i])) * delta1_part[0][i]);
  }
  delta1.push_back(temp_delta1);
  temp_delta1.clear();



///////////////////////////////////^^^^^^^


  // delta1 and delta2

  vector <vector<float> > temp_v_weight; // 5 x 3
  vector <vector<float> > temp_w_weight; // 4 x 3
  vector <vector<float> > t_layer1; // 4 x 1
  vector<float> temp_w;
  t_layer1 = Transpose(layer1);

    for (int j = 0; j < delta2[0].size(); j++) {
      temp_w.push_back(t_layer1[0][0] * delta2[0][j]);
    }
    temp_w_weight.push_back(temp_w);
    temp_w.clear();

    for (int j = 0; j < delta2[0].size(); j++) {
      temp_w.push_back(t_layer1[1][0] * delta2[0][j]);
    }
    temp_w_weight.push_back(temp_w);
    temp_w.clear();

    for (int j = 0; j < delta2[0].size(); j++) {
      temp_w.push_back(t_layer1[2][0] * delta2[0][j]);
    }
    temp_w_weight.push_back(temp_w);
    temp_w.clear();

    for (int j = 0; j < delta2[0].size(); j++) {
      temp_w.push_back(t_layer1[3][0] * delta2[0][j]);
    }
    temp_w_weight.push_back(temp_w);
    temp_w.clear();



    for (int i = 0; i < w.size(); i++) {
      for (int j = 0; j < w[0].size(); j++) {
        w[i][j] = w[i][j] + alpha * temp_w_weight[i][j];
      }
    }

    // Gte new w


    vector<vector<float> > new_delta1;
    vector<float> n_d1_t;
    vector <vector<float> > t_x;
    t_x = Transpose(x);

    for (int i = 1; i < delta1[0].size(); i++) {
      n_d1_t.push_back(delta1[0][i]);
    }
    new_delta1.push_back(n_d1_t);

    for (int j = 0; j < new_delta1[0].size(); j++) {
      temp_w.push_back(t_x[0][0] * new_delta1[0][j]);
    }
    temp_v_weight.push_back(temp_w);
    temp_w.clear();

    for (int j = 0; j < new_delta1[0].size(); j++) {
      temp_w.push_back(t_x[1][0] * new_delta1[0][j]);
    }
    temp_v_weight.push_back(temp_w);
    temp_w.clear();
    for (int j = 0; j < new_delta1[0].size(); j++) {
      temp_w.push_back(t_x[2][0] * new_delta1[0][j]);
    }
    temp_v_weight.push_back(temp_w);
    temp_w.clear();
    for (int j = 0; j < new_delta1[0].size(); j++) {
      temp_w.push_back(t_x[3][0] * new_delta1[0][j]);
    }
    temp_v_weight.push_back(temp_w);
    temp_w.clear();
    for (int j = 0; j < new_delta1[0].size(); j++) {
      temp_w.push_back(t_x[4][0] * new_delta1[0][j]);
    }
    temp_v_weight.push_back(temp_w);
    temp_w.clear();

    for (int i = 0; i < v.size(); i++) {
      for (int j = 0; j < v[0].size(); j++) {
        v[i][j] = v[i][j] + alpha * temp_v_weight[i][j];
      }
    }


}

/************
Main Function
************/

int main (int argc, char* argv[]) {
  vector<vector<float> > x;
vector<float> temp;
    string line = " .7   .5    .3    .2";
    //split( fields, line, ' ' );
    //cout << fields[0] << " " << fields[1] << " " <<  fields[2] << " " << fields[3] << endl;

    char * pch;
    char tab2[1024];
    strcpy(tab2, line.c_str());
    //printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (tab2," ");
    while (pch != NULL)
      {
      //printf ("%s\n",pch);
      string str(pch);
      temp.push_back(atof(str.c_str()));
      pch = strtok (NULL, " ");
    }



/*
temp.push_back(0.7000);
temp.push_back(0.5000);
temp.push_back(0.3000);
temp.push_back(0.2000);
*/
x.push_back(temp);
print(x);

cout << "X: " << endl;
print(x);

vector<vector<float> > v;
temp.clear();

temp.push_back(-0.0200);
temp.push_back(0.0300);
temp.push_back(0.0500);
v.push_back(temp);
temp.clear();

temp.push_back(0.0700);
temp.push_back(-0.1100);
temp.push_back(0.1300);
v.push_back(temp);
temp.clear();

temp.push_back(-0.1700);
temp.push_back(-0.1900);
temp.push_back(0.2300 );
v.push_back(temp);
temp.clear();

temp.push_back(0.2900);
temp.push_back(0.3100);
temp.push_back(-0.3700);
v.push_back(temp);
temp.clear();

temp.push_back(-0.4100);
temp.push_back(0.4300);
temp.push_back(-0.4700);
v.push_back(temp);
temp.clear();


cout << "V: " << endl;
print(v);



vector<vector<float> > w;
temp.clear();

temp.push_back(0.5300);
temp.push_back(-0.5900);
temp.push_back(-0.6100);
w.push_back(temp);
temp.clear();

temp.push_back(-0.6700);
temp.push_back(-0.7100);
temp.push_back(-0.7300);
w.push_back(temp);
temp.clear();

temp.push_back(0.7900);
temp.push_back(0.8300);
temp.push_back(0.8900);
w.push_back(temp);
temp.clear();

temp.push_back(-0.9700);
temp.push_back(0.1010);
temp.push_back(0.1030);
w.push_back(temp);
temp.clear();


cout << "W: " << endl;
print(w);



int result = 0;

Adjust(v, w, result, x);


cout << "V" << endl;
print(v);

cout << "W" << endl;
print(w);


  /**************
  Breaking INPUTS
  **************/
  

  /*
  vector <vector<float> > test0;
  vector<float> test00;
  test00.push_back(1);
  test00.push_back(2);
  test0.push_back(test00);
  test00.clear();
  test00.push_back(3);
  test00.push_back(4);
  test0.push_back(test00);
  test00.clear();
  test00.push_back(5);
  test00.push_back(6);
  test0.push_back(test00);
  cout << "Matrix: " << endl;
  print(test0);
  cout << "Transpost Matrix: " << endl;
  print(Transpose(test0));
  cout << "Matrix X Transpose Matrix: " << endl;
  print(Mutiply(test0, Transpose(test0)));
  */

  return 0;
}