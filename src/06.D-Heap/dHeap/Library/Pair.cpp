#include "Pair.h"

bool Pair::operator<(const Pair& _pair) const {
	return dist < _pair.dist;
}

bool Pair::operator>(const Pair& _pair) const {
	return dist > _pair.dist;
}