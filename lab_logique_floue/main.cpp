#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

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


int main()
{
    //cout << "Hello world!" << endl;
    //int i(0);



    //RECUPERATION DATAS
    int nbre_pts(0), nbre_coordinates(0)/*nbre_coordinates?*//*tmp2*/, value_possible(0)/*value_possible?*//*tmp1*/;


    ifstream fichier("/home/julien/Desktop/test.txt");
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

        for(int L=2; L<3; L++)
        {
            int a(0), b(0);
            double mat_of_membership_function_value_per_coordinates[nbre_pts][nbre_coordinates][L], x(0);

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
                        mat_of_membership_function_value_per_coordinates[i][j][k]=max(1-(std::fabs(x-a)/b),(double)0);
                        //cout << 1-(std::fabs(x-a)/b) << endl;
                        //cout << max(1-(std::fabs(x-a)/b),(double)0) << endl;

                        //SEEMS OK
                        //cout << i<<"\t"<<j<<"\t"<<k<<"\t"<< mat_of_membership_function_value_per_coordinates[i][j][k] << endl; //DISPLAY number of the point + nbre of coordinate used + nbre of membership displayed + VALUE of membership
                    }
                }
            }

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


            double mat_of_areas[L][L][3]; //for each area define X, Y, GROUP

            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
                    mat_of_areas[i][j][0]=1/(double)L+j*1/(double)L;
                    mat_of_areas[i][j][1]=1/(double)L+i*1/(double)L;
                    mat_of_areas[i][j][2]=2;
                    //SEEMS OK
                    //cout << i << "\t" << j <<"\t"<< mat_of_areas[i][j][0]<<"\t"<<mat_of_areas[i][j][1] << endl; //DISPLAY THE DIFFERENT AREAS LIKE MAT With their x(abs) ending and y(ord) ending
                }
            }




            //vector<Point> vector_of_points_in_area(0); //creation of table empty which will contain the points Points that are in the define(chosen) area
            vector<int> vector_of_ranks_points_in_area(0);
            double mat_of_adaptability_of_each_area[L][L][2], mat_of_Gij_CFij_of_each_area[L][L][2]; //---> absolument les mettre a 0 !!! for the moment not the case so TODO LIST ==>> DONE
            double Gij(0), CFij(0)/*, Sum_of_membership_function_G1(0)*/;

            //INITIALISATION A 0 OF BOTH MAT
            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
                    mat_of_adaptability_of_each_area[L][L][0]=0;
                    mat_of_adaptability_of_each_area[L][L][1]=0;
                    mat_of_Gij_CFij_of_each_area[L][L][0]=2; //we put Gij in none group
                    mat_of_Gij_CFij_of_each_area[L][L][1]=0;
                }
            }

            for(int i=0; i<L; i++)
            {
                for(int j=0; j<L; j++)
                {
                    /*vector<Point> vector_of_points_in_area(0); //creation of table empty which will contain the points Points that are in the define(chosen) area
                    vector<int> vector_of_ranks_points_in_area(0);*/

                    //parcourt of table containing all points, checking if they are or not in the area
                    for(int k=0; k<nbre_pts; k++)
                    {
                        if(tab[k][0]<=mat_of_areas[i][j][0] && tab[k][0]<=mat_of_areas[i][j][1])
                        {
                            /*//we only need the rank of the points
                            vector_of_ranks_points_in_area.push_back(k);

                            //just a test && not using it for the moment
                            Point my_point;
                            my_point.X=tab[k][0];
                            my_point.Y=tab[k][1];
                            my_point.value=tab[k][2];*/
                            vector_of_points_in_area.push_back(my_point);
                        }

                    }


                    //on parcourt le vector in order to calculate CF ij && G ij of the area
                    for(int l=0; l<vector_of_ranks_points_in_area.size(); l++)
                    {
                        if(tab_value_by_pt[vector_of_ranks_points_in_area[l]]==0)
                            mat_of_adaptability_of_each_area[i][j][0]+=mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][0][i]*mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][1][j];
                        if(tab_value_by_pt[vector_of_ranks_points_in_area[l]]==1)
                            mat_of_adaptability_of_each_area[i][j][1]+=mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][0][i]*mat_of_membership_function_value_per_coordinates[vector_of_ranks_points_in_area[l]][1][j];
                        //mat_of_membership_function_value_per_coordinates[i][j][k]
                    }

                    if(mat_of_adaptability_of_each_area[i][j][0]>mat_of_adaptability_of_each_area[i][j][1])
                        mat_of_Gij_CFij_of_each_area[i][j][0]=0;
                    else if(mat_of_adaptability_of_each_area[i][j][1]>mat_of_adaptability_of_each_area[i][j][0])
                        mat_of_Gij_CFij_of_each_area[i][j][0]=1;
                    else mat_of_Gij_CFij_of_each_area[i][j][0]=2;

                    if(mat_of_adaptability_of_each_area[i][j][0]+mat_of_adaptability_of_each_area[i][j][1]>0)
                        mat_of_Gij_CFij_of_each_area[i][j][1]=(std::fabs(mat_of_adaptability_of_each_area[i][j][0]-mat_of_adaptability_of_each_area[i][j][1]))/(mat_of_adaptability_of_each_area[i][j][0]+mat_of_adaptability_of_each_area[i][j][1]);
                    else if(mat_of_adaptability_of_each_area[i][j][0]+mat_of_adaptability_of_each_area[i][j][1]==0)
                        mat_of_Gij_CFij_of_each_area[i][j][1]=0;

                    vector_of_ranks_points_in_area.empty();
                }
            }



            //end of L locked calc
        }


        /*CALC OF ADAPTIBILITY*/


    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }


    return 0;
}
