//g++ -o aaa test.cpp -lm -lpthread -lX11


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

#define taille_image 100
#define TAILLE_IMAGE 100

class Point
{
    public:
    double X, Y;
    int value;
};

//void dessiner_schema(double L, int nbre_pts, int /*const& */*tab_value_by_pt, double /*const& */mat_fake_Gij[][7][7][2], double /*const&*/mat_of_all_areas[][7][7][2])//, double /*const&*/tab[][3])
//{
	//int nbre_pts2(0), nbre_coordinates2(0)/*nbre_coordinates?*//*tmp2*/, value_possible2(0)/*value_possible?*//*tmp1*/;
	/*ifstream fichier2("test.txt");
    if(fichier2)
    {
        fichier2.seekg(0, ios::beg);
        //string ligne;
        int mot2;
        double coordonnee2;

        for(int i=0; i<3; i++)
        {
            switch(i)
            {
                case 0:
                    fichier2 >> mot2;
                    //cout << mot << endl;
                    nbre_pts2=(int)mot2;
                    cout << nbre_pts2 << endl;
                    break;
                case 1:
                    fichier2 >> mot2;
                    value_possible2=(int)mot2;
                    cout << value_possible2 << endl;
                    break;
                case 2:
                    fichier2 >> mot2;
                    nbre_coordinates2=(int)mot2;
                    cout << nbre_coordinates2 << endl;
                    break;
            }

        }


        double tab[nbre_pts2][nbre_coordinates2+1];
        //int tab_value_by_pt[nbre_pts];
        //i=0;

        for(int i=0; i<nbre_pts2; i++)
        {
            for(int j=0; j<nbre_coordinates2; j++)
            {
                fichier2 >> coordonnee2;
                tab[i][j]=coordonnee2;
            }

            fichier2 >> mot2;
            tab[i][nbre_coordinates2]=mot2;
            //tab_value_by_pt[i]=mot;
        }
		

	
	int LBIS=(int)L;
							//L=(double)LBIS;
							unsigned char purple[] = { 255,0,255 }, red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
							CImg<unsigned char> img2(TAILLE_IMAGE+1,TAILLE_IMAGE+1,1,3);        // Define a 100x100 color image with 8 bits per color component.
  					img2.fill(0);                                 // Set pixel values to 0 (color : black)
  					//unsigned char purple[] = { 255,0,255 }, red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };      // Define a purple color

						for(int i=0; i<nbre_pts; i++)
  					{
							if(tab_value_by_pt[i]==0)
								img2.draw_point ( tab[i][0]*TAILLE_IMAGE, tab[i][1]*TAILLE_IMAGE, 0, red, 1 );
							if(tab_value_by_pt[i]==1)
								img2.draw_point ( tab[i][0]*TAILLE_IMAGE, tab[i][1]*TAILLE_IMAGE, 0, green, 1 );
			
						}
						//TODO LIST !!! PLUS TARD CREE UN VECTOR AVEC LES NOUVEAUX POINTS, IL FAUDRA AUSSI LES COLORIER
										
						for(int i=0; i<LBIS; i++)
            {
            	for(int j=0; j<LBIS; j++)
              {

								if(j!=LBIS-1)
								{								
									if(mat_fake_Gij[LBIS-2][i][j][0]!=mat_fake_Gij[LBIS-2][i][j+1][0])
										img2.draw_line (mat_of_all_areas[LBIS-2][i][j][0]*TAILLE_IMAGE, (mat_of_all_areas[LBIS-2][i][j][1]-(double)1/LBIS)*TAILLE_IMAGE, mat_of_all_areas[LBIS-2][i][j][0]*TAILLE_IMAGE, mat_of_all_areas[LBIS-2][i][j][1]*TAILLE_IMAGE, blue, 1, ~0U, true );	
												//img.draw_line (5, 0, 5, 1000, blue, 1, ~0U, true );
								}
								
								
								if(i!=LBIS-1)
								{
									if(mat_fake_Gij[LBIS-2][i][j][0]!=mat_fake_Gij[LBIS-2][i+1][j][0])
										img2.draw_line ((mat_of_all_areas[LBIS-2][i][j][0]-(double)1/LBIS)*TAILLE_IMAGE, mat_of_all_areas[LBIS-2][i][j][1]*TAILLE_IMAGE, mat_of_all_areas[LBIS-2][i][j][0]*TAILLE_IMAGE, mat_of_all_areas[LBIS-2][i][j][1]*TAILLE_IMAGE, blue, 1, ~0U, true );
								}
								
							}
						}
					
										
										//img.display("L = "+L);
						//const char* titre="L = "+LBIS;
						//img2.display(titre);

				switch(LBIS)
				{					
						case 2:
							img2.display("L = 2");
							break;
						case 3:
							img2.display("L = 3");
							break;
						case 4:
							img2.display("L = 4");
							break;
						case 5:
							img2.display("L = 5");
							break;
						case 6:
							img2.display("L = 6");
							break;
						case 7:
							img2.display("L = 7");
							break;
				}
	}
}*/

