//g++ -o making_graphs.exe making_graphs.cpp -lm -lpthread -lX11

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
//#include <ctgmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

#define TAILLE_IMAGE 500
#define K_min 2
#define K_max 4
#define NBRE_POINTS 748

//before using modify K_min K_max NBRE_POINTS title_of_document

int main(int argc, char** argv)
{
	

	if(argc!=1) return -1;
	else
	{
		//string title_doc(argv[1]);
		string mot("");
		//int K_min(atoi(argv[2])), K_max(atoi(argv[3])), NBRE_POINTS(atoi(argv[4]));		

//matrice qui serviront a sauvegarde l'ensemble des donnees pour en faire une moyenne a la fin et la seconde compte le nombre de termes a chaque fois
		double*** matrice_of_all_average_percentage = new double**[K_max-K_min];
		double*** matrice_of_number_of_terms_used = new double**[K_max-K_min];

//finition de l'allocation de toute la memoire necessaire pour nos 2 variables
		for(int i=0; i<K_max-K_min; i++) matrice_of_all_average_percentage[i]=new double*[5];
		for(int i=0; i<K_max-K_min; i++)
		{
			for(int j=0; j<5; j++) 
			{
				matrice_of_all_average_percentage[i][j]=new double[NBRE_POINTS];
			}
		}
	
		for(int i=0; i<K_max-K_min; i++) matrice_of_number_of_terms_used[i]=new double*[5];
		for(int i=0; i<K_max-K_min; i++)
		{
			for(int j=0; j<5; j++) 
			{
				matrice_of_number_of_terms_used[i][j]=new double[NBRE_POINTS];
			}
		}


//initialisation de nos 2 variables
		for(int i=0; i<K_max-K_min; i++)
		{
			for(int j=0; j<5; j++)
			{
				for(int k=0; k<NBRE_POINTS; k++)
				{
					matrice_of_all_average_percentage[i][j][k]=(double)0;
				}
			}
		} 
	
		for(int i=0; i<K_max-K_min; i++)
		{
			for(int j=0; j<5; j++)
			{
				for(int k=0; k<NBRE_POINTS; k++)
				{
					matrice_of_number_of_terms_used[i][j][k]=(double)0;
				}
			}
		}





		//int NBRE_POINTS(0), NBRE_COORD(0), NBRE_CLASSES(0);
		double donnee((double)0);

//		ifstream fichier(title_doc/*+".txt"*/);
//ifstream fichier("MON_FICHIER.txt");
		ifstream fichier("test_result_transfusion_normalized.txt");
		if(fichier)
		{
			fichier.seekg(0, ios::beg);//placed at the very beginning 
			//will able us to get each word

			//fichier >> NBRE_POINTS;
			//cout << NBRE_POINTS << endl;

			//pattern to use "nb_pattern 1	K=2	iteration 0"
			for(int K=K_min; K<K_max; K++)
			{
				for(int nb_pattern=1; nb_pattern<6; nb_pattern++)
				{				
					for(int iteration=0; iteration<10; iteration++)//iteration here shows the number of k-fold division ==> usu. 10-fold cross validation
					{	
						fichier >> mot; //read nb_pattern
						//cout << mot ;
						fichier >> mot; //read N.
						//cout << mot ;
						fichier >> mot; //read K=N.
						//cout << mot ;
						fichier >> mot; //read iteration
						//cout << mot ;
						fichier >> mot; //read N.
						//cout << mot << endl;
			

						int taille(0), reste(NBRE_POINTS%10);
						if(iteration<reste) taille=NBRE_POINTS-(NBRE_POINTS/10+1);		
						else taille=NBRE_POINTS-NBRE_POINTS/10;

						if(taille%nb_pattern==0) taille=taille/nb_pattern;
						else taille=taille/nb_pattern+1;

						//cout << taille << endl;

						for(int i=0; i<taille; i++)
						{
							fichier >> donnee;
							matrice_of_all_average_percentage[K-K_min][nb_pattern-1][i]+=donnee;
							matrice_of_number_of_terms_used[K-K_min][nb_pattern-1][i]++;
						}
					}
				}
			}

		}
		else cout << "Cannot open the file to read" << endl;

		
//utilisation de la librairie CImg
		CImg<unsigned char> img(TAILLE_IMAGE+300,TAILLE_IMAGE+1,1,3);        // Define a 100x100 color image with 8 bits per color component.
  	img.fill(0);                                 // Set pixel values to 0 (color : black)
		unsigned char purple[] = { 255,0,255 }, red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 }, white[] = {255, 255, 255}, color_test[] = {126,126,126}; //set the different colors to use

//application de la division pour avoir la moyenne et creation des images
		for(int i=0; i<K_max-K_min; i++)
		{
			for(int j=0; j<5; j++)
			{
				img.fill(0);
				/*img.draw_line(0, 1, TAILLE_IMAGE, 1, green, 1, ~0U, true );
				img.draw_line(0, TAILLE_IMAGE-5*90, TAILLE_IMAGE, TAILLE_IMAGE-5*90, blue, 1, ~0U, true );
				img.draw_line(0, TAILLE_IMAGE-5*80, TAILLE_IMAGE, TAILLE_IMAGE-5*80, purple, 1, ~0U, true );
				img.draw_line(0, TAILLE_IMAGE-5*70, TAILLE_IMAGE, TAILLE_IMAGE-5*70, red, 1, ~0U, true );
				img.draw_line(0, TAILLE_IMAGE-5*50, TAILLE_IMAGE, TAILLE_IMAGE-5*50, color_test, 1, ~0U, true );*/
				int k=0;
				while(matrice_of_number_of_terms_used[i][j][k]!=0)
				{
					img.draw_line((j+1)*k, 1, (j+1)*(k+1), 1, green, 1, ~0U, true );
					img.draw_line((j+1)*k, TAILLE_IMAGE-5*90, (j+1)*(k+1), TAILLE_IMAGE-5*90, blue, 1, ~0U, true );
					img.draw_line((j+1)*k, TAILLE_IMAGE-5*80, (j+1)*(k+1), TAILLE_IMAGE-5*80, purple, 1, ~0U, true );
					img.draw_line((j+1)*k, TAILLE_IMAGE-5*70, (j+1)*(k+1), TAILLE_IMAGE-5*70, red, 1, ~0U, true );
					img.draw_line((j+1)*k, TAILLE_IMAGE-5*50, (j+1)*(k+1), TAILLE_IMAGE-5*50, color_test, 1, ~0U, true );

					if(matrice_of_number_of_terms_used[i][j][k]!=0) matrice_of_all_average_percentage[i][j][k]/=matrice_of_number_of_terms_used[i][j][k];
					//img.draw_point ( (j+1)*k, TAILLE_IMAGE - 5*matrice_of_all_average_percentage[i][j][k], 0, red, 1 );
					if(k==0) img.draw_line (0, TAILLE_IMAGE, (j+1)*k, TAILLE_IMAGE - 5*matrice_of_all_average_percentage[i][j][k], white, 1, ~0U, true );
					else img.draw_line ((j+1)*(k-1), TAILLE_IMAGE - 5*matrice_of_all_average_percentage[i][j][k-1], (j+1)*k, TAILLE_IMAGE - 5*matrice_of_all_average_percentage[i][j][k], white, 1, ~0U, true );
					k++;
				}

				//img.display("");
				switch(i)
				{					
					case 0:
						switch(j)
						{
							case 0:
								img.display("K = 2 and nb_pattern used = 1");
								img.save_png("K=2andNb_pattern_used=1.png", 0);
								img.save_other("K=2andNb_pattern_used=1.svg", 100);
								break;
							case 1:
								img.display("K = 2 and nb_pattern used = 2");
								img.save_png("K=2andNb_pattern_used=2.png", 0);
								img.save_other("K=2andNb_pattern_used=2.svg", 100);
							case 2:
								img.display("K = 2 and nb_pattern used = 3");
								img.save_png("K=2andNb_pattern_used=3.png", 0);
								img.save_other("K=2andNb_pattern_used=3.svg", 100);
								break;
							case 3:
								img.display("K = 2 and nb_pattern used = 4");
								img.save_png("K=2andNb_pattern_used=4.png", 0);
								img.save_other("K=2andNb_pattern_used=4.svg", 100);
								break;
							case 4:
								img.display("K = 2 and nb_pattern used = 5");
								img.save_png("K=2andNb_pattern_used=5.png", 0);
								img.save_other("K=2andNb_pattern_used=5.svg", 100);
								break;
						}
						break;
					case 1:
						switch(j)
						{
							case 0:
								img.display("K = 3 and nb_pattern used = 1");
								img.save_png("K=3andNb_pattern_used=1.png", 0);
								img.save_other("K=3andNb_pattern_used=1.svg", 100);
								break;
							case 1:
								img.display("K = 3 and nb_pattern used = 2");
								img.save_png("K=3andNb_pattern_used=2.png", 0);
								img.save_other("K=3andNb_pattern_used=2.svg", 100);
							case 2:
								img.display("K = 3 and nb_pattern used = 3");
								img.save_png("K=3andNb_pattern_used=3.png", 0);
								img.save_other("K=3andNb_pattern_used=3.svg", 100);
								break;
							case 3:
								img.display("K = 3 and nb_pattern used = 4");
								img.save_png("K=3andNb_pattern_used=4.png", 0);
								img.save_other("K=3andNb_pattern_used=4.svg", 100);
								break;
							case 4:
								img.display("K = 3 and nb_pattern used = 5");
								img.save_png("K=3andNb_pattern_used=5.png", 0);
								img.save_other("K=3andNb_pattern_used=5.svg", 100);
								break;
						}
						break;					
				}
			}
		}		



//desallocation de toute la memoire utilisee
		for(int i=0; i<K_max-K_min; i++)
		{
			for(int j=0; j<5; j++)
			{
				delete[] matrice_of_all_average_percentage[i][j];
				delete[] matrice_of_number_of_terms_used[i][j];
			}
		}
		for(int i=0; i<K_max-K_min; i++)
		{
			delete[] matrice_of_all_average_percentage[i];
			delete[] matrice_of_number_of_terms_used[i];
		}
		delete[] matrice_of_all_average_percentage;
		delete[] matrice_of_number_of_terms_used;



		return EXIT_SUCCESS;
	}
}
