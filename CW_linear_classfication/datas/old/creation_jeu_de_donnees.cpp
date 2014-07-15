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


double get_value_normalized(double value_to_normalize, double max, double min, double new_max, double new_min)
{
	double value_normalized((value_to_normalize-min)/(max-min)*(new_max-new_min)+new_min);//cf Min-max normalization
	return value_normalized;
}



int main()
{

	int nbre_datas(0), nb_rand(0);	
	vector<int> num_files_used_class_0, num_files_used_class_1;
	vector<string> mon_dico;
	srand(time(0));
	

	//opening the file class 0 (-1)
	ifstream fichier("comp.sys.ibm.pc.hardware.txt"), fichier_class1("comp.sys.mac.hardware.txt");
  if(fichier)
	{
		fichier.seekg(0, ios::beg);//placed at the very beginning 
		string ligne;
		getline(fichier, ligne);
		nbre_datas=stoi(ligne);//getting the number of files

		for(int i=0; i<NBRE_FILES_USED; i++)
		{
			nb_rand = rand() % nbre_datas;//generate a random nbre in order to know which random file to use to get the datas
			//cout << nb_rand << endl;
			num_files_used_class_0.push_back(nb_rand);//we keep it to know which file had been used
			fichier.seekg(0, ios::beg);
			for(int j=0; j<nb_rand+1; j++) getline(fichier, ligne); //we do a 'for' until we are at the requested line

			//string name_file_tmp("/home/julien/project_fuzzy/datas/comp.sys.ibm.pc.hardware/"+ligne);
			//cout << name_file_tmp << endl;
			ifstream fichier_tmp("/home/julien/project_fuzzy/CW_linear_classfication/datas/comp.sys.ibm.pc.hardware/"+ligne);//we open the randomly chosen file
			if(fichier_tmp)
			{
				string mot("");
				while(fichier_tmp >> mot)
				{
					if(std::find(mon_dico.begin(), mon_dico.end(), mot) == mon_dico.end()) mon_dico.push_back(mot);
				}
				//cout << "seems to work" << endl;
			}
			else
		  {
	      cout << "ERROR: Cannot open file_tmp."+ligne << endl;
		  }
			//fichier_tmp.close();//done automatically?
		}


	}
  else
  {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }
	//fichier.close(); //done automatically?


/////////////////////////////////////////


//opening the file class 1
  if(fichier_class1)
	{
		fichier_class1.seekg(0, ios::beg);//placed at the very beginning 
		string ligne("");
		getline(fichier_class1, ligne);
		nbre_datas=stoi(ligne);//getting the number of files
		for(int i=0; i<NBRE_FILES_USED; i++)
		{
			nb_rand = rand() % nbre_datas;//generate a random nbre in order to know which random file to use to get the datas
			//cout << nb_rand << endl;			
			num_files_used_class_1.push_back(nb_rand);//we keep it to know which file had been used
			fichier_class1.seekg(0, ios::beg);
			for(int j=0; j<nb_rand+1; j++) getline(fichier_class1, ligne); //we do a 'for' until we are at the requested line

			//string name_file_tmp("/home/julien/project_fuzzy/datas/comp.sys.ibm.pc.hardware/"+ligne);
			//cout << name_file_tmp << endl;
			ifstream fichier_tmp("/home/julien/project_fuzzy/CW_linear_classfication/datas/comp.sys.mac.hardware/"+ligne);//we open the randomly chosen file
			if(fichier_tmp)
			{
				string mot("");
				while(fichier_tmp >> mot)
				{
					if(find(mon_dico.begin(), mon_dico.end(), mot) == mon_dico.end()) mon_dico.push_back(mot);

				}
				//cout << "seems to work" << endl;
			}
			else
		  {
	      cout << "ERROR: Cannot open file_tmp." << endl;
		  }
			//fichier_tmp.close();//done automatically?
		}
	}
  else
  {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }
	//fichier_class1.close(); //done automatically?
	

	//for(unsigned int i=0; i<mon_dico.size(); i++) cout << mon_dico[i] << "\t";

	ofstream monFlux("datas_normalized.txt");
	ifstream class0("/home/julien/project_fuzzy/CW_linear_classfication/datas/comp.sys.ibm.pc.hardware.txt"), class1("/home/julien/project_fuzzy/CW_linear_classfication/datas/comp.sys.mac.hardware.txt");
	vector<int> bag_of_words_max(mon_dico.size(), 0), bag_of_words_min(mon_dico.size(), 0);
	double mat_bag_of_words_class0[NBRE_FILES_USED][mon_dico.size()], mat_bag_of_words_class1[NBRE_FILES_USED][mon_dico.size()];

//have to do initialization
	for(int i=0; i<NBRE_FILES_USED; i++)
	{	
		for(int j=0; j<(int)mon_dico.size(); j++)
		{	
			mat_bag_of_words_class0[i][j]=0;
			mat_bag_of_words_class0[i][j]=0;
		}
	}
//end of initialization

	if(class0 && class1)
	{
		for(int i=0; i<NBRE_FILES_USED; i++)
		{	
			class0.seekg(0, ios::beg);
			class1.seekg(0, ios::beg);
			string ligne(""), ligne_bis("");
			vector<int> bag_of_words_class0(mon_dico.size(), 0), bag_of_words_class1(mon_dico.size(), 0);
			for(int j=0; j<num_files_used_class_0.at(i)+1; j++) getline(class0, ligne);
		//cout << num_files_used_class_0.at(i) << endl;
		//cout << ligne << endl;
			ifstream fichier_tmp("/home/julien/project_fuzzy/CW_linear_classfication/datas/comp.sys.ibm.pc.hardware/"+ligne);//we open the randomly chosen file
			if(fichier_tmp)
			{
				string mot("");
				while(fichier_tmp >> mot)
				{
				//bag_of_words_class0.at(find(mon_dico.begin(), mon_dico.end(), mot))++;
					sort(mon_dico.begin(), mon_dico.end());
					auto iter = std::lower_bound(mon_dico.begin(), mon_dico.end(), mot);
					int index=(int)(iter-mon_dico.begin());
					bag_of_words_class0[index]++;
					mat_bag_of_words_class0[i][index]++;
					//cout << mot << "\t" << bag_of_words_class0[index]; 
					if(bag_of_words_class0[index]>bag_of_words_max[index]) bag_of_words_max[index]=bag_of_words_class0[index];
					//if(bag_of_words_class0[index]<bag_of_words_min[index]) bag_of_words_min[index]=bag_of_words_class0[index];
				//cout << "index" << int(iter-mon_dico.begin()) << endl;
				}
				//cout << "seems to work" << endl;
			}
			else
			{
	  		cout << "ERROR: Cannot open file_tmp." << endl;
			}



			for(int j=0; j<num_files_used_class_1.at(i)+1; j++) getline(class1, ligne_bis);
			ifstream fichier_tmp_bis("/home/julien/project_fuzzy/CW_linear_classfication/datas/comp.sys.mac.hardware/"+ligne_bis);//we open the randomly chosen file
			if(fichier_tmp_bis)
			{
				string mot("");
				while(fichier_tmp_bis >> mot)
				{
				//bag_of_words_class0.at(find(mon_dico.begin(), mon_dico.end(), mot))++;
					sort(mon_dico.begin(), mon_dico.end());
					auto iter = std::lower_bound(mon_dico.begin(), mon_dico.end(), mot);
					int index=(int)(iter-mon_dico.begin());
					bag_of_words_class1[index]++;
					mat_bag_of_words_class1[i][index]++;
					//cout << mot << "\t" << bag_of_words_class1[index]; 
					if(bag_of_words_class1[index]>bag_of_words_max[index]) bag_of_words_max[index]=bag_of_words_class1[index];
					//if(bag_of_words_class1[index]<bag_of_words_min[index]) bag_of_words_min[index]=bag_of_words_class1[index];
					//cout << "index" << int(iter-mon_dico.begin()) << endl;
				}
				//cout << "seems to work" << endl;
			}
			else
			{
	  		cout << "ERROR: Cannot open file_tmp_bis." << endl;
			}
		}


//initialization of mat of min
for(int j=0; j<(int)mon_dico.size(); j++)
{	
	bag_of_words_min[j]=mat_bag_of_words_class0[0][j];
}

//calc of the min
for(int i=0; i<NBRE_FILES_USED; i++)
{	
	for(int j=0; j<(int)mon_dico.size(); j++)
	{	
		if(bag_of_words_min[j]>mat_bag_of_words_class0[i][j])	bag_of_words_min[j]=mat_bag_of_words_class0[i][j];
		if(bag_of_words_min[j]>mat_bag_of_words_class1[i][j])	bag_of_words_min[j]=mat_bag_of_words_class1[i][j];
	}
}



		monFlux << 2*NBRE_FILES_USED << endl;
		monFlux << (int)mon_dico.size() << endl;
		monFlux << 2 << endl;

//CODE COPY
		for(int i=0; i<NBRE_FILES_USED; i++)
		{	
			
			for(int j=0; j<(int)mon_dico.size(); j++) 
			{
				mat_bag_of_words_class0[i][j]=get_value_normalized(mat_bag_of_words_class0[i][j], bag_of_words_max[j], bag_of_words_min[j], 1, 0);
				monFlux << mat_bag_of_words_class0[i][j] << " ";				
			}
			monFlux << "0" << endl;



			for(int j=0; j<(int)mon_dico.size(); j++) 
			{
				mat_bag_of_words_class1[i][j]=get_value_normalized(mat_bag_of_words_class1[i][j], bag_of_words_max[j], bag_of_words_min[j], 1, 0);
				monFlux << mat_bag_of_words_class1[i][j] << " ";				
			}
			monFlux << "1" << endl;
		}


	}

	return EXIT_SUCCESS;
}
