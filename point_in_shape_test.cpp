#include "test.h"

int main(){
    int error_counter = 0;
    cout<<"-------------------------------------Simple Square----------------------------"<<endl;
    Test square;
    //Case: Points located inside the outline
    square.shape.outline = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
    square.label = "InsideSquare";
    square.points = {{5, 5}, {2, 9}, {9, 9}};
    square.results = {1, 1, 1};
    error_counter = run_test(square);
    
    square.label = "OutsideSquare";
    // Case: Points located outside whose ray passes along horizontal edges and through vertical edges.
    square.points = {{-2, 5}, {12, 5}, {-2, 10}, {-2, 0}};  
    square.results = {0, 0, 0, 0};
    error_counter += run_test(square);
    
    square.label = "OnEdgeOnVertex";
    // Special case: Points located on edges and verices.
    square.points = {{5, 10}, {10, 5}, {5, 0}, {0, 5}, {0, 0}, {0, 10}, {10, 10}, {0, 10}};  
    square.results = {1, 1, 1, 1, 1, 1, 1, 1};
    error_counter += run_test(square);

    //------------------------------------------------------------------------------------------------------------
    cout<<"-------------------------------------Square with one cutout----------------------------"<<endl;
    Test squareWithHole;
    error_counter = 0;
    //Case: Points located inside the outline but outside the cutout.
    squareWithHole.shape.outline = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
    squareWithHole.shape.cutouts = {{{2, 2}, {8, 2}, {8, 8}, {2, 8}}};
    squareWithHole.label = "InsideSquareWithHole";
    squareWithHole.points = {{1, 5}, {5, 9}, {9, 9}};
    squareWithHole.results = {1, 1, 1};
    error_counter += run_test(squareWithHole);
    
    //Case: Points located inside the cutout and outside the outline.
    squareWithHole.label = "OutsideSquareWithHole";
    squareWithHole.points = {{5, 5}, {5, 7}, {-2, 5}};
    squareWithHole.results = {0, 0, 0};
    error_counter += run_test(squareWithHole);

    //Case: Points located on the edge of the cutout and outline
    squareWithHole.label = "OnEdgeSquareWithHole";
    squareWithHole.points = {{0, 5}, {5, 8}, {2, 5}, {5, 2}};
    squareWithHole.results = {1, 1, 1, 1};
    error_counter += run_test(squareWithHole);

    //------------------------------------------------------------------------------------------------------------
    cout<<"-------------------------------------Square with multiple cutouts----------------------------"<<endl;
    Test squareWithMultipleHoles;
    error_counter = 0;
    squareWithMultipleHoles.shape.outline = {{0, 0}, {10, 0}, {10, 10}, {0, 10}};
    squareWithMultipleHoles.shape.cutouts = {{{2, 5}, {4, 5}, {4, 8}, {2, 8}}, {{5, 2}, {5, 4}, {8, 4}, {8, 2}}, {{5, 5}, {8, 5}, {8, 8}, {5, 8}}};
    squareWithMultipleHoles.label = "InsideCutouts";
    squareWithMultipleHoles.points = {{3, 7}, {7, 3}, {7, 7}};
    squareWithMultipleHoles.results = {0, 0, 0};
    error_counter += run_test(squareWithMultipleHoles);

    squareWithMultipleHoles.label = "EdgeOfCutouts";
    squareWithMultipleHoles.points = {{5, 3}, {8, 3}, {7, 2}, {7, 4}, {2, 6}, {4, 6}, {8, 7}};
    squareWithMultipleHoles.results = {1, 1, 1, 1, 1, 1, 1};
    error_counter += run_test(squareWithMultipleHoles);

    //------------------------------------------------------------------------------------------------------------
    cout<<"-------------------------------------Non orthogonal shape-----------------------------"<<endl;
    Test triangle;
    error_counter = 0;
    triangle.shape.outline = {{0, 0}, {10, 0}, {5, 5}};
    triangle.label = "InsideUpTriangle";
    triangle.points = {{5, 3}, {5, 5}, {5, 0}, {3, 3}, {7, 3}};
    triangle.results = {1, 1, 1, 1, 1};
    error_counter = run_test(triangle);
    // Testing special cases 1:
    // X------.------>
    //      .   . 
    //    .       . 
    //  .           .
    // . . . . . . . .
    triangle.label = "OutsideUpTriangle";
    triangle.points = {{2, 5}, {0, 3}};
    triangle.results = {0, 0};
    error_counter = run_test(triangle);

    // Testing special cases 2:
    // . . . . . . . .
    //  .           .
    //    .       . 
    //      .   . 
    // X------.------>
    triangle.shape.outline = {{5, 0}, {10, 5}, {0, 5}};
    triangle.label = "OutsideDownTriangle";
    triangle.points = {{0, 0}, {0, 3}};
    triangle.results = {0, 0};
    error_counter = run_test(triangle);

    cout<<"-------------------------------------From File with known location----------------------------"<<endl;
    // Testing for the provided shape from file with random points located on it whose outcome is know.
    // The test points with known labels are strored in "geometry_files/shape_test_points.txt" for shape 
    // in "geometry_files/shape.txt".
    Test geometryfromfile;
    error_counter = 0;
    geometryfromfile.shape = readShapeFromFile("geometry_files/shape.txt");
    geometryfromfile.results = {};
    geometryfromfile.points = readPointsWithLabelFromFile("geometry_files/shape_test_points.txt", geometryfromfile.results);
    geometryfromfile.label = "geometryfromfile";
    error_counter += run_test(geometryfromfile);

    return 0;
}