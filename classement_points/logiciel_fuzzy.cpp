//g++ -o aaa test.cpp -lm -lpthread -lX11


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

//#define taille_image 100
#define TAILLE_IMAGE 200

class Point
{
    public:
    double X, Y;
    int value;
};


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


double get_value_membership_function(double x, double k, double L)
{
	double value_membership(0), a(0), b(0);
	a=(k-1)/(L-1);
	b=1/(L-1);
	value_membership=max(1-(std::fabs(x-a)/b), (double)0);
	return value_membership;
}


int get_initial_color(double i, double j, double L, double mat_of_all_Gij_CFij[][7][7][2])
{
	int initial_color(0);
	double x1(0), x2(0), alpha1(0), alpha2(0);

	x1=(double)j/(double)TAILLE_IMAGE;
	x2=(double)i/(double)TAILLE_IMAGE;
								//if(x1==0.29 || x1==0.58 || x2==0.45)cout << x1 << "\t" << x2 << endl;
	alpha1=(double)0;
	alpha2=(double)0;

	for(int k=0; k<L; k++)
	{
		for(int l=0; l<L; l++)
		{

								
								
//CALC OF ALPHA_1 et ALPHA_2 && calc inst of membership_function
			if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==0)
			{
														//cout << "point rouge" << endl;
      	alpha1=max(get_value_membership_function(x1, (double)(l+1), L)*get_value_membership_function(x2, (double)(k+1), L)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha1);
											//alpha1=max(max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha1);
			}

      if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==1)
			{	
														//cout << "point vert" << endl;
        alpha2=max(get_value_membership_function(x1, (double)(l+1), L)*get_value_membership_function(x2, (double)(k+1), L)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha2);
											//alpha2=max(max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha2);
			}
										
		}
	}
								

	if(alpha1 > alpha2) initial_color=0;
	if(alpha2 > alpha1) initial_color=1;
	else if(alpha1==alpha2) initial_color=2;
	return initial_color;
}


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



						//cout << "ADAPTIBILITY value START" << endl;

						double x1(0), x2(0), a1(0), a2(0), b(0), sum_test(0);//, b2(0);

            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
										//sum_test=0;
                    /*vector<Point> vector_of_points_in_area(0); //creation of table empty which will contain the points Points that are in the define(chosen) area
                    vector<int> vector_of_ranks_points_in_area(0);*/

                    //parcourt of table containing all points, checking if they are or not in the area
                    for(int k=0; k<nbre_pts; k++)
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
                        	b=1/(L-1);

													a2=(((double)i+1)-1)/(L-1);//de mm que pour j, voir le commentaire ultérieur
                        	//b2=1/(L-1);

													x1=tab[k][0];
													x2=tab[k][1];

													//cout << "calc of memb func of x1 " << max(1-(std::fabs(x1-a1)/b1),(double)0) << endl;
													//cout << "calc of memb func of x2 " << max(1-(std::fabs(x2-a2)/b2),(double)0) << endl;
                         	//mat_of_membership_function_value_per_coordinates[i][j][k-1]=max(1-(std::fabs(x-a)/b),(double)0);

													//CALC OF BETA_1 et BETA_2 (adaptibility) && calc inst of membership_function
													if(tab_value_by_pt[k]==0)
													{
														//cout << "point rouge" << endl;
                            //mat_of_adaptability_of_each_area[i][j][0]+=max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0);
														mat_of_adaptability_of_each_area[i][j][0]+=get_value_membership_function(x1, (double)(j+1), L)*get_value_membership_function(x2, (double)(i+1), L);
														//sum_test+=get_value_membership_function(x1, (double)(j+1), L)*get_value_membership_function(x2, (double)(i+1), L);
														//if(sum_test!=mat_of_adaptability_of_each_area[i][j][0]) cout << "ERR\t" << mat_of_adaptability_of_each_area[i][j][0] << "\t" << sum_test << endl;
													}

                        	if(tab_value_by_pt[k]==1)
													{	
														//cout << "point vert" << endl;
                            //mat_of_adaptability_of_each_area[i][j][1]+=max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0);
														mat_of_adaptability_of_each_area[i][j][1]+=get_value_membership_function(x1, (double)(j+1), L)*get_value_membership_function(x2, (double)(i+1), L);
													}
												
                        

												//

                    }


                    //on parcourt le vector in order to calculate CF ij && G ij of the area
                    /*for(int l=0; l<vector_of_ranks_points_in_area.size(); l++)
                    {
                        if(tab_value_by_pt[vector_of_ranks_points_in_area[l]]==0)
                            mat_of_adaptability_of_each_area[i][j][0]+=mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][0][i]*mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][1][j];
                        if(tab_value_by_pt[vector_of_ranks_points_in_area[l]]==1)
                            mat_of_adaptability_of_each_area[i][j][1]+=mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][0][i]*mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][1][j];
                        //mat_of_membership_function_value_per_coordinates[i][j][k]
                    }*/

										//cout << mat_of_adaptability_of_each_area[i][j][0] << "\t" << mat_of_adaptability_of_each_area[i][j][1] << endl; 

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
	
										//cout << mat_of_all_Gij_CFij[(int)L-2][i][j][1] << "\t";


										//vector_of_ranks_points_in_area.clear();
                } 
            }

						//cout << "ADAPTIBILITY value END" << endl;


						/*cout << "Gij value START" << endl;						

						for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
									cout << i << "\t" << j << "\t" << mat_of_Gij_CFij_of_each_area[i][j][0] << endl; 
								}
						}

						cout << "Gij value END" << endl;*/

										
						

            //end of L locked calc
        }



				//ON AFFICHE TOUS LES DESSINS
				for(int L=2; L<8; L++)
				{


					/*cout << "Gij value START" << endl;						

						for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
									cout << i << "\t" << j << "\t" << mat_of_all_Gij_CFij[(int)L-2][i][j][0] << endl; 
								}
						}

						cout << "Gij value END" << endl;*/
					


//TODO LIST ==> define again all the drawing



				//determination des bordures a colorier
										//string nom_map("L = "+L);
						CImg<unsigned char> img(TAILLE_IMAGE+1,TAILLE_IMAGE+1,1,3);        // Define a 100x100 color image with 8 bits per color component.
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


//BRASSAGE HORIZONTAL
						double x1(0), x2(0), a1(0), a2(0), b(0), alpha1(0), alpha2(0);
						bool same=true, changing_color(false);
						int previous_color(0), current_color(0), previous_coloration_coord[2]={0,0},new_coloration_coord(0), old_coloration_Y_axis(0);
						int test_initial_color(0);
						//TODO LIST !!! PLUS TARD CREE UN VECTOR AVEC LES NOUVEAUX POINTS, IL FAUDRA AUSSI LES COLORIER
						//img.draw_line (5, 0, 5, 1000, blue, 1, ~0U, true );
						for(int i=0; i<TAILLE_IMAGE+1; i++)
            {
							//if(previous_coloration_coord[1]!=new_coloration_coord) cout << previous_coloration_coord[1] << "\t" << new_coloration_coord << endl;
							//previous_coloration_coord[1]=new_coloration_coord;
							//changing_color=false;
							//test_initial_color=get_initial_color((double)i, (double)0, L, mat_of_all_Gij_CFij[(int)L-2]);
							//cout << "test\t" << test_initial_color;
							previous_color=get_initial_color((double)i, (double)0, L, mat_of_all_Gij_CFij);
							current_color=get_initial_color((double)i, (double)0, L, mat_of_all_Gij_CFij);
							//previous_color=0;
							//current_color=0;

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

								
								
//CALC OF ALPHA_1 et ALPHA_2 && calc inst of membership_function
										if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==0)
										{
														//cout << "point rouge" << endl;
                      alpha1=max(get_value_membership_function(x1, (double)(l+1), L)*get_value_membership_function(x2, (double)(k+1), L)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha1);
											//alpha1=max(max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha1);
										}

                    if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==1)
										{	
														//cout << "point vert" << endl;
                    	alpha2=max(get_value_membership_function(x1, (double)(l+1), L)*get_value_membership_function(x2, (double)(k+1), L)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha2);
											//alpha2=max(max(1-(std::fabs(x1-a1)/b),(double)0)*max(1-(std::fabs(x2-a2)/b),(double)0)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha2);
										}
										
									}
								}
								

								if(alpha1 > alpha2) current_color=0;
								if(alpha2 > alpha1) current_color=1;
								else if(alpha1==alpha2) 
								{
									img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
									//current_color=2;
								}
			

