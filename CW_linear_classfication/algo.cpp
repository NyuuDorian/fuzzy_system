//GET THE SIGN TO GET THE CLASS ! :D 

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctgmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/*#define PHI 0 
#define ETA 0
#define A 1*/

//#define NBRE_POINTS 2000
//#define NBRE_COORD 8
#define NBRE_ITERATION 10


/*

double norme(x)
{
	double NORME_X(0);
	return NORME_X;
}

double** produit_matriciel()
{
	
}*/

//MU=calculate_MU_i_plus_1(MU, SIGMA, matrice_of_all_coord[j], ALPHA, matrice_of_all_value[j], NBRE_COORD);

inline double* calculate_MU_i_plus_1(double* MU_i, double* SIGMA_i, double* X_i, double alpha_i, int y_i, int dim)
{
	//double* new_MU=new double[dim];
	//double new_MU[dim];
	for(int j=0; j<dim; j++)
	{
		//if(X_i[j]!=0) cout << j << "\tinit_new_MU " << new_MU[j] << "\tnew_MU_calc ";
		//new_MU[j]=MU_i[j]+alpha_i*y_i*SIGMA_i[j]*X_i[j];
		MU_i[j]+=alpha_i*y_i*SIGMA_i[j]*X_i[j];
		/*if(X_i[j]!=0)
		{
			//cout << new_MU[j] << "\tMU " << MU_i[j] << "\tSIGMA " << SIGMA_i[j] << "\tX_i " << X_i[j] << "\talpha_i " << alpha_i << "\ty_i " << y_i << endl; //HELP to detect the error
		}*/
	}
	//return new_MU;
	return MU_i;
}

inline double* calculate_inverse_SIGMA_i(double* SIGMA, int dim, double* inverse_SIGMA)
{
	//double* inverse_SIGMA=new double[dim];
	//double inverse_SIGMA[dim];	
	for(int i=0; i<dim; i++)
	{
		if(SIGMA[i]==0) inverse_SIGMA[i]=0;
		else inverse_SIGMA[i]=1/SIGMA[i];
	}
	return inverse_SIGMA;
}

inline double* calculate_inverse_SIGMA_i_plus_1(double* inverse_SIGMA_i, double* DIAG_X_i, double alpha_i, double phi, int dim)
{
	//double* new_inverse_SIGMA=new double[dim];
	//double new_inverse_SIGMA[dim];
	for(int j=0; j<dim; j++)
	{
		//new_inverse_SIGMA[j]=inverse_SIGMA_i[j]+2*alpha_i*phi*DIAG_X_i[j];
		inverse_SIGMA_i[j]+=2*alpha_i*phi*DIAG_X_i[j];
	}	
	//return new_inverse_SIGMA;
	return inverse_SIGMA_i;
}

inline double* diag_X_i( double* X, int dim, double* diag_X)
{
	//double* diag_X = new double[dim];
	//double diag_X[dim];
	for(int i=0; i<dim; i++)
	{
		diag_X[i]=pow(X[i],2);
	}
	return diag_X;
}


inline double calculate_GAMMA_i(int y_i, double* x_i, double* MU_i, double* SIGMA_i, int dim, double PHI)
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
inline double calculate_ALPHA_i(int y_i, double* x_i, double* MU_i, double* SIGMA_i, int dim, double PHI)
{
	double ALPHA(0), GAMMA=calculate_GAMMA_i(y_i, x_i, MU_i, SIGMA_i, dim, PHI);
	ALPHA=max(GAMMA, (double)0);
//	cout << ALPHA << endl;
	return ALPHA;
}


