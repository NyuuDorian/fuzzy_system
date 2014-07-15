#include "updateInt.hh"

double UpdateInt::updateBeta(double oldB, double newB)
{
  return (( ( 1 - gamma ) * oldB ) + ( gamma * newB ) );
}
