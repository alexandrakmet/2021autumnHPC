#include "mpi.h"
#include <cmath>
#include <iostream>
#include <windows.h>
using namespace std;

int ProcNum = 0; 
int ProcRank = 0; 


double Fact(int n)
{
	if (n == 0)
		return 1;
	else
		return n * Fact(n - 1);
}

void main(int argc, char *argv[])
{
	SetConsoleOutputCP(1251);
	int n, x;
	int i;
	long double drob, drobSum = 0, Result, sum;
	double startwtime = 0.0;
	double endwtime;
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	if (ProcRank == 0)
	{
		cout << "Enter n: ";
		cin >> n;
		cout << "Enter x: ";
		cin >> x;
	
		startwtime = MPI_Wtime();
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int powX = 0;
	for (i = ProcRank; i <= n; i += ProcNum)
	{
		if(i % 2 == 1)
			drob = -1 * pow(x, i) / Fact(i);
		else
			drob = pow(x, i) / Fact(i);
		drobSum += drob;
	}


	MPI_Reduce(&drobSum, &Result, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	cout.precision(20);
	if (ProcRank == 0)
	{
		cout <<"Result: " << Result << endl << endl;
		endwtime = MPI_Wtime();
		cout << "Time: " << (endwtime - startwtime) * 1000 << endl;
	}

	MPI_Finalize();
}