#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string.h>
#include <cstring>

#define dim  3 // numbers of Demention -> 3
#define K 2
#define K2 3
#define K3 4
#define K4 5
using namespace std;
//定義類，封裝輸入向量x,及它要分到哪個類別



class InputFeature
{
public:
	double x[dim];//保存輸入數據的向量坐標
	int cluster;//標志分類的哪一類(0,1,...,K)
	InputFeature(double x[dim])//構造函數
	{
       memcpy(this->x,x,sizeof(double)*dim);
	   cluster=-1;
	}
	//輸入函數
	void print()
	{
		cout<<"cluster="<<cluster<<"   x=[";
		for (int i=0;i<dim;i++)
		{
			cout<<x[i]<<" ";
		}
		cout<<"]"<<endl;
	}
	//計算該特征向量與輸入向量的2範數(歐式距離)
	double distanceOf(double u[dim])
	{
        double distance=0;
		for (int i=0;i<dim;i++)
		{
			distance+=(u[i]-x[i])*(u[i]-x[i]);
		}
		distance=sqrt(distance);
		return distance;
	}
};


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


vector<InputFeature> InputVector;//保存輸入特征向量
void inputData(vector<double> &min, vector<double> &max)//從文件中讀取數據
{
  vector <string> fields;
  int num_input, column_num_input;
  string line;
  double xt[dim];//將讀入的字符串轉化为小數
  // Start to Split 
  getline(cin, line);
  split( fields, line, ' ' );

  

  // Analyzing the first line, get number of input and column of input
  num_input = atoi(fields[0].c_str());
  column_num_input = atoi(fields[1].c_str());

  vector<float> Test_Data;
    for (int i = 0; i < num_input; i++) {
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




	xt[0] = Test_Data[0];
	xt[1] = Test_Data[1];
	xt[2] = Test_Data[2];
/*
    cout << xt[0] << " ";
    cout << xt[1] << " ";
    cout << xt[2] << endl;
*/
    for (int k = 0;k < 3; k++) {
  		if (xt[k] > max[k])
  			max[k] = xt[k];
  		if (xt[k] < min[k])
  			min[k] = xt[k];
  }
  	Test_Data.clear();
    InputFeature t1(xt);//生成特征向量
	InputVector.push_back(t1);//保存到數組
  }

}

float RandomFloat(float lower, float upper)
{ 
  float temp;
  do{
  temp = rand() * (upper-lower) / RAND_MAX + lower;
  } while (temp > -0.01 && temp < 0.01);

  return temp;
}


//計算在誤差err內，2次迭代的結果是否一样
bool CompareU(double U0[K][dim],double U[K][dim],double err)
{
	for (int k=0;k<K;k++)
	{
		for (int d=0;d<dim;d++)
		{
			if(abs(U0[k][d]-U[k][d])>err)
			{
				return false;
			}
		}
   }
	return true;
}

// Kmeans algorithm start here 
void KMEANS(double U[K][dim], double &total_distance)
{

	//cout << "KKKKKKKKKKKKKKKK " << K << endl;
   double U0[K][dim];
   memcpy(U0,U,sizeof(double)*K*dim);
   while (true)
   {
	   //第一步 標定集合中的點，離哪個U點最近，即將其cluster修改为對應的分類
	   int j;
	   vector<InputFeature>::iterator it;
	   for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   double dist[K];
		   for (j=0;j<K;j++)//計算該向量到各個標定向量的歐式距離
		   {
			   dist[j]=it->distanceOf(U[j]);
		   }
		   double minDist=dist[0];//初始化最小距離
		   it->cluster=0;//初始化分類
		   for (j=1;j<K;j++)
		   {
			   if (dist[j]<minDist)//如果發現離第j個更近，則更新分類
			   {
				   minDist=dist[j];
				   it->cluster=j;
			   }
		   }
	   }
	   //第二步 更新重心U
	   double sum[K][dim],num[K];
	   memset(&sum,0,sizeof(double)*K*dim);
	   memset(&num,0,sizeof(double)*K);
       for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   for (int d=0;d<dim;d++)//計算所有相同分類的坐標重心
		   {
			   sum[it->cluster][d]+=it->x[d];
		   }
		   num[it->cluster]++;//計算相同分類的數目
	   }
	   for (j=0;j<K;j++)//更新標定向量的重心
	   {
		   for (int d=0;d<dim;d++)
		   {
			   if (num[j]!=0)
			     U[j][d]=(sum[j][d])/(num[j]);
		   }
	   }
	   //判斷是否收斂， U==U0時收斂
	   if (CompareU(U0,U,1.0e-5))
	   {
		   break;
	   }
	   memcpy(U0,U,sizeof(double)*K*dim);//將本次迭代的結果保存
   }
   
   //此時每個元素的分類情況为：
   
   //cout<<"Points: "<<endl;
   vector<InputFeature>::iterator it;
   //for(it = InputVector.begin(); it != InputVector.end(); ++it)
   //{
