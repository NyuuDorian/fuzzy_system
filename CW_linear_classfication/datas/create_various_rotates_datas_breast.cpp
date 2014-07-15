#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


//#define NB_PTS_TO_USE 200


double get_value_normalized(double value_to_normalize, double max, double min, double new_max, double new_min)
{
	double value_normalized((value_to_normalize-min)/(max-min)*(new_max-new_min)+new_min);//cf Min-max normalization
	return value_normalized;
}



int main(int argc, char** argv)
{

	if(argc!=3) return -1;
	else 
	{
		string title_doc(argv[1]);
		int NB_PTS_TO_USE(stoi(argv[2]));

	int NB_PTS(0), NB_COORD(0), NB_CLASS(0);
	string mot("");

	ofstream fichier_sortie(title_doc+".txt");
	ifstream fichier_bis("breast-cancer-wisconsin_ter.data");
  if(fichier_bis && fichier_sortie)
	{
		fichier_bis.seekg(0, ios::beg);//placed at the very beginning
		fichier_bis >> mot;
		NB_PTS=stoi(mot);
		//fichier_sortie << NB_PTS << endl;
		fichier_sortie << NB_PTS_TO_USE << endl;
		fichier_bis >> mot;
		NB_COORD=stoi(mot);
		fichier_sortie << NB_COORD-1 << endl;
		fichier_bis >> mot;
		NB_CLASS=stoi(mot);
		fichier_sortie << NB_CLASS << endl;
	}
	else
	{
		cout << "ERROR: Cannot open fichier_bis" << endl;
	}
	fichier_bis.close();



	int nb_rand(0);
	srand(time(0));



	//opening the file class 0 (-1)
	ifstream fichier("breast-cancer-wisconsin_ter.data");
  if(fichier && fichier_sortie)
	{
		//fichier.seekg(0, ios::beg);//placed at the very beginning 
		
		for(int i=0; i<NB_PTS_TO_USE; i++)
		{
			nb_rand = rand() % NB_PTS;//generate a random nbre in order to know which random file to use to get the datas
			//cout << nb_rand << endl;
			//num_files_used_class_0.push_back(nb_rand);//we keep it to know which file had been used
			fichier.seekg(0, ios::beg);
			fichier >> mot;//read nb_of_pt
			fichier >> mot;//read nb_of_att
			fichier >> mot;//read nb_of_class

			cout << nb_rand << endl;

			for(int k=0; k<nb_rand; k++)
			{
				for(int j=0; j<NB_COORD+1; j++) 
				{
					fichier >> mot; //we do a 'for' until we are at the requested line
				}
			}
			for(int j=0; j<NB_COORD+1; j++) 
			{
					fichier >> mot; //we do a 'for' until we are at the requested line

					cout << mot << " ";
					if(j!=0)
					{
						if(j!=NB_COORD) fichier_sortie << j-1 << " : " << (stod(mot)-1)/9 << " ";
						else 
						{
							if(mot=="4") fichier_sortie << j-1 << " : " << 1 << endl;
							if(mot=="2") fichier_sortie << j-1 << " : " << 0 << endl;
						}
					}
			}
			cout << endl;
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
