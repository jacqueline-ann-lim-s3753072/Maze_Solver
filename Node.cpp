#include "Node.h"
#include <iostream>

// I have created three pointers, pointing to addresses on the heap, however this isn't necessary as we could set the three
// variables to the three stack variables already declared in the header private section. Alternatively, if I was allowed to
// remove them I would only keep the three pointers pointing to the heap addresses. However I've decided to do both, even though
// move memory is being allocated to 6 variables instead of 3, 3 on the stack and 3 on the heap, I wanted to showcase my understanding
// of both memory management and heap allocation, hence I've created 3 heap objects (3 int objects) set them to their respectable
// pointers, and set the 3 variables already defined row, col, dist_traveled to the pointers value. I've then just used each getter
// to only return the stack variable values, and setters fix up both the stack and heap values.

Node::Node(int row, int col, int dist_traveled)
{
    this->rowPnt = new int(row);
    this->colPnt = new int(col);
    this->dist_traveledPnt = new int(dist_traveled);
    
    this->row = *rowPnt;
    this->col = *colPnt;
    this->dist_traveled = *dist_traveledPnt;
}

Node::~Node(){
    delete rowPnt;
    delete colPnt;
    delete dist_traveledPnt;
}

int Node::getRow(){

    return this->row;
}

int Node::getCol(){

    return this->col;
}

int Node::getDistanceTraveled(){

    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    delete this->dist_traveledPnt;
    *this->dist_traveledPnt = dist_traveled;
    this->dist_traveled = *dist_traveledPnt;
}

int Node::getEstimatedDist2Goal(Node* goal){
    
    int distance = getDistanceTraveled() + abs(this->col - goal->col) + abs(this->row - goal->row);
    return distance;
}

//--------------------------------                             