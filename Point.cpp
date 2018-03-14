#include "Point.hpp"
#include <cmath>

const float Point::EPS = (float)10e-6;

bool Point::operator==(const Point& p2) const {
	return fabs(x - p2.x) < EPS && fabs(y - p2.y) < EPS && fabs(z - p2.z) < EPS;
}
bool Point::operator!=(const Point& p2) const {
	return !this->operator==(p2);
}

std::ostream & operator<<(std::ostream& os, const Point& V1){
    return os << V1.x << ' ' << V1.y << ' ' << V1.z;
}

float Point::distance(const Point& p1, const Point& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
		(p1.y - p2.y) * (p1.y - p2.y) +
		(p1.z - p2.z) * (p1.z - p2.z));
}

std::size_t PointHasher::operator()(const Point& p) const
{
	using std::size_t;
	using std::hash;

	return ((hash<float>()(p.x)
		^ (hash<float>()(p.y) << 1)) >> 1)
		^ (hash<float>()(p.z) << 1);
}