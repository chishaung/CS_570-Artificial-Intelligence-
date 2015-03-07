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

#define alpha 0.15
#define E 2.71828
#define Training 70000

using namespace std;


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
  temp = rand() * (upper-lower) / RAND_MAX + lower;
  //} while (temp > -0.9 && temp < 0.9);

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

vector<float> Forward(vector<float> x, 
  vector <vector<float> > v,vector <vector<float> > w) {

  vector<float> layer1;
  vector<float> layer2;
  layer1.clear();
  
  float value;
  value = 
  x[0]*v[0][0] + x[1]*v[1][0] + x[2]*v[2][0] + x[3]*v[3][0] + x[4]*v[4][0];
  value = Sigmoid(value);
  layer1.push_back(value);

  value = 
  x[1]*v[0][1] + x[1]*v[1][1] + x[2]*v[2][1] + x[3]*v[3][1] + x[4]*v[4][1];
  value = Sigmoid(value);
  layer1.push_back(value);

  value = 
  x[2]*v[0][2] + x[1]*v[1][2] + x[2]*v[2][2] + x[3]*v[3][2] + x[4]*v[4][2];
  value = Sigmoid(value);
  layer1.push_back(value);

  // Add Bias into layer1, and get a 1 x 4 matrix layer1
  layer1.insert(layer1.begin(), -1);



  value = 
  layer1[0]*w[0][0] +  layer1[1]*w[1][0] + layer1[1]*w[2][0] + layer1[1]*w[3][0];
  value = Sigmoid(value);
  layer2.push_back(value);

  value = 
  layer1[0]*w[0][1] +  layer1[1]*w[1][1] + layer1[1]*w[2][1] + layer1[1]*w[3][1];
  value = Sigmoid(value);
  layer2.push_back(value);

  value = 
  layer1[0]*w[0][2] +  layer1[1]*w[1][2] + layer1[1]*w[2][2] + layer1[1]*w[3][2];
  value = Sigmoid(value);
  layer2.push_back(value);


  // So, yes, I get 1 x 3 matrix 'layer2', and return it 

  return layer2;
}

