#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

int main () {
      //double tab [327680]; // se plante à l'exécution
      double * tab= new double [(int) pow(3,13)];
      int i;
      //tab = new double [5000000];
      for (i=0;i<(int) pow(3,13);i++)
			{
         tab [i] = i;
					cout << tab[i] << endl;
			}
      return 0;
}
