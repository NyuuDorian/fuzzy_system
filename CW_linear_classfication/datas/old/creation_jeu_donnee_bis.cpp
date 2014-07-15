#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


#define NBRE_DATA 2000
#define DIM 8


int main()
{

	int nbre_datas(NBRE_DATA), nb_rand(0);	
	vector< vector<double> > coord;
	vector<int> class_value;
	vector<string> mon_dico;
	srand(time(0));
	string mot(""), classe("");
	string tmp("");

	//opening the file class 0 (-1)
	ifstream fichier("/home/julien/project_fuzzy/CW_linear_classfication/datas/test.txt");
  if(fichier)
	{
		fichier.seekg(0, ios::beg);//placed at the very beginning 
		//string ligne;
		//getline(fichier, ligne);
		//nbre_datas=stoi(ligne);//getting the number of files
		fichier >> tmp;
		fichier >> tmp;
		fichier >> tmp;

		for(int i=0; i<NBRE_DATA; i++)
		{
			std::vector<double> tempvector,tempvector2;
			//coord.push_back(0);
			//
			//cout << nb_rand << endl;
			//num_files_used_class_0.push_back(nb_rand);//we keep it to know which file had been used
			for(int j=0; j<DIM; j++) 
			{
				fichier >> mot;
				tempvector.push_back(stod(mot));
			}
			coord.push_back(tempvector);
			fichier >> classe;
			class_value.push_back(stoi(classe));
		}
	}
  else
  {
      cout << "ERROR: Cannot open fichier on reading mode." << endl;
  }
	//fichier.close(); //done automatically?


	/*for(unsigned int i=0; i<NBRE_DATA; i++) 
	{
		for(int j=0; j<DIM; j++)
		{
			cout << coord.at(i).at(j) << "\t";
		}
		cout << class_value.at(i) << endl;
	}*/

	ofstream output("output_bis.txt");
	if(output)
	{
		for(int i=0; i<NBRE_DATA; i++)
		{		
			nb_rand = rand() % nbre_datas;//generate a random nbre in order to know which random file to use to get the datas
			nbre_datas--;
			for(int i=0; i<DIM; i++) output << coord.at(nb_rand).at(i) << " ";
			output << class_value.at(nb_rand) << endl;
			coord.erase(coord.begin()+nb_rand);
			class_value.erase(class_value.begin()+nb_rand); 
		}
	}
	else
  {
      cout << "ERROR: cannot open output on writting mode." << endl;
  }

	return EXIT_SUCCESS;
}
