#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){

    nodesExplored = new NodeList();
    emptyNodes = new NodeList(); 
    checkedNodes = new NodeList(); 
}

PathSolver::~PathSolver(){

    delete nodesExplored;
    delete emptyNodes;
    delete checkedNodes;
    // we do not delete path as it is being deleted in the main method since its only a shallow copy

}

void PathSolver::forwardSearch(Env env){

    Node* goal = nullptr;
    bool stopSearch = false;
    
    // setup the goal and start
    // checking if they exist and there are only one of each

    for(int x = 0; x < ENV_DIM; x++) {
        for(int y = 0; y < ENV_DIM; y++) {
            if (env[x][y] == SYMBOL_GOAL) {
                if(goal != nullptr) {
                    std::cout << "Two Goals Exists" << std::endl;
                    stopSearch = true;
                    x = ENV_DIM;
                    y = ENV_DIM;
                }
                goal = new Node(x, y, 0);
            }
            else if (env[x][y] == SYMBOL_START) {
                if(start != nullptr) {
                    std::cout << "Two Starts Exists" << std::endl;
                    stopSearch = true;
                    x = ENV_DIM;
                    y = ENV_DIM;
                }
                start = new Node(x, y, 0);
                emptyNodes->addElement(start);
            }
        }
    }

    if(goal == nullptr || start == nullptr) {
        std::cout << "No Start or Goal Found" << std::endl;
        stopSearch = true;
    }

    // begin the forward search
    
    if (stopSearch == false) {

        Node* position = start; // first node to begin the search
        bool check = true; // once check is false, we have arrived at the goal
        
        // we want to check whether or not emptyNodes has new nodes each loop, as if it doesn't it means there isn't a possible path
        int emptyNodesLength = emptyNodes->getLength();
        int nodeListMax = 0; // Counter used for this check

        while(check == true) {
            
            // check nodes around position
            addBlankNodes(position, emptyNodes, env);

            if(position == start) {
                checkedNodes->addElement(new Node(start->getRow(), start->getCol(), start->getDistanceTraveled()));
                // add start to checkedNodes since we want to do that after addBlankNodes method 
            }
            
            int defaultPos = position->getDistanceTraveled();
            bool updatedOnce = false;

            // check list for smallest distance to goal
            for(int i = 0; i < emptyNodes->getLength(); i++) {
                
                if(checkIfExists(emptyNodes->getNode(i), checkedNodes) == false) {
                    // check if goal
                    if((emptyNodes->getNode(i)->getRow() == goal->getRow()) && (emptyNodes->getNode(i)->getCol() == goal->getCol())) {
                        checkedNodes->addElement(new Node(emptyNodes->getNode(i)->getRow(), emptyNodes->getNode(i)->getCol(), emptyNodes->getNode(i)->getDistanceTraveled()));
                        check = false;
                        i = emptyNodes->getLength();
                        this->success = true;
                    }

                    // Look for next node 
                    else if(emptyNodes->getNode(i)->getDistanceTraveled() <= defaultPos + 1) {
                        // Update once since we need the pos to be distance + 1 to check for the else if statement below
                        if (updatedOnce == false) {
                            position = emptyNodes->getNode(i);
                            updatedOnce = true;
                        }
                        // Check if there is a node closer to the goal than the current position
                        else if((emptyNodes->getNode(i)->getEstimatedDist2Goal(goal) - emptyNodes->getNode(i)->getDistanceTraveled()) < (position->getEstimatedDist2Goal(goal) - position->getDistanceTraveled())) {
                            position = emptyNodes->getNode(i);
                        }
                    }
                }
                
                // Check to see if we are stuck
                if(emptyNodesLength == emptyNodes->getLength()) {
                    // If we are stuck this means that there is no where to go and the loop will keep going
                    // We want it to keep going until NODE_LIST_ARRAY_MAX_SIZE has been hit since that means we have looped enough times for
                    // the code to check whether or not there is a node somewhere to go

                    if(nodeListMax == NODE_LIST_ARRAY_MAX_SIZE) {
                        check = false;
                        this->success = false;
                        std::cout << "There is no possible path" << std::endl;
                    }
                    nodeListMax++;
                }
            }

            emptyNodesLength = emptyNodes->getLength();

            // add node to closed node list and check
            if(check == true) {
                checkedNodes->addElement(new Node(position->getRow(), position->getCol(), position->getDistanceTraveled()));
            }
        }

    }
    
}

bool PathSolver::checkIfExists(Node* check, NodeList* list) {

    bool returnCheck = false;
    for(int i = 0; i < list->getLength(); i++) {
        if((check->getCol() == list->getNode(i)->getCol()) && (check->getRow() == list->getNode(i)->getRow())) {
            returnCheck = true;
            i = list->getLength();
        }
    }

    return returnCheck;
}