/*double** membership_calc(Point p, int L)
{
    int a(0), b(0);
    double mat_of_membership_function_value_per_coordinates[L][2];

    for(int k=1; k<L+1; k++)
    {
        a=(k-1)/(L-1);
        b=1/(L-1);
        mat_of_membership_function_value_per_coordinates[k][0]=max(1-(std::fabs(p.X-a)/b),(double)0);
        mat_of_membership_function_value_per_coordinates[k][0]=max(1-(std::fabs(p.Y-a)/b),(double)0);
    }
    return mat_of_membership_function_value_per_coordinates;
}*/


int main()
{
    //cout << "Hello world!" << endl;
    //int i(0);



    //RECUPERATION DATAS
    int nbre_pts(0), nbre_coordinates(0)/*nbre_coordinates?*//*tmp2*/, value_possible(0)/*value_possible?*//*tmp1*/;
		unsigned char purple[] = { 255,0,255 }, red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 }, white[] = {255, 255, 255}, color_test[] = {126,126,126};

    //ifstream fichier("/home/julien/Desktop/test.txt");
		ifstream fichier("test.txt");
    if(fichier)
    {
        fichier.seekg(0, ios::beg);
        //string ligne;
        int mot;
        double coordonnee;

        for(int i=0; i<3; i++)
        {
            switch(i)
            {
                case 0:
                    fichier >> mot;
                    //cout << mot << endl;
                    nbre_pts=(int)mot;
                    cout << nbre_pts << endl;
                    break;
                case 1:
                    fichier >> mot;
                    value_possible=(int)mot;
                    cout << value_possible << endl;
                    break;
                case 2:
                    fichier >> mot;
                    nbre_coordinates=(int)mot;
                    cout << nbre_coordinates << endl;
                    break;
            }

        }


        double tab[nbre_pts][nbre_coordinates+1];
        int tab_value_by_pt[nbre_pts];
        //i=0;

        for(int i=0; i<nbre_pts; i++)
        {
            for(int j=0; j<nbre_coordinates; j++)
            {
                fichier >> coordonnee;
                tab[i][j]=coordonnee;
            }

            fichier >> mot;
            tab[i][nbre_coordinates]=mot;
            tab_value_by_pt[i]=mot;
        }



        //check all got caught
        /*for(int j=0; j<nbre_pts; j++)
        {
            for(int k=0; k<nbre_coordinates+1; k++)
            {
                cout << tab[j][k] ;
                cout << "\t" ;
            }
            cout << "\n" ;
        }*/ //OK

        //FIN RECUPERATION DATAS


        /*CALC OF MEMBERSHIP FUNCTION*/
        //int L=2;//VALUE OF L
        //matrix with 4 dim in order to save all the conditions with the 6 different L possible
        //int mat_tot[];

				double mat_of_all_Gij_CFij[6][7][7][2]={0}, mat_of_all_areas[6][7][7][2]={0};


        for(double L=2; L<8; L++)
        {
            //double a(0), b(0);
            //double mat_of_membership_function_value_per_coordinates[nbre_pts][nbre_coordinates][(int)L], x(0);


						//old calc of membership value
						/*						
						cout << "membership value START" << endl;

            //go through the data matrix (tab)
            for(int i=0; i<nbre_pts; i++)
            {
                for(int j=0; j<nbre_coordinates; j++)
                {
                    x=tab[i][j];
                    //k varies between 1..L
                    for(int k=1; k<L+1; k++)
                    {
                        a=(k-1)/(L-1);
                        b=1/(L-1);
                        //cout << a << " " << b << endl;
                        mat_of_membership_function_value_per_coordinates[i][j][k-1]=max(1-(std::fabs(x-a)/b),(double)0);
                        //cout << 1-(std::fabs(x-a)/b) << endl;
                        //cout << max(1-(std::fabs(x-a)/b),(double)0) << endl;

                        //SEEMS OK
                        cout << i<<"\t"<<j<<"\t"<<k<<"\t"<< mat_of_membership_function_value_per_coordinates[i][j][k-1] << endl; //DISPLAY number of the point + nbre of coordinate used + nbre of membership displayed + VALUE of membership
                    }
                }
            }

						cout << "membership value END" << endl;*/

            //mat_tot[L-2]=mat_of_membership_function_value_per_coordinates;

            //TODO REFAIRE LE CALCUL DE LADAPTIBILITY
            /*CALC OF ADAPTIBILITY*/

            //FAUX
            /*//cout << value_possible << endl;
            double mat_of_all_adaptibility[value_possible], Sum(0);

            //initialisation du tableau a 0
            for(int i=0; i<value_possible; i++) mat_of_all_adaptibility[i]=0;

            //go through matrix of membership function values
            for(int i=0; i<nbre_pts; i++)
            {
                for(int j=0; j<nbre_coordinates; j++)ĵ
                {
                    //k varies between 1..L
                    double Mult(1);

                    for(int k=0; k<L; k++)
                    {
                        for(int l=0; l<L; l++)
                        {
                            //calc of adaptibility which is defined by the sum of the different membership function of the 1st coordinate multiply with all others membership function of the secund coordinate
                            mat_of_all_adaptibility[tab_value_by_pt[i]]+=mat_of_membership_function_value_per_coordinates[i][j][k]*mat_of_membership_function_value_per_coordinates[i][j+1][l];
                        }
                    }

                }
            }

            cout << mat_of_all_adaptibility[0] << endl;
            cout << mat_of_all_adaptibility[1] << endl;*/


            double mat_of_areas[(int)L][(int)L][3]; //for each area define X, Y, GROUP

            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
                    mat_of_areas[i][j][0]=1/L+j*1/L;//modif of x
                    mat_of_areas[i][j][1]=1/L+i*1/L;//modif of y
                    mat_of_areas[i][j][2]=2;


										//on remplit la matrice contenant toutes les aires
										mat_of_all_areas[(int)L-2][i][j][0]=mat_of_areas[i][j][0];
										mat_of_all_areas[(int)L-2][i][j][1]=mat_of_areas[i][j][1];

                    //SEEMS OK
                    //cout << i << "\t" << j <<"\t"<< mat_of_areas[i][j][0]<<"\t"<<mat_of_areas[i][j][1] << endl; //DISPLAY THE DIFFERENT AREAS LIKE MAT With their x(abs) ending and y(ord) ending
                }
            }




            //vector<Point> vector_of_points_in_area(0); //creation of table empty which will contain the points Points that are in the define(chosen) area
            vector<int> vector_of_ranks_points_in_area(0);
						//for mat Gij_CFij [2] permet d'avoir Gij en [0] et CFij [1], et pr mat of adaptability [2] permet davoir betaG1 en [0] et betaG2 en [1]
            double mat_of_adaptability_of_each_area[(int)L][(int)L][2], mat_of_Gij_CFij_of_each_area[(int)L][(int)L][2]; //---> absolument les mettre a 0 !!! for the moment not the case so TODO LIST ==>> DONE
            double Gij(0), CFij(0)/*, Sum_of_membership_function_G1(0)*/;

            //INITIALISATION A 0 OF BOTH MAT
            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
                    mat_of_adaptability_of_each_area[i][j][0]=0;
                    mat_of_adaptability_of_each_area[i][j][1]=0;
                    mat_of_Gij_CFij_of_each_area[i][j][0]=2; //we put Gij in none group
                    mat_of_Gij_CFij_of_each_area[i][j][1]=0;
                }
            }



						cout << "ADAPTIBILITY value START" << endl;

						double x1(0), x2(0), a1(0), a2(0), b1(0), b2(0);

            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
                    /*vector<Point> vector_of_points_in_area(0); //creation of table empty which will contain the points Points that are in the define(chosen) area
                    vector<int> vector_of_ranks_points_in_area(0);*/

                    //parcourt of table containing all points, checking if they are or not in the area
                    for(int k=0; k<nbre_pts; k++)
                    {

												
                        if(tab[k][0]<mat_of_areas[i][j][0] && tab[k][1]<mat_of_areas[i][j][1] && tab[k][0]>=(mat_of_areas[i][j][0]-1/L) && tab[k][1]>=(mat_of_areas[i][j][1]-1/L))
                        {
                            //we only need the rank of the points
                            //vector_of_ranks_points_in_area.push_back(k);

                            //just a test && not using it for the moment
                            /*Point my_point;
                            my_point.X=tab[k][0];
                            my_point.Y=tab[k][1];
                            my_point.value=tab[k][2];*/
                            //vector_of_points_in_area.push_back(my_point);

													//cout << "point dans " << i << "\t" << j << endl;

													//if((tab[k][0]<mat_of_areas[i][j][0] && tab[k][1]<mat_of_areas[i][j][1]) || tab[k][0]==1)
													//{

													a1=(((double)j+1)-1)/(L-1);//car j varie entre 0 et L-1 au lieu de 1 et L
                        	b1=1/(L-1);

													a2=(((double)i+1)-1)/(L-1);//de mm que pour j, voir le commentaire ultérieur
                        	b2=1/(L-1);

													x1=tab[k][0];
													x2=tab[k][1];

													//cout << "calc of memb func of x1 " << max(1-(std::fabs(x1-a1)/b1),(double)0) << endl;
													//cout << "calc of memb func of x2 " << max(1-(std::fabs(x2-a2)/b2),(double)0) << endl;
                         	//mat_of_membership_function_value_per_coordinates[i][j][k-1]=max(1-(std::fabs(x-a)/b),(double)0);

													//CALC OF BETA_1 et BETA_2 (adaptibility) && calc inst of membership_function
													if(tab_value_by_pt[k]==0)
													{
														//cout << "point rouge" << endl;
                            mat_of_adaptability_of_each_area[i][j][0]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}

                        	if(tab_value_by_pt[k]==1)
													{	
														//cout << "point vert" << endl;
                            mat_of_adaptability_of_each_area[i][j][1]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}
												
                        }

												//the 3rd following cases are considering if we are on a edge
												else if(tab[k][0]==1 && tab[k][1]==1 && tab[k][0]==(mat_of_areas[i][j][0]) && tab[k][1]==(mat_of_areas[i][j][1]-1/L))
												{
													a1=(((double)j+1)-1)/(L-1);//car j varie entre 0 et L-1 au lieu de 1 et L
                        	b1=1/(L-1);

													a2=(((double)i+1)-1)/(L-1);//de mm que pour j, voir le commentaire ultérieur
                        	b2=1/(L-1);

													x1=tab[k][0];
													x2=tab[k][1];

													//cout << "calc of memb func of x1 " << max(1-(std::fabs(x1-a1)/b1),(double)0) << endl;
													//cout << "calc of memb func of x2 " << max(1-(std::fabs(x2-a2)/b2),(double)0) << endl;
                         	//mat_of_membership_function_value_per_coordinates[i][j][k-1]=max(1-(std::fabs(x-a)/b),(double)0);

													//CALC OF BETA_1 et BETA_2 (adaptibility) && calc inst of membership_function
													if(tab_value_by_pt[k]==0)
													{
														//cout << "point rouge" << endl;
                            mat_of_adaptability_of_each_area[i][j][0]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}

                        	if(tab_value_by_pt[k]==1)
													{	
														//cout << "point vert" << endl;
                            mat_of_adaptability_of_each_area[i][j][1]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}
												}
												else if(tab[k][0]<mat_of_areas[i][j][0] && tab[k][1]==1 && tab[k][0]>=(mat_of_areas[i][j][0]-1/L) && tab[k][1]==(mat_of_areas[i][j][1]))
												{
													a1=(((double)j+1)-1)/(L-1);//car j varie entre 0 et L-1 au lieu de 1 et L
                        	b1=1/(L-1);

													a2=(((double)i+1)-1)/(L-1);//de mm que pour j, voir le commentaire ultérieur
                        	b2=1/(L-1);

													x1=tab[k][0];
													x2=tab[k][1];

													//cout << "calc of memb func of x1 " << max(1-(std::fabs(x1-a1)/b1),(double)0) << endl;
													//cout << "calc of memb func of x2 " << max(1-(std::fabs(x2-a2)/b2),(double)0) << endl;
                         	//mat_of_membership_function_value_per_coordinates[i][j][k-1]=max(1-(std::fabs(x-a)/b),(double)0);

													//CALC OF BETA_1 et BETA_2 (adaptibility) && calc inst of membership_function
													if(tab_value_by_pt[k]==0)
													{
														//cout << "point rouge" << endl;
                            mat_of_adaptability_of_each_area[i][j][0]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}

                        	if(tab_value_by_pt[k]==1)
													{	
														//cout << "point vert" << endl;
                            mat_of_adaptability_of_each_area[i][j][1]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}
												}
												else if(tab[k][0]==1 && tab[k][1]<mat_of_areas[i][j][1] && tab[k][0]==(mat_of_areas[i][j][0]) && tab[k][1]>=(mat_of_areas[i][j][1]-1/L))
												{
													a1=(((double)j+1)-1)/(L-1);//car j varie entre 0 et L-1 au lieu de 1 et L
                        	b1=1/(L-1);

													a2=(((double)i+1)-1)/(L-1);//de mm que pour j, voir le commentaire ultérieur
                        	b2=1/(L-1);

													x1=tab[k][0];
													x2=tab[k][1];

													//cout << "calc of memb func of x1 " << max(1-(std::fabs(x1-a1)/b1),(double)0) << endl;
													//cout << "calc of memb func of x2 " << max(1-(std::fabs(x2-a2)/b2),(double)0) << endl;
                         	//mat_of_membership_function_value_per_coordinates[i][j][k-1]=max(1-(std::fabs(x-a)/b),(double)0);

													//CALC OF BETA_1 et BETA_2 (adaptibility) && calc inst of membership_function
													if(tab_value_by_pt[k]==0)
													{
														//cout << "point rouge" << endl;
                            mat_of_adaptability_of_each_area[i][j][0]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}

                        	if(tab_value_by_pt[k]==1)
													{	
														//cout << "point vert" << endl;
                            mat_of_adaptability_of_each_area[i][j][1]+=max(1-(std::fabs(x1-a1)/b1),(double)0)*max(1-(std::fabs(x2-a2)/b2),(double)0);
													}
												}
												//

                    }
