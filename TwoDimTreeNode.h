//
// Created by elif zorlu on 8.11.2025.
//

#ifndef TWODIMTREENODE_H
#define TWODIMTREENODE_H

#include "Rectangle.h"
#include "linkedlist.h"




class TwoDimTreeNode {

private:

    Rectangle Extent ;
    List<Rectangle> Vertical_rectangles;
    // list of rectangles overlapping the vertical midline
     List<Rectangle> Horizontal_rectangles;
    // list of rectangles overlapping the horizontal midline
    TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;


public:
    // constructor
    explicit TwoDimTreeNode(const Rectangle& extent);

    // the getter functions
    const Rectangle& getExtent() const {
        return Extent;
    }

    List<Rectangle>& getVertical() {
        return Vertical_rectangles;
    }

    List<Rectangle>& getHorizontal() {
        return Horizontal_rectangles;
    }

    TwoDimTreeNode*& getTopLeft() {
        return TopLeft;
    }

    TwoDimTreeNode*& getTopRight() {
        return TopRight;
    }


    TwoDimTreeNode*& getBottomLeft() {
        return BottomLeft;
    }


    TwoDimTreeNode*& getBottomRight() {
        return BottomRight;
    }



};



#endif //TWODIMTREENODE_H
