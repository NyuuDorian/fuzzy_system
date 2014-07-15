#include<cstdlib>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<boost/random.hpp>
#include<vector>

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
  int classNum = 2;//default クラス数を変更する場合：要改変

  std::string trainingfile,errorfile,testfile,Enum,outputfile;
  int errorNum=50;//固定
  //std::cout << "the number of partition is " << L << std::endl;
  if( argv[1] != NULL )
    trainingfile = trainingfile.append(argv[1]);
  else
  {
    std::cout << "there is no training filename" << std::endl;
    return 1;
  }
  if( argv[2] != NULL )
    errorfile = errorfile.append(argv[2]);
  else
  {
    std::cout << "there is no training2 filename" << std::endl;
    return 1;
  }
  if( argv[3] != NULL )
    testfile = testfile.append(argv[3]);
  else
  {
    std::cout << "there is no test filename" << std::endl;
    return 1;
  }
  Enum = Enum.append(argv[4]);
  std::istringstream is(Enum);
  is >> errorNum;
  Enum = Enum.append("outputfile.txt");

  std::ifstream training(trainingfile.c_str());
  std::ifstream trainE(errorfile.c_str());
  std::ifstream test(testfile.c_str());
  int trainNum,dataNum,dimNum,tempclass,gomi;
  double temp,temp2,tempbeta;
  std::vector< std::vector<double> > trainvector,errorvector,testvector;
  std::vector<int> trainclass,errorclass,testclass;

  int minusmiss,plusmiss;
  std::vector<int> MMset,PMset,CNset;
  int endindex;

  training >> trainNum;
  training >> dimNum;
  training >> gomi;
  trainE >> gomi;
  trainE >> gomi;
  trainE >> gomi;
  for( int i=0; i<trainNum; i++ )
  {
    std::vector<double> tempvector,tempvector2;
    for( int j=0; j<dimNum; j++ )
    {
      training >> temp;
      trainE >> temp2;
      tempvector.push_back(temp);
      tempvector2.push_back(temp2);
    }
    trainvector.push_back(tempvector);
    errorvector.push_back(tempvector2);
    training >> tempclass;
    trainclass.push_back(tempclass);
    trainE >> tempclass;
    errorclass.push_back(tempclass);
  }

  for( int i=0;i<errorNum;i++ )
  {
    uniform_int<> dice(0,errorvector.size()-1);
    variate_generator< boost::mt19937,boost::uniform_int<> >
      randD( boost::mt19937(i),dice );
    int tempvalue = randD();
    trainvector.push_back(errorvector.at(tempvalue));
    trainclass.push_back(errorclass.at(tempvalue));
    std::vector< std::vector<double> >::iterator it =
      errorvector.erase(errorvector.begin()+tempvalue);
    std::vector<int>::iterator it2 = errorclass.erase(errorclass.begin()+tempvalue);
  }
  trainNum += errorNum;

  test >> dataNum;
  test >> gomi;
  test >> gomi;
  for( int i=0; i<dataNum; i++ )
  {
    std::vector<double> tempvector;
    for( int j=0; j<dimNum; j++ )
    {
      test >> temp;
      tempvector.push_back(temp);
    }
    testvector.push_back(tempvector);
    test >> tempclass;
    testclass.push_back(tempclass);
  }

  int ruleNum = pow(L,dimNum);//二次元問題
  UpdateInt UI;
  int count = 0;
  int rulecount = 0;//上限ruleNum-1
  double x,y;
  int className;
  std::vector< std::vector<double> > betaold;
  std::vector< std::vector<double> > betanew;
  std::vector<int> C;
  std::vector<double> CF;
  std::vector<double> trainingdata;
  std::vector<int> partition;
  std::vector<double> inference;
  double maxinf=0;
  int infClass;//推論結果
  int correctNum=0;
  std::vector<double> rate;

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

  while( count < trainNum )
  {
    if( count%20 == 0 )
      std::cout << count << std::endl;
    //初期化
    betanew.clear();
    C.clear();
    CF.clear();
    inference.clear();
    trainingdata.clear();
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
    partition.clear();
    for( int i=0; i<dimNum; i++ )
      partition.push_back(0);

    rulecount = 0;
    correctNum = 0;
    minusmiss = 0;
    plusmiss = 0;
    maxinf = 0;

    //学習用パターン生成
    if( count < trainNum - errorNum )
      endindex = trainvector.size() - 1 - errorNum;
    else
      endindex = trainvector.size()-1;
    uniform_int<> ranvalue(0,endindex);
    variate_generator< boost::mt19937,boost::uniform_int<> >
      randD( boost::mt19937(count),ranvalue );
    int ranindex = randD();
    trainingdata = trainvector.at(ranindex);
    tempclass = trainclass.at(ranindex);
    std::vector< std::vector<double> >::iterator it =
      trainvector.erase(trainvector.begin()+ranindex);
    std::vector<int>::iterator it2 = trainclass.erase(trainclass.begin()+ranindex);
    className = tempclass;


    //メンバシップ値計算
    for( int i=0; i<ruleNum; i++ )
    {
      tempbeta = 1;
      for( int j=0; j<dimNum; j++ )
      {
        //std::cout << membership_function(trainingdata.at(7),partition.at(7)+1,L) << std::endl;
        tempbeta *= membership_function(trainingdata.at(j),partition.at(j)+1,L);
      }
      betanew.at(i).at(className) += tempbeta;
      partition.at(0) += 1;//繰り上げていく
      for( int j=0; j<dimNum-1; j++ )
      {
        if(partition.at(j) > L-1)
        {
          partition.at(j) = 0;
          partition.at(j+1) += 1;
        }
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

    //正解率算出
    for( int n=0; n<dataNum; n++ )
    {
      partition.clear();
      for( int i=0; i<dimNum; i++ )
        partition.push_back(0);
      inference.clear();
      for( int i=0; i<ruleNum; i++ )
        inference.push_back(1);
      rulecount = 0;
      maxinf = 0;

      for( int i=0; i<ruleNum; i++ )
      {
        for( int j=0; j<dimNum; j++ )
        {
          //std::cout << membership_function(testvector.at(n).at(7),partition.at(7)+1,L) << std::endl;
          inference.at(i) *= membership_function(testvector.at(n).at(j),partition.at(j)+1,L);
        }
        partition.at(0) += 1;//繰り上げていく
        for( int j=0; j<dimNum-1; j++ )
        {
          if(partition.at(j) > L-1)
          {
            partition.at(j) = 0;
            partition.at(j+1) += 1;
          }
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
      if( infClass == testclass.at(n) )
        correctNum++;
      if( infClass == 1 && testclass.at(n) == 0 )
        minusmiss++;
      if( infClass == 0 && testclass.at(n) == 1 )
        plusmiss++;
    }
    rate.push_back((double)correctNum / (double)dataNum );
    CNset.push_back(correctNum);
    MMset.push_back(minusmiss);
    PMset.push_back(plusmiss);
    count++;
  }
  std::cout << std::endl;
  std::ofstream output(Enum.c_str());
  for( int i=0; i<trainNum; i++ )
    output << rate.at(i) << " " << CNset.at(i) << " " << PMset.at(i) << " " << MMset.at(i) << std::endl;
  training.close();
  trainE.close();
  test.close();
  output.close();
  
  return 0;
}
