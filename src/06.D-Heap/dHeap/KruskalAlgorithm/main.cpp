#include "KruskalAlgorithm.h"

void main() {
	try {

		Graph graph(1);

		cin >> graph;

		cout << KruskalAlgorithm::kruskalAlgorithm(graph);

	}
	catch (const exception & e) {
		cout << e.what() << endl;
	}
}