//
// Created by elif zorlu on 9.11.2025.
//

#include "TwoDimTree.h"

// creates a new root node that covers the entire extent tree
TwoDimTree::TwoDimTree(const Rectangle& extent) {
    root = new TwoDimTreeNode(extent);
}

// quad tree destructor (to avoid memory leak)
TwoDimTree::~TwoDimTree() {
    clearTree(root);
    root = nullptr;
}

// quad tree recursive clear tree implementation
void TwoDimTree::clearTree(TwoDimTreeNode* node) {

    // base case: tree is empty
    if (node == nullptr)
        return;

    clearTree(node->getTopLeft()); // clear top-left quadrant
    clearTree(node->getTopRight()); // clear top-right quadrant
    clearTree(node->getBottomLeft()); // clear bottom-left quadrant
    clearTree(node->getBottomRight()); // clear bottom-right quadrant

    delete node; // deletes the current node after clearing all of its children
}


void TwoDimTree::insert(const Rectangle& rectangle) {
    if (root == nullptr) return;
    recursive_Insertion(root, rectangle);
}

void TwoDimTree::search(int x, int y, List<Rectangle>& results) {
    if (root == nullptr) return;
    recursive_Search(root, x, y, results);
}


/******************************************************************************
 * Member Function: recursive_Insertion
 * ----------------------
 * Purpose:
 *- Recursively inserts a rectangle into the TwoDimTree following quadtree rules
 *- Rectangles that insersect with the vertical middle line are stored in the Vertical Rectangles list.
 *- Rectangles that intersect with the horizontal middle line are stored in the Horizontal Rectangles list.
 *- Rectangles that fit completely in one of the quadrants are recursively sent to that child node. (and a child node is created if it doesn't exist already)
 *- Prevents infinite subdividing by storing very small rectangles at the current node.
 *
 * Parameters:
 * - node: Pointer to the current TwoDimTreeNode
 * - rectangle: The Rectangle object to insert into the tree.
 *
 * Returns:
 * - None.
 *
 * Known Issues:
 *  - None.
 ******************************************************************************/
void TwoDimTree::recursive_Insertion(TwoDimTreeNode* node, const Rectangle& rectangle) {
    if (node == nullptr) return;

    // retrieve the borders of the extent with the help of getter functions
    int L = node->getExtent().getLeft();
    int R = node->getExtent().getRight();
    int T = node->getExtent().getTop();
    int B = node->getExtent().getBottom();

    // find the center of the tree rectangle
    int center_tree_X = (L + R) / 2;
    int center_tree_Y = (T + B) / 2;

    // base case:
    // until width or height of the rectangle is less or equal to 1, keep subdividing.
    if ((R - L) <= 1 || (B - T) <= 1) {
        node->getVertical().insert(rectangle, node->getVertical().zeroth());
        return;
    }


    bool intersects_Vertical_line =
        (rectangle.getLeft() <= center_tree_X && rectangle.getRight() > center_tree_X);

    bool intersects_Horizontal_Line =
        (rectangle.getTop() <= center_tree_Y && rectangle.getBottom() > center_tree_Y);

    // if rectangle intersects with vertical line, it gets stored in Vertical list
    if (intersects_Vertical_line) {
        node->getVertical().insert(rectangle, node->getVertical().zeroth());
        return;
    }

    // if rectangle intersects only with horizontal line, it gets stored in Horizontal list

    if (intersects_Horizontal_Line) {
        node->getHorizontal().insert(rectangle, node->getHorizontal().zeroth());
        return;
    }


    // if intersects with none of the lines, rectangle should go to a single quadrant
    bool inTopQuadrant    = (rectangle.getBottom() <= center_tree_Y);
    bool inBottomQuadrant = (rectangle.getTop()    >= center_tree_Y);
    bool inLeftQuadrant   = (rectangle.getRight()  <= center_tree_X);
    bool inRightQuadrant  = (rectangle.getLeft()   >= center_tree_X);

    // checks if already a top-left child exists already, if not creates a new child node that represents the top-left quadrant
    if (inTopQuadrant && inLeftQuadrant) {
        if (node->getTopLeft() == nullptr) {
            node->getTopLeft() = new TwoDimTreeNode(
                Rectangle(T, L, center_tree_Y, center_tree_X)
            );
        }
        // recursively inserts the rectangle into the child node (Top-Left Quadrant)
        recursive_Insertion(node->getTopLeft(), rectangle);
        return;
    }

    // Top-Right
    if (inTopQuadrant && inRightQuadrant) {
        if (node->getTopRight() == nullptr) {
            node->getTopRight() = new TwoDimTreeNode(
                Rectangle(T, center_tree_X + 1, center_tree_Y, R)
            );
        }
        recursive_Insertion(node->getTopRight(), rectangle);
        return;
    }

    // Bottom-Left
    if (inBottomQuadrant && inLeftQuadrant) {
        if (node->getBottomLeft() == nullptr) {
            node->getBottomLeft() = new TwoDimTreeNode(
                Rectangle(center_tree_Y + 1, L, B, center_tree_X)
            );
        }
        recursive_Insertion(node->getBottomLeft(), rectangle);
        return;
    }

    // Bottom-Right
    if (inBottomQuadrant && inRightQuadrant) {
        if (node->getBottomRight() == nullptr) {
            node->getBottomRight() = new TwoDimTreeNode(
                Rectangle(center_tree_Y + 1, center_tree_X + 1, B, R)
            );
        }
        recursive_Insertion(node->getBottomRight(), rectangle);
        return;
    }

    // a cautionary line to catch a rectangle from getting lost if it doesn't satisfy any of the conditions
    node->getVertical().insert(rectangle, node->getVertical().zeroth());
}


