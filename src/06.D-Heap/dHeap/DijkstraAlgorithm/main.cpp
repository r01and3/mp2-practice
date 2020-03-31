#include "DijkstraAlgorithm.h"

void main() {
	try {
		Graph graph(1);
		int* dist;
		int* path;

		cin >> graph;

		DijkstraAlgorithm::dijkstraAlgorithm(graph, dist, path, 1);
		for (int i = 0; i < graph.getVertexCount(); i++)
			cout << "Vertex: " << i << " Distance: " << dist[i] << endl;
	}
	catch (const exception & e) {
		cout << e.what() << endl;
	}
}