//	   it->print();
  // }
   
   //計算誤差函數
   double J = 0;
   double J2 = 0;
   for(it = InputVector.begin(); it != InputVector.end(); ++it)
   {
   		if (it->cluster == 0) {
   			J+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 1) {
   			J2+=it->distanceOf(U[it->cluster]);
   		}
	   //J+=it->distanceOf(U[0]);
	   //J2+=it->distanceOf(U[1]);
   }

   //輸出聚類的結果
   //cout<<"The Clusters location: "<<endl;
   for (int k=0;k<K;k++)
   {
	   //cout<<"Cluster "<< k <<": ";
	   for (int d=0;d<dim;d++)
	   {
		   cout<< setw(11) << U[k][d];
	   }
	   cout<<endl;
   }
   cout<< "0    " << J <<endl;
   cout<< "1    " << J2 <<endl;
}




//計算在誤差err內，2次迭代的結果是否一样
bool CompareU2(double U0[K2][dim],double U[K2][dim],double err)
{
	for (int k=0;k<K2;k++)
	{
		for (int d=0;d<dim;d++)
		{
			if(abs(U0[k][d]-U[k][d])>err)
			{
				return false;
			}
		}
   }
	return true;
}

// K2means algorithm start here 
void KMEANS2(double U[K2][dim], double &total_distance)
{

	//cout << "K2K2K2K2K2K2K2K2K2K2K2K2K2K2K2K2 " << K2 << endl;
   double U0[K2][dim];
   memcpy(U0,U,sizeof(double)*K2*dim);
   while (true)
   {
	   //第一步 標定集合中的點，離哪個U點最近，即將其cluster修改为對應的分類
	   int j;
	   vector<InputFeature>::iterator it;
	   for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   double dist[K2];
		   for (j=0;j<K2;j++)//計算該向量到各個標定向量的歐式距離
		   {
			   dist[j]=it->distanceOf(U[j]);
		   }
		   double minDist=dist[0];//初始化最小距離
		   it->cluster=0;//初始化分類
		   for (j=1;j<K2;j++)
		   {
			   if (dist[j]<minDist)//如果發現離第j個更近，則更新分類
			   {
				   minDist=dist[j];
				   it->cluster=j;
			   }
		   }
	   }
	   //第二步 更新重心U
	   double sum[K2][dim],num[K2];
	   memset(&sum,0,sizeof(double)*K2*dim);
	   memset(&num,0,sizeof(double)*K2);
       for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   for (int d=0;d<dim;d++)//計算所有相同分類的坐標重心
		   {
			   sum[it->cluster][d]+=it->x[d];
		   }
		   num[it->cluster]++;//計算相同分類的數目
	   }
	   for (j=0;j<K2;j++)//更新標定向量的重心
	   {
		   for (int d=0;d<dim;d++)
		   {
			   if (num[j]!=0)
			     U[j][d]=(sum[j][d])/(num[j]);
		   }
	   }
	   //判斷是否收斂， U==U0時收斂
	   if (CompareU(U0,U,1.0e-5))
	   {
		   break;
	   }
	   memcpy(U0,U,sizeof(double)*K2*dim);//將本次迭代的結果保存
   }
   
   //此時每個元素的分類情況为：
   
   //cout<<"Points: "<<endl;
   vector<InputFeature>::iterator it;
   //for(it = InputVector.begin(); it != InputVector.end(); ++it)
   //{
