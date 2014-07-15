#include<cstdlib>
#include<iostream>
#include<string>
#include<sstream>
#include<boost/random.hpp>
#include<vector>

#include "defineClass.hh"
#include "updateDis.hh"

using namespace boost;

//メンバシップ値の算出
double membership_function(double X,int part,int L){
  double Xk = (double)(part-1)/(double)(L-1);
  double tmp = fabs(X-Xk);
  double v = 1/(double)(L-1);
  double membership = 1-(tmp/v);
  //std::cout << tmp << std::endl;
  if(membership < 0)
    membership = 0;
  return membership;
}

int main(int argc,char *argv[])
{
//初期値設定　分割数，ルール数，平均，分散
  int L = 3;//default
  int seed = 0;//default
  double phi = 1.0;//default
  //std::cout << "the number of partition is " << L << std::endl;
  if( argv[1] != NULL )
  {
    std::string s(argv[1]);
    std::istringstream is(s);
    is >> L;
  }
  std::cout << L << std::endl;

  uniform_real<> range(0.0,1.0);
  int ruleNum = pow(L,2);
  std::vector<double> mean;
  std::vector< std::vector<double> > variance;
  DefineClass DC;
  UpdateDis UD(phi);
  //std::cout << DC.identifyClass(0.3,0.3,225) << std::endl;
  int count = 0;
  int rulecount = 0;//上限ruleNum-1
  bool onLine;
  double x,y;
  int className;
  std::vector<double> mValue;
  double inference;//識別するための値　正なら+1クラス　負なら-1クラス
  int infClass;//推論結果
  int gridcorrect=0;//gridでの正解数
  int gridcount=0;//gridのオンライン以外の数
  std::vector<double> correct;//grid用にdoubleへ変更
  for( int i=0; i<361; i++ )
    correct.push_back(0);

  while( seed < 10 )
  {
    //if ( seed % 20 == 0 )
    // std::cout << "." << std::endl;
    //初期化
    mean.clear();
    variance.clear();
    for( int i=0; i<ruleNum; i++ )
    {
      std::vector<double> tempvector;
      for( int j=0; j<ruleNum; j++ )
      {
        if( i == j )
          tempvector.push_back(0.1);//分散初期値
        else
          tempvector.push_back(0.0);
      }
      variance.push_back(tempvector);
      mean.push_back(0);//平均初期値
    }
    count = 0;
    variate_generator< mt19937,uniform_real<> > Patrand( mt19937(seed),range );

    while( count < 361 )
    {
      //初期化
      mValue.clear();
      for( int i=0; i<ruleNum; i++ )
        mValue.push_back(1);
      onLine = true;
      rulecount = 0;
      inference = 0;
      gridcorrect = 0;
      gridcount = 0;

      //学習用パターン生成
      while( onLine )
      {
        x = Patrand();
        y = Patrand();
        onLine = DC.IsOnLine(x,y,count);
      }
      className = DC.identifyClass(x,y,count);


      //メンバシップ値計算
      //2次元問題確定なのでforを２回繰り返すが，多次元ならいつも通りの指数を使ったプログラムで
      for( int ypart = 1; ypart <= L; ypart++ )
      {
        for( int xpart = 1; xpart <= L; xpart++ )
        {
          mValue.at(rulecount) *= membership_function(x,xpart,L);
          mValue.at(rulecount) *= membership_function(y,ypart,L);
          rulecount++;
        }
      }

/*
      //学習用パターンでの推測
      //membership値ベクトルとCFの平均ベクトルの掛け算（スカラーになる）今はこれ
      //メンバシップ値とCFの掛け算の絶対値をとった時に一番でかいやつのルールをつかう方法がしたい
      for( int i=0; i<ruleNum; i++ )
        inference += mValue.at(i) * mean.at(i);
      if( inference > 0 )
      {
        infClass = 1;
        //std::cout << "推論結果　+1" << std::endl;
      }
      else if (inference < 0 )
      {
        infClass = -1;
        //std::cout << "推論結果　-1" << std::endl;
      }
      else
      {
        infClass = 0;
        //std::cout << "推論結果　0" << std::endl;
      }
      if ( infClass == className )
      {
        //std::cout << "正解" << std::endl;
        correct.at(count) += 1;
      }
*/

      //分布更新
      UD.updateAlpha( mean, variance, mValue, className );
      mean = UD.updateMean( mean, variance, mValue, className );
      variance = UD.updateVariance( variance, mValue, className );

      //grid状での正解率算出
      for( double x1=0.01; x1<1.00; x1=x1+0.01 )
      {
        for( double x2=0.01; x2<1.00; x2=x2+0.01 )
        {
          if( DC.IsOnLine(x1,x2,count) )
            continue;
          className = DC.identifyClass(x1,x2,count);
          mValue.clear();
          for( int i=0; i<ruleNum; i++ )
            mValue.push_back(1);
          rulecount = 0;
          inference = 0;
          for( int ypart = 1; ypart <= L; ypart++ )
          {
            for( int xpart = 1; xpart <= L; xpart++ )
            {
              mValue.at(rulecount) *= membership_function(x1,xpart,L);
              mValue.at(rulecount) *= membership_function(x2,ypart,L);
              rulecount++;
            }
          }
          for( int i=0; i<ruleNum; i++ )
            inference += mValue.at(i) * mean.at(i);
          if( inference > 0 )
            infClass = 1;
          else if (inference < 0 )
            infClass = -1;
          else
            infClass = 0;
          if( infClass == className )
            gridcorrect++;
          gridcount++;
        }
      }
      correct.at(count) += (double)gridcorrect / (double)gridcount;

      count++;
    }
    seed++;

  }
  std::cout << std::endl;

  for( int i=0; i<361; i++ )
    std::cout << correct.at(i) / 10.0 << std::endl;

  return 0;
}
