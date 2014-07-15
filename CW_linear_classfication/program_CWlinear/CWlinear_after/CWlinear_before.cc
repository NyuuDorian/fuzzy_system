#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<boost/random.hpp>
#include<vector>

#include "updateDis.hh"

using namespace boost;


int main(int argc,char *argv[])
{
//初期値設定　分割数，ルール数，平均，分散
  int seed = 0;//default
  double phi = 1.0;//default
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
  int trainNum,dataNum,dimNum,classNum,tempclass,gomi;
  double temp,temp2;
  std::vector< std::vector<double> > trainvector,errorvector,testvector;
  std::vector<int> trainclass,errorclass,testclass;

  int minusmiss,plusmiss;
  std::vector<int> MMset,PMset,CNset;

  int startindex;

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
    if( tempclass == 0 )
      tempclass = -1;
    trainclass.push_back(tempclass);
    trainE >> tempclass;
    if( tempclass == 0 )
      tempclass = -1;
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
  test >> classNum;
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
    if( tempclass == 0 )
      tempclass = -1;
    testclass.push_back(tempclass);
  }

  std::vector<double> mean;
  std::vector< std::vector<double> > variance;
  UpdateDis UD(phi);
  //std::cout << DC.identifyClass(0.3,0.3,225) << std::endl;
  int count = 0;
  std::vector<double> trainingdata;
  double classvalue;
  double inference;//識別するための値　正なら+1クラス　負なら-1クラス
  int infClass;//推論結果
  int correctNum=0;//gridでの正解数
  std::vector<double> rate;

  double inferenceminus=0;

  //初期化
  mean.clear();
  variance.clear();
  for( int i=0; i<dimNum; i++ )
  {
    std::vector<double> tempvector;
    for( int j=0; j<dimNum; j++ )
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

  while( count < trainNum )
  {
    if( count%50 == 0 )
      std::cout << count << std::endl;
    //初期化
    trainingdata.clear();

    inference = 0;
    correctNum = 0;
    minusmiss = 0;
    plusmiss = 0;

    //学習用パターン
    if( count < errorNum )
      startindex = trainNum - errorNum;
    else
      startindex = 0;
    uniform_int<> ranvalue(startindex,trainvector.size()-1);
    variate_generator< boost::mt19937,boost::uniform_int<> >
    randD( boost::mt19937(count),ranvalue );
    int ranindex = randD();
    trainingdata = trainvector.at(ranindex);
    tempclass = trainclass.at(ranindex);
    std::vector< std::vector<double> >::iterator it =
      trainvector.erase(trainvector.begin()+ranindex);
    std::vector<int>::iterator it2 = trainclass.erase(trainclass.begin()+ranindex);
    if( tempclass == 0 )
      tempclass = -1;
    classvalue = (double)tempclass;

    //inferenceをマイナス側に調整するための数値調査
    for( int i=0; i<dimNum; i++ ){
      inference += trainingdata.at(i) * mean.at(i);
    }
    if( inference > 0 && classvalue < 0 ){
      //std::cout << "o" << std::endl;
      inferenceminus = 2 * inference;
    }

    //分布更新
    UD.updateAlpha( mean, variance, trainingdata, classvalue );
    mean = UD.updateMean( mean, variance, trainingdata, classvalue );
    variance = UD.updateVariance( variance, trainingdata, classvalue );

    //正解率算出
    for( int n=0; n<dataNum; n++ )
    {
      inference = 0;
      for( int i=0; i<dimNum; i++ ){

        inference += testvector.at(n).at(i) * mean.at(i);
      }
      //inference -= inferenceminus;
      //std::cout << inference << std::endl; 0.0003
      if( inference > 0 )
        infClass = 1;
      else if (inference < 0 )
        infClass = -1;
      else
        infClass = 0;
      if( infClass == testclass.at(n) )
        correctNum++;
      if( infClass == 1 && testclass.at(n) == -1 )
        minusmiss++;
      if( infClass == -1 && testclass.at(n) == 1 )
        plusmiss++;
    }
    rate.push_back((double)correctNum/(double)dataNum);
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
