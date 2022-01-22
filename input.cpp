#include "network.h"
#include <iostream>
#include <cmath>

double norm(double *inp,int n);

int main(int argc,char* argv[])
{
	int en;
	int m = 1;
	if (argc==1) { en=10; } else { en=atoi(argv[1]); }
	
	int iterations=0;
	int converged;
	Network network;
	network.generate_scalefree(en,3,2);
	//network.genstate_normal(0,1);

	for (int i=0;i<en;i++) { network.state[i] = 1; }	
	
	double oldstate[en];
	double desired[en];
	double input[en];

	double energy = 0.0;
	
	std::cout << "The current state vector is:\n";
	network.print_state();

	std::cout << "\nNetwork adjacency is:\n";
	network.print_adjacency();

	do {

		converged = 1;
		for (int i=0;i<en;i++) { oldstate[i] = network.state[i]; } 

		for (int i=0;i<m;i++) { input[i] = 0.0-network.state[i]; }
		for (int i=m;i<en;i++) { input[i]=0.0; }

		energy+=norm(&input[0],m);

		network.iterate_input(&input[0]);
		for (int i=0;i<en;i++)
		{
			if (network.state[i]-oldstate[i] != 0.0) { converged = 0; }
		}
		iterations+=1;

		if (iterations%1000==0) { std::cout << "\nIteration: " << iterations << " control energy: " << energy << "\n"; }

	} while (iterations<100000000&&converged==0);

	std::cout << "\nAfter " << iterations << " iterations, state is:\n";
	network.print_state();
	std::cout << "\nControl energy: " << energy << "\n"; 

	return 0;
}

double norm(double *inp, int n)
{
	double sum = 0;
	for (int i=0;i<n;i++) { sum+=*(inp+i)* *(inp+i); }
	double nor = sqrt(sum);
	return nor;
}


