//GET THE SIGN TO GET THE CLASS ! :D 

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctgmath>
#include <vector>
#include <cstdlib>

using namespace std;

/*#define PHI 0 
#define ETA 0
#define A 1*/

//#define NBRE_POINTS 2000
//#define NBRE_COORD 8
#define NBRE_ITERATION 10


//calculate the value of the membership value
double get_value_membership_function(double x, double k, double L)
{
	double value_membership(0), a(0), b(0);
	a=(k-1)/(L-1);
	b=1/(L-1);
	value_membership=max((double)1-(std::fabs(x-a)/b),(double)0);
	return value_membership;
}


double* calculate_MU_i_plus_1(double* MU_i, double* SIGMA_i, double* X_i, double alpha_i, int y_i, int dim)
{
	double* new_MU=new double[dim];
	for(int j=0; j<dim; j++)
	{
		//if(X_i[j]!=0) cout << j << "\tinit_new_MU " << new_MU[j] << "\tnew_MU_calc ";
		new_MU[j]=MU_i[j]+alpha_i*y_i*SIGMA_i[j]*X_i[j];
		/*if(X_i[j]!=0)
		{
			//cout << new_MU[j] << "\tMU " << MU_i[j] << "\tSIGMA " << SIGMA_i[j] << "\tX_i " << X_i[j] << "\talpha_i " << alpha_i << "\ty_i " << y_i << endl; //HELP to detect the error
		}*/
	}
	return new_MU;
}

double* calculate_inverse_SIGMA_i(double* SIGMA, int dim)
{
	double* inverse_SIGMA=new double[dim];
	for(int i=0; i<dim; i++)
	{
		if(SIGMA[i]==0) inverse_SIGMA[i]=0;
		else inverse_SIGMA[i]=1/SIGMA[i];
	}
	return inverse_SIGMA;
}

double* calculate_inverse_SIGMA_i_plus_1(double* inverse_SIGMA_i, double* DIAG_X_i, double alpha_i, double phi, int dim)
{
	double* new_inverse_SIGMA=new double[dim];
	for(int j=0; j<dim; j++)
	{
		new_inverse_SIGMA[j]=inverse_SIGMA_i[j]+2*alpha_i*phi*DIAG_X_i[j];
	}	
	return new_inverse_SIGMA;
}

double* diag_X_i( double* X, int dim)
{
	double* diag_X = new double[dim];
	for(int i=0; i<dim; i++)
	{
		diag_X[i]=pow(X[i],2);
	}
	return diag_X;
}


double calculate_GAMMA_i(int y_i, double* x_i, double* MU_i, double* SIGMA_i, int dim, double PHI)
{
	double GAMMA(0), M_i(0), V_i(0);
	
//M_i=y_i*(x_i*MU_i);
	for(int j=0; j<dim; j++)
	{
		M_i+=x_i[j]*MU_i[j];
	}
	M_i*=y_i;
//	cerr << "M_i " << M_i << "\t";

//V_i=tranposee_x_i*SIGMA_i*x_i;
	for(int j=0; j<dim; j++)
	{
		V_i+=x_i[j]*SIGMA_i[j]*x_i[j];
	}
	if(V_i==0) V_i=0.00000001;

//	cerr << "V_i " << V_i << "\t";

//	double tmp((1+2*PHI*M_i ) - (8 * PHI * (M_i -PHI*V_i )));

	GAMMA=( -(1+2*PHI*M_i) + sqrt( pow(1+2*PHI*M_i, 2 ) - (8 * PHI * (M_i -PHI*V_i )) ))/(4*PHI*V_i);
	

//	cerr << "tmp " << tmp << "\t";
//	cerr << "GAMMA " << GAMMA << endl;

	return GAMMA;
}


//ALPHA=calculate_ALPHA_i(matrice_of_all_value[j], matrice_of_all_coord[j], MU, SIGMA, NBRE_COORD, phi);
double calculate_ALPHA_i(int y_i, double* x_i, double* MU_i, double* SIGMA_i, int dim, double PHI)
{
	double ALPHA(0), GAMMA=calculate_GAMMA_i(y_i, x_i, MU_i, SIGMA_i, dim, PHI);
	ALPHA=max(GAMMA, (double)0);
//	cout << ALPHA << endl;
	return ALPHA;
}