//	   it->print();
  // }
   
   //計算誤差函數
   double J = 0;
   double J2 = 0;
   double J3 = 0;

   for(it = InputVector.begin(); it != InputVector.end(); ++it)
   {
	    if (it->cluster == 0) {
   			J+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 1) {
   			J2+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 2) {
   			J3+=it->distanceOf(U[it->cluster]);
   		}
	   //J+=it->distanceOf(U[0]);
	   //J2+=it->distanceOf(U[1]);
   }

   //輸出聚類的結果
   //cout<<"The Clusters location: "<<endl;
   for (int k=0;k<K2;k++)
   {
	   //cout<<"Cluster "<< k <<": ";
	   for (int d=0;d<dim;d++)
	   {
		   cout<< setw(11) << U[k][d];
	   }
	   cout<<endl;
   }
   cout<<"0    "<< J <<endl;
   cout<<"1    "<< J2 <<endl;
   cout<<"2    "<< J3 <<endl;
}

//計算在誤差err內，2次迭代的結果是否一样
bool CompareU3(double U0[K3][dim],double U[K3][dim],double err)
{
	for (int k=0;k<K3;k++)
	{
		for (int d=0;d<dim;d++)
		{
			if(abs(U0[k][d]-U[k][d])>err)
			{
				return false;
			}
		}
   }
	return true;
}

// K3means algorithm start here 
void KMEANS3(double U[K3][dim], double &total_distance)
{

	//cout << "K3K3K3K3K3K3K3K3K3K3K3K3K3K3K3K3 " << K3 << endl;
   double U0[K3][dim];
   memcpy(U0,U,sizeof(double)*K3*dim);
   while (true)
   {
	   //第一步 標定集合中的點，離哪個U點最近，即將其cluster修改为對應的分類
	   int j;
	   vector<InputFeature>::iterator it;
	   for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   double dist[K3];
		   for (j=0;j<K3;j++)//計算該向量到各個標定向量的歐式距離
		   {
			   dist[j]=it->distanceOf(U[j]);
		   }
		   double minDist=dist[0];//初始化最小距離
		   it->cluster=0;//初始化分類
		   for (j=1;j<K3;j++)
		   {
			   if (dist[j]<minDist)//如果發現離第j個更近，則更新分類
			   {
				   minDist=dist[j];
				   it->cluster=j;
			   }
		   }
	   }
	   //第二步 更新重心U
	   double sum[K3][dim],num[K3];
	   memset(&sum,0,sizeof(double)*K3*dim);
	   memset(&num,0,sizeof(double)*K3);
       for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   for (int d=0;d<dim;d++)//計算所有相同分類的坐標重心
		   {
			   sum[it->cluster][d]+=it->x[d];
		   }
		   num[it->cluster]++;//計算相同分類的數目
	   }
	   for (j=0;j<K3;j++)//更新標定向量的重心
	   {
		   for (int d=0;d<dim;d++)
		   {
			   if (num[j]!=0)
			     U[j][d]=(sum[j][d])/(num[j]);
		   }
	   }
	   //判斷是否收斂， U==U0時收斂
	   if (CompareU(U0,U,1.0e-5))
	   {
		   break;
	   }
	   memcpy(U0,U,sizeof(double)*K3*dim);//將本次迭代的結果保存
   }
   
   //此時每個元素的分類情況为：
   
   //cout<<"Points: "<<endl;
   vector<InputFeature>::iterator it;
   //for(it = InputVector.begin(); it != InputVector.end(); ++it)
   //{
//	   it->print();
  // }
   
   //計算誤差函數
   double J = 0;
   double J2 = 0;
   double J3 = 0;
   double J4 = 0;

   for(it = InputVector.begin(); it != InputVector.end(); ++it)
   {
	    if (it->cluster == 0) {
   			J+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 1) {
   			J2+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 2) {
   			J3+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 3) {
   			J4+=it->distanceOf(U[it->cluster]);
   		}
   }

   //輸出聚類的結果
   //cout<<"The Clusters location: "<<endl;
   for (int k=0;k<K3;k++)
   {
	   //cout<<"Cluster "<< k <<": ";
	   for (int d=0;d<dim;d++)
	   {
		   cout<< setw(11) << U[k][d];
	   }
	   cout<<endl;
   }
   cout<<"0    "<< J <<endl;
   cout<<"1    "<< J2 <<endl;
   cout<<"2    "<< J3 <<endl;
   cout<<"3    "<< J4 <<endl;
}