void PathSolver::addBlankNodes(Node* pos, NodeList* empty, Env env) {

    int x = pos->getCol();
    int y = pos->getRow();

    for(int i = 0; i < 2; i++) {
        if((x + this->num[i]) >= 0 && (x + this->num[i]) < ENV_DIM) {
            Node* check = new Node(y, x+num[i], pos->getDistanceTraveled()+1);
            if(env[check->getRow()][check->getCol()] == SYMBOL_EMPTY) {
                if (checkIfExists(check, empty) == false) {
                    empty->addElement(new Node(y, x+num[i], pos->getDistanceTraveled()+1));
                }
            }
            else if(env[check->getRow()][check->getCol()] == SYMBOL_GOAL) {
                if (checkIfExists(check, empty) == false) {
                    empty->addElement(new Node(y, x+num[i], pos->getDistanceTraveled()+1));
                }
            }
            delete check;
            check = nullptr;
        }
    }

    for(int i = 0; i < 2; i++) {
        if((y + this->num[i]) >= 0 && (y + this->num[i]) < ENV_DIM) {
            Node* check = new Node(y+num[i], x, pos->getDistanceTraveled()+1);
            if(env[check->getRow()][check->getCol()] == SYMBOL_EMPTY) {
                if (checkIfExists(check, empty) == false) {
                    empty->addElement(new Node(y+num[i], x, pos->getDistanceTraveled()+1));
                }
            }
            else if(env[check->getRow()][check->getCol()] == SYMBOL_GOAL) {
                if (checkIfExists(check, empty) == false) {
                    empty->addElement(new Node(y+num[i], x, pos->getDistanceTraveled()+1));
                }
            }
            delete check;
            check = nullptr;
        }
    }
    
}

NodeList* PathSolver::getNodesExplored(){

    NodeList* nodesExplored = new NodeList(*checkedNodes);
    return nodesExplored;
}

NodeList* PathSolver::getPath(Env env){

    int greatestDistance = -1;
    Node* current = nullptr;
    NodeList* deleted = new NodeList();
    bool wait = true;

    if(success == true) {

        while(wait == true) {

            Node* previous = current;
            
            NodeList* sameDistance = new NodeList();

            // Get greatest distance
            for(int i = 0; i < this->checkedNodes->getLength(); i++) {
                if((checkIfExists(checkedNodes->getNode(i), deleted) == false) && (checkedNodes->getNode(i)->getDistanceTraveled() > greatestDistance)) {
                    greatestDistance = checkedNodes->getNode(i)->getDistanceTraveled();
                    current = checkedNodes->getNode(i);
                }
            }
            
            // Check for all nodes with same distance
            for(int i = 0; i < this->checkedNodes->getLength(); i++) {
                if((checkIfExists(checkedNodes->getNode(i), deleted) == false) && checkedNodes->getNode(i)->getDistanceTraveled() == greatestDistance) {
                    sameDistance->addElement(new Node(checkedNodes->getNode(i)->getRow(), checkedNodes->getNode(i)->getCol(), checkedNodes->getNode(i)->getDistanceTraveled()));
                }
            }
            
            if(sameDistance->getLength() == 1) {
                path->addElement(new Node(current->getRow(), current->getCol(), current->getDistanceTraveled()));
                deleted->addElement(new Node(current->getRow(), current->getCol(), current->getDistanceTraveled()));
            }

            else if(sameDistance->getLength() > 1) {
                // get the previous x1 and y1
                int x1 = previous->getCol();
                int y1 = previous->getRow();

                for(int y = 0; y < sameDistance->getLength(); y++) {
                    // get current x1 and y1
                    int x2 = sameDistance->getNode(y)->getCol();
                    int y2 = sameDistance->getNode(y)->getRow();
                    for(int i = 0; i < 2; i++) {
                        // if the node adjancent is the same
                        if((x2+num[i] == x1) && (y1 == y2)) {
                            current = sameDistance->getNode(y);
                        }
                        if((y2+num[i] == y1) && (x1 == x2)) {
                            current = sameDistance->getNode(y);
                        }
                    }
                    deleted->addElement(new Node(sameDistance->getNode(y)->getRow(), sameDistance->getNode(y)->getCol(), sameDistance->getNode(y)->getDistanceTraveled()));    
                }
                path->addElement(new Node(current->getRow(), current->getCol(), current->getDistanceTraveled()));
                current = path->getNode(path->getLength()-1); // since we delete sameDistance we will lose pointer to previous current
            }

            if(current->getCol() == start->getCol() && current->getRow() == start->getRow()) {
                wait = false;
            }

            greatestDistance = -1;
            delete sameDistance;
            
        }
        delete deleted;
    }
    
    return path;
}

//-----------------------------