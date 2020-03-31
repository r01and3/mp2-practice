#include "KruskalAlgorithm.h"

Graph KruskalAlgorithm::kruskalAlgorithm(const Graph& _graph) {

	if (!_graph.IsConnected()) throw exception("Incoherent graph");

	Graph result(_graph.getVertexCount());
	dividedSet cc(_graph.getVertexCount());
	Edge* tmp = new Edge[_graph.getEdgeCount()];
	for (int i = 0; i < _graph.getEdgeCount(); i++)
		tmp[i] = _graph[i];
	dHeap<Edge> edge(_graph.getEdgeCount(), _graph.getEdgeCount(), 2, tmp);


	while (!edge.IsEmpty()) {
		if (cc.find(edge.getRoot().start) != cc.find(edge.getRoot().end)) {
			result.addNewEdge(edge.getRoot());
			cc.combine(cc.find(edge.getRoot().start), cc.find(edge.getRoot().end));
		}
		edge.popMinElems();
	}

	return result;

}