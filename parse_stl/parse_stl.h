#ifndef PARSE_STL_H
#define PARSE_STL_H

#include <string>
#include <vector>

namespace parse_stl {

  struct point {
    double x;
    double y;
    double z;

    point() : x(0), y(0), z(0) {}
    point(double xp, double yp, double zp) : x(xp), y(yp), z(zp) {}
  };

  struct triangle {
    point normal;
    point v1;
    point v2;
    point v3;
    triangle(point normalp, point v1p, point v2p, point v3p) :
      normal(normalp), v1(v1p), v2(v2p), v3(v3p) {}
  };

  std::ostream& operator<<(std::ostream& out, const triangle& t);

  struct stl_data {
    std::string name;
    std::vector<triangle> triangles;

    stl_data(std::string namep) : name(namep) {}
  };

  stl_data parse_stl(const std::string& stl_path);

}

#endif