int main(int argc, char** argv)
{
	

if(argc!=2) return -1;
else
{
	string title_doc(argv[1]);
		
	
	int NBRE_POINTS(0), NBRE_COORD(0), NBRE_CLASSES(0);

	ifstream fichier(title_doc+".txt");
	if(fichier)
	{
		fichier.seekg(0, ios::beg);//placed at the very beginning 
		//will able us to get each word

		fichier >> NBRE_POINTS;
		cout << NBRE_POINTS << endl;
		fichier >> NBRE_COORD;
		cout << NBRE_COORD << endl;
		fichier >> NBRE_CLASSES;
		cout << NBRE_CLASSES << endl; 
	}
	else cout << "Cannot open the file to read" << endl;
	
	double phi=1; //confidence parameter φ = Φ^(-1)(η); ou Φ^(-1) est la fonction inverse de Φ
	double a = 0.1; //initial variance parameter, a>0



//	initialisation 

	double ALPHA(0);
	double** matrice_of_all_coord= new double*[NBRE_POINTS];
	int* matrice_of_all_value= new int[NBRE_POINTS];//value -1 or +1
	int* matrice_of_all_prediction_value= new int[NBRE_POINTS];//value -1 or +1
	bool can_read_next(true);

	for(int i=0; i<NBRE_POINTS; i++) matrice_of_all_coord[i]=new double[NBRE_COORD]; 

  if(fichier)
	{
		fichier.seekg(0, ios::beg);//placed at the very beginning 
		string mot("");//will able us to get each word

		fichier >> mot;
		fichier >> mot;
		fichier >> mot;

		for(int i=0; i<NBRE_POINTS; i++)
		{
			for(int j=0; j<NBRE_COORD; j++) 
			{
				if(can_read_next) 
				{
					fichier >> mot;	//read "place"
					can_read_next=false;					
				}
		
				if(j==stoi(mot)) 
				{
					fichier >> mot; //read ":"
					fichier >> mot;	//read "normalized nb"
				//cout << mot << " ";
				//tempvector.push_back(stod(mot));
					matrice_of_all_coord[i][j]=stod(mot);
					can_read_next=true;
				}
				else matrice_of_all_coord[i][j]=0;
			}

			if(stoi(mot)!=NBRE_COORD)
				fichier >> mot; //read NBRE_COORD IFF this one has not already been read before
			//cout << mot << "\t";
			fichier >> mot;	//read ":"
			//cout << mot << "\t";
	
			//coord.push_back(tempvector);
			fichier >> mot;	//read CLASS
			//cout << mot << endl;
			if(stoi(mot)==0) matrice_of_all_value[i]=-1;			
			else matrice_of_all_value[i]=stoi(mot);
			//class_value.push_back(stoi(classe));

			can_read_next=true;
			//cout << matrice_of_all_value[i] << " ";
		}
	}
  else
  {
      cout << "ERROR: Cannot open fichier on reading mode." << endl;
  }


ofstream test_result("test_result_"+ title_doc +".txt");
if(test_result)
{

	//define the number of divided areas for the fuzzy classification, here it varies between 2~3, maybe later will try 2~7
	for(int K=2; K<4; K++)
	{
		double* MU=new double[(int)pow(K,NBRE_COORD)]; //consequent_real_value
		double* SIGMA=new double[(int)pow(K,NBRE_COORD)];		
		double* inverse_SIGMA=new double[(int)pow(K,NBRE_COORD)];


//initiliser MU et SIGMA avec des valeurs aleatoires entre -1 et 1, (eventuellement eviter le 0 ? pour la diagonale de SIGMA)
//SIGMA etant une matrice diagonale, nous utilisont un vecteur (moins lourd et facilite les calculs)
		for(int i=0; i<(int)pow(K,NBRE_COORD); i++) 
		{
			//MU[i]=0;
			SIGMA[i]=a;
			inverse_SIGMA[i]=1/a;
		}


		for(int i=0; i<NBRE_ITERATION; i++)
		{
			for(int j=i*NBRE_POINTS/10; j<i*NBRE_POINTS/10+NBRE_POINTS/10; j++)
			{

//calc of vector membership value of vector x
				double* membership_value_of_x = new double[(int)pow(K,NBRE_COORD)];
				//initialisation a 1
				for(int k=0; k<(int)pow(K,NBRE_COORD); k++)
				{
					membership_value_of_x[k]=1;
					for(int l=0; l<NBRE_COORD; l++)
					{
						membership_value_of_x[k]*=membership_function(matrice_of_all_coord[j][k]);//membership function of each coordinates
					}				
				}

//now improve mean and variance using membership_value_of_x
//TODO LIST few modifications of the functions used below and defined a little in the upper part 
				ALPHA=calculate_ALPHA_i(matrice_of_all_value[j], membership_value_of_x, MU, SIGMA, (int)pow(K,NBRE_COORD), phi);
				SIGMA=calculate_inverse_SIGMA_i(inverse_SIGMA, (int)pow(K,NBRE_COORD));//inverse of inverse gives natural
				MU=calculate_MU_i_plus_1(MU, SIGMA, membership_value_of_x, ALPHA, matrice_of_all_value[j], (int)pow(K,NBRE_COORD));
				inverse_SIGMA=calculate_inverse_SIGMA_i_plus_1(inverse_SIGMA, diag_X_i(membership_value_of_x, (int)pow(K,NBRE_COORD)), ALPHA, phi, (int)pow(K,NBRE_COORD));

			}
		}

		/*int counter_correct_classification(0);
			double classifier(0);
			//int minus_pos(0), maxi_pos(0), null_pos(0);			

			for( int k=i*NBRE_POINTS/10+NBRE_POINTS/10; k<i*NBRE_POINTS/10+2*NBRE_POINTS/10; k++ ) //on decale de +NBRE_POINTS/10 pour avoir les 200 points TESTS
	    {
				int tmp(0);
				if(k<NBRE_POINTS) tmp=k;
				else tmp=k-NBRE_POINTS;

				classifier = 0;
	      for( int l=0; l<NBRE_COORD; l++ ){
	        classifier += matrice_of_all_coord[tmp][l] * MU[l];
	      }
				//cout << k << " " << classifier << endl;
      	if( classifier > 0 ) matrice_of_all_prediction_value[tmp] = 1;
      	else if (classifier < 0 ) matrice_of_all_prediction_value[tmp] = -1;
   			else {matrice_of_all_prediction_value[tmp]=0; /*cout << "TIC ";*/}
      	if( matrice_of_all_prediction_value[tmp]==matrice_of_all_value[tmp] ) counter_correct_classification++;


	      /*classifier = 0;
	      for( int l=0; l<NBRE_COORD; l++ ){
	        classifier += matrice_of_all_coord[k][l] * MU[l];
	      }
				//cout << k << " " << classifier << endl;
      	if( classifier > 0 ) matrice_of_all_prediction_value[k] = 1;
      	else if (classifier < 0 ) matrice_of_all_prediction_value[k] = -1;
   			else {matrice_of_all_prediction_value[k]=0; }
      	if( matrice_of_all_prediction_value[k]==matrice_of_all_value[k] ) counter_correct_classification++;*/
				//else if(matrice_of_all_prediction_value[k]==-1) minus_pos++;
				//else if(matrice_of_all_prediction_value[k]==1) maxi_pos++;
				//else if(matrice_of_all_prediction_value[k]==0) null_pos++;
    	}
	
			//if(j<50) cout << counter_correct_classification << endl ;
		
		test_result << (double)counter_correct_classification*100/(NBRE_POINTS/10) << " %" << endl;//" " << minus_pos << " " << maxi_pos << " " << null_pos << endl;
		cout << "iteration " << i << "\t" << (double)counter_correct_classification*100/(NBRE_POINTS/10) << " %" << endl;*/

		
		
	}
}
else cout << "cannot write on test_result" << endl;




	return EXIT_SUCCESS;
}
}