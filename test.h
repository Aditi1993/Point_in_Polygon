// test.h
#ifndef TEST_H
#define TEST_H
#include "point_in_shape.h"
#include <iostream>

/**
 * @brief Structure representing a test case for point-in-shape evaluation.
 *
 * Each test contains:
 *  - A label for identification.
 *  - A polygon shape (outline + optional cutouts).
 *  - A list of test points.
 *  - The expected results for each point:
 *      - 1  = inside,
 *      - 0 = outside.
 */
struct Test{
    std::string label;
    Polygonshape shape;
    std::vector<Point<CoordType>> points;
    std::vector<int> results;
};

/**
 * @brief Reads a list of points and their expected classification results from a file.
 *
 * The file format must include a block starting with:
 *     POINTS <numPoints>
 * followed by lines:
 *     <x> <y> <result>
 *
 * Example:
 *     POINTS 3
 *     0.0 0.0 -1
 *     5.0 5.0  1
 *     0.0 5.0  0
 *
 * @param filename Path to the input file.
 * @param result Output vector of expected classification results per point.
 * @return Vector of 2D points (Point<CoordType>) parsed from the file.
 */
vector<Point<CoordType>> readPointsWithLabelFromFile(const string filename, vector<int>& result);

/**
 * @brief Executes a point-in-shape test case by comparing expected results to actual.
 *
 * Uses `is_point_in_shape()` for each point in the test set and compares its return value
 * (1 = inside, 0 = outside) to the expected result.
 *
 * @param test A test case containing a shape, test points, and expected classifications.
 * @return The number of test failures.
 */
int run_test(Test& test);

#endif /* TEST_H */