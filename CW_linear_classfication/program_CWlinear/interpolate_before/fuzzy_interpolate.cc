#include<cstdlib>
#include<iostream>
#include<string>
#include<sstream>
#include<boost/random.hpp>
#include<vector>

#include "defineClass.hh"
#include "updateInt.hh"

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

double certaintyFactor(std::vector<double> betaQ,int maxclass){
  double betabar = 0;
  double betasum = 0;

  for(int i=0;i<2;i++){//二クラス問題
    betasum += betaQ.at(i);
  }
  betabar = (betasum - betaQ.at(maxclass)) / (2 - 1);

  return ((betaQ.at(maxclass) - betabar) / betasum);
}

int main(int argc,char *argv[])
{
//初期値設定　分割数，ルール数，平均，分散
  int L = 3;//default
  int seed = 0;//default
  int classNum = 2;//default クラス数を変更する場合：要改変
  //std::cout << "the number of partition is " << L << std::endl;
  if( argv[1] != NULL )
  {
    std::string s(argv[1]);
    std::istringstream is(s);
    is >> L;
  }
  std::cout << "the number of partition is " << L << std::endl;

  uniform_real<> range(0.0,1.0);
  int ruleNum = pow(L,2);//二次元問題
  DefineClass DC;
  UpdateInt UI;
  int count = 0;
  int rulecount = 0;//上限ruleNum-1
  bool onLine;
  double x,y;
  int className;
  std::vector< std::vector<double> > betaold;
  std::vector< std::vector<double> > betanew;
  std::vector<int> C;
  std::vector<double> CF;
  double tempbeta=1;
  std::vector<double> inference;
  double maxinf=0;
  int infClass;//推論結果
  int gridcorrect=0;//gridでの正解数
  int gridcount=0;//gridのオンライン以外の数
  std::vector<double> correct;//grid用にdoubleへ変更
  for( int i=0; i<361; i++ )
    correct.push_back(0);

  while( seed < 10 )
  {
    //if ( seed % 2 == 0 )
    //std::cout << "." << std::endl;
    //初期化
    betaold.clear();
    for( int i=0; i<ruleNum; i++ )
    {
      std::vector<double> tempvector;
      for( int j=0; j<2; j++ )
      {
        tempvector.push_back(0);
      }
      betaold.push_back(tempvector);
    }
    count = 0;
    variate_generator< mt19937,uniform_real<> > Patrand( mt19937(seed),range );

    while( count < 361 )
    {
      //初期化
      betanew.clear();
      C.clear();
      CF.clear();
      inference.clear();
      for( int i=0; i<ruleNum; i++ )
      {
        std::vector<double> tempvector;
        for( int j=0; j<2; j++ )
          tempvector.push_back(0);
        betanew.push_back(tempvector);
        C.push_back(0);
        CF.push_back(0);
        inference.push_back(0);
      }
      onLine = true;
      rulecount = 0;
      gridcorrect = 0;
      gridcount = 0;
      maxinf = 0;

      //学習用パターン生成
      while( onLine )
      {
        x = Patrand();
        y = Patrand();
        onLine = DC.IsOnLine(x,y,count);
      }
      className = DC.identifyClass(x,y,count);
      if( className == -1 )
        className = 0;

      //メンバシップ値計算
      //2次元問題確定なのでforを２回繰り返すが，多次元ならいつも通りの指数を使ったプログラムで
      for( int ypart = 1; ypart <= L; ypart++ )
      {
        for( int xpart = 1; xpart <= L; xpart++ )
        {
          tempbeta = 1;
          tempbeta *= membership_function(x,xpart,L);
          tempbeta *= membership_function(y,ypart,L);
          betanew.at(rulecount).at(className) += tempbeta;
          rulecount++;
        }
      }

      //ベータ更新
      for( int i=0; i<ruleNum; i++ )
      {
        for( int j=0; j<2; j++ )
          betanew.at(i).at(j) = UI.updateBeta(betaold.at(i).at(j),betanew.at(i).at(j));
      }
      betaold = betanew;

      //後件部決定
      for( int i=0; i<ruleNum; i++ )
      {
        if( betanew.at(i).at(0) > betanew.at(i).at(1) )
        {
          C.at(i) = 0;
          CF.at(i) = certaintyFactor(betanew.at(i),0);

        }
        else
        {
          C.at(i) = 1;
          CF.at(i) =  certaintyFactor(betanew.at(i),1);
        }
      }


      //grid状での正解率算出
      for( double x1=0.01; x1<1.00; x1=x1+0.01 )
      {
        for( double x2=0.01; x2<1.00; x2=x2+0.01 )
        {
          if( DC.IsOnLine(x1,x2,count) )
            continue;
          className = DC.identifyClass(x1,x2,count);
          if( className == -1 )
            className = 0;
          rulecount = 0;
          maxinf = 0;
          for( int ypart = 1; ypart <= L; ypart++ )
          {
            for( int xpart = 1; xpart <= L; xpart++ )
            {
              tempbeta = 1;
              tempbeta *= membership_function(x1,xpart,L);
              tempbeta *= membership_function(x2,ypart,L);
              tempbeta *= CF.at(rulecount);
              inference.at(rulecount) = tempbeta;
              rulecount++;
            }
          }
          for( int i=0; i<ruleNum; i++ )
          {
            if( maxinf < inference.at(i) )
            {
              maxinf = inference.at(i);
              infClass = C.at(i);
            }
          }
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
