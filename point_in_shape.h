// point_in_shape.h
#ifndef POINT_IN_SHAPE_H
#define POINT_IN_SHAPE_H
#include <iostream>

using namespace std;
using CoordType = double; // Keeping all inputs to double

/**
 * @brief A 2D point with coordinates of type T.
 * 
 * @tparam T The type used for the coordinates (e.g., int, float, double).
 */
template<typename T>
struct Point{
    T x,y;
};

/** 
 * @brief A polygon represented as a list of CoordType-coordinate points.
 */
using Polygon = vector<Point<CoordType>>;

/**
 * @brief Represents a polygon with optional number of cutout regions (holes).
 */
struct Polygonshape{
    Polygon outline;            ///< Outer boundary of the polygon
    vector<Polygon> cutouts;    ///< List of interior "hole" polygons
};

/**
 * @brief Reads a polygon from a file
 *
 * @param file Input file stream (must be open).
 * @param numPoints Number of points to read from the file.
 * @return The resulting polygon with numPoints vertices.
 */
Polygon readPolygon(std::ifstream& file, int numPoints);

/**
 * @brief Reads a polygon shape with optional number of cutouts from a file.
 *
 * The file format must include blocks starting with:
 *     OUTLINE <numPoints> or CUT <numPoints>
 * followed by lines:
 *     <x> <y> 
 * Example:
 *     OUTLINE 3
 *     0.0 0.0 
 *     5.0 5.0  
 *     0.0 5.0  
 *
 * Note: There can be only "one OUTLINE" and the cutouts are inside the OUTLINE 
 * without overlap with one another. 
 * @param filename The path to the input file.
 * @return Polygonshape A filled Polygonshape with outer boundary (outline) and any cutouts.
 */
Polygonshape readShapeFromFile(const string filename);

/**
 * @brief Prints the given Polygonshape to stdout (used to debug).
 *
 * @param poly The polygon shape to print.
 */
void PrintPolygonShape(const Polygonshape& poly);

/**
 * @brief Checks whether a point lies on the edge defined by two endpoints.
 *
 * @param p The point to check.
 * @param a One endpoint of the edge.
 * @param b The other endpoint of the edge.
 * @param tol Tolerance for floating-point inaccuracy (default = 1e-6).
 * @return true If the point lies on the edge (within tolerance).
 * @return false Otherwise.
 */
bool is_point_on_edge(const Point<CoordType>& p, const Point<CoordType>& a, const Point<CoordType>& b, double tol = 1e-6);

/**
 * @brief Determines the position of a point relative to a polygon, including edge detection.
 *
 * This function first checks whether the point lies exactly on any of the polygon's edges.
 * If so, it returns -1. Otherwise, it uses the ray casting algorithm to determine whether
 * the point is inside or outside the polygon.
 * 
 * @param location The point to be tested.
 * @param polygon The polygon defined by a sequence of vertices (assumed closed).
 * @return int Returns:
 *         - -1 if the point lies on the edge of the polygon,
 *         -  0 if the point lies outside the polygon.
 *         -  1 if the point lies strictly inside the polygon,
 */
int point_in_polygon_with_edge(const Point<CoordType>& location, const Polygon& polygon);

/**
 * @brief Determines whether a point lies inside a complex shape with holes.
 *
 * A point is considered "inside" if it lies inside the outer polygon and edges but outside all cutouts.
 * Note: (1) The "cutouts are inside the outline" and "no overlap" with the outline's edge
 *       (2) "Cutouts do not overlap" with one another
 * 
 * @param location The point to test.
 * @param shape The shape consisting of an outline and cutouts.
 * @return true If the point is within the shape.
 * @return false Otherwise.
 */
bool is_point_in_shape(const Point<CoordType>& location, const Polygonshape& shape);

#endif /* POINT_IN_SHAPE_H */