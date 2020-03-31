#include "Graph.h"

Graph::Graph(int _vertexCount) {

	if (_vertexCount <= 0) throw "Incorrect number of vertices";

	vertexCount = _vertexCount;
	edgeCount = 0;
	edge = new Edge[vertexCount * (vertexCount - 1) / 2];

}

Graph::Graph(int _vertexCount, int _edgeCount, Edge* _edge) {

	if (_vertexCount <= 0 || _edgeCount < 0) throw "Incorrect number of vertices or edges";

	vertexCount = _vertexCount;

	edgeCount = _edgeCount;
	edge = new Edge[vertexCount * (vertexCount - 1) / 2];
	for (int i = 0; i < edgeCount; i++)
		edge[i] = _edge[i];

}

Graph::Graph(const Graph& _copy) {

	vertexCount = _copy.vertexCount;

	edgeCount = _copy.edgeCount;
	edge = new Edge[vertexCount * (vertexCount - 1) / 2];
	for (int i = 0; i < edgeCount; i++)
		edge[i] = _copy.edge[i];

}

Graph::~Graph() {

	delete[] edge;

}

bool Graph::IsConnected() const {

	int* am;
	adjacencyMatrix(am);

	for (int i = 0; i < vertexCount; i++) {
		int j = 0;
		for (j; j < vertexCount; j++)
			if (am[i * vertexCount + j] != 0) j = vertexCount + 1;
		if (j == vertexCount) return false;
	}

	return true;

}

void Graph::adjacencyMatrix(int*& _am) const {

	_am = new int[vertexCount * vertexCount]();

	for (int i = 0; i < edgeCount; i++) {
		int s = edge[i].start;
		int e = edge[i].end;
		_am[s * vertexCount + e] = edge[i].weight;
		_am[e * vertexCount + s] = edge[i].weight;
	}

}

void Graph::addNewEdge(const Edge& _edge) {

	if (_edge.start >= vertexCount || _edge.end >= vertexCount) return;

	for (int i = 0; i < edgeCount; i++)
		if (_edge == edge[i]) return;

	edge[edgeCount] = _edge;
	edgeCount++;

}

int Graph::getVertexCount() const {
	return vertexCount;
}

int Graph::getEdgeCount() const {
	return edgeCount;
}

Edge Graph::operator[](int i) const {

	if (i < edgeCount) return edge[i];
	else throw "Out of range";

}

Graph& Graph::operator=(const Graph& _graph) {
	if (*this == _graph) return *this;
	if (edge != nullptr) delete[] edge;
	vertexCount = _graph.vertexCount;
	edgeCount = _graph.edgeCount;
	edge = new Edge[vertexCount * (vertexCount - 1) / 2];
	for (int i = 0; i < edgeCount; i++)
		edge[i] = _graph.edge[i];
	return *this;
}

bool Graph::operator==(const Graph& _graph) const {
	if (vertexCount != _graph.vertexCount || edgeCount != _graph.edgeCount) return false;
	for (int i = 0; i < edgeCount; i++)
		if (edge[i] != _graph.edge[i]) return false;
	return true;
}

ostream& operator<<(ostream& out, const Graph& graph) {
	for (int i = 0; i < graph.edgeCount; i++) {
		out << "Edge number: " << i << endl;
		out << graph.edge[i] << endl;
	}

	return out;
}

istream& operator>>(istream& in, Graph& graph) {

	int _vertexCount, _edgeCount;
	cout << "Enter Vertex Count and Edges Count" << endl;

	in >> _vertexCount >> _edgeCount;

	graph = Graph(_vertexCount);

	for (int i = 0; i < _edgeCount; i++) {
		Edge edge;
		in >> edge;
		graph.addNewEdge(edge);
	}

	return in;
}

Edge::Edge(int _start, int _end, int _weight) {

	if (_start < 0 || _end < 0 || _weight <= 0) throw "Invalid data";

	start = _start;
	end = _end;
	weight = _weight;

}

bool Edge::operator<(const Edge& _edge) const {
	return weight < _edge.weight;
}

bool Edge::operator>(const Edge& _edge) const {
	return weight > _edge.weight;
}

bool Edge::operator==(const Edge& _edge) const {
	return (start == _edge.start) && (end == _edge.end) && (weight == _edge.weight);
}

bool Edge::operator!=(const Edge& _edge) const {
	return (start != _edge.start) || (end != _edge.end) || (weight != _edge.weight);
}

Edge& Edge::operator=(const Edge& _edge) {

	if (*this == _edge) return *this;

	start = _edge.start;
	end = _edge.end;
	weight = _edge.weight;

}

ostream& operator<<(ostream& out, const Edge& edge) {
	out << "Start: " << edge.start << endl;
	out << "End: " << edge.end << endl;
	out << "Weight: " << edge.weight << endl;
	return out;
}

istream& operator>>(istream& in, Edge& edge) {
	cout << "Enter start vertex: ";
	in >> edge.start;
	cout << "Enter end vertex: ";
	in >> edge.end;
	cout << "Enter weight: ";
	in >> edge.weight;
	return in;
}