//計算在誤差err內，2次迭代的結果是否一样
bool CompareU4(double U0[K4][dim],double U[K4][dim],double err)
{
	for (int k=0;k<K4;k++)
	{
		for (int d=0;d<dim;d++)
		{
			if(abs(U0[k][d]-U[k][d])>err)
			{
				return false;
			}
		}
   }
	return true;
}

// K4means algorithm start here 
void KMEANS4(double U[K4][dim], double &total_distance)
{

	//cout << "K4K4K4K4K4K4K4K4K4K4K4K4K4K4K4K4 " << K4 << endl;
   double U0[K4][dim];
   memcpy(U0,U,sizeof(double)*K4*dim);
   while (true)
   {
	   //第一步 標定集合中的點，離哪個U點最近，即將其cluster修改为對應的分類
	   int j;
	   vector<InputFeature>::iterator it;
	   for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   double dist[K4];
		   for (j=0;j<K4;j++)//計算該向量到各個標定向量的歐式距離
		   {
			   dist[j]=it->distanceOf(U[j]);
		   }
		   double minDist=dist[0];//初始化最小距離
		   it->cluster=0;//初始化分類
		   for (j=1;j<K4;j++)
		   {
			   if (dist[j]<minDist)//如果發現離第j個更近，則更新分類
			   {
				   minDist=dist[j];
				   it->cluster=j;
			   }
		   }
	   }
	   //第二步 更新重心U
	   double sum[K4][dim],num[K4];
	   memset(&sum,0,sizeof(double)*K4*dim);
	   memset(&num,0,sizeof(double)*K4);
       for(it = InputVector.begin(); it != InputVector.end(); ++it)
	   {
		   for (int d=0;d<dim;d++)//計算所有相同分類的坐標重心
		   {
			   sum[it->cluster][d]+=it->x[d];
		   }
		   num[it->cluster]++;//計算相同分類的數目
	   }
	   for (j=0;j<K4;j++)//更新標定向量的重心
	   {
		   for (int d=0;d<dim;d++)
		   {
			   if (num[j]!=0)
			     U[j][d]=(sum[j][d])/(num[j]);
		   }
	   }
	   //判斷是否收斂， U==U0時收斂
	   if (CompareU(U0,U,1.0e-5))
	   {
		   break;
	   }
	   memcpy(U0,U,sizeof(double)*K4*dim);//將本次迭代的結果保存
   }
   
   //此時每個元素的分類情況为：
   
   //cout<<"Points: "<<endl;
   vector<InputFeature>::iterator it;
   //for(it = InputVector.begin(); it != InputVector.end(); ++it)
   //{
//	   it->print();
  // }
   
   //計算誤差函數
   double J = 0;
   double J2 = 0;
   double J3 = 0;
   double J4 = 0;
   double J5 = 0;

   for(it = InputVector.begin(); it != InputVector.end(); ++it)
   {
	   if (it->cluster == 0) {
   			J+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 1) {
   			J2+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 2) {
   			J3+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 3) {
   			J4+=it->distanceOf(U[it->cluster]);
   		}
   		if (it->cluster == 4) {
   			J5+=it->distanceOf(U[it->cluster]);
   		}
   }

   //輸出聚類的結果
   //cout<<"The Clusters location: "<<endl;
   for (int k=0;k<K4;k++)
   {
	   //cout<<"Cluster "<< k <<": ";
	   for (int d=0;d<dim;d++)
	   {
		   cout<< setw(11) << U[k][d];
	   }
	   cout<<endl;
   }
   cout<<"0    "<< J <<endl;
   cout<<"1    "<< J2 <<endl;
   cout<<"2    "<< J3 <<endl;
   cout<<"3    "<< J4 <<endl;
   cout<<"4    "<< J5 <<endl;
}


