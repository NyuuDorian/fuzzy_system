//TODO LIST HAVE TO MAKE BEGINING VALUES RANDOMLY PICKED UP FROM -1 to 1
//TODO LIST HAVE TO MAKE A SHUFFLE OF THE DATAS

//GET THE SIGN TO GET THE CLASS ! :D 








//all includes, anemspace and #define values

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctgmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

/*#define PHI 0 
#define ETA 0
#define A 1*/

//#define NBRE_POINTS 2000
//#define NBRE_COORD 8
#define NBRE_ITERATION 10








//ALL FUNCTION DEFINED HERE


//calculate the value of the membership value
inline double get_value_membership_function(double x, double k, double L)
{
	double value_membership(0), a(0), b(0);
	//cout << "k " << k << endl;
	a=(k/*+1*/-1)/(L-1);//BEWARE k BETWEEN 1..L
	b=1/(L-1);
	value_membership=max((double)1-(std::fabs(x-a)/b),(double)0);
	return value_membership;
}


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

inline double* calculate_inverse_SIGMA_i_plus_1(/*int y_i, */double* inverse_SIGMA_i, double* DIAG_X_i, double alpha_i, double phi, int dim)
{
	//double* new_inverse_SIGMA=new double[dim];
	//double new_inverse_SIGMA[dim];
	for(int j=0; j<dim; j++)
	{
		//new_inverse_SIGMA[j]=inverse_SIGMA_i[j]+2*alpha_i*phi*DIAG_X_i[j];
		//inverse_SIGMA_i[j]+=2*alpha_i*y_i*phi*DIAG_X_i[j];
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
	if(V_i==0) V_i=0.00000001;//either problem because it becomes singular (degenerated)

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













//BEGINING OF THE PROGRAMME



int main(int argc, char** argv)
{
	

	if(argc!=4) return -1;
	else
	{
		string title_doc(argv[1]);
		int taille_min_K(atoi(argv[2])), taille_max_K(atoi(argv[3]));		

	
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

		double ALPHA[NBRE_CLASSES];
		for(int z=0; z<NBRE_CLASSES; z++) ALPHA[z]=0;
		double** matrice_of_all_coord= new double*[NBRE_POINTS];
		int* matrice_of_all_value= new int[NBRE_POINTS];//value -1 or +1
		int* matrice_of_all_prediction_value= new int[NBRE_POINTS];//value -1 or +1
		bool can_read_next(true);
		vector<int> mat_of_all_points_rank;

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
				/*if(stoi(mot)==0) matrice_of_all_value[i]=-1;			
				else */matrice_of_all_value[i]=stoi(mot);//on garde la classe ORIGINALE i.e. 0 || 1
				//class_value.push_back(stoi(classe));

				can_read_next=true;
				//cout << matrice_of_all_value[i] << " ";
			}
		}
		else
		{
		    cout << "ERROR: Cannot open fichier on reading mode." << endl;
		}


	//check the matrix outputed ==> SEEMS OK
		/*for(int i=0; i<NBRE_POINTS; i++)
		{
			for(int j=0; j<NBRE_COORD; j++)
			{
				cout << matrice_of_all_coord[i][j] << "\t";
			}
			cout << matrice_of_all_value[i] << endl;
		}*/


	//mix randomly the datas
		srand(time(0));
		randomly_mix(matrice_of_all_coord, matrice_of_all_value, NBRE_POINTS, NBRE_COORD);


		int data_fold_beginning[NBRE_ITERATION]={0}, data_fold_ending[NBRE_ITERATION]={0}, reste(NBRE_POINTS%(NBRE_POINTS/NBRE_ITERATION));

		for(int i=0; i<NBRE_ITERATION; i++)
		{
			if(i==0)
			{
				data_fold_beginning[i]=0;//i*NBRE_POINTS/NBRE_ITERATION;
				if(reste!=0) 
				{
					data_fold_ending[i]=NBRE_POINTS/NBRE_ITERATION+1;
					reste--;
				}
				else data_fold_ending[i]=NBRE_POINTS/NBRE_ITERATION;//i*NBRE_POINTS/NBRE_ITERATION+NBRE_POINTS/NBRE_ITERATION;
			}
			else 
			{
				data_fold_beginning[i]=data_fold_ending[i-1];
				if(i!=NBRE_ITERATION-1) 
				{
					if(reste!=0) 
					{
						data_fold_ending[i]=data_fold_ending[i-1]+NBRE_POINTS/NBRE_ITERATION+1;//i*NBRE_POINTS/NBRE_ITERATION+NBRE_POINTS/NBRE_ITERATION;
						reste--;
					}
					else data_fold_ending[i]=data_fold_ending[i-1]+NBRE_POINTS/NBRE_ITERATION;//i*NBRE_POINTS/NBRE_ITERATION+NBRE_POINTS/NBRE_ITERATION;
				}
				else data_fold_ending[i]=NBRE_POINTS;
			}
		}

	///test des def de debuts et fin de separation
	/*	for(int i=0; i<NBRE_ITERATION; i++)
		{
			cout << data_fold_beginning[i] << "\t" << data_fold_ending[i] << endl;
		}*/
	
	 


	//check the matrix outputed after applying randomly_mixed function
		/*for(int i=0; i<NBRE_POINTS; i++)
		{
			for(int j=0; j<NBRE_COORD; j++)
			{
				cout << matrice_of_all_coord[i][j] << "\t";
			}
			cout << matrice_of_all_value[i] << endl;
		}*/




		ofstream test_result("test_result_"+ title_doc +".txt");
		if(test_result)
		{

			//define the number of divided areas for the fuzzy classification, here it varies between 2~3, maybe later will try 2~7 ==> 2~3 for the moment
			for(int K=taille_min_K; K<taille_max_K; K++)
			{
				double moyenne_pourcentage(0);

				cout << "K="<< K << endl;
		/*		double* MU=new double[(int)pow(K,NBRE_COORD)]; //consequent_real_value
				double* SIGMA=new double[(int)pow(K,NBRE_COORD)];		
				double* inverse_SIGMA=new double[(int)pow(K,NBRE_COORD)];
				double* diag_X=new double[(int)pow(K,NBRE_COORD)];
		*/
		//multiclassification
		//NBRE_CLASSES
				double** MU=new double*[NBRE_CLASSES]; //consequent_real_value
				double** SIGMA=new double*[NBRE_CLASSES];		
				double** inverse_SIGMA=new double*[NBRE_CLASSES];
				double** diag_X=new double*[NBRE_CLASSES];

				for(int z=0; z<NBRE_CLASSES; z++) MU[z]=new double[(int)pow(K,NBRE_COORD)];
				for(int z=0; z<NBRE_CLASSES; z++) SIGMA[z]=new double[(int)pow(K,NBRE_COORD)];
				for(int z=0; z<NBRE_CLASSES; z++) inverse_SIGMA[z]=new double[(int)pow(K,NBRE_COORD)];
				for(int z=0; z<NBRE_CLASSES; z++) diag_X[z]=new double[(int)pow(K,NBRE_COORD)];

		//INITIALISATION A 0 pr eviter les erreursplus tard sauf pr SIGMA ET INVERSE SIGMA
				for(int z=0; z<NBRE_CLASSES; z++)
				{
					for(int y=0; y<(int)pow(K,NBRE_COORD); y++)
					{
						MU[z][y]=0;
						SIGMA[z][y]=a;
						inverse_SIGMA[z][y]=1/a;
						diag_X[z][y]=0;
					}
				}

				//cout << (int)pow(K,NBRE_COORD) << endl;


		//TODO LIST initiliser une liste de longueur (int)pow(K,NBRE_COORD) qui contiendra toutes les valeurs possibles ==> DONE
				int** matrix_for_calc_of_membership_func =	new int*[(int)pow(K,NBRE_COORD)];
				for(int z=0; z<(int)pow(K,NBRE_COORD); z++) matrix_for_calc_of_membership_func[z]=new int[NBRE_COORD];//initialisation
				for(int z=0; z<(int)pow(K,NBRE_COORD); z++) 
				{
					int tmp=z;
					for(int y=0; y<NBRE_COORD; y++)
					{
						matrix_for_calc_of_membership_func[z][y]=tmp/(int)pow(K, NBRE_COORD-1-y);
						//cout << tmp/(int)pow(K, NBRE_COORD-1-y) << "\t";
						int coeff(tmp/(int)pow(K, NBRE_COORD-1-y));
						tmp-=coeff*(int)pow(K, NBRE_COORD-1-y);
					}
					//cout << endl;
				}	


				for(int i=0; i<NBRE_ITERATION; i++)		
				{


//TODO LIST re-initialiser les valeurs de MU et SIGMA et inverse-SIGMA

					for(int z=0; z<NBRE_CLASSES; z++)
					{
						for(int y=0; y<(int)pow(K,NBRE_COORD); y++)
						{
							MU[z][y]=0;
							SIGMA[z][y]=a;
							inverse_SIGMA[z][y]=1/a;
							diag_X[z][y]=0;
						}
					}



					mat_of_all_points_rank.clear();
					for(int z=0; z<NBRE_POINTS; z++) mat_of_all_points_rank.push_back(z);//initialisation of vector<int> mat_of_all_points_rank;

					//cout << mat_of_all_points_rank.size() << endl;

		//done previously
					//for(int z=0; z<(int)pow(K,NBRE_COORD); z++) MU[z]=0;//initiliasition everything at 0
					for(int z=data_fold_beginning[i]; z<data_fold_ending[i]; z++) mat_of_all_points_rank.erase(mat_of_all_points_rank.begin()+data_fold_beginning[i]);//removing all points belonging to the validation dataset

					//cout << mat_of_all_points_rank.size() << endl;
		

		//initiliser MU et SIGMA avec des valeurs aleatoires entre -1 et 1, (eventuellement eviter le 0 ? pour la diagonale de SIGMA)
		//SIGMA etant une matrice diagonale, nous utilisont un vecteur (moins lourd et facilite les calculs)

		//done previously
		/*			for(int z=0; z<(int)pow(K,NBRE_COORD); z++) 
					{
						//MU[i]=0;
						SIGMA[z]=a;
						inverse_SIGMA[z]=1/a;
					}
		*/

					int taille((int)mat_of_all_points_rank.size());

					for(int n=0; n<taille; n++)
					//for(int j=i*NBRE_POINTS/10; j<i*NBRE_POINTS/10+NBRE_POINTS/10; j++)
					//for(int j=i*100; j<i*100+100; j++)
					{

						int nb_rand = rand() % mat_of_all_points_rank.size();				

		//calc of vector membership value of vector x				
						double* membership_value_of_x = new double[(int)pow(K,NBRE_COORD)];			


						//initialisation a 1
						for(int k=0; k<(int)pow(K,NBRE_COORD); k++)
						{
							membership_value_of_x[k]=1;
							for(int l=0; l<NBRE_COORD; l++)
							{
								//get_value_membership_function(double x, double k, double L)
								//membership_value_of_x[k]*=get_value_membership_function(matrice_of_all_coord[j][l], (double)(matrix_for_calc_of_membership_func[k][l]+1)/*BECAUSE VARIES BETWEEN 1..K*/, (double)K);//membership function of each coordinates
								membership_value_of_x[k]*=get_value_membership_function(matrice_of_all_coord[mat_of_all_points_rank[nb_rand]][l], (double)matrix_for_calc_of_membership_func[k][l]+1/*BECAUSE VARIES BETWEEN 1..K*/, (double)K);//membership function of each coordinates
							}
							//if(membership_value_of_x[k]!=0 && K==2) cout << k << " " << membership_value_of_x[k] << endl;				
						}

			//now improve mean and variance using membership_value_of_x
			//TODO LIST few modifications of the functions used below and defined a little in the upper part ==> DONE

						for(int t=0; t<NBRE_CLASSES; t++)
						{


							int signe(0);
							if(matrice_of_all_value[mat_of_all_points_rank[nb_rand]]==t) signe=1;
							else signe=-1;					

							ALPHA[t]=calculate_ALPHA_i(signe, membership_value_of_x, MU[t], SIGMA[t], (int)pow(K,NBRE_COORD), phi);
							/*SIGMA=*/calculate_inverse_SIGMA_i(inverse_SIGMA[t], (int)pow(K,NBRE_COORD), SIGMA[t]);//inverse of inverse gives natural
							/*MU=*/calculate_MU_i_plus_1(MU[t], SIGMA[t], membership_value_of_x, ALPHA[t], signe, (int)pow(K,NBRE_COORD));
							diag_X_i(membership_value_of_x, (int)pow(K,NBRE_COORD), diag_X[t]);
							/*inverse_SIGMA=*///calculate_inverse_SIGMA_i_plus_1(signe, inverse_SIGMA[t], diag_X[t], ALPHA[t], phi, (int)pow(K,NBRE_COORD));
							calculate_inverse_SIGMA_i_plus_1(inverse_SIGMA[t], diag_X[t], ALPHA[t], phi, (int)pow(K,NBRE_COORD));
						}

						mat_of_all_points_rank.erase(mat_of_all_points_rank.begin()+nb_rand); //TODO LIST how to erase that POINT OMG, MAYBE JUST SHUFFLE THE VECTOR WOULD BE OKAY =D


				//			}//previous end of each point getting through

			//TODO LIST WRITE IN A FILE THE RESULTS ==> DONE
			//here we calculate the inference of the test datas to know if the classifier is effective


						int counter_correct_classification(0);
						double classifier[NBRE_CLASSES];
						for(int z=0; z<NBRE_CLASSES; z++) classifier[z]=0;		
			



						for(int m=data_fold_beginning[i]; m<data_fold_ending[i]; m++)
						//for( int j=i*NBRE_POINTS/10+NBRE_POINTS/10; j<i*NBRE_POINTS/10+2*NBRE_POINTS/10; j++ ) //on decale de +NBRE_POINTS/10 pour avoir les 200 points TESTS
						//for( int j=i*100+100; j<i*100+2*100; j++ )
						{

			//have to change every j with tmp_bis
							int tmp_bis(m);
			
							//int tmp_bis(0);
							//if(j<NBRE_POINTS) tmp_bis=j;
							//else tmp_bis=j-NBRE_POINTS;


							//initialisation a 1
							for(int k=0; k<(int)pow(K,NBRE_COORD); k++)
							{
								membership_value_of_x[k]=1;
								for(int l=0; l<NBRE_COORD; l++)
								{
									//get_value_membership_function(double x, double k, double L)
									membership_value_of_x[k]*=get_value_membership_function(matrice_of_all_coord[tmp_bis][l], (double)matrix_for_calc_of_membership_func[k][l]+1, (double)K);//membership function of each coordinates
								}				
							}
				

							for(int t=0; t<NBRE_CLASSES; t++)
							{
								classifier[t] = 0;
								for( int l=0; l<(int)pow(K,NBRE_COORD); l++ ){
									classifier[t] += membership_value_of_x[l] * MU[t][l];
								}
							}


			//TODO LIST a adapter pour la multiclassification pour le choix de la "classe"
							//cout << k << " " << classifier << endl;
							double rank_of_classe[2]={classifier[0], 0};
							for(int z=0; z<NBRE_CLASSES; z++) 
							{
								if(classifier[z]>rank_of_classe[0]) 
								{
									rank_of_classe[0]=classifier[z]; 
									rank_of_classe[1]=z;
								}
							}

							bool alone(true);
							for(int z=0; z<NBRE_CLASSES; z++) 
							{	
								if(classifier[z]==rank_of_classe[0] && z!=rank_of_classe[1]) alone=false;
							}
			
							/*if( classifier > 0 ) matrice_of_all_prediction_value[tmp_bis] = 1;
							else if (classifier < 0 ) matrice_of_all_prediction_value[tmp_bis] = -1;
				 			else {matrice_of_all_prediction_value[tmp_bis]=0; }
							*/
							if( rank_of_classe[0] > 0 && alone == true ) matrice_of_all_prediction_value[tmp_bis]=rank_of_classe[1];
							else	matrice_of_all_prediction_value[tmp_bis]=-1;				
							if( matrice_of_all_prediction_value[tmp_bis]==matrice_of_all_value[tmp_bis] ) counter_correct_classification++;

						}


						int nbre_elt((data_fold_ending[i]-1)-data_fold_beginning[i]+1);

						if(n==0) test_result << "K=" << K << "\t" << "iteration " << i << endl;		
						test_result << (double)counter_correct_classification*100/nbre_elt << "\t";//" " << minus_pos << " " << maxi_pos << " " << null_pos << endl;
						cout << "K=" << K << "\titeration " << i << "\tpts n. " << n << "\t" << (double)counter_correct_classification*100/nbre_elt << " %" << endl;
						if(n==taille-1) moyenne_pourcentage+=(double)counter_correct_classification*100/nbre_elt;




						delete[] membership_value_of_x;
					}

						//if(j<50) cout << counter_correct_classification << endl ;


					/*int nbre_elt((data_fold_ending[i]-1)-data_fold_beginning[i]+1);
	
					test_result << "K=" << K << "\t" << "iteration " << i << "\t" << (double)counter_correct_classification*100/nbre_elt << " %" << endl;//" " << minus_pos << " " << maxi_pos << " " << null_pos << endl;
					cout << "iteration " << i << "\t" << (double)counter_correct_classification*100/nbre_elt << " %" << endl;
					//test_result << (double)counter_correct_classification*100/100 << " %" << endl;
					//cout << "iteration " << i << "\t" << (double)counter_correct_classification*100/100 << " %" << endl;*/



				//
				//moyenne_pourcentage+=(double)counter_correct_classification*100/100;
		

					test_result << endl;

				}
		
				for(int z=0; z<NBRE_CLASSES; z++) delete[] matrix_for_calc_of_membership_func[z];
				delete[] matrix_for_calc_of_membership_func;
				for(int z=0; z<NBRE_CLASSES; z++) delete[] MU[z];	
				delete[] MU;
				for(int z=0; z<NBRE_CLASSES; z++) delete[] SIGMA[z];
				delete[] SIGMA;
				for(int z=0; z<NBRE_CLASSES; z++) delete[] inverse_SIGMA[z];
				delete[] inverse_SIGMA;
				for(int z=0; z<NBRE_CLASSES; z++) delete[] diag_X[z];
				delete[] diag_X;

/*				delete matrix_for_calc_of_membership_func;
				delete MU;
				delete SIGMA;
				delete inverse_SIGMA;
				delete diag_X;
*/

				//cout << "mean_% " << moyenne_pourcentage/NBRE_ITERATION << endl;
		
			}
		}
		else cout << "cannot write on test_result" << endl;

		for(int z=0; z<NBRE_CLASSES; z++) delete[] matrice_of_all_coord[z];
		delete[] matrice_of_all_coord;
		delete[] matrice_of_all_value;//value -1 or +1
		delete[] matrice_of_all_prediction_value;//value -1 or +1

/*		delete matrice_of_all_coord;
		delete matrice_of_all_value;//value -1 or +1
		delete matrice_of_all_prediction_value;//value -1 or +1
*/
		return EXIT_SUCCESS;
	}
}