void Adjust(vector <vector<float> > &v,vector <vector<float> > &w, int result, vector<float> x) {

  vector<float> delta1;
  vector<float> delta2;
  vector<float> t;
  vector<float> layer1;
  vector<float> layer2;
  vector<float> y;

  
  float value;
  value = 
  x[0]*v[0][0] + x[1]*v[1][0] + x[2]*v[2][0] + x[3]*v[3][0] + x[4]*v[4][0];
  value = Sigmoid(value);
  layer1.push_back(value);

  value = 
  x[1]*v[0][1] + x[1]*v[1][1] + x[2]*v[2][1] + x[3]*v[3][1] + x[4]*v[4][1];
  value = Sigmoid(value);
  layer1.push_back(value);

  value = 
  x[2]*v[0][2] + x[1]*v[1][2] + x[2]*v[2][2] + x[3]*v[3][2] + x[4]*v[4][2];
  value = Sigmoid(value);
  layer1.push_back(value);

  // Add Bias into layer1, and get a 1 x 4 matrix layer1
  layer1.insert(layer1.begin(), -1);



  value = 
  layer1[0]*w[0][0] +  layer1[1]*w[1][0] + layer1[1]*w[2][0] + layer1[1]*w[3][0];
  value = Sigmoid(value);
  layer2.push_back(value);

  value = 
  layer1[0]*w[0][1] +  layer1[1]*w[1][1] + layer1[1]*w[2][1] + layer1[1]*w[3][1];
  value = Sigmoid(value);
  layer2.push_back(value);

  value = 
  layer1[0]*w[0][2] +  layer1[1]*w[1][2] + layer1[1]*w[2][2] + layer1[1]*w[3][2];
  value = Sigmoid(value);
  layer2.push_back(value);


  // So, yes, I get 1 x 3 matrix 'layer2', and return it 

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

  for (int i = 0; i < 3; i++) {
    value = (t[i] - y[i]) * y[i] * (1 - y[i]);
    delta2.push_back(value);
  }

  vector <vector<float> > trans_w;
  trans_w = Transpose(w);
  // To get Delta 1:
  // delta1 =( layer1 (1 - layer1)) ( delta2 . Transpose[w]);
  // w is 4 x 3, trans(w) is 3 x 4
  // delta2 . trans(w) is 1 x 4 
  vector<float> part1;
  float temp_value;
  temp_value = 
  delta2[0] * trans_w[0][0] + delta2[1] * trans_w[1][0] + delta2[2] * trans_w[2][0];
  part1.push_back(temp_value);

  temp_value = 
  delta2[0] * trans_w[0][1] + delta2[1] * trans_w[1][1] + delta2[2] * trans_w[2][1];
  part1.push_back(temp_value);

  temp_value = 
  delta2[0] * trans_w[0][2] + delta2[1] * trans_w[1][2] + delta2[2] * trans_w[2][2];
  part1.push_back(temp_value);

  temp_value = 
  delta2[0] * trans_w[0][3] + delta2[1] * trans_w[1][3] + delta2[2] * trans_w[2][3];
  part1.push_back(temp_value);

  vector<float> part2;
  float value2;
  for (int i = 0; i < layer1.size(); i++) {
    value2 = layer1[i] * (1 - layer1[i]);
    part2.push_back(value2);
  }

  

  for (int i = 0; i < part1.size(); i++) {
    temp_value = part1[i] * part2[i];
    delta1.push_back(temp_value);
  }


  // So far, I get delta1 and delta2
  // Now, time to adjust weight v and w


  vector <vector<float> > w_part2;
  vector <vector<float> > Trans_layer1;
  vector<float> Temp_layer1;

  Temp_layer1.push_back(layer1[0]);
  Trans_layer1.push_back(Temp_layer1);
  Temp_layer1.clear();
  Temp_layer1.push_back(layer1[1]);
  Trans_layer1.push_back(Temp_layer1);
  Temp_layer1.clear();
  Temp_layer1.push_back(layer1[2]);
  Trans_layer1.push_back(Temp_layer1);
  Temp_layer1.clear();
  Temp_layer1.push_back(layer1[3]);
  Trans_layer1.push_back(Temp_layer1);
  Temp_layer1.clear();

  Temp_layer1.push_back(Trans_layer1[0][0] * delta2[0]);
  Temp_layer1.push_back(Trans_layer1[0][0] * delta2[1]);
  Temp_layer1.push_back(Trans_layer1[0][0] * delta2[2]);
  w_part2.push_back(Temp_layer1);
  Temp_layer1.clear();

  Temp_layer1.push_back(Trans_layer1[1][0] * delta2[0]);
  Temp_layer1.push_back(Trans_layer1[1][0] * delta2[1]);
  Temp_layer1.push_back(Trans_layer1[1][0] * delta2[2]);
  w_part2.push_back(Temp_layer1);
  Temp_layer1.clear();

  Temp_layer1.push_back(Trans_layer1[2][0] * delta2[0]);
  Temp_layer1.push_back(Trans_layer1[2][0] * delta2[1]);
  Temp_layer1.push_back(Trans_layer1[2][0] * delta2[2]);
  w_part2.push_back(Temp_layer1);
  Temp_layer1.clear();

  Temp_layer1.push_back(Trans_layer1[3][0] * delta2[0]);
  Temp_layer1.push_back(Trans_layer1[3][0] * delta2[1]);
  Temp_layer1.push_back(Trans_layer1[3][0] * delta2[2]);
  w_part2.push_back(Temp_layer1);
  Temp_layer1.clear();


  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      w[i][j] = w[i][j] + (alpha * w_part2[i][j]);
    }
  }

  // Here we get adjusted weight w
  // Now, to get weight v

  // Remove first element of delta1
  
  vector<float> temp_delta1;
  for (int i = 1; i < delta1.size(); i++)
    temp_delta1.push_back(delta1[i]);
  delta1 = temp_delta1;
  temp_delta1.clear();
  
  
  //delta1.pop_back();
  // Trans_x
  vector <vector<float> > v_part2;
  vector <vector<float> > Trans_x;
  vector<float> Temp_x;

  Temp_x.push_back(x[0]);
  Trans_x.push_back(Temp_x);
  Temp_x.clear();
  Temp_x.push_back(x[1]);
  Trans_x.push_back(Temp_x);
  Temp_x.clear();
  Temp_x.push_back(x[2]);
  Trans_x.push_back(Temp_x);
  Temp_x.clear();
  Temp_x.push_back(x[3]);
  Trans_x.push_back(Temp_x);
  Temp_x.clear();
  Temp_x.push_back(x[4]);
  Trans_x.push_back(Temp_x);
  Temp_x.clear();

  // for adjusted v

  Temp_x.push_back(Trans_x[0][0] * delta1[0]);
  Temp_x.push_back(Trans_x[0][0] * delta1[1]);
  Temp_x.push_back(Trans_x[0][0] * delta1[2]);
  v_part2.push_back(Temp_x);
  Temp_x.clear();

  Temp_x.push_back(Trans_x[1][0] * delta1[0]);
  Temp_x.push_back(Trans_x[1][0] * delta1[1]);
  Temp_x.push_back(Trans_x[1][0] * delta1[2]);
  v_part2.push_back(Temp_x);
  Temp_x.clear();

  Temp_x.push_back(Trans_x[2][0] * delta1[0]);
  Temp_x.push_back(Trans_x[2][0] * delta1[1]);
  Temp_x.push_back(Trans_x[2][0] * delta1[2]);
  v_part2.push_back(Temp_x);
  Temp_x.clear();

  Temp_x.push_back(Trans_x[3][0] * delta1[0]);
  Temp_x.push_back(Trans_x[3][0] * delta1[1]);
  Temp_x.push_back(Trans_x[3][0] * delta1[2]);
  v_part2.push_back(Temp_x);
  Temp_x.clear();

  Temp_x.push_back(Trans_x[4][0] * delta1[0]);
  Temp_x.push_back(Trans_x[4][0] * delta1[1]);
  Temp_x.push_back(Trans_x[4][0] * delta1[2]);
  v_part2.push_back(Temp_x);
  Temp_x.clear();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      v[i][j] = v[i][j] + (alpha * v_part2[i][j]);
    }
  }
}

