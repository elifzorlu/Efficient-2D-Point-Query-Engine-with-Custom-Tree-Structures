//
// Created by elif zorlu on 12.11.2025.
//

#include "TwoDimTree.h"
#include <iostream>
#include <fstream>

int main() {
    // reads from rectdb.txt
    std::ifstream inputFile("rectdb.txt");
    if (!inputFile) {
        std::cerr << "Cannot open rectdb.txt" << std::endl;
        return 1;
    }

    // get the inputs of the extent rectangle from the file
    int top, left, bottom, right;
    inputFile >> top >> left >> bottom >> right;
    Rectangle extent(top, left, bottom, right);

    // create the tree
    TwoDimTree tree(extent);

    // read rectangles until x=-1 is entered
    while (inputFile >> top) {
        if (top < 0) break;
        inputFile >> left >> bottom >> right;
        Rectangle rect(top, left, bottom, right);
        tree.insert(rect);
    }
    inputFile.close();

    // process the queries
    int x, y;
    while (std::cin >> x) {
        if (x == -1) break;
        std::cin >> y;

        List<Rectangle> results;
        tree.search(x, y, results);

        // output the results in the required format
        std::cout << x << " " << y << std::endl;
        std::cout << results.size() << std::endl;

        if (!results.isEmpty()) {
            ListItr<Rectangle> itr = results.first();
            while (!itr.isPastEnd()) {
                const Rectangle& rect = itr.retrieve();
                std::cout << rect.getTop() << " " << rect.getLeft() << " "
                          << rect.getBottom() << " " << rect.getRight() << std::endl;
                itr.advance();
            }
        }
    }

    return 0;
}