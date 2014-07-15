#ifndef _UPDATEINT_HH_
#define _UPDATEINT_HH_

#include<cstdlib>
#include<vector>

class UpdateInt
{
public:

  UpdateInt(){
    gamma = 0.1;
  }

  UpdateInt(double g){
    gamma = g;
  }

  double updateBeta(double oldB, double newB);

private:
  double gamma;

};

#endif