;

                    //on parcourt le vector in order to calculate CF ij && G ij of the area
                    /*for(int l=0; l<vector_of_ranks_points_in_area.size(); l++)
                    {
                        if(tab_value_by_pt[vector_of_ranks_points_in_area[l]]==0)
                            mat_of_adaptability_of_each_area[i][j][0]+=mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][0][i]*mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][1][j];
                        if(tab_value_by_pt[vector_of_ranks_points_in_area[l]]==1)
                            mat_of_adaptability_of_each_area[i][j][1]+=mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][0][i]*mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][1][j];
                        //mat_of_membership_function_value_per_coordinates[i][j][k]
                    }*/

										cout << mat_of_adaptability_of_each_area[i][j][0] << "\t" << mat_of_adaptability_of_each_area[i][j][1] << endl; 

										//CALC OF Gij
                    if(mat_of_adaptability_of_each_area[i][j][0]>mat_of_adaptability_of_each_area[i][j][1])
                        mat_of_Gij_CFij_of_each_area[i][j][0]=0;
                    else if(mat_of_adaptability_of_each_area[i][j][1]>mat_of_adaptability_of_each_area[i][j][0])
                        mat_of_Gij_CFij_of_each_area[i][j][0]=1;
                    else mat_of_Gij_CFij_of_each_area[i][j][0]=2;

										//CALC OF CFij
                    if(mat_of_adaptability_of_each_area[i][j][0]+mat_of_adaptability_of_each_area[i][j][1]>0)
                        mat_of_Gij_CFij_of_each_area[i][j][1]=(std::fabs(mat_of_adaptability_of_each_area[i][j][0]-mat_of_adaptability_of_each_area[i][j][1]))/(mat_of_adaptability_of_each_area[i][j][0]+mat_of_adaptability_of_each_area[i][j][1]);
                    else if(mat_of_adaptability_of_each_area[i][j][0]+mat_of_adaptability_of_each_area[i][j][1]==0)
                        mat_of_Gij_CFij_of_each_area[i][j][1]=0;


										//on remplit la matrice generale
										mat_of_all_Gij_CFij[(int)L-2][i][j][0]=mat_of_Gij_CFij_of_each_area[i][j][0];
										mat_of_all_Gij_CFij[(int)L-2][i][j][1]=mat_of_Gij_CFij_of_each_area[i][j][1];


										//vector_of_ranks_points_in_area.clear();
                } 
            }

						cout << "ADAPTIBILITY value END" << endl;


						/*cout << "Gij value START" << endl;						

						for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
									cout << i << "\t" << j << "\t" << mat_of_Gij_CFij_of_each_area[i][j][0] << endl; 
								}
						}

						cout << "Gij value END" << endl;*/

			
						/*
						//on parcourt les area et on determine le groupe pour ceux qui n'en ont pas
										//vector<int[2]> mat_of_undetermine_area(0);
						bool undeterminate_area_remaining(true);
						//on parcourt les area et on determine si on doit colorier le contour bas, droite, bas+droite, ou aucun avec respectivement le code couleur suivant 1, 2, 3, 0
						do
						{
											//mat_of_undetermine_area.clear();
							undeterminate_area_remaining=false;
							for(int i=0; i<L; i++)
         			{
         				for(int j=0; j<L; j++)
         				{
									if(mat_of_Gij_CFij_of_each_area[i][j][0]==2)
									{
														//mat_of_undetermine_area.push_back({i, j});

										if(j!=L-1)			
										{
															mat_of_Gij_CFij_of_each_area[i][j][0]=mat_of_Gij_CFij_of_each_area[i][j+1][0];
															if(mat_of_Gij_CFij_of_each_area[i][j+1][0]==2 && i!=L-1)
																mat_of_Gij_CFij_of_each_area[i][j][0]=mat_of_Gij_CFij_of_each_area[i+1][j][0];
															if(mat_of_Gij_CFij_of_each_area[i][j+1][0]==2 && i==L-1)
																mat_of_Gij_CFij_of_each_area[i][j][0]=mat_of_Gij_CFij_of_each_area[i-1][j][0];
										}														
										else
										{
															mat_of_Gij_CFij_of_each_area[i][j][0]=mat_of_Gij_CFij_of_each_area[i][j-1][0];
															if(mat_of_Gij_CFij_of_each_area[i][j+1][0]==2 && i!=L-1)
																mat_of_Gij_CFij_of_each_area[i][j][0]=mat_of_Gij_CFij_of_each_area[i+1][j][0];
															if(mat_of_Gij_CFij_of_each_area[i][j+1][0]==2 && i==L-1)
																mat_of_Gij_CFij_of_each_area[i][j][0]=mat_of_Gij_CFij_of_each_area[i-1][j][0];	
										}

														//si l'aire est tjrs indeterminée il faut recommencer			
										if(mat_of_Gij_CFij_of_each_area[i][j][0]==2)
											undeterminate_area_remaining=true;
   								}                			
                }
           		}
						} while(undeterminate_area_remaining);*/


						/*cout << "Gij after DETERMINATION value START" << endl;						

						for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
									cout << i << "\t" << j << "\t" << mat_of_Gij_CFij_of_each_area[i][j][0] << endl; 
								}
						}

						cout << "Gij after DETERMINATION value END" << endl;*/

										
						

            //end of L locked calc
        }



				//pb of initializer
				double mat_fake_Gij[6][7][7][2]; //matrix useful for using the fuzzy rule on undetermined areas without modifying the genuine matrix
				//initialisation degueulasse..
				for(int i=0; i<6; i++)
				{for(int j=0; j<7; j++)
				{for(int k=0; k<7; k++)
				{for(int l=0; l<2; l++){mat_fake_Gij[i][j][k][l]=mat_of_all_Gij_CFij[i][j][k][l];}}}}


				//ON AFFICHE TOUS LES DESSINS
				for(int L=2; L<8; L++)
				{


					cout << "Gij value START" << endl;						

						for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
									cout << i << "\t" << j << "\t" << mat_of_all_Gij_CFij[(int)L-2][i][j][0] << endl; 
								}
						}

						cout << "Gij value END" << endl;


					//fake determination of Group ==> we use "mat_fake_Gij" and a fuzzy rule of determination
					bool undeterminate_area_remaining(true);
						//on parcourt les area et on determine si on doit colorier le contour bas, droite, bas+droite, ou aucun avec respectivement le code couleur suivant 1, 2, 3, 0
						do
						{
											//mat_of_undetermine_area.clear();
							undeterminate_area_remaining=false;
							for(int i=0; i<L; i++)
         			{
         				for(int j=0; j<L; j++)
         				{
									if(mat_fake_Gij[(int)L-2][i][j][0]==2)
									{
														//mat_of_undetermine_area.push_back({i, j});

										if(j!=L-1)			
										{
															mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i][j+1][0];
															if(mat_fake_Gij[(int)L-2][i][j+1][0]==2 && i!=L-1)
																mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i+1][j][0];
															if(mat_fake_Gij[(int)L-2][i][j+1][0]==2 && i==L-1)
																mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i-1][j][0];
															if(mat_fake_Gij[(int)L-2][i][j][0]==2 && j!=0 )
																mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i][j-1][0];
										}														
										else
										{
															mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i][j-1][0];
															if(mat_fake_Gij[(int)L-2][i][j-1][0]==2 && i!=L-1)
																mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i+1][j][0];
															if(mat_fake_Gij[(int)L-2][i][j-1][0]==2 && i==L-1)
																mat_fake_Gij[(int)L-2][i][j][0]=mat_fake_Gij[(int)L-2][i-1][j][0];	
															/*if(mat_of_all_Gij_CFij[(int)L-2][i][j][0]==2 && j!=0 )
																mat_of_all_Gij_CFij[(int)L-2][i][j][0]=mat_of_all_Gij_CFij[(int)L-2][i][j-1][0];*/
										}

														//si l'aire est tjrs indeterminée il faut recommencer			
										if(mat_fake_Gij[(int)L-2][i][j][0]==2)
											undeterminate_area_remaining=true;
   								}                			
                }
           		}
						} while(/*0*/undeterminate_area_remaining);


