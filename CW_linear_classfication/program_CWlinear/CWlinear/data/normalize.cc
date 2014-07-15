#include<cstdlib>
#include<fstream>
#include<vector>
int main(int argc,char *argv[])
{
  std::string filename(argv[1]);
  std::string outputname(argv[2]);
  std::ifstream input(filename.c_str());
  std::ofstream output(outputname.c_str());
  double tmp;
  int dataNum,dimNum,number;
  input >> dataNum;
  input >> dimNum;
  input >> number;
  std::vector<double> data[dataNum];
  int classname[dataNum];
  for(int i=0; i<dataNum; i++){
    for(int j=0; j<dimNum; j++){
      input >> tmp;
      data[i].push_back(tmp);
    }
    input >> classname[i];
  }

  double min_data=100;
  double max_data=0;

  for(int j=0; j<dimNum; j++){
    min_data = 100;
    max_data = 0;
    for(int i=0; i<dataNum; i++){
      if( min_data > data[i].at(j) )
        min_data = data[i].at(j);
      if( max_data < data[i].at(j) )
        max_data = data[i].at(j);
    }
    for(int i=0; i<dataNum; i++){
      data[i].at(j) -= min_data;
      if( max_data != 0 )
        data[i].at(j) /= (max_data-min_data);
    }
  }

  output << dataNum << std::endl;
  output << dimNum << std::endl;
  output << number << std::endl;

  for(int i=0; i<dataNum; i++){
    for(int j=0; j<dimNum; j++){
      output << data[i].at(j) << " ";
    }
    output << classname[i] << std::endl;
  }

  input.close();
  output.close();

  return 0;
}