//here we draw point from left to right to complete the line and get a closed border but the previous line is situated at the left
								//if(i==(previous_coloration_coord[0]+1))
								//{	
									//if(changing_color && j<=previous_coloration_coord[1]) img.draw_line (j, TAILLE_IMAGE-i, j+5, TAILLE_IMAGE-i, blue, 1, ~0U, true );//img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );


//here we draw point from left to right to complete the line and get a closed border but the previous line is situated at the right
									//if(j>=previous_coloration_coord[1] && !changing_color) img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
								//}

								//if( i>0 && i==(old_coloration_Y_axis+1) && changing_color && j<previous_coloration_coord[1]) img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
								
								if(current_color!=previous_color)
								{
									//old_coloration_Y_axis=previous_coloration_coord[0];
									//previous_coloration_coord[0]=i;
									//new_coloration_coord=j;
									//be_on_the_right_of=true;
									//if(current_color!=2 && previous_color!=2)
									//changing_color=true; 
									//cout << "omg" << endl;									
									img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
									previous_color=current_color;
								}  							
							}
						}


//BRASSAGE VERTICAL
						bool changing_color_bis(false);
						int previous_color_bis(0), current_color_bis(0);
						int test_initial_color_bis(0);

						for(int j=0; j<TAILLE_IMAGE+1; j++)
            {
							//test_initial_color_bis=get_initial_color((double)0, (double)j, L, mat_of_all_Gij_CFij);
							//cout << "test\t" << test_initial_color_bis << "\n";
							changing_color_bis=false;
							previous_color_bis=get_initial_color((double)0, (double)j, L, mat_of_all_Gij_CFij);
							current_color_bis=get_initial_color((double)0, (double)j, L, mat_of_all_Gij_CFij);

            	for(int i=0; i<TAILLE_IMAGE+1; i++)
              {
								
								x1=(double)j/(double)TAILLE_IMAGE;
								x2=(double)i/(double)TAILLE_IMAGE;
								//if(x1==0.29 || x1==0.58 || x2==0.45)cout << x1 << "\t" << x2 << endl;
								alpha1=(double)0;
								alpha2=(double)0;

								for(int k=0; k<L; k++)
								{
									for(int l=0; l<L; l++)
									{								
								
//CALC OF ALPHA_1 et ALPHA_2 && calc inst of membership_function
										if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==0)
										{
														//cout << "point rouge" << endl;
                      alpha1=max(get_value_membership_function(x1, (double)l+1, L)*get_value_membership_function(x2, (double)k+1, L)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha1);
										}

                    if(mat_of_all_Gij_CFij[(int)L-2][k][l][0]==1)
										{	
														//cout << "point vert" << endl;
                    	alpha2=max(get_value_membership_function(x1, (double)l+1, L)*get_value_membership_function(x2, (double)k+1, L)*mat_of_all_Gij_CFij[(int)L-2][k][l][1], alpha2);
										}
										
									}
								}
								

								if(alpha1 > alpha2) current_color_bis=0;
								if(alpha2 > alpha1) current_color_bis=1;
								else if(alpha1==alpha2) 
								{
									img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
									//current_color=2;
								}
			
								if(current_color_bis!=previous_color_bis)
								{
									img.draw_point ( j, TAILLE_IMAGE-i, 0, white, 1 );
									previous_color_bis=current_color_bis;
								}  							
							}
						}
		
				switch(L)
				{					
						case 2:
							img.display("L = 2");
							img.save_png("L=2.png", 0);
							img.save_other("L=2.svg", 100);
							break;
						case 3:
							img.display("L = 3");
							img.save_png("L=3.png", 0);
							img.save_other("L=3.svg", 100);
							break;
						case 4:
							img.display("L = 4");
							img.save_png("L=4.png", 0);
							img.save_other("L=4.svg", 100);
							break;
						case 5:
							img.display("L = 5");
							img.save_png("L=5.png", 0);
							img.save_other("L=5.svg", 100);
							break;
						case 6:
							img.display("L = 6");
							img.save_png("L=6.png", 0);
							img.save_other("L=6.svg", 100);
							break;
						case 7:
							img.display("L = 7");
							img.save_png("L=7.png", 0);
							img.save_other("L=7.svg", 100);
							break;
				}
				}
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    return 0;
}