//TODO LIST ==> define again all the drawing



				//determination des bordures a colorier
										//string nom_map("L = "+L);
						CImg<unsigned char> img(TAILLE_IMAGE,TAILLE_IMAGE,1,3);        // Define a 100x100 color image with 8 bits per color component.
  					img.fill(0);                                 // Set pixel values to 0 (color : black)
  					//unsigned char purple[] = { 255,0,255 }, red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };      // Define a purple color


//OK ==> drawing of each point with color
						for(int i=0; i<nbre_pts; i++)
  					{
							if(tab_value_by_pt[i]==0)
								img.draw_point ( tab[i][0]*TAILLE_IMAGE, TAILLE_IMAGE-tab[i][1]*TAILLE_IMAGE, 0, red, 1 );
							if(tab_value_by_pt[i]==1)
								img.draw_point ( tab[i][0]*TAILLE_IMAGE, TAILLE_IMAGE-tab[i][1]*TAILLE_IMAGE, 0, green, 1 );
			
						}

						double x1(0), x2(0), a1(0), a2(0), b(0), alpha1(0), alpha2(0);
						//TODO LIST !!! PLUS TARD CREE UN VECTOR AVEC LES NOUVEAUX POINTS, IL FAUDRA AUSSI LES COLORIER
						//img.draw_line (5, 0, 5, 1000, blue, 1, ~0U, true );
						for(int i=0; i<TAILLE_IMAGE+1; i++)
            {
            	for(int j=0; j<TAILLE_IMAGE+1; j++)
              {
								//cout
								x1=(double)j/(double)TAILLE_IMAGE;
								x2=(double)i/(double)TAILLE_IMAGE;
								//if(x1==0.29 || x1==0.58 || x2==0.45)cout << x1 << "\t" << x2 << endl;
								alpha1=(double)0;
								alpha2=(double)0;

								for(int k=0; k<L; k++)
								{
									for(int l=0; l<L; l++)
									{
										a1=(((double)l+1)-1)/((double)L-1);//car j varie entre 0 et L-1 au lieu de 1 et L
                		b=1/((double)L-1);

										a2=(((double)k+1)-1)/((double)L-1);//de mm que pour j, voir le commentaire ultérieur
                		//b=1/(L-1);

								
								
//CALC OF BETA_1 et BETA_2 (adaptibility) && calc inst of membership_function
										if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==0)
										{
														//cout << "point rouge" << endl;
                      alpha1=max(max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha1);
										}

                    if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==1)
										{	
														//cout << "point vert" << endl;
                    	alpha2=max(max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha2);
										}
										
									}
								}
								
								//cout << "alpha1 : " << alpha1 << "\t" << "alpha2 : " << alpha2 << endl;
								//if(x1==0.29) cout << x1*TAILLE_IMAGE << endl;
								//img.draw_point ( x1*TAILLE_IMAGE, TAILLE_IMAGE-x2*TAILLE_IMAGE, 0, white, 1 );			
								
								if(alpha1==alpha2) 
								{
									img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
									//break;
									
								}
								else if(alpha1 > alpha2) img.draw_point ( j, TAILLE_IMAGE-i, 0, blue, 1 );
								else if(alpha1 < alpha2) img.draw_point ( j, TAILLE_IMAGE-i, 0, purple, 1 ); 							
							}
						}
					
				//img.draw_point(29,45,0,color_test,1);						
				//img.draw_point(58,45,0,color_test,1);
						
				switch(L)
				{					
						case 2:
							img.display("L = 2");
							break;
						case 3:
							img.display("L = 3");
							break;
						case 4:
							img.display("L = 4");
							break;
						case 5:
							img.display("L = 5");
							break;
						case 6:
							img.display("L = 6");
							break;
						case 7:
							img.display("L = 7");
							break;
				}
				}

//#################################################################################################################################################################################



						






//END OF TODO LIST ==> define again all the drawing




        
				

    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }


		


    return 0;
}

