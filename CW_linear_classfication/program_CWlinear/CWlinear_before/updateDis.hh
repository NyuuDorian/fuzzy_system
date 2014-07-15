#ifndef _UPDATEDIS_HH_
#define _UPDATEDIS_HH_

#include<cstdlib>
#include<iostream>
#include<cmath>
#include<vector>

class UpdateDis
{
public:

  UpdateDis(){
    phi = 1.0;
    alpha = 0.0;
  }

  UpdateDis(double p){
    phi = p;
    alpha = 0.0;
  }

  void updateAlpha(std::vector<double> mean, std::vector< std::vector<double> > variance,
                   std::vector<double> mValue, double className);

  std::vector<double> updateMean(std::vector<double> mean, std::vector< std::vector<double> > variance,
                                 std::vector<double> mValue, double className);

  std::vector< std::vector<double> > updateVariance(std::vector< std::vector<double> > variance,
                                                    std::vector<double> mValue, double className);


private:
  double phi;//求め方が分からないのでエクセルの関数を使用
  double alpha;

};

#endif
