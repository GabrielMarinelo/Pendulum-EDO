#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <getopt.h>
using namespace std;

double range = 6;
double h = .01;
double omega = 4;
double lambda = 0;
double F = 0;
double sigma = 5;

double f(double t, double z1, double z2){
    return F*cos(sigma*t)-lambda*z2-pow(omega, 2)*sin(z1);
}

int main(int argc, char **argv){
    
    fstream file;
    double z1 = 1, z2 = 1, t = 0, k1, k2;
    int option_index;
    bool fase = false, keep = false;

    while(( option_index = getopt(argc, argv, "l:f:s:o:r:d:x:v:keh" )) != -1){
        switch (option_index){
            case 'h':
                cout << "--------------------------\n";
                cout << "-l to set lambda, the damping constant \n";
                cout << "-f to set the amplitude of the external force, F*cos(sigma*t)\n";
                cout << "-o to set de natural frequency (omega)\n";
                cout << "-s to set the external frenquency\n";
                cout << "-r to set the graph range (begin in zero)\n";
                cout << "-x to set the initial position\n";
                cout << "-v to set the initial velocity\n";
                cout << "-d to set the step, (deltaT)\n";
                cout << "-k to show the phase space\n";
                cout << "-e to keep the data on the data file\n";
                cout << "--------------------------\n"; 
                break;
            case 'l':
                lambda = stod(optarg);
                break;
            case 'f':
                F = stod(optarg);
                break;
            case 'o':
                omega = stod(optarg);
                break;
            case 's':
                sigma = stod(optarg);
                break;
            case 'r':
                range = stod(optarg);
                break;
            case 'x':
                z1 = stod(optarg);
                break;
            case 'v':
                z2 = stod(optarg);
                break;
            case 'd':
                h = stod(optarg);
                break;
            case 'k':
                fase = true;
                break;
            case 'e':
                keep = true;
                break;
            default :
                return 1;
        }
    }

    file.open("2order.txt");
    for (double i = 0; i <= range; i += h){
        
        if(!fase){
            file << t << " " << z1 << endl;
        }else{
            file << z1 << " " << z2 << endl;
        }

        z1 += z2 * h;
        k1 = h * f(t, z1, z2);
        k2 = h * f(t + h, z1, z2 + k1);
        z2 += (k1 + k2)/2;
        t  += h;
    }
    file.close();

    system("gnuplot --persist -e \"plot '2order.txt'\" ");
    
    if(!keep)
        system("> 2order.txt");
    
    return 0;
}