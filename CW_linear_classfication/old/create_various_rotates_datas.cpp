#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


#define NBRE_FILES_USED 50


int main(int argc, char** argv)
{

	if(argc!=2) return -1;
	else 
	{
		string title_doc(argv[1]); //output_bis


	//opening the file class 0 (-1)
	ifstream fichier(title_doc+".txt");
  if(fichier)
	{
		fichier.seekg(0, ios::beg);//placed at the very beginning 
		string mot("");
//		getline(fichier, ligne);
		fichier >> mot; //2000
		int NBRE_POINTS(stoi(mot));
		fichier >> mot; //8
		int NBRE_COORD(stoi(mot));
		fichier >> mot; //2
		int NBRE_CLASSES(stoi(mot));
		
		double** all_coord=new double*[NBRE_POINTS];
		for(int i=0; i<NBRE_POINTS; i++) all_coord[i]=new double[NBRE_COORD];
		
		ofstream monFlux(title_doc+"_2"+".txt");
		monFlux << NBRE_POINTS << endl;
		monFlux << NBRE_COORD << endl;
		monFlux << NBRE_CLASSES << endl;

		for(int i=0; i<NBRE_POINTS; i++)
		{
			for(int j=0; j<NBRE_COORD+1; j++)
			{
				fichier >> mot;
				monFlux << j << " : " << mot << "\t";
			}
			monFlux << endl;
		}


	}
  else
  {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }
	//fichier.close(); //done automatically?

	return EXIT_SUCCESS;
	}
}
