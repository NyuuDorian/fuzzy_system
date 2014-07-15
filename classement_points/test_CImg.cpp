//g++ -o bbb test_CImg.cpp -lm -lpthread -lX11

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


int main()
{

						CImg<unsigned char> img(TAILLE_IMAGE,TAILLE_IMAGE,1,3);        // Define a 100x100 color image with 8 bits per color component.
  					img.fill(0);                                 // Set pixel values to 0 (color : black)
  					unsigned char purple[] = { 255,0,255 }, red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 }, grey[] = {127,127,127}, white[] = {255,255,255};      // Define a purple color
						double x1(0), x2(0);

						for(int i=0; i<TAILLE_IMAGE; i++)
            {
            	for(int j=0; j<TAILLE_IMAGE; j++)
              {

									x1=(double)j/TAILLE_IMAGE;
									x2=(double)i/TAILLE_IMAGE;
									img.draw_point ( x1*TAILLE_IMAGE, x2*TAILLE_IMAGE, 0, blue, 1 );			
								
							}
						}
				img.display("test");
				//img.draw_point(29,45,0,color_test,1);						
				//img.draw_point(58,45,0,color_test,1);
						
				
	return 0;
}
