#include "network.h"
#include <fstream>

int main(int argc,char* argv[]) 
{
	int n,m0,m;
	if (argc==1) { n=10; } else { n=atoi(argv[1]); }
	if (argc>2) { m0=atoi(argv[2]); } else { m0=3; }
	if (argc>3) { m=atoi(argv[3]); } else { m=2; }
	
	std::ofstream filename;
	filename.open("adjacency.csv");
	
	Network network;
	network.generate_scalefree(n,m0,m);
	network.print_adjacency(filename);

	filename.close();
	std::cout << network;
	
	return 0;
}
