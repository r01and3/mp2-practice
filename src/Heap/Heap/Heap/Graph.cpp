#include "Graph.h"

Edge::Edge(const Edge& _edge) {
	Vertex1 = _edge.Vertex1;
	Vertex2 = _edge.Vertex2;
	weight = _edge.weight;
}

bool Edge::operator<(const Edge& _edge) const {
	return weight < _edge.weight;
}

bool Edge::operator>(const Edge& _edge) const {
	return weight > _edge.weight;
}

bool Edge::operator==(const Edge& _edge) const {
	if (Vertex1 == _edge.Vertex1 && Vertex2 == _edge.Vertex2) return true;
	if (Vertex1 == _edge.Vertex2 && Vertex2 == _edge.Vertex1) return true;
	return false;
}

Edge& Edge::operator=(const Edge& _edge) {
	if (*this == _edge) return *this;
	Vertex1 = _edge.Vertex1;
	Vertex2 = _edge.Vertex2;
	weight = _edge.weight;
	return *this;
}

Graph::Graph(int _vertexCount) {
	vertexCount = _vertexCount;
	edgeCount = 0;
	edges = new Edge[(vertexCount * (vertexCount - 1)) / 2];
}

Graph::Graph(int _vertexCount, int _edgeCount, Edge* _edges) {
	vertexCount = _vertexCount;
	edgeCount = _edgeCount;
	edges = new Edge[(vertexCount * (vertexCount - 1)) / 2];
	for (int i = 0; i < edgeCount; i++)
		edges[i] = _edges[i];
}

Graph::Graph(const Graph& _graph) {
	vertexCount = _graph.vertexCount;
	edgeCount = _graph.edgeCount;
	edges = new Edge[(vertexCount * (vertexCount - 1)) / 2];
	for (int i = 0; i < edgeCount; i++)
		edges[i] = _graph.edges[i];
}

Graph::~Graph() {
	delete[] edges;
}

void Graph::addNewVertex() {
	Edge* tmp = new Edge[(vertexCount * (vertexCount - 1)) / 2];
	for (int i = 0; i < edgeCount; i++)
		tmp[i] = edges[i];
	vertexCount++;
	delete[] edges;
	edges = new Edge[(vertexCount * (vertexCount - 1)) / 2];
	for (int i = 0; i < edgeCount; i++)
		edges[i] = tmp[i];
}

void Graph::deleteVertex(int _vertex) {
	if (_vertex >= vertexCount) throw "No vertex with this number found";
	vertexCount
}