#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

void speedup(long t_par, long t_seq);
void scalability(long t_par1, long t_parn);
void efficiency(int n, long t_par, long t_seq);


void speedup(long t_par, long t_seq) {

	float su = ((float)t_seq)/((float)t_par);
	cout<<"Speedup = " <<su<<"\n";
}


void scalability(long t_par1, long t_parn) {

	float scal = ((float)t_par1)/((float)t_parn);
	cout<<"Scalability = "<< scal<<"\n";
}


void efficiency(int n, long t_par, long t_seq) {

	float eff = ((float)t_seq)/((float)n * (float)t_par);
	cout<<"Efficiency = "<<eff<<"\n";
}