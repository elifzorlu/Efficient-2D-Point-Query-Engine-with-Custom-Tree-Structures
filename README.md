# 2D Point Query Engine (Quadtree Spatial Index) — C++

A 2D spatial indexing system using a **quadtree-style** data structure to efficiently store and query **axis-aligned rectangles**.  
Supports fast **point-in-rectangle** queries by recursively partitioning space and pruning irrelevant regions during search.

## Overview
This project implements a **TwoDimTree (quadtree-like)** structure to organize rectangles within an overall **extent** region.  
Given a query point `(x, y)`, the search returns **all rectangles that contain the point**.

The implementation is written in **C++** and includes custom data structures and explicit memory management to emphasize correctness and performance.

## Key Features
- Recursive **TwoDimTree / quadtree-style** spatial partitioning
- Efficient **point query**: returns all rectangles containing `(x, y)`
- Custom implementations of:
  - Linked list + iterator (for storing rectangles in node lists)
  - Tree nodes + recursive traversal
- Edge-case handling to prevent infinite subdivision
- Proper cleanup to avoid memory leaks (recursive tree deletion)

## Technical Details
- **Language:** C++ (C++20)
- **Core Concepts:**
  - Spatial data structures
  - Recursive algorithms
  - Geometric querying
  - Manual memory management
- **Algorithm Highlights:**
  - Quadtree-style recursive subdivision
  - Recursive search with pruning based on extent containment

## Input / Output Format
### Rectangle Database
Rectangles are read from a file (e.g., `rectdb.txt`):
1) First line: extent rectangle as `top left bottom right`  
2) Following lines: rectangles as `top left bottom right`  
3) Terminates when a negative value is encountered (e.g., `top = -1`)

### Queries
Queries are read from `stdin` as `x y` pairs and terminate on `x = -1`.

### Output
For each query point `(x, y)` the program prints:
- The query point
- Number of matching rectangles
- The list of matching rectangles (each as `top left bottom right`)

## Usage Overview
The project demonstrates a quadtree-style spatial indexing structure for efficient
point-in-rectangle queries. The focus is on data structures, algorithms, and
correctness rather than production deployment or packaging.

