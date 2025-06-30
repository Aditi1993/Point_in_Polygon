/* This is a C++ program to find whether a given point lies inside or outside a ploygon defined in a text file by the user.*/
#include "point_in_shape.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    // Reading in the user input for the file and point
    string filename = argv[1];
    Point<CoordType> input_location;
    input_location.x = atof(argv[2]);
    input_location.y = atof(argv[3]);

    // Reading the file into geometry
    Polygonshape geometry;
    geometry = readShapeFromFile(filename);
    if (geometry.outline.empty()){
        cerr << "Error in reading geometry file" << endl;
        return -1;
    }
    // PrintPolygonShape(geometry); // debugging mode

    // Raycasting and Edge detection to find if the point is inside or outside the geometry
    if (is_point_in_shape(input_location, geometry)){
        cout << "Point " << input_location.x << "," << input_location.y << " is INSIDE the shape\n";
        return 1;
    } else {
        cout << "Point " << input_location.x << "," << input_location.y << " is OUTSIDE the shape\n";
        return 0;
    }
};