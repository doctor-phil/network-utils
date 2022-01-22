#ifndef SEQUENCE
#define SEQUENCE

#include "digraph/directed_graph.h"
#include <iostream>
#include <sstream>
#include <string>

class Sequence
{
	public:
	Sequence(void);
	//constructor: dimension 
	Sequence(int n, int p, int T);
	~Sequence() { free(digraphs); };
	int n;
	int k;
	int T;

	DirectedGraph* digraphs[];

};

Sequence::Sequence(void)
{
	int n = 10;
	int k = 2;
	int T = 10;
	DirectedGraph* digraphs[T];
	std::stringstream ss;
	ss << "double[" << k << "]";
	std::string ts = ss.str();
	char* type = (char*) ts.c_str();
	for (int i=0;i<T;i++)
	{
		digraphs[i] = initialize_digraph(sizeof(double[k]),type);
	}
}
#endif
