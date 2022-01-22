#include "network.h"
#include <iostream>

int main(int argc,char* argv[])
{
	int en;
	if (argc==1) { en=10; } else { en=atoi(argv[1]); }
	
	int iterations=0;
	int converged;
	Network network;
	network.generate_scalefree(en,3,2);
	network.genstate_normal(0,1);
	
	double oldstate[en];
	
	std::cout << "The current state vector is:\n";
	network.print_state();

	std::cout << "\nNetwork adjacency is:\n";
	network.print_adjacency();

	do {
		converged = 1;
		for (int i=0;i<en;i++) { oldstate[i] = network.state[i]; } 

		network.iterate();
		for (int i=0;i<en;i++)
		{
			if (network.state[i]-oldstate[i] > 0.000001) { converged = 0; }
		}
		iterations+=1;

	} while (iterations<=1000000&&converged==0);

	std::cout << "\nAfter " << iterations << " iterations, state is:\n";
	network.print_state();

	return 0;
}