int main()
{
	double total_distance;
	vector<double> min;
  	vector<double> max;
  	for (int i = 0;i < 3; i++) {
  		min.push_back(100);
  		max.push_back(-100);
  	}
	// Read input file
	inputData(min, max);
	srand((unsigned)time(NULL));
	// Initialize start cluster
	double num1, num2, num3, num4, num5, num6, num7, num8, num9,  num10, num11,num12, num13, num14, num15;
	num1 = RandomFloat(min[0], max[0]);
	num1 = RandomFloat(min[0], max[0]);
	num2 = RandomFloat(min[1], max[1]);
	num3 = RandomFloat(min[2], max[2]);

	num4 = RandomFloat(min[0], max[0]);
	num5 = RandomFloat(min[1], max[1]);
	num6 = RandomFloat(min[2], max[2]);
	/*
	vector<double> num1;
	vector<double> num2;
	vector<double> num3;
	for (int i = 0; i < K; i++) {
		num1.push_back(RandomFloat(min[0], max[0]););
		num2.push_back(RandomFloat(min[1], max[1]));
		num3.push_back(RandomFloat(min[2], max[2]));
	}
*/

	cout << "K: 2" << endl;
	cout << "Means (size: 2 X 3)" << endl;
	double U[K][dim]={{num1, num2, num3},{num4, num5, num6}};
	KMEANS(U, total_distance);

	num1 = RandomFloat(min[0], max[0]);
	num2 = RandomFloat(min[1], max[1]);
	num3 = RandomFloat(min[2], max[2]);
	num4 = RandomFloat(min[0], max[0]);
	num5 = RandomFloat(min[1], max[1]);
	num6 = RandomFloat(min[2], max[2]);
	num7 = RandomFloat(min[0], max[0]);
	num8 = RandomFloat(min[1], max[1]);
	num9 = RandomFloat(min[2], max[2]);

	cout << endl << "K: 3" << endl;
	cout << "Means (size: 3 X 3)" << endl;
	double total_distance2;
    double W[K2][dim]={{num1, num2, num3},{num4, num5, num6},{num7,num8,num9}};
    KMEANS2(W, total_distance2);

    num1 = RandomFloat(min[0], max[0]);
	num2 = RandomFloat(min[1], max[1]);
	num3 = RandomFloat(min[2], max[2]);
	num4 = RandomFloat(min[0], max[0]);
	num5 = RandomFloat(min[1], max[1]);
	num6 = RandomFloat(min[2], max[2]);
	num7 = RandomFloat(min[0], max[0]);
	num8 = RandomFloat(min[1], max[1]);
	num9 = RandomFloat(min[2], max[2]);
	num10 = RandomFloat(min[0], max[0]);
	num11 = RandomFloat(min[1], max[1]);
	num12 = RandomFloat(min[2], max[2]);

	cout << endl << "K: 4" << endl;
	cout << "Means (size: 4 X 3)" << endl; 
    double V[K3][dim] = 				 {{num1, num2, num3},
    									 {num4, num5, num6},
    									 {num7, num8, num9},
    									 {num10, num11, num12}};
    KMEANS3(V, total_distance2);


	num1 = RandomFloat(min[0], max[0]);
	num2 = RandomFloat(min[1], max[1]);
	num3 = RandomFloat(min[2], max[2]);
	num4 = RandomFloat(min[0], max[0]);
	num5 = RandomFloat(min[1], max[1]);
	num6 = RandomFloat(min[2], max[2]);
	num7 = RandomFloat(min[0], max[0]);
	num8 = RandomFloat(min[1], max[1]);
	num9 = RandomFloat(min[2], max[2]);
	num10 = RandomFloat(min[0], max[0]);
	num11 = RandomFloat(min[1], max[1]);
	num12 = RandomFloat(min[2], max[2]);
	num13 = RandomFloat(min[0], max[0]);
	num14 = RandomFloat(min[1], max[1]);
	num15 = RandomFloat(min[2], max[2]);



    cout << endl << "K: 5" << endl;
	cout << "Means (size: 5 X 3)" << endl;
    double X[K4][dim] = 				 {{num1, num2, num3},
    									 {num4, num5, num6},
    									 {num7, num8, num9},
    									 {num10, num11, num12},
    									 {num13, num14, num15}};
    KMEANS4(X, total_distance2);

	return 0;
}