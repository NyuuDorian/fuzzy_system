#include "updateDis.hh"


void UpdateDis::updateAlpha(std::vector<double> mean, std::vector< std::vector<double> > variance,
                            std::vector<double> mValue, double className)
{
  double Mi = 0;
  for( int i=0; i<mean.size(); i++ )
    Mi += mValue.at(i) * mean.at(i);
  Mi *= className;

  std::vector<double> tVi;
  for( int i=0; i<mean.size(); i++ )
  {
    tVi.push_back(0);
    for( int j=0; j<mean.size(); j++ )
    {
      tVi.at(i) += mValue.at(j) * variance.at(j).at(i);
    }
  }
  double Vi = 0;
  for( int i=0; i<mean.size(); i++ )
    Vi += tVi.at(i) * mValue.at(i);

  double denominator;
  double numerator;
  double beta = 2 * phi * Mi + 1;
  numerator = -1 * beta + sqrt( beta * beta - ( 8 * phi * (Mi - (phi * Vi)) ) );
  denominator = 4 * phi * Vi;

  alpha = numerator / denominator;

  if( alpha < 0 )
    alpha = 0;

//  std::cout << mValue.at(5) << std::endl;

}


std::vector<double> UpdateDis::updateMean(std::vector<double> mean, std::vector< std::vector<double> > variance,
                             std::vector<double> mValue, double className)
{
  std::vector<double> first;
  std::vector<double> second;
  first = mean;
  for( int i=0; i<mean.size(); i++ )
  {
    second.push_back(0);
    for( int j=0; j<mean.size(); j++ )
    {
      second.at(i) += variance.at(i).at(j) * mValue.at(j);
    }
    second.at(i) *= alpha * className;
  }

  std::vector<double> ans;
  for( int i=0; i<mean.size(); i++ )
    ans.push_back( first.at(i) + second.at(i) );

  return ans;
}


std::vector< std::vector<double> > UpdateDis::updateVariance(std::vector< std::vector<double> > variance,
                                                             std::vector<double> mValue, double className)
{
  std::vector< std::vector<double> > first;
  std::vector< std::vector<double> > second;

  first = variance;//第一項

  std::vector<double> tate;//第二項左
  for( int i=0; i<mValue.size(); i++ )
  {
    tate.push_back(0);
    for( int j=0; j<mValue.size(); j++ )
      tate.at(i) += variance.at(i).at(j) * mValue.at(j);
  }

  double scalar;//第二項真ん中
  double denominator;
  double numerator;
  numerator = 2 * alpha * phi;
  std::vector<double> tVi;
  for( int i=0; i<mValue.size(); i++ )
  {
    tVi.push_back(0);
    for( int j=0; j<mValue.size(); j++ )
    {
      tVi.at(i) += mValue.at(j) * variance.at(j).at(i);
    }
  }
  double Vi = 0;
  for( int i=0; i<mValue.size(); i++ )
    Vi += tVi.at(i) * mValue.at(i);
  denominator = 1 + ( 2 * alpha * phi * Vi );
  scalar = numerator / denominator;

  std::vector<double> yoko;//第二項右
  for( int i=0; i<mValue.size(); i++ )
  {
    yoko.push_back(0);
    for( int j=0; j<mValue.size(); j++ )
      yoko.at(i) += mValue.at(j) * variance.at(j).at(i);
  }

  for( int i=0; i<mValue.size(); i++ )//第二項全部
  {
    std::vector<double> temp;
    for( int j=0; j<mValue.size(); j++ )
      temp.push_back( tate.at(i) * yoko.at(j) * scalar );
    second.push_back(temp);
  }

  std::vector< std::vector<double> > ans;//統合
  for( int i=0; i<mValue.size(); i++ )
  {
    std::vector<double> temp;
    for( int j=0; j<mValue.size(); j++ )
      temp.push_back( first.at(i).at(j) - second.at(i).at(j) );
    ans.push_back(temp);
  }

  return ans;
}