/******************************************************************************
 * Member Function: recursive_Search
 * ----------------------
 * Purpose:
 *- Recursively searches the TwoDimTree for all rectangles that contain the (x,y) point
 *- Firstly, checks the Vertical Rectangles and Horizontal Rectangles Lists.
 *- If the (x,y) point is not on a center line, recurses into exactly one child quadrant that contains the point.
 *- Accumulates all matching rectangles into the provided results list.
 *
 * Parameters:
 * - node: pointer to the current TwoDimTreeNode
 * - X : x-coordinate of the point
 * - Y : y-coordinate of the point
 * - results: reference to a List<Rectangle> that stores all rectangles containing the (x,y) point.
 *
 * Returns:
 * - None.
 *
 *
 * Known Issues:
 *  - None.
 ******************************************************************************/
void TwoDimTree::recursive_Search(
    TwoDimTreeNode* node, int x, int y, List<Rectangle>& results) {

    // base cases:
    // if the node doesn't exist, stop recursion.
    if (node == nullptr) return;

    // if the node is outside the Extent rectangle, stop the recursion
    if (!node->getExtent().rectangle_contains_point(x, y)) return;

    // Check vertical rectangles list using an iterator
    {
        ListItr<Rectangle> itr = node->getVertical().first();
        while (!itr.isPastEnd()) {
            const Rectangle& rect = itr.retrieve(); // for each rectangle, check if it contains the (x,y) point
            if (rect.rectangle_contains_point(x, y)) {  // if yes, insert it
                results.insert(rect, results.zeroth());
            }
            itr.advance();
        }
    }

    // Check horizontal list
    {
        ListItr<Rectangle> itr = node->getHorizontal().first();
        while (!itr.isPastEnd()) {
            const Rectangle& rect = itr.retrieve(); // for each rectangle, check if it contains the (x,y) point
            if (rect.rectangle_contains_point(x, y)) {
                results.insert(rect, results.zeroth()); // if yes, insert it
            }
            itr.advance();
        }
    }

    // get the extent rectangle's borders
    int L = node->getExtent().getLeft();
    int R = node->getExtent().getRight();
    int T = node->getExtent().getTop();
    int B = node->getExtent().getBottom();

    // calculate the extent's vertical and horizontal line
    int center_X_line = (L + R) / 2;
    int center_Y_line = (T + B) / 2;

    // if any of the coordinates is on a center line, stop recursion.
    if (x == center_X_line || y == center_Y_line) return;

    // recurse into the unique child
    if (y < center_Y_line) { // Top
        if (x < center_X_line)
            recursive_Search(node->getTopLeft(), x, y, results);
        else
            recursive_Search(node->getTopRight(), x, y, results);
    } else { // Bottom
        if (x < center_X_line)
            recursive_Search(node->getBottomLeft(), x, y, results);
        else
            recursive_Search(node->getBottomRight(), x, y, results);
    }
}
