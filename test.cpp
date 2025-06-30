#include "test.h"
#include <iostream>
#include <fstream>


vector<Point<CoordType>> readPointsWithLabelFromFile(const string filename, vector<int>& result){
    vector<Point<CoordType>> points;
    string shapeType;
    int numPoints;

    ifstream shapeFile(filename);
    if(!shapeFile){
        cerr <<"Can't open input file: "<< filename << endl;
        return points;
    }

    while(shapeFile >> shapeType >> numPoints){
        if (shapeType == "POINTS"){
            for (int i = 0; i < numPoints; ++i){
                CoordType x, y;
                int position;
                shapeFile >> x >> y >> position;
                points.push_back({x, y});
                result.push_back(position);
            }
        }

    }
    shapeFile.close();

    return points;
};


int run_test(Test& test){
    int error_count = 0;
    for (int i = 0; i < test.points.size(); i++){
        if (is_point_in_shape(test.points[i], test.shape)!=test.results[i]){
            cout << test.label << " Test failed for point: " << test.points[i].x << "," << test.points[i].y << endl;
            error_count++;
        }
    }
    if (error_count > 0){
        cout << test.label << "Test FAILED! with "<< error_count << " errors." << endl;
    } else {
        cout << test.label << "Test PASSED! " << endl;
    }
    return error_count;
}
