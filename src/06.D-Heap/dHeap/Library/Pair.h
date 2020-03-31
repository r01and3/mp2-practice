#pragma once

struct Pair {
	int vertex;
	int dist;

	bool operator<(const Pair&) const;
	bool operator>(const Pair&) const;
};