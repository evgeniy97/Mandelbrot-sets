#include "stdio.h"
#include "stdlib.h"
#include "svpng.inc"
// http://cimg.eu/
//#include <string>
//#include <fstream>
//#include <iostream>
//#include <cstdio>
//#include <vector>
//#include <sys/stat.h> // для создания папки
//#include <sys/types.h> // для создания папки

const int screensize[2] = {600,600}; // so we will have array 600*600
const double scale = 250.;
const double center[2] = {-0.7,0};
const int iterations = 767;

int main(int argc, char* argv[]){
    //std::ios_base::sync_with_stdio(false);

    // create massiv of unsigned char
    unsigned char picture[screensize[0]*[screensize[1] *3], *pic = picture;

    for (int y = 0; y < screensize[1]; y++) 
    {
        for (int x = 0; x < screensize[0];x++)
        {
            double constant[2] = {(x-screensize[0]/2)/scale+center[0],
            (y-screensize[1]/2)/scale-center[1]}; 

            double pos_[2] = {0.,0.} ;
            double pos_new[2] = {0.,0.};
            int n = 0;

            for (n; n < iterations; n++ )
            {
                if (pos_[0]*pos_[0]+pos_[1]*pos_[1] > 4) 
                {
                    break;
                }

                pos_new[0] = pos_[0]*pos_[0] - pos_[1]*pos_[1] + constant[0];
                pos_new[1] = 2*pos_[0]*pos_[1] + constant[1];

                pos_[0] = pos_new[0];
                pos_[1] = pos_new[1];
            }

            // Вот тут понять
            //row[x] = {255,255,unsigned(n - 511)};
            //if (n < 512) row[x] = {255,unsigned(n - 255),0};
            //if (n < 256) row[x] =  {unsigned(n),0,0};
            *p++ = (unsigned char)x;    /* R */
            *p++ = (unsigned char)y;    /* G */
            *p++ = 128;             

        }
    }
    // Тут должно быть создание картинки
    FILE *fp = fopen("mandelbort.png", "wb");
    svpng(fp, 256, 256, picture, 0);
    fclose(fp);
    return 0;
}