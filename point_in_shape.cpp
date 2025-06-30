#include "point_in_shape.h"
#include <iostream>
#include <fstream>

using namespace std;

Polygon readPolygon(std::ifstream& file, int numPoints){
    Polygon poly;
    for (int i = 0; i < numPoints; ++i){
        CoordType x, y;
        file >> x >> y;
        poly.push_back({x, y});
    }
    return poly;
};

Polygonshape readShapeFromFile(const string filename) {
    Polygonshape shape;
    string shapeType;  // will be read from the file
    int numVertices;   // will be read from the file

    ifstream shapeFile(filename);
    if(!shapeFile){
        cerr <<"Can't open input file: "<< filename << endl;
    }

    while(shapeFile >> shapeType >> numVertices){
        if (shapeType == "OUTLINE") {
            shape.outline = readPolygon(shapeFile, numVertices);
        } else if (shapeType == "CUT"){
            shape.cutouts.push_back(readPolygon(shapeFile, numVertices));
        } else {
            cout << "Shape type not recognised. " << endl;
        }
    }
    shapeFile.close();
    return shape;
};

void PrintPolygonShape(const Polygonshape& polyout){
    // Used in debug mode.
    cout << "OUTLINE " << polyout.outline.size()<< "\n";
    for(const auto& pt : polyout.outline){
        cout << pt.x << " " << pt.y << "\n";
    }
    for(int i = 0; i < polyout.cutouts.size(); ++i){
        cout << "CUT " << polyout.cutouts[i].size()<< "\n";
        for(const auto& pt : polyout.cutouts[i]){
            cout << pt.x << " " << pt.y << "\n";
        }
    }
};

bool is_point_on_edge(const Point<CoordType>& p, const Point<CoordType>& a, const Point<CoordType>& b, double tol){
    // First, check if the three points are colinear using the cross product of vectors (b - a) and (p - a)
    // For colinear vectors, the angle between them is 0 therefore, the cross product |AP|*|AB|*sin(0) is 0.
    double cross = (b.y - a.y) * (p.x - a.x) - (b.x - a.x) * (p.y - a.y);
    if (abs(cross) > tol) return false; // Not colinear -> point p definitely is not on the edge

    // Second, we ensure the point p lies between a and b using dot product projection.
    // This avoids accepting points that are colinear but lie outside the edge bounds.
    double dot_product = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
    double squared_length = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);

    // For the condition to meet, the dot product must be between 0 and the squared edge length (inclusive, with tolerance)
    return dot_product >= -tol && dot_product <= squared_length + tol;
}

int point_in_polygon_with_edge(const Point<CoordType>& location, const Polygon& polygon){
    int numCrossings = 0;                   // counter for number of times the ray intersects with the polygon edge. 
    int numVertices = polygon.size();
    
    for(int i = 0; i < numVertices; i++){
        const Point<CoordType>& p1 = polygon[i];
        const Point<CoordType>& p2 = polygon[(i + 1) % numVertices];    // allows to wrap around to close the polygon

        // First, check if the point lies on this edge (special case, treated seperately)
        if (is_point_on_edge(location, p1, p2)){
            return -1;
        }

        // Ray casting algorithm (Assumption: horizontal ray along +x direction) 
        // The goal is to check, if this ray will intersect with the edge defined by points p1 ad p2 at location.y.
        if (((p1.y <= location.y) && (location.y < p2.y)) || ((p2.y <= location.y) && (location.y < p1.y))){
            if (location.x <= max(p1.x, p2.x)){
                // Compute the x-coordinate of the intersection point of the edge with the horizontal ray. 
                double xIntersect = p1.x + (p2.x - p1.x) * (location.y - p1.y) / (p2.y - p1.y);
                // Count it as a crossing only if it is strictly to the right of the point
                if (location.x < xIntersect){
                    ++numCrossings;
                }
            }
        }
    }

    // Even number of crossings -> outside, Odd -> inside
    return (numCrossings % 2 == 1) ? 1 : 0;
}

bool is_point_in_shape(const Point<CoordType>& location, const Polygonshape& shape){
    
    int inOutline = point_in_polygon_with_edge(location, shape.outline);
    
    if (inOutline == -1){
        // If point is on the outline edge -> considered inside shape
        return true;
    } 
    else if (inOutline == 1){
        // If point is inside the outline -> check if it lies in any of the cutouts
        for (const auto& cutout : shape.cutouts){
            int inCutout = point_in_polygon_with_edge(location, cutout);
            if (inCutout == -1){
                // If point is on cutout edge -> still considered inside shape
                return true; 
            }
            if (inCutout == 1){
                // If point is inside a cutout -> not in the shape
                return false;
            }
        }
        // Point is inside the outline and not in any cutout -> inside shape
        return true;
    } 
    else {
        // Point is outside outline -> not in the shape
        return false;
    }
    return false;
}