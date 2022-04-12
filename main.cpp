#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unistd.h>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env, char** characters, int row, int col);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);
void test(Env env);
Env* setRowCol();
Env make_env(Env old, const int rows, const int cols, const int maxCols, char c);
void delete_env(Env *env, int rows, int cols);

int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    //testNode();
    //testNodeList();
    //std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    
    Env* env = new Env();
    env = setRowCol();
    test(*env);
    //delete_env(env, 19, 19);
    //delete env;

    //fix
    //readEnvStdin(env, characters, rows, cols);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    
    //PathSolver* pathSolver = new PathSolver();
    //pathSolver->forwardSearch(env);

    //NodeList* exploredPositions = nullptr;
    //exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    //NodeList* solution = pathSolver->getPath(env);

    //printEnvStdout(env, solution);

    //delete pathSolver;
    //delete exploredPositions;
    //delete solution; 

}

Env make_env(Env* old, const int rows, const int cols, const int maxCols, char c) {
    Env env = nullptr;
    Env* send = nullptr;

    std::cout << rows << ", " << cols << ", " << maxCols << ", "<< c << std::endl;

    if (rows >= 0 && cols >= 0) {
        env = new char*[rows];
        int tempCols = 1;
        if(maxCols > cols) {
            tempCols = maxCols - 1;
        }
        else {
            tempCols = cols;
        }

        
        // create the new size
        for (int i = 1; i <= rows; i++) {
            if(i != rows) {
                env[i-1] = new char[tempCols];
            }
            else {
                env[i-1] = new char[cols];
            }
        }

        
        // fill in previous data
        for(int y = 1; y <= rows; y++) {
            for (int x = 1; x <= tempCols; x++) {
                if(y == rows && x <= cols) {
                    if(x == cols) {
                        env[y-1][x-1] = c;
                        y = rows + 1;
                        x = tempCols + 1;
                    }
                    else {
                        env[y-1][x-1] = *old[y-1][x-1];
                        delete[] old[y-1][x-1];
                    }
                }
                else if(x < tempCols) {
                    env[y-1][x-1] = *old[y-1][x-1];
                    delete[] old[y-1][x-1];
                }
            }
        } 
    }
    send = new Env(env);

    return *send;
}

Env* setRowCol() {
    Env* env = new Env();
    bool check = true;
    int maxCols = 1;
    char c;
    int row = 1;
    int col = 1;

    while(check == true) {
        c = std::cin.get();

        if(std::cin.eof()) {
            check = false;
        }
        else if(! (std::cin.eof() || std::cin.fail())) {
            if(c == '\n') {
                row++;
                maxCols = col;
                col = 1;
            }
            else {
                env = new Env(make_env(env, row, col, maxCols, c));
                col++;
            }
        }
    }

    return env;

}

void delete_env(Env* env, int rows, int cols) {
    if (rows >= 0 && cols >= 0) {
        for (int i = 0; i <= rows; i++) {
            std::cout << i << std::endl;
            for(int x = 0; x <= cols; x++) {
                delete env[i][x];
            }
            //delete[] env[i];
            
        }
        //delete[] env;
    }

}

void readEnvStdin(Env env, char** characters, int row, int col){
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            env[r][c] = characters[r][c];
        }
    }
    //test(*env);
}

//remove later
void test(Env env) {
    for (int row = 0; row < ENV_DIM; row++) {
        for (int col = 0; col < ENV_DIM; col++) {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
}

void printEnvStdout(Env env, NodeList* solution) {
    
    Node* first = nullptr;
    Node* next = nullptr;
    int dist;
    
    for(int currentdist = 1; currentdist < solution->getLength() - 1; currentdist++) {
        for(int x = 0; x < solution->getLength() - 1; x++) {
            
            dist = solution->getNode(x)->getDistanceTraveled();
            if(dist == currentdist && (env[solution->getNode(x)->getRow()][solution->getNode(x)->getCol()] != SYMBOL_GOAL)) {
                first = solution->getNode(x);
            }
            else if(dist == currentdist+1) {
                next = solution->getNode(x);
            }
        }
        
        if(first != nullptr && next != nullptr) {
            char a = '\0';

            if(first->getRow()-1 == next->getRow()) {
                a = '^';
            }
            else if(first->getRow()+1 == next->getRow()) {
                a = 'V';
            }
            else if(first->getCol()-1 == next->getCol()) {
                a = '<';
            }
            else if(first->getCol()+1 == next->getCol()) {
                a = '>';
            }

            if(a != '\0') {
                env[first->getRow()][first->getCol()] = a;
            }
        }
    }

    for (int row = 0; row < ENV_DIM; row++) {
        for (int col = 0; col < ENV_DIM; col++) {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}