#include <iostream>
#include <stdlib.h>
#include <vector>
#include "libr.h"
#include "jacobi.h"
#include "measures.h"
using namespace std;


int main() {

	int n, num_it, nthread;

	cout<<"\n";

	cout<<"Dimension of the space: ";
	cin>>n;

	if (n < 1) {
		cout<<"\n";
		cout<<"The dimension has to be a positive integer"<<"\n";
		cout<<"\n";
		return 0;
	}

	cout<<"Number of threads: ";
	cin>>nthread;

	if (nthread < 1) {
		cout<<"\n";
		cout<<"The number of threads has to be a positive integer"<<"\n";
		cout<<"\n";
		return 0;
	}

	cout<<"Number of iterations of the Jacobi method: ";
	cin>>num_it;

	if (num_it < 1) {
		cout<<"\n";
		cout<<"The number of iterations has to be a positive integer"<<"\n";
		cout<<"\n";
		return 0;
	}

	cout<<"\n";
	
	cout<<"GENERATING DATA..."<<"\n";

	vector<vector<float>> A = mat_gen(n);
	vector<float> b = vect_gen(n);
	vector<float> x_0 = vect_gen(n);

	cout<<"\n";
	
	cout<<"SEQUENTIAL:"<<"\n";
	long t_seq = jacobi_seq(n, num_it, A, b, x_0);

	cout<<"PARALLEL "<< nthread <<" THREADS:"<<"\n";
	long t_par = jacobi_par(n, num_it, nthread, A, b, x_0);

	cout<<"1 THREAD:"<<"\n";
	long t_par1 = jacobi_par(n, num_it, 1, A, b, x_0);

	cout<<"FASTFLOW "<< nthread <<" THREADS:"<<"\n";
	long t_ff = jacobi_ff(n, num_it, nthread, A, b, x_0);

	cout<<"FASTFLOW 1 THREAD:"<<"\n";
	long t_ff1 = jacobi_ff(n, num_it, 1, A, b, x_0);

	
	cout<<"THREAD MEASURES"<<"\n";
	speedup(t_par, t_seq);
	efficiency(nthread, t_par, t_seq);
	scalability(t_par1, t_par);

	cout<<"\n";

	cout<<"FASTFLOW MEASURES"<<"\n";
	speedup(t_ff, t_seq);
	efficiency(nthread, t_ff, t_seq);
	scalability(t_ff1, t_ff);

	cout<<"\n";
}
