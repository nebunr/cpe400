#include <iostream>
#include "graph.h"

int test();

int main()
{
	// Seed randomness
	srand(time(NULL));

	// Declarations and initializers
	int sum = 0;
	int num_tests = 1;

	// Run simulation as num_test amount of tests
	for(int i = 0; i < num_tests; i++){
		sum += test();
	}

	// Print out the average amount of packets sent
	std::cout << "Average Packets Sent: "<< (float)sum/(float)num_tests << std::endl;
}

// Runs the simulation 1 time
int test(){
	// Declaration and initializes
	int number_nodes = 20;
	Graph g(number_nodes);

	// Make random network each time
	for(int i = 0; i < number_nodes; i++)
	{
		int numLink = rand() % (number_nodes - 1) + 1;
		int newLink;

		for(int j = 0; j < numLink; j++)
		{
			int cost = rand() % number_nodes + 1;
			newLink = rand() % (number_nodes-1);

			// Make sure that the new link makes a path
			// Also make sure that there doesn't already exist a path
			while(newLink == i && (g.GetCost(i, newLink) != -1))
			{
				newLink = rand() % (number_nodes-1);
			}

			// Add random path to the graph
			// Make sure its symmetrical as the graph is undirected
			g.AddPath(i, newLink, cost);
			g.AddPath(newLink, i, cost);
		}
	}

	// Print out the graph
	std::cout << g;
	// Run simulation for as long as the network is alive
	while(g.run()){ }
	// Return how many packets were sent while network was alive
	return g.GetPacketsSent();
}
