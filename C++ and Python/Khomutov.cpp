#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <vector>

#include <sys/stat.h> // для создания папки
#include <sys/types.h> // для создания папки

const int screensize[2] = {600,600}; // so we will have array 600*600
const double scale = 250.;
const double center[2] = {-0.7,0};
const int iterations = 767; // 767 to large
const double colour[3] = {0.2,0.6,1};

int main(int argc, char* argv[]){
    std::ios_base::sync_with_stdio(false);
    mkdir("result");
    // std::vector <std::vector<double>> pic;
    for (int y = 0; y < screensize[1]; y++) 
    {
        std::vector <double> row;
        for (int x = 0; x < screensize[0];x++)
        {
            double constant[2] = {(x-screensize[0]/2)/scale+center[0],
            (y-screensize[1]/2)/scale-center[1]}; 

            double pos_[2] = {0.,0.} ;
            double pos_new[2] = {0.,0.};
            double intensity = 0.;

            for (int n = 0; n < iterations; n++ )
            {
                if (pos_[0]*pos_[0]+pos_[1]*pos_[1] > 4) 
                {
                    intensity = 1000./n;
                    break;
                }

                pos_new[0] = pos_[0]*pos_[0] - pos_[1]*pos_[1] + constant[0];
                pos_new[1] = 2*pos_[0]*pos_[1] + constant[1];

                pos_[0] = pos_new[0];
                pos_[1] = pos_new[1];
            }

            if (intensity > 255){
                intensity = 255;
            }
            row.push_back(intensity);
        }

        std::string path = "result/" + std::to_string(y) + ".txt";
		std::ofstream out(path, std::ios_base::trunc);

        for (auto i = row.begin(); i != row.end(); ++i)
        {
            out << *i << ' ';
        }

        out.close();
        // pic.push_back(row);
    }
     // Запускаем построение картинки на Python
    std::string command = "python Mandelbrot.py";
    std::system(command.c_str());
    return 0;
}