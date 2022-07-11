#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
using namespace std;

vector<int> factoriz(int n, int nt);
vector<vector<float>> mat_gen(int n);
vector<float> vect_gen(int n);
void print_mat(vector<vector<float>> A);
void print_vect(vector<float> b);


vector<int> factoriz(int n, int nt) {

	vector<int> fact(nt+1,0);
	int r = n%nt;	//remainder
	int chunk = n/nt;	//floor(n/nt)
	int i = 1;
	fact[0] = 0;

	for(i; i<r+1; i++)	//the first r intervals have length=chunk+1
		fact[i] = fact[i-1] + chunk + 1;

	for (i; i<nt+1; i++) //the other intervals have length=chunk
		fact[i] = fact[i-1] + chunk;

	return fact;
}


vector<vector<float>> mat_gen(int n) {

	vector<vector<float>> A(n, vector<float>(n, 0));
	float sum = 0;

	srand(time(NULL));

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			A[i][j] = (((float)((rand()%20000)))/1000.0) - 10;
			sum+=abs(A[i][j]);
		}
		A[i][i] = 1.1*sum + 1;
		sum = 0;
	}

	return A;
}


vector<float> vect_gen(int n) {

	vector<float> b(n);

	srand(time(NULL));

	for (int i=0; i<n; i++)
		b[i] = (((float)((rand()%20000)))/1000.0) - 10;
		
	return b;
}


void print_mat(vector<vector<float>> A, int n){

	for (int i=0; i<n; i++) {
		cout<<"| ";
		for (int j=0; j<n; j++) {
			cout<<A[i][j]<<" ";
		}
		cout<<"| \n";
	}
}


void print_vect(vector<float> b, int n) {

	for (int i=0; i<n; i++)
		cout<<"|"<<b[i]<<"| \n";
}

