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
#include <stdio.h>
#include <string.h>

#define alpha 0.1
#define E 2.718
#define Training 180000


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
  //do{
  //temp = rand() * (upper-lower) / RAND_MAX + lower;
  temp = rand() * (upper-lower) / RAND_MAX + lower;
  //} while (temp > -0.01 && temp < 0.01);

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
  RandomFloat(-weightRange, weightRange); 
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
  //print(x);
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
  
  //cout << "RRRR: " << result << endl;
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
  


  clock_t tStart = clock();
  srand((unsigned)time(NULL));
  float weightRange = 1 / sqrt(2);
  



  /**************
  Breaking INPUTS
  **************/
  
  string line;
  vector <vector<float> > input_vec;
  vector <vector<float> > v;
  vector <vector<float> > w;
  vector <string> fields;
  vector <float> Case;
  vector <float> y;
  vector<float> layer1;
  int num_input;
  int column_num_input;
  int num_test;
  int column_num_test;

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

  // Start to Split 
  getline(cin, line);
  split( fields, line, ' ' );

  // Analyzing the first line, get number of input and column of input
  num_input = atoi(fields[0].c_str());
  column_num_input = atoi(fields[1].c_str());
  //cout << num_input << endl;
  //cout << column_num_input << endl;

  for (int i = 0; i < num_input; i++) {
    getline(cin, line);
    fields.clear();
    split( fields, line, ' ' );

    for (int i = 0; i < 5; i++)
      Case.push_back(atof(fields[i].c_str()));

    input_vec.push_back(Case);
    Case.clear();
  }
  //print(input_vec);

  // So far, here I get input_vec as a 150 x 4 Matrix

  // Here I will need to get v and w, I will need to pass 
  // #1. Trainging Data's Size
  // #2. Hidden Layer's Size
  // #3. v and w as reference 
  int inSize = 4;
  int hiddenSize = 3;
  int outSize = 3;
  intiWeight(inSize, outSize, hiddenSize, v, w);
  // And I should return matirx v and w back

//print (v);
//print (w);
  //int training_index= 0;

  for (int i = 0; i < Training; i++) {
    // Then, I should randomly pick one of the them for training
    int training_index;
    
    training_index = rand() % num_input; // Randomly get index between 0 ~ 149
    training_index = rand() % num_input;
    //cout << "TITI: " << training_index << endl;
    vector<vector<float> > x; // x is the traning input
    //training_index = 0;
  
    x.push_back(input_vec[training_index]);
    int result;
    result = x[0][4];
    x[0].pop_back();    // remove the last element, that is, result
    //x.push_back(-1);  // Add Bias into x
    //x[0].insert(x[0].begin(), -1);


    //cout << "result: " << result << endl;

    Adjust(v, w, result, x);
    x.clear();
  } 


  
  vector<vector<float> > result;

  getline(cin, line);
  split( fields, line, ' ' );
  int index, max;

  num_test = atoi(fields[0].c_str());
  column_num_test = atoi(fields[1].c_str());
  //cout << num_test << endl;
  //cout << column_num_test << endl;

  vector<float> Test_Data;
  vector<vector<float> > Test_X;
  for (int i = 0; i < num_test; i++) {
    getline(cin, line);
    fields.clear();
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
      Test_Data.push_back(atof(str.c_str()));
      pch = strtok (NULL, " ");
    }



    //Test_Data.push_back(atof(fields[0].c_str()));
    //Test_Data.push_back(atof(fields[1].c_str()));
    //Test_Data.push_back(atof(fields[2].c_str()));
    //Test_Data.push_back(atof(fields[3].c_str()));
    //Test_Data.insert(Test_Data.begin(), -1);
    Test_X.push_back(Test_Data);
    //print(Test_X);
    result = Forward(Test_X, v, w);





    

    cout << "TEST(" << i << "): ";
    index = 0;
    for (int j =0; j < result[0].size(); j++) {
      if (result[0][j] > result[0][index])
        index = j;
    //cout << result[0][j] << "  ";
    }

    cout  << index;
    cout << endl;
    //for (int j = 0; j < fields.size(); j++)
      //cout << "==>" << fields[i] << endl;
    //print(fields);
    //cout << endl;
    Test_Data.clear();
    Test_X.clear();

    //layer1.clear();
    

  }
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


  return 0;
}