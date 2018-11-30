#include "stdio.h"
#include "stdlib.h"
#include "svpng.inc"
#include "mpi.h"
#include <omp.h>

const int screensize[2] = {1200,1200};
const double scale = 500.;
const double center[2] = {-0.7,0};
const int iterations = 767;

int main(int argc, char* argv[]){

    unsigned char picture[screensize[0]*screensize[1]*3];

    int Ranks;
    int myRank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Ranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); 

    const int number_to_calculate = screensize[1] / Ranks; 
    unsigned char part_picture[screensize[0]*number_to_calculate*3], *pic = part_picture;

    for (int y = 0; y < screensize[1]; y++)
    {

        #pragma omp parallel num_threads(2)
        {
        int tid = omp_get_thread_num();
        unsigned char *pic = part_picture + tid*screensize[0]*3; // надо смещать по x
        #pragma omp for
        for (int x = 0; x < screensize[0];x++)
        {
            double constant[2] = {(x-screensize[0]/2)/scale+center[0],
            (y-screensize[1]/2)/scale-center[1]}; 

            double pos_[2] = {0.,0.} ;
            double pos_new[2] = {0.,0.};
            int n = 0;

            for (n; n < iterations; n++ )
            {
                if (pos_[0]*pos_[0]+pos_[1]*pos_[1] > 4)  break;

                pos_new[0] = pos_[0]*pos_[0] - pos_[1]*pos_[1] + constant[0];
                pos_new[1] = 2*pos_[0]*pos_[1] + constant[1];

                pos_[0] = pos_new[0]; pos_[1] = pos_new[1];
            }

            unsigned char R = 255; unsigned char G = 255; unsigned char B = n - 511; 
            if (n < 512) {G = n - 255; B = 0; };
            if (n < 256) {R = n; G = 0; B = 0; };
            *pic++ = R;
            *pic++ = G;    
            *pic++ = B;            
        }
        }
    }

    MPI_Gather(part_picture,number_to_calculate*screensize[0]*3,MPI_UNSIGNED_CHAR,picture,
    number_to_calculate*screensize[0]*3,MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

    if (myRank == 0)
    {
    FILE *fp = fopen("mandelbort.png", "wb");
    svpng(fp, screensize[0], screensize[1], picture, 0);
    fclose(fp);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}