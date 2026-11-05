/*
 * Jan 2024
 *
 * Field regions calculator for near, far, reactive etc.
 */

#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "fieldregions.h"

#define PI 3.14159

#define RD 10.0
#define RL 10.0

int main(int argc, char **argv)
{
    int opt;
    int verbose = 0, short_ant = 0;

    double frequency, ant;
    double d_f, d_rnf;
    double r_d, r_l;

    if(argc < 2)
    {
        usage();
        return 1;
    }

    while((opt = getopt(argc, argv, "f:D:sv")) != -1)
    {
        switch(opt)
        {
            case 'f':
                sscanf(optarg, "%lf", &frequency);
                break;
            case 'D':
                sscanf(optarg, "%lf", &ant);
                break;
            case 's':
                short_ant = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                usage();
                return 1;
        }
    }

    /* Short antenna? */
    if(ant < ftol(frequency) / 2) short_ant = 1;

    /* Calculations */
    d_f = fraunhofer(ftol(frequency), ant);
    d_rnf = 0.62 * sqrt(pow(ant, 3) / ftol(frequency));

    r_d = d_f / ant;
    r_l = d_f / ftol(frequency);

    /* Output */
    if(verbose)
    {
        puts("Long antenna:");
        printf("Near field region d_f < %.1f m (%e m)\n",
            d_f, d_f);

        puts("Ratio of Fraunhofer distance to antenna dimension:");
        printf("d_f / D = %f\n", r_d);

        puts("Ratio of Fraunhofer distance to wavelength:");
        printf("d_f / lambda = %f\n", r_l);

        printf("Reactive near field d_rnf < %.1f m (%e m)\n---\n",
            d_rnf, d_rnf);
    }
    
    if(short_ant)
    {
        puts("Short antenna:");
        d_rnf = ftol(frequency) / (2 * PI);
        d_f = 2 * ftol(frequency);
        printf("%.3f m < Rad. nf. < %.3f m < Transition < %.3f m < ff.\n",
            d_rnf, ftol(frequency), d_f);

        return 0;
    }

    puts("Long antenna:");
    printf("%.3f m < Radiative near field < %.3f m\n", d_rnf, d_f);

    if(r_d < RD || r_l < RL)
    {
        printf("Conditions for d_f not satisfied:\n"
            "r_d = %f < %f\n"
            "r_l = %f < %f\n",
            r_d, RD, r_l, RL);
    }

    return 0;
}

double fraunhofer(double lambda, double D)
{
    return 2.0 * D * D / lambda;
}

double ftol(double f)
{
    return 299792458.0 / f;
}

void usage()
{
    puts("Calculate near-, far-field distances for antennae.\n"
       "Long, short antennae automatically detected.\n"
       "Usage:\n"
       "fieldregions -f [frequency (Hz)] -D [antenna (m)]\n---\n"
       "Example:\n"
       "fieldregions -f 6e10 -D 0.5\n"
       "(calculate near, far field for 60 GHz with\n" 
       "antenna diameter 0.5 m)\n---\n"
       "-s force short antenna\n"
       "-v verbose (long antenna despite short being detected)"
    );
}

