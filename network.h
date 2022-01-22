#ifndef NETWORK
#define NETWORK

#include <iostream>
#include <random>
#include <cmath>

/*------------------------------------------------------------------------------------------------
This library defines network objects that are capable of simulating linear dynamical processes with arbitrary control sequences. First generate Barabasi-Albert or Erdos-Renyi random networks with one of the generate functions, then iterate the process by a single (or multiple) time interval(s).

Controllers are connected through the coupling buffer, and arbitrary inputs can be sent to any controller using iteration with an input buffer address.

This Code was written by Philip Solimine https://github.com/doctor-phil
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
--------------------------------------------------------------------------------------------------*/

class Network
{
	public:
		Network(void);                
		Network(int a);
		Network(const Network &net); 				//Copy Constructor
		~Network() { delete [] adjacency; delete [] state; }		//Destructor

									//Network Generators:
		void generate_scalefree(int a, int m0, int m);			//Scale-free generator (Barabasi-Albert Model)
		void generate_er(int a, double k);				//Erdos-Renyi generator
									
									//Output:
		void print_adjacency(void);					//Print adjacency matrix to stdout
		void print_state(void);						//Print the state vector to stdout
		void print_adjacency(std::ostream& o);				//Print adjacency matrix to given output stream
		void print_state(std::ostream& o);				//Print the state vector to given output stream
		friend std::ostream& operator<<(std::ostream& os, Network& net);//<< operator

									//Simulate Dynamical Processes:
		void genstate_normal(double mean, double stddev);		//draw states for each node from iid normal dist
		void iterate(void);						//iterate dynamical process once
		void iterate(int k);						//iterate k times
		void iterate_input(double *inp);				//iterate once with a given m-array of controller inputs
	
									//Operations:
		double average_degree(void);					//return average degree of network
	
		int *adjacency;						//Stores adjacency matrix as nxn integer array
		double *state;						//Store the state vector of all nodes nx1
		double *coupling;					//A coupling matrix between nodes and controllers nxm
		double *input;						//
		int n;							//Number of nodes in the network
		int m;							//Number of external controllers
};

Network::Network(void)							//init 10 node empty network
{
	n=10;
	m=10;
	state = new double[10];
	for (int i=0;i<10;i++) { state[i] = 0; }

	adjacency = new int[100];
	for (int i=0;i<100;i++) { adjacency[i] = 0; }
	
	coupling = new double [m*m];
	input = new double [m];
	
	for (int i=0;i<m;i++) { input[i] = 0; }
	for (int i=0;i<m*m;i++) { coupling[i] = 0; }
	for (int i=0;i<m;i++) { coupling[i*i]=1; }			//coupling is the identity (may cause problems in input.cpp)
}

Network::Network(int a)							//init a node empty network
{
	n = a;
	m = a;
	state = new double[n];
	for (int i=0;i<10;i++) { state[i] = 0; }

	adjacency = new int[n*n];
	for (int i=0;i<a*a;i++) { adjacency[i] = 0; }
	
	coupling = new double [m*m];
	input = new double [m];

	for (int i=0;i<m;i++) { input[i] = 0; }
	for (int i=0;i<m*m;i++) { coupling[i] = 0; }
}

Network::Network(const Network &net)					//copy existing network
{
	n = net.n;
	m = net.m;

	state = new double[10];
	for (int i=0;i<10;i++) { state[i] = net.state[i]; }

	adjacency = new int[n*n];
	for (int i=0;i<n*n;i++) { adjacency[i] = net.adjacency[i]; }	

	coupling = new double [m*m];
	input = new double [m];

	for (int i=0;i<m;i++) { input[i] = 0; }
	for (int i=0;i<m*m;i++) { coupling[i] = 0; }
}

void Network::generate_scalefree(int a,int m0, int m)			//overwrite network with a randomly-drawn scale-free network
{
	n=a;
	delete [] adjacency;
	adjacency = new int [n*n];
	int k[n];
	double r;
	double prob;
	int node;
	double sum = m0 * m0 - m0;
	double newsum = sum;
	int num;

	for (int i=0;i<n;i++) { k[i]=0; }			

	for (int i=0;i<m0;i++)
	{
		k[i] = m0-1;
		for (int j=0;j<m0;j++)
		{
			if (j!=i&&j<m0&&i<m0) { *(adjacency+i*n+j) = 1; } else { *(adjacency+i*n+j)=0; } 
		}
	}

	std::random_device rd;
	std::mt19937 mt(rd());
  	std::uniform_real_distribution<double> distribution(0.0,1.0);

	for (int i=m0; i<n; i++)
	{
		num=0;
		
		do {
			node = (int)floor(distribution(mt)*(i+1));
			r = distribution(mt);
			prob = k[node] / sum;
			if (r<=prob && *(adjacency+i*n+node)!=1) 
			{ 
				*(adjacency+i*n+node)=1;
				*(adjacency+node*n+i)=1; 
				k[node]+=1;
				num+=1;
				newsum+=2;
			}
		} while (num<m);

		k[i] = m;
		sum=newsum;
	}
}

