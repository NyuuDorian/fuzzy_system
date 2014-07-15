#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

#define K_MAX 5 //nombre darea MAX par cote
#define K_MIN 2 //nombre MIN darea par cote
#define NBRE_PTS 150 //nbre total de points
#define NBRE_COORD 4 //nbre de coord par point
#define NBRE_CLASSE 3 //nbre de classes differentes


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

double get_value_membership_function(double x, double k, double L)
{
	double value_membership(0), a(0), b(0);
	a=(k-1)/(L-1);
	b=1/(L-1);
	value_membership=max(1-(std::fabs(x-a)/b),(double)0);
	return value_membership;
}

double get_6_significative_num(double number_to_truncate)
{
	double new_num=number_to_truncate*pow(10,6), intpart;
	double fractpart=modf (new_num , &intpart);
	if(fractpart>=0.5) new_num=ceil(new_num);
	else new_num=floor(new_num);
	//cout << new_num << "\t";
	new_num/=pow(10,6);
	//cout << new_num << "\t";
	return new_num;
}


int main()
{


/*sepal length: 4.3  7.9   5.84  0.83    0.7826   
    sepal width: 2.0  4.4   3.05  0.43   -0.4194
   petal length: 1.0  6.9   3.76  1.76    0.9490  (high!)
    petal width: 0.1  2.5   1.20  0.76    0.9565  (high!)*/

	//enum Iris{Iris-setosa, Iris-versicolor, Iris-virginica};
	//int nbre_pts(150), nbre_coord(4);//number of points, number of coordinates
	double min_max_each_coord[NBRE_COORD][2]={{4.3,7.9}, {2.0,4.4}, {1.0, 6.9}, {0.1, 2.5}};//matrix gathering the min and the max of each column
	double mat_initial_coord[NBRE_PTS][NBRE_COORD]={0};//matrix gathering all the 4 coordinates NORMALIZED extracted from the file
	int mat_initial_value_of_each_point[NBRE_PTS]={0}, mat_final_value_of_each_point[NBRE_PTS]={0};//matrix giving the class of each point
	string str;	


	//cout.precision(6);
	//cout.setf(ios::fixed,ios::floatfield);

	ifstream fichier("iris.data.corrected.txt");
  if(fichier)
	{
		fichier.seekg(0, ios::beg);//on se place au debut du fichier

//on recupere toutes les donnees
		for(int i=0; i<NBRE_PTS; i++)
		{
			string ligne;
			getline(fichier, ligne); //on recupere ligne par ligne le fichier
			size_t depart(0),found(-1);//ces marqueurs permettent de recuperer les indices de la ou sont placees les virgules
			for(int j=0; j<NBRE_COORD; j++)//also found!=std::string::npos
			{
				found = ligne.find(',',found+1);
				mat_initial_coord[i][j]=get_6_significative_num(get_value_normalized(stod(ligne.substr(depart, found-depart)), min_max_each_coord[j][1], min_max_each_coord[j][0], 1, 0));//on utilise la fonction de normalisartion precemment definie
				
				//cout << mat_initial_coord[i][j]; //SEEMS OK
				//cout << "\t";
				//printf("%7d", mat_initial_coord[i][j]);
				//cout << ", ";
				if(found!=string::npos) depart=found+1;
			}
			//cout << "\n";
//on recupere mtn la classe a laquelle appartient chaque point			
			if(ligne.substr(depart)=="Iris-setosa") mat_initial_value_of_each_point[i]=1;//0 ==> none class, 1==> iris-sectosa, 2==> versicolor, 3==> virginica
			else if(ligne.substr(depart)=="Iris-versicolor") mat_initial_value_of_each_point[i]=2;
			else if(ligne.substr(depart)=="Iris-virginica") mat_initial_value_of_each_point[i]=3;
			else cout << "ERR" << endl;
			//cout << mat_initial_value_of_each_point[i] << endl; //OK
		}
  }
  else
  {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
  }

//4*[K_MAX] car on a des area en 4 dimension
	double mat_of_all_Gij_CFij[K_MAX-K_MIN+1][K_MAX][K_MAX][K_MAX][K_MAX][2]={0};//on prend la taille maximale a chaque fois mais en realite seul i<K utile
	double mat_of_adaptability_of_all_area[K_MAX-K_MIN+1][K_MAX][K_MAX][K_MAX][K_MAX][NBRE_CLASSE+1]={0};//de mm que precedemment

	for(double K=K_MIN; K<K_MAX+1; K++)
	{
		int i(0), j(0), k(0), l(0);//ce seront les indices des area de 4 dimensions
		while(i!=K)
		{
			for(int m=0; m<NBRE_PTS; m++)
			{

				//cout << mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][mat_initial_value_of_each_point[m]] << endl;


//calc of ADAPTIBILITY
//on selectionne ladaptibility de la classe mat_initial_value_of_each_point[m]
				mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][mat_initial_value_of_each_point[m]]+=get_value_membership_function(mat_initial_coord[m][0], (double)i+1, K)*get_value_membership_function(mat_initial_coord[m][1], (double)j+1, K)*get_value_membership_function(mat_initial_coord[m][2], (double)k+1, K)*get_value_membership_function(mat_initial_coord[m][3], (double)l+1, K);

	
			}

//if Gijkl == G1
			if(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1] > mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2] && mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1] > mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]) 
			{
//calc of Gijkl && CFijkl
				mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]=1;
				if((mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3])>0) mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]-(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]/(K-1)+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]/(K-1)))/(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]);
				else /*cout << "G1 && none value of CF" << endl;*/mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=0;
				//cout << "G1" << endl;
			}

