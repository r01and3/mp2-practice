#include "dijkstraAlgorithm.h"

void DijkstraAlgorithm::dijkstraAlgorithm(const Graph& _graph, int*& _dist, int*& _path, int _vertexNumber) {

	if (!_graph.IsConnected()) throw exception("Incoherent graph");

	_dist = new int[_graph.getVertexCount()];
	_path = new int[_graph.getVertexCount()];

	for (int i = 0; i < _graph.getVertexCount(); i++) {
		if (i == _vertexNumber) {
			_path[i] = 0;
			_dist[i] = 0;
		}
		else {
			_path[i] = -1;
			_dist[i] = INT_MAX;
		}
	}

	dHeap<Pair> queue(_graph.getVertexCount(), 2);
	Pair p;
	p.dist = 0;
	p.vertex = _vertexNumber;
	queue.addElem(p);

	while (!queue.IsEmpty()) {
		for (int i = 0; i < _graph.getEdgeCount(); i++) {
			int s = _graph[i].start;
			int e = _graph[i].end;
			if (queue.getRoot().vertex == s && _dist[e] > queue.getRoot().dist + _graph[i].weight) {
				_dist[e] = queue.getRoot().dist + _graph[i].weight;
				_path[e] = queue.getRoot().vertex;
				Pair p;
				p.dist = _dist[e];
				p.vertex = e;
				queue.addElem(p);
			}
			else if (queue.getRoot().vertex == e && _dist[s] > queue.getRoot().dist + _graph[i].weight) {
				_dist[s] = queue.getRoot().dist + _graph[i].weight;
				_path[s] = queue.getRoot().vertex;
				Pair p;
				p.dist = _dist[s];
				p.vertex = s;
				queue.addElem(p);
			}
		}
		queue.popMinElems();
	}

}