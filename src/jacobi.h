#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <thread>
#include <barrier>
#include <ff/parallel_for.hpp>
#include "utimer.cpp"
#include "libr.h"
using namespace std;


const float tol = 1e-12;

long jacobi_seq(int n, int num_it, vector<vector<float>> A, vector<float> b, vector<float> yk);
long jacobi_par(int n, int num_it, int nthread, vector<vector<float>> A, vector<float> b, vector<float> xk);
long jacobi_ff(int n, int num_it, int nthread, vector<vector<float>> A, vector<float> b, vector<float> xk);


long jacobi_seq(int n, int num_it, vector<vector<float>> A, vector<float> b, vector<float> yk) {

	vector<float> ykp1(n,0);
	float delta = 0.0;	//delta_k+1
	float delta2 = 0.0;	//delta_k
	float sum = 0.0;	//support variable
	int cont = 0;		//counter
	
	long seq_time;

	{
		utimer seq("Elapsed sequential time", &seq_time);

		for (int k=0; k<num_it; k++) {
			for (int i=0; i<n; i++) {
				for (int j=0; j<n; j++)
					sum-=A[i][j]*yk[j];
				sum+=A[i][i]*yk[i];		//imposing the condition j!=i

				ykp1[i] = (sum + b[i])/A[i][i];
				delta += std::abs(ykp1[i] - yk[i]);
				sum = 0;
			}
			yk = ykp1;

			delta = delta/(float)n;

			if (delta - delta2 > 0)	//checking if delta increased
				cont++;

			delta2 = delta;

			if (delta < tol) {
				cout<<"Tolerance reached at iteration "<<k+1<<" with delta = "<<delta<<"\n";
				k = num_it;
			}
			else if (cont > 6) {
				cout<<"Delta = "<<delta<<" is not improving anymore. Stopped at iteration "<<k+1<<"\n";
				k = num_it;
			}
			else	//if the execution does not stop delta must be 0
				delta = 0.0;
		}
	}

	cout<<"\n";

	return seq_time;
}


long jacobi_par(int n, int num_it, int nthread, vector<vector<float>> A, vector<float> b, vector<float> xk) {

	vector<float> xkp1(n,0);

	vector<float> part_delta(nthread,0); //delta of each thread
	float delta = 0.0;	//delta_k+1
	float delta2 = 0.0; //delta_k		
	int cont = 0;		//counter
	long par_time;

	thread * t[nthread];

	int k;
	int niter = num_it;

	vector<int> fact = factoriz(n, nthread); //creating a vector whose elements are the chunks (optimal partition)

	barrier Barr(nthread, [&](){
		niter--; 

		xk = xkp1; 
		
		for (int s = 0; s < nthread; s++) {	//computing delta_k+1 and resetting partial deltas
			delta += part_delta[s];
			part_delta[s] = 0;
		}
		
		delta /= (float)n;

		if (delta - delta2 > 0)	//checking if delta increased
				cont++;

		delta2 = delta;

		if (delta < tol) {
				cout<<"Tolerance reached at iteration "<<num_it-niter<<" with delta = "<<delta<<"\n";
				niter = 0;
		}
		else if (cont > 6) {
				cout<<"Delta = "<<delta<<" is not improving anymore. Stopped at iteration "<<num_it-niter<<"\n";
				niter = 0;
		}
		else
			delta = 0.0;

		return;
	});

	auto task = [&](int i, int n, vector<int> fact) {

		float temp = 0.0;

		while (niter>0) {
			k = fact[i];	//the 1st component that i-th thread have to compute
			for (k; k < fact[i+1]; k++) {
				for (int j=0; j<n; j++)
					temp-=A[k][j]*xk[j];
				temp+=A[k][k]*xk[k]; //imposing the condition j!=i

				xkp1[k] = (temp + b[k])/A[k][k];
				part_delta[i] += std::abs(xkp1[k]-xk[k]); 

				temp = 0;
				
			}

			Barr.arrive_and_wait();
		}			
	}; 


	{
		utimer par("Elapsed parallel time", &par_time);

		for(int i=0; i<nthread; i++)
			t[i] = new thread(task, i, n, fact);
		
				
		for(int i=0; i<nthread; i++)
				t[i]->join();
  	}

  	cout<<"\n";

  	return par_time;
 }



 long jacobi_ff(int n, int num_it, int nthread, vector<vector<float>> A, vector<float> b, vector<float> xk) {

	vector<float> xkp1(n,0);
	float delta = 0.0;	//delta_k+1
	float delta2 = 0.0;	//delta_k
	int cont = 0;	//counter

	ff::ParallelFor pf(nthread);
	
	long par_time;

	{
		utimer ff("Elapsed FastFlow time", &par_time);

		for (int i=0; i<num_it; i++) {

			pf.parallel_for(0, n, 1, 0, [&](int i) {
				
				float temp = 0;

				for (int j=0; j<n; j++)
					temp-=A[i][j]*xk[j];
				temp+=A[i][i]*xk[i];	//imposing the condition j!=i
				
				xkp1[i] = (temp + b[i])/A[i][i];

				temp = 0.0;
			},	
			nthread);

			for (int s=0; s<n; s++) {	//computing delta_k+1
				delta += std::abs(xkp1[s]-xk[s]);
			}

			xk = xkp1;

			delta /= (float)n;

			if (delta - delta2 > 0) ////checking if delta increased
				cont++;

			delta2 = delta;

			if (delta < tol) {
				cout<<"Tolerance reached at iteration "<<i+1<<" with delta = "<<delta<<"\n";
				i = num_it;
			}
			else if (cont > 6) {
				cout<<"Delta = "<<delta<<" is not improving anymore. Stopped at iteration "<<i+1<<"\n";
				i = num_it;
			}
			else
				delta = 0.0;
		}	
	}

	cout<<"\n";

	return par_time;
 }
