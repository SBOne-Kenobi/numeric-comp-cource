#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <limits>

#include "src/barycentric_int.hpp"
#include "src/rb_int.hpp"

int main() {

    std::vector<Point<double>> points;
    std::vector<double> values;
    double minX, minY, maxX, maxY;
    minX = minY = std::numeric_limits<double>::max();
    maxX = maxY = std::numeric_limits<double>::min();
    {
        std::ifstream in(RESOURCES_DIR "/surface.xyz");
        std::string s;
        while (std::getline(in, s)) {
            std::istringstream is(s);
            double x, y, z;
            is >> x >> y >> z;
            minX = std::min(minX, x);
            minY = std::min(minY, y);
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);
            points.push_back({x, y});
            values.push_back(z);
        }
    }
    assert(points.size() == 128 * 128);

    // making regular grid
    {
        std::ofstream out(RESOURCES_DIR "/my_points_1.xyz");
        for (int i = 0; i < 128; ++i) {
            double tx = i / 127.;
            double x = minX * (1 - tx) + maxX * tx;
            for (int j = 0; j < 128; ++j) {
                double ty = j / 127.;
                double y = minY * (1 - ty) + maxY * ty;
                Point<double> p{x, y};
                Point<double> p0, p1, p2;
                double z0, z1, z2;

                p0 = points[i * 128 + j];
                z0 = values[i * 128 + j];
                if (i + 1 < 128) {
                    p1 = points[(i + 1) * 128 + j];
                    z1 = values[(i + 1) * 128 + j];
                } else {
                    p1 = points[(i - 1) * 128 + j];
                    z1 = values[(i - 1) * 128 + j];
                }
                if (j + 1 < 128) {
                    p2 = points[i * 128 + j + 1];
                    z2 = values[i * 128 + j + 1];
                } else {
                    p2 = points[i * 128 + j - 1];
                    z2 = values[i * 128 + j - 1];
                }
                double z = barycentricInterpolation(p0, p1, p2, z0, z1, z2, p);
                out << std::fixed << x << " " << y << " " << z << "\n";
            }
        }
    }

    {
        std::ofstream out(RESOURCES_DIR "/my_points_2.xyz");
        for (int i = 0; i < 128; ++i) {
            double tx = i / 127.;
            double x = minX * (1 - tx) + maxX * tx;
            for (int j = 0; j < 128; ++j) {
                double ty = j / 127.;
                double y = minY * (1 - ty) + maxY * ty;
                Point<double> p{x, y};
                Point<double> ps[4];
                double zs[4];

                int in = i + 1 < 128 ? i + 1 : i - 1;
                int jn = j + 1 < 128 ? j + 1 : j - 1;
                int cur = 0;
                for (int ii : {i, in}) {
                    for (int jj : {j, jn}) {
                        ps[cur] = points[ii * 128 + jj];
                        zs[cur] = values[ii * 128 + jj];
                        ++cur;
                    }
                }

                double z = radBasedInterpolation(ps, zs, p, 10.);
                out << std::fixed << x << " " << y << " " << z << "\n";
            }
        }
    }

}
