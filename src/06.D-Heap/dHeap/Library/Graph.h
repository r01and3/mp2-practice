#pragma once
#include <iostream>

using namespace std;

struct Edge {
	int start;
	int end;
	int weight;

	Edge() : start(0), end(0), weight(0) {};
	Edge(int, int, int);
	Edge(const Edge& _copy) : start(_copy.start), end(_copy.end), weight(_copy.weight) {};
	~Edge() {};

	bool operator>(const Edge&) const;
	bool operator<(const Edge&) const;
	bool operator==(const Edge&) const;
	bool operator!=(const Edge&) const;

	Edge& operator=(const Edge&);

	friend ostream& operator<<(ostream&, const Edge&);
	friend istream& operator>>(istream&, Edge&);
};

class Graph {
private:
	int vertexCount;
	int edgeCount;
	Edge* edge;
public:
	Graph(int);
	Graph(int, int, Edge*);
	Graph(const Graph&);
	~Graph();

	bool IsConnected() const;
	void adjacencyMatrix(int*&) const;

	void addNewEdge(const Edge&);

	int getVertexCount() const;
	int getEdgeCount() const;

	Edge operator[](int) const;
	Graph& operator=(const Graph&);
	bool operator==(const Graph&) const;

	friend ostream& operator<<(ostream&, const Graph&);
	friend istream& operator>>(istream&, Graph&);
};

