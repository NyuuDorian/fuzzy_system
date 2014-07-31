#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

#define K_MAX 5 //nombre darea MAX par cote
#define K_MIN 2 //nombre MIN darea par cote
#define NBRE_PTS 699 //nbre total de points
#define NBRE_COORD 10 //nbre de coord par point
#define NBRE_CLASSE 2 //nbre de classes differentes

//in order to normalize I am using Min-max normalization
//vi'= (vi-min)/(max-min)*(new_max-new_min)+new_min ==> [0,1]

//(other normalization) z-score normalization
//vi'=(vi-mean)/SD
//SD stands for Standard Deviation 

double get_value_normalized(double value_to_normalize, double max, double min, double new_max, double new_min)
{
	double value_normalized((value_to_normalize-min)/(max-min)*(new_max-new_min)+new_min);//cf Min-max normalization
	return value_normalized;
}


int main()
{


	double min_max_each_coord[NBRE_COORD][2]={0};//matrix gathering the min and the max of each column, [0] is MIN and [1] is MAX
	double mat_initial_coord[NBRE_PTS][NBRE_COORD]={0}, mat_normalized_coord[NBRE_PTS][NBRE_COORD]={0};//matrix gathering all the coordinates NOT NORMALIZED extracted from the file
	int mat_initial_class_of_each_point[NBRE_PTS]={0};//matrix giving the class of each point
	string str;	


	//cout.precision(6);
	//cout.setf(ios::fixed,ios::floatfield);

	ifstream fichier("wine.data.txt");
  if(fichier)
	{
		fichier.seekg(0, ios::beg);//on se place au debut du fichier

//on recupere toutes les donnees
		for(int i=0; i<NBRE_PTS; i++)
		{
			string ligne;
			getline(fichier, ligne); //on recupere ligne par ligne le fichier
			//cout << ligne << endl;
			size_t depart(0),found(-1);//ces marqueurs permettent de recuperer les indices de la ou sont placees les virgules
			for(int j=0; j<NBRE_COORD+1; j++)//also found!=std::string::npos
			{
				found = ligne.find(',',found+1);
				if(j==0) mat_initial_class_of_each_point[i]=stoi(ligne.substr(depart, found-depart));
				else 
				{
					mat_initial_coord[i][j-1]=stod(ligne.substr(depart, found-depart));
					//cout << mat_initial_coord[i][j-1] << ", ";
				}
				if(found!=string::npos) depart=found+1;
			}
			//cout << mat_initial_class_of_each_point[i] << endl; //OK
		}
  }
  else
  {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }

	//initialization of mat min_max with the first ligne of coordinates
	for(int i=0; i<NBRE_COORD; i++)
	{
		min_max_each_coord[i][0]=mat_initial_coord[0][i];
		min_max_each_coord[i][1]=mat_initial_coord[0][i];
	}

	//now we get the real min and max
	for(int i=0; i<NBRE_PTS; i++)
	{
		for(int j=0; j<NBRE_COORD; j++)
		{
			if(mat_initial_coord[i][j]<min_max_each_coord[j][0]) min_max_each_coord[j][0]=mat_initial_coord[i][j];
			else if(mat_initial_coord[i][j]>min_max_each_coord[j][1]) min_max_each_coord[j][1]=mat_initial_coord[i][j];
		}
	}

	
	string const nomFichier("/home/julien/project_fuzzy/IRIS_WINE/test_writing.txt");
	ofstream monFlux(nomFichier.c_str());
	if(monFlux)
	{
		//now we have the get the normalized values
		for(int i=0; i<NBRE_PTS; i++)
		{
			for(int j=0; j<NBRE_COORD; j++)
			{
				mat_normalized_coord[i][j]=get_value_normalized(mat_initial_coord[i][j], min_max_each_coord[j][1], min_max_each_coord[j][0], 1, 0);
				cout << mat_normalized_coord[i][j] << ", ";
				monFlux << mat_normalized_coord[i][j] << ", ";
			}
			cout << mat_initial_class_of_each_point[i] << endl;
			monFlux << mat_initial_class_of_each_point[i] << endl;
		}
	}	
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}
	

	return EXIT_SUCCESS;
}
