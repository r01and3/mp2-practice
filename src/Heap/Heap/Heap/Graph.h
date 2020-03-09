#pragma once
#include <iostream>

struct Edge {
	int Vertex1;
	int Vertex2;
	int weight;

	Edge() : Vertex1(0), Vertex2(0), weight(0) {};
	Edge(int _Vertex1, int _Vertex2, int _weight) : Vertex1(_Vertex1), Vertex2(_Vertex2), weight(_weight) {};
	Edge(const Edge&);
	~Edge() {};

	bool operator<(const Edge&) const;
	bool operator>(const Edge&) const;
	bool operator==(const Edge&) const;

	Edge& operator=(const Edge&);
};

class Graph {
private:
	int vertexCount;
	int edgeCount;
	Edge* edges;
public:
	Graph(int);
	Graph(int, int, Edge*);
	Graph(const Graph&);
	~Graph();

	void addNewVertex();
	void deleteVertex(int);

	void addNewEdge(const Edge&);
	void deleteEdge(const Edge&);
};