//permet de melanger de maniere aleatoire les donnees recue creant ainsi des donnees totalement random
void randomly_mix(double** matrice_of_all_coord, int* matrice_of_all_value, int NBRE_POINTS, int NBRE_COORD)
{
	vector< vector<double> > matrice_of_all_coord_tmp;
	vector<int> matrice_of_all_value_tmp;
	int nb_rand(0), nbre_datas(NBRE_POINTS);

	for(int i=0; i<NBRE_POINTS; i++)
	{
		vector<double> matrice_of_all_coord_tmp_bis;
		for(int j=0; j<NBRE_COORD; j++)
		{
			matrice_of_all_coord_tmp_bis.push_back(matrice_of_all_coord[i][j]);
		}
		matrice_of_all_coord_tmp.push_back(matrice_of_all_coord_tmp_bis);
		matrice_of_all_value_tmp.push_back(matrice_of_all_value[i]);
	}

	for(int i=0; i<NBRE_POINTS; i++)
	{
		nb_rand = rand() % nbre_datas;
		nbre_datas--;
		for(int j=0; j<NBRE_COORD; j++)
		{
			matrice_of_all_coord[i][j]=matrice_of_all_coord_tmp[nb_rand][j];
		}
		matrice_of_all_value[i]=matrice_of_all_value_tmp[nb_rand];
		matrice_of_all_coord_tmp.erase(matrice_of_all_coord_tmp.begin()+nb_rand);
		matrice_of_all_value_tmp.erase(matrice_of_all_value_tmp.begin()+nb_rand);
	}

//check the new matrix created ==> seems OK
	/*for(int i=0; i<NBRE_POINTS; i++)
	{
		for(int j=0; j<NBRE_COORD; j++)
		{
			cout << matrice_of_all_coord[i][j] << "\t";
		}
		cout << matrice_of_all_value[i] << endl;
	}*/
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
	//x_i belongs to R^d
	//y_i belongs to {-1,+1}
	//w_i+1=w_i+alpha_i*y_i*x_i

	//alpha_i = max( (1 - y_i(w_i . x_i)) / ||x_i||^2 , (double)0)

	//Sigma belongs to R^d_x_d

	//MU_i+1 = MU_i * alpha_i * y_i * SIGMA_i * x_i

	//double Φ=PHI, η=ETA; //initial parameters
	double phi=1; //confidence parameter φ = Φ^(-1)(η); ou Φ^(-1) est la fonction inverse de Φ
	double a = 0.1; //initial variance parameter, a>0



//	initialisation 

	double* MU=new double[NBRE_COORD]; // all points initialized to 0
	double* SIGMA=new double[NBRE_COORD]; //TODO LIST : SIGMA[0] = a * I avec I matrice unite ds d_x_d
	double* inverse_SIGMA=new double[NBRE_COORD];
	double* diag_X=new double[NBRE_COORD];
	double ALPHA(0);
	double** matrice_of_all_coord= new double*[NBRE_POINTS];
	int* matrice_of_all_value= new int[NBRE_POINTS];//value -1 or +1
	int* matrice_of_all_prediction_value= new int[NBRE_POINTS];//value -1 or +1
	bool can_read_next(true);
	vector<int> mat_of_all_points_rank;

	for(int i=0; i<NBRE_POINTS; i++) matrice_of_all_coord[i]=new double[NBRE_COORD];
	for(int i=0; i<NBRE_COORD; i++) MU[i]=0; 

//TODO LIST INITIATE matrice_of_all_coord ==> DONE
//TODO LIST INITIATE matrice_of_all_value ==> DONE
//TODO LIST CALC matrice_of_all_prediction_value --> sign(x.w) ==> DONE
	//ifstream fichier("output_bis.txt");
  if(fichier)
	{
		fichier.seekg(0, ios::beg);//placed at the very beginning 
		string mot("");//will able us to get each word

		fichier >> mot;
		fichier >> mot;
		fichier >> mot;

		for(int i=0; i<NBRE_POINTS; i++)
		{
			//std::vector<double> tempvector,tempvector2;
			//coord.push_back(0);
			//
			//cout << nb_rand << endl;
			//num_files_used_class_0.push_back(nb_rand);//we keep it to know which file had been used


//TODO LIST have to change the way of reading the file ==> DONE
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


//TEST mat of all coord correctly initialized ? ==> recup of datas seems OK
/*for(int i=0; i<NBRE_POINTS; i++)
{
	for(int j=0; j<NBRE_COORD; j++)
	{
		if(matrice_of_all_coord[i][j]!=0 && i<10) cout << j << " : " << matrice_of_all_coord[i][j] << " "; 
	}
	cout << endl;
}*/




//INITIALIZATION OF SIGMA, only for i=0, the others members have to be calculated by the algorithm
	for(int j=0; j<NBRE_COORD; j++)
	{
		SIGMA[j]=a;
		//cout << SIGMA[j] << " ";
		inverse_SIGMA[j]=1/a;
		//cout << inverse_SIGMA[j] << endl;
	}


//initialisation of SIGMA


	//NOW APPLY VARIANCE ALGORITHM	
	//calculate MU_i+1 && SIGMA_i+1^(-1)	
	//	μ i+1 = μ i + α i y i Σ i x i  ==> α==ALPHA 
	//	Σ ^(−1) i+1 = Σ^−1 i + 2α i φ diag (x i )   ==> a==ALPHA
	//where diag (x i ) is a diagonal matrix with the square
	//of the elements of x i on the diagonal.
	/*for(int i=0; i<NBRE_POINTS, i++)
	{
		alpha_i = max( (1 - y_i(w_i . x_i)) / pow(norme(x_i),2) , (double)0)
		calculate_ALPHA_i();

		calculate_MU_i_plus_1();
		calculate_inverse_SIGMA_i_plus_1();
	}*/

//mix randomly the datas
	srand(time(0));
	randomly_mix(matrice_of_all_coord, matrice_of_all_value, NBRE_POINTS, NBRE_COORD);


	int data_fold_beginning[NBRE_ITERATION]={0}, data_fold_ending[NBRE_ITERATION]={0};
	for(int i=0; i<NBRE_ITERATION; i++)
	{
		data_fold_beginning[i]=i*NBRE_POINTS/NBRE_ITERATION;
		if(i!=NBRE_ITERATION-1) data_fold_ending[i]=i*NBRE_POINTS/NBRE_ITERATION+NBRE_POINTS/NBRE_ITERATION;
		else data_fold_ending[i]=NBRE_POINTS;
	}


	double moyenne_pourcentage(0);


ofstream test_result("test_result_"+ title_doc +".txt");
if(test_result)
{

	for(int i=0; i<NBRE_ITERATION; i++)
	{

		for(int z=0; z<NBRE_COORD; z++) MU[z]=0;//initiliasition everything at 0			
//initiliser MU et SIGMA avec des valeurs aleatoires entre -1 et 1, (eventuellement eviter le 0 ? pour la diagonale de SIGMA)
//SIGMA etant une matrice diagonale, nous utilisont un vecteur (moins lourd et facilite les calculs)
		for(int z=0; z<NBRE_COORD; z++) 
		{
			//MU[i]=0;
			SIGMA[z]=a;
			inverse_SIGMA[z]=1/a;
		}
		for(int z=0; z<NBRE_POINTS; z++) mat_of_all_points_rank.push_back(z);//initialisation of vector<int> mat_of_all_points_rank;
		for(int z=data_fold_beginning[i]; z<data_fold_ending[i]; z++) mat_of_all_points_rank.erase(mat_of_all_points_rank.begin()+data_fold_beginning[i]);//removing all points belonging to the validation dataset


		for(int n=0; n<(int)mat_of_all_points_rank.size(); n++)
		//for(int j=i*NBRE_POINTS/10; j<i*NBRE_POINTS/10+NBRE_POINTS/10; j++)
		{
//			cout << j << endl;
			
			int nb_rand = rand() % mat_of_all_points_rank.size();

			//TODO LIST update alpha ==> DONE
			//cerr << j << "\t";

			ALPHA=calculate_ALPHA_i(matrice_of_all_value[mat_of_all_points_rank[nb_rand]], matrice_of_all_coord[mat_of_all_points_rank[nb_rand]], MU, SIGMA, NBRE_COORD, phi);
			//ALPHA=calculate_ALPHA_i(matrice_of_all_value[j], matrice_of_all_coord[j], MU, SIGMA, NBRE_COORD, phi);
			//if(j<10) cout << ALPHA << endl;
			//cout << j << "\t" << ALPHA << endl;
			//inverse_SIGMA=calculate_inverse_SIGMA_i(SIGMA, NBRE_COORD);

//test de la fonction inverse sigma
			/*for(int k=0; k<NBRE_COORD; k++)
			{
				if(j<50) cout << inverse_SIGMA[k] << " ";					
			}*/


			/*SIGMA=*/calculate_inverse_SIGMA_i(inverse_SIGMA, NBRE_COORD, SIGMA);//inverse of inverse gives natural
			
//test de la fonction inverse sigma
			/*if(j<50) cout << endl;
			for(int k=0; k<NBRE_COORD; k++)
			{
				if(j<50) cout << SIGMA[k] << " ";					
			}
			if(j<50) cout << endl << endl;*/


			calculate_MU_i_plus_1(MU, SIGMA, matrice_of_all_coord[mat_of_all_points_rank[nb_rand]], ALPHA, matrice_of_all_value[mat_of_all_points_rank[nb_rand]], NBRE_COORD);
//			/*MU=*/calculate_MU_i_plus_1(MU, SIGMA, matrice_of_all_coord[j], ALPHA, matrice_of_all_value[j], NBRE_COORD);

//TEST OF MU CALC ==> NOT OK
			/*for(int k=0; k<NBRE_COORD; k++)
			{
				if(j<2 && MU[k]!=0) cout << MU[k] << "\t";
			}
			if(j<2) cout << endl;*/

			diag_X_i(matrice_of_all_coord[mat_of_all_points_rank[nb_rand]], NBRE_COORD, diag_X);
//			diag_X_i(matrice_of_all_coord[j], NBRE_COORD, diag_X);



			/*inverse_SIGMA=*/calculate_inverse_SIGMA_i_plus_1(inverse_SIGMA, diag_X, ALPHA, phi, NBRE_COORD);
//TEST OF INVERSE SIGMA
			/*for(int k=0; k<NBRE_COORD; k++)
			{
				if(j<2 && inverse_SIGMA[k]!=10) cout << inverse_SIGMA[k] << "\t";
			}
			if(j<2) cout << endl;*/


		}

			int counter_correct_classification(0);
			double classifier(0);
			//int minus_pos(0), maxi_pos(0), null_pos(0);			

			for(int m=data_fold_beginning[i]; m<data_fold_ending[i]; m++)
			//for( int k=i*NBRE_POINTS/10+NBRE_POINTS/10; k<i*NBRE_POINTS/10+2*NBRE_POINTS/10; k++ ) //on decale de +NBRE_POINTS/10 pour avoir les 200 points TESTS
	    {
				int tmp(m);
				//if(k<NBRE_POINTS) tmp=k;
				//else tmp=k-NBRE_POINTS;

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

			int nbre_elt((data_fold_ending[i]-1)-data_fold_beginning[i]+1);
		
		test_result << "iteration " << i << "\t" << (double)counter_correct_classification*100/nbre_elt << " %" << endl;//" " << minus_pos << " " << maxi_pos << " " << null_pos << endl;
		cout << "iteration " << i << "\t" << (double)counter_correct_classification*100/nbre_elt << " %" << endl;

		moyenne_pourcentage+=(double)counter_correct_classification*100/nbre_elt;


	}


}
else cout << "cannot write on test_result" << endl;

	test_result << "mean_% " << moyenne_pourcentage/NBRE_ITERATION << " %" << endl;
	cout << "mean_% " << moyenne_pourcentage/NBRE_ITERATION << " %" << endl;

		//delete matrix_for_calc_of_membership_func;
		delete MU;
		delete SIGMA;
		delete inverse_SIGMA;
		delete diag_X;

		delete matrice_of_all_coord;
		delete matrice_of_all_value;//value -1 or +1
		delete matrice_of_all_prediction_value;//value -1 or +1


	return EXIT_SUCCESS;
}
}