/************
Main Function
************/

int main (int argc, char* argv[]) {


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
  print(test0);
  print(Transpose(test0));
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

  for (int i = 0; i < Training; i++) {
  // Then, I should randomly pick one of the them for training
  int training_index;
  training_index = rand() % 150; // Randomly get index between 0 ~ 149
  vector<float> x; // x is the traning input
  x = input_vec[training_index];
  int result;
  result = x[4];
  x.pop_back();    // remove the last element, that is, result
  //x.push_back(-1);  // Add Bias into x
  x.insert(x.begin(), -1);

  // Now, send x(should be size 5, add bias already) to forward()
  // #1. 1 x 5 matrix 'x'
  // #2. 5 x 3 matrix 'v'
  // #3. 4 x 3 matrix 'w'
  // then it should return 1 x 3 matrix 'layer2' back as 'y'
  //y = Forward(x, v, w);
  // Here I get 1 x 3 matrix 'y'

  // Now, time to adjust weights
  // Should call the Adjust() function
  // I should pass
  // #1. 4 x 3 matrix 'w' as reference, and it may chaged
  // #2. 5 x 3 matrix 'v' as reference, and it may chaged  
  Adjust(v, w, result, x);

  } // Finish training



  // So now, I get the new weight matrix of 'v' and 'w'
  // and keep doing loop to adjust weight.


  
  vector<float> result;
  /*
  vector<float> trythis;
  trythis.push_back(8);
  trythis.push_back(4);
  trythis.push_back(6);
  trythis.push_back(.5);
  result = Forward(trythis, v, w, layer1);

  cout << "The value of layer2 after apply Sigmoid function: " << endl;
  for (int i =0; i < result.size(); i++) {
    cout << result[i] << "  ";
  }
  cout << endl;
  */

  // After N times of training, the weight should be adjusted well (or better)
  // So now, it's the time to send test data to the adjusted weight NN
  // And see what is the result
  getline(cin, line);
  split( fields, line, ' ' );
  int index, max;

  num_test = atoi(fields[0].c_str());
  column_num_test = atoi(fields[1].c_str());
  //cout << num_test << endl;
  //cout << column_num_test << endl;

  vector<float> Test_Data;
  for (int i = 0; i < num_test; i++) {
    getline(cin, line);
    fields.clear();
    split( fields, line, ' ' );
    //cout << fields[0] << " " << fields[1] << " " <<  fields[2] << " " << fields[3] << endl;
    Test_Data.push_back(atof(fields[0].c_str()));
    Test_Data.push_back(atof(fields[1].c_str()));
    Test_Data.push_back(atof(fields[2].c_str()));
    Test_Data.push_back(atof(fields[3].c_str()));
    result = Forward(Test_Data, v, w);





    Test_Data.clear();

    cout << "TEST(" << i+1 << "): ";
    index = 0;
    for (int j =0; j < result.size(); j++) {
      if (result[j] > result[index])
        index = j;
    //cout << result[j] << "  ";
  }

    cout  << index;
    cout << endl;
    //for (int j = 0; j < fields.size(); j++)
      //cout << "==>" << fields[i] << endl;
    //print(fields);
    //cout << endl;
    Test_Data.clear();
    //layer1.clear();

  }
  











	return 0;
}