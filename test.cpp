#include "digraph/directed_graph.h"
#include <iostream>
#include <cmath>
#include <random>


int main() {
	
	DirectedGraph* digraph = initialize_digraph(sizeof(float[2]),(char*)"float[2]");

	float a [2] = {1.3, 23.354};
	float b [2] = {547.23235, 6.345};
	float c [2] = {76.345, 67.56};

	add_vertex(digraph,&a);
	add_vertex(digraph,&b);
	add_vertex(digraph,&c);

	add_arc(digraph,a,b,1);
	add_arc(digraph,b,c,1);
	add_arc(digraph,c,a,1);

	create_adjacency_matrix(digraph);

	float** adj = get_adjacency_matrix(digraph);

	for (int i=0; i<3; i++) 
	{
		for (int j=0; j<3; j++)
		{
			if (adj[i][j] != FLT_MAX) {
				std::cout << floor(adj[i][j]);
			} else {
				std::cout << 0;
			}
			if (j%3 == 2)
			{
				std::cout << "\n";
			} else {
				std::cout << " ";
			}
		}
	}

	std::cout << "graph size: " << (get_vertices(digraph)->size) << std::endl;

	std::cout << *digraph << std::endl << std::endl;



	DirectedGraph* digraphs[5];
	
	for (int i=0; i<5; i++)
       	{
		digraphs[i] = initialize_digraph(sizeof(float[2]),(char*)"float[2]");
		add_vertex(digraphs[i],&a);
		add_vertex(digraphs[i],&b);
		add_vertex(digraphs[i],&c);
		if (i<3)
		{
			add_arc(digraphs[i],a,b,1);
			add_arc(digraphs[i],b,c,1);
			add_arc(digraphs[i],c,a,1);

		} else {
			add_arc(digraphs[i],a,c,1);
			add_arc(digraphs[i],c,b,1);
			add_arc(digraphs[i],b,a,1);
		}
	}

	std::cout << *digraphs[1] << std::endl << std::endl;
	std::cout << *digraphs[4] << std::endl;


	return 0;
}
