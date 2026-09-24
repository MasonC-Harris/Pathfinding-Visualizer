#pragma once

#include "Node.h"
#include <SFML/System/Vector2.hpp>
#include <list>
#include <optional>
#include <queue>
#include <stack>
#include <vector>
#include "Grid.h"


class Algo {
    private:
        
        //Movements for the path
        std::vector<std::list<int>> movements() {
            return {
                {-1, 0},  // left
                {1, 0},   // right
                {0, 1},   // up
                {0, -1}   // down
            };
        }

        // The std::optional<> allows for a null like state so I can 
        // check if these values have been grabbed yet
        std::optional<sf::Vector2i> startingPos, endingPos;
        
        Grid& grid;

        ///////// BFS /////////
        //Hold the positions of cells to be processed
        std::queue<sf::Vector2i> frontier;
        //Memory for each cells search state
        std::vector<std::vector<Node>> memory;
        
        ///////// DFS /////////
        std::stack<sf::Vector2i> dfsFrontier;
        
        //This is for horiziontal prioritized movements
        std::vector<std::list<int>> movementsHz() {
            return {
                {0, 1},   // up
                {0, -1},   // down
                {-1, 0},  // left
                {1, 0}   // right
            };
        }

    public:
        
        bool found = false;

        //Constructor intialzing grid reference
        Algo(Grid& grid);


        //Algorithms
        void BFS();
        void DFS();
        //void Dijkstra();
        //void AStar();

        void Trail();

        void GetStartAndEnd();

        void Reset();
};