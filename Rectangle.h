//
// Created by elif zorlu on 4.11.2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H



class Rectangle {

public:
    // constructor
    Rectangle(int top=0, int left=0, int bottom=0, int right=0)
    : Top(top), Left(left), Bottom(bottom), Right(right) {}

    /* getter functions:
     * - these functions help the private members
     * - of the class to be shared to outside of class. */
    int getTop() const {
        return Top ;
    }

    int getLeft() const {
        return Left ;
    }

    int getBottom() const {
        return Bottom ;
    }

    int getRight() const {
        return Right ;
    }

    /******************************************************************************
    * Member Function: rectangle_contains_point
    * ----------------------
    * Purpose:
    *- Checks whether a point is inside a rectangle.
    * - x should be greater or equal to "Left" and less than "Right"
    * - y should be greater or equal to "Top" and less than "Bottom"
    *
    * Parameters:
    * - x (int) : x-coordinate of the point
    * - y (int): y-coordinate of the point
    *
    * Returns:
    * - bool: whether the point is in the rectangle or not
    *
    * Known Issues:
    *  - None.
    ******************************************************************************/
    bool rectangle_contains_point(int x, int y) const {
        bool contains = (x >= Left && x < Right && y >= Top && y < Bottom);
        return contains;
    }




private:
    int Top, Left, Bottom, Right;


};

#endif //RECTANGLE_H