void Network::generate_er(int a, double k)				//overwrite network with a randomly drawn ER network
{
	n = a;
	delete [] adjacency;
	adjacency = new int[n*n];

	std::random_device device;
	std::mt19937 mt(device());
  	std::uniform_real_distribution<double> distribution(0.0,1.0);
	double draw;

	for (int i=0;i<n;i++)
	{
		*(adjacency+i*n+i)=0;

		for (int j=0;j<i;j++)
		{
			draw = distribution(mt);
			if (draw<k) { *(adjacency+j*n+i)=1; *(adjacency+i*n+j)=1; } else { *(adjacency+j*n+i)=0; *(adjacency+i*n+j)=0; }
		}
	}
}

void Network::print_adjacency(void)
{
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			std::cout << (int)*(adjacency+i*n+j);
			if (j<(n-1)) { std::cout << ","; } else { std::cout << "\n"; }
		}
	}
}

void Network::print_adjacency(std::ostream& o) 
{
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			o << (int)*(adjacency+i*n+j);
			if (j<(n-1)) { o << ","; } else { o << "\n"; }
		}
	}
}

std::ostream& operator<<(std::ostream& o, Network& net)
{
	for (int i=0;i<net.n;i++)
	{
		for (int j=0;j<net.n;j++)
		{
			o << (int)net.adjacency[i*net.n+j];
			if (j<(net.n-1)) { o << ","; } else { o << "\n"; }
		}
	}
	return (o);
}

void Network::iterate(void)
{
	double sumelts=0;
	double newstate[n];

	for (int i=0;i<n;i++)
	{
		newstate[i]=0;
		for (int j=0;j<n;j++)
		{
			newstate[i]+=(double)*(adjacency+i*n+j) * *(state+j);
			sumelts+=(double)*(adjacency+i*n+j);
		}
		*(newstate+i) = newstate[i]/sumelts;
		sumelts = 0;
	}
	for (int i=0;i<n;i++) { *(state+i)=newstate[i]; }
}

void Network::iterate(int k)
{
	double sumelts=0;
	double newstate[n];
	for (int it=0;it<k;it++)
	{
		for (int i=0;i<n;i++)
		{
			newstate[i]=0;
			for (int j=0;j<n;j++)
			{
				newstate[i]+=(double)*(adjacency+i*n+j) * *(state+j);
				sumelts+=(double)*(adjacency+i*n+j);
			}
			newstate[i] = newstate[i]/sumelts;
			sumelts = 0;
		}
		for (int i=0;i<n;i++) { *(state+i)=newstate[i]; }
	}
}

void Network::genstate_normal(double mean, double stddev)
{
	std::random_device device;
	std::mt19937 mt(device());
	std::normal_distribution<double> distribution(mean,stddev);

	for (int i=0;i<n;i++)
	{
		*(state+i)=distribution(mt);
	}
}

double Network::average_degree(void)
{
	double k;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<i;j++)
		{
			k+=(double)*(adjacency+i*n+j);
		}
	}
	return k/(double)n;
}

void Network::print_state(void)
{
	for (int i=0;i<n;i++)
	{
		std::cout << (double)*(state+i);
		if (i<(n-1)) { std::cout << ","; } else { std::cout << "\n"; }
	}
}

void Network::print_state(std::ostream& o)
{
	for (int i=0;i<n;i++)
	{
		o << (double)*(state+i);
		if (i<(n-1)) { o << ","; } else { std::cout << "\n"; }
	}
}

void Network::iterate_input(double* inp)
{
	for (int i=0;i<m;i++) { *(input+i)=*(inp+i); }

	double sumelts=0;
	double newstate[n];

	for (int i=0;i<n;i++)
	{
		newstate[i]=0;
		for (int j=0;j<n;j++)
		{
			newstate[i]+=(double)*(adjacency+i*n+j) * *(state+j);
			sumelts+=(double)*(adjacency+i*n+j);
		}
		
		for (int j=0;j<m;j++) { newstate[i]+=*(coupling+m*j+i) * *(input+j); }
		
		newstate[i] = newstate[i]/sumelts;
		sumelts = 0;
	}

	for (int i=0;i<n;i++) { *(state+i)=newstate[i]; }
}

#endif