//if Gijkl == G2
			else if(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2] > mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1] && mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2] > mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]) 
			{
//calc of Gijkl && CFijkl
				mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]=2;
				if((mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3])>0) mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]-(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]/(K-1)+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]/(K-1)))/(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]);
				else /*cout << "G2 && none value of CF" << endl;*/mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=0;
				//cout << "G2" << endl;
			}

//if Gijkl == G3
			else if(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3] > mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2] && mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3] > mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]) 
			{
//calc of Gijkl && CFijkl
				mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]=3;
				if((mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3])>0) mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]-(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]/(K-1)+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]/(K-1)))/(mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][1]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][2]+mat_of_adaptability_of_all_area[(int)K-2][i][j][k][l][3]);
				else /*cout << "G3 && none value of CF" << endl;*/mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=0;
				//cout << "G3" << endl;
			}

//if Gijkl == NONE
			else 
			{
//calc of Gijkl && CFijkl
				mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]=0;
				mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1]=0;
				//cout << "NEITHER GROUP NOR CF" << endl;
			}
			//cout << mat_of_adaptability_of_all_area[(int)K-2][0][0][0][0][0] << endl;

			//cout << i << "\t" << j << "\t" << k << "\t" << l << endl; 

			l++;
			if(l==(int)K) {k++; l=0;}
			if(k==(int)K) {j++; k=0;}
			if(j==(int)K) {i++; j=0;}
		}
	
	
		int compteur_valeur_similaire(0);

		for(int m=0; m<NBRE_PTS; m++)
		{
			double alpha1(0), alpha2(0), alpha3(0);
			i=0; j=0; k=0; l=0;
			while(i!=K)
			{

//CALC OF ALPHA1, ALPHA2, ALPHA3 for each point
				if(mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]==1)
				{
					alpha1=max(get_value_membership_function(mat_initial_coord[m][0], (double)i+1, K)*get_value_membership_function(mat_initial_coord[m][1], (double)j+1, K)*get_value_membership_function(mat_initial_coord[m][2], (double)k+1, K)*get_value_membership_function(mat_initial_coord[m][3], (double)l+1, K)*mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1], alpha1);
				}
				else if(mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]==2)
				{	
					alpha2=max(get_value_membership_function(mat_initial_coord[m][0], (double)i+1, K)*get_value_membership_function(mat_initial_coord[m][1], (double)j+1, K)*get_value_membership_function(mat_initial_coord[m][2], (double)k+1, K)*get_value_membership_function(mat_initial_coord[m][3], (double)l+1, K)*mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1], alpha2);
				}
				else if(mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][0]==3)
				{	
        	alpha3=max(get_value_membership_function(mat_initial_coord[m][0], (double)i+1, K)*get_value_membership_function(mat_initial_coord[m][1], (double)j+1, K)*get_value_membership_function(mat_initial_coord[m][2], (double)k+1, K)*get_value_membership_function(mat_initial_coord[m][3], (double)l+1, K)*mat_of_all_Gij_CFij[(int)K-2][i][j][k][l][1], alpha3);
				}
			


				l++;
				if(l==(int)K) {k++; l=0;}
				if(k==(int)K) {j++; k=0;}
				if(j==(int)K) {i++; j=0;}
			}

			if(alpha1 > alpha2 && alpha1 > alpha3) mat_final_value_of_each_point[m]=1;
			else if(alpha2 > alpha1 && alpha2 > alpha3) mat_final_value_of_each_point[m]=2;
			else if(alpha3 > alpha2 && alpha3 > alpha1) mat_final_value_of_each_point[m]=3;
			else mat_final_value_of_each_point[m]=0;				


			if(mat_final_value_of_each_point[m]==mat_initial_value_of_each_point[m]) compteur_valeur_similaire++;
			//else cout << mat_final_value_of_each_point[m] << "\t" << mat_initial_value_of_each_point[m] << endl;
			//else if (mat_final_value_of_each_point[m]==0) compteur_valeur_similaire++;
			//cout << mat_final_value_of_each_point[m];
	
		}

		//	cout << "\n" << compteur_valeur_similaire << endl;
		cout << "K = " << (int)K << " : \t" << (double)compteur_valeur_similaire*100/NBRE_PTS << " % " << endl;


	}

  return 0;
}
