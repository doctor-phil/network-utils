# network

This package contains 4 files, not including this README. One is the Makefile which contains the compilation directive for the C program. 

The library header file network.h defines the class Scalefree for a scalefree network. Within this header file is the definition of the Scalefree() constructor which uses the Barabasi-Albert model of preferential attachment to draw a network with a scale-free degree distribution.

The C++ source code file scalefree.cpp contains the main() routine which initiates a scale-free network. The first command line argument given to this program, if it exists, is defined to be the number of nodes in the desired network. If there is no command line input, then this defaults to 10 nodes. The second command line argument, if it exists, defines the m0 starting number of nodes to include in the completely connected component which serves as the initiation of the network, before the rest of the n-m0 nodes are added with preferential attachment. The default value of m0 is 3. The third and final command line input is m, the number of links each new node will make when it is added to the network. The default value of m is 2. If assigned separately, m should be set to a value that is smaller than m0. This file outputs the adjacency matrix to stdout, but also will create a file called adjacency.csv which will store the adjacency matrix. (this file can become very large when n is large.)

The final file is plotgraph.r. This is an R script that uses the libraries igraph and ggplot2, inputs the adjacency.csv file, and outputs pdf and jpg images containing a visual representation of the graph along with its degree distribution on a log-log scale.

Dependencies:
network.h/scalefree.cpp - requires C++ <random> library, <iostream> and <fstream>, and <cmath>

plotgraph.r - requires "igraph" and "ggplot2" libraries for R
