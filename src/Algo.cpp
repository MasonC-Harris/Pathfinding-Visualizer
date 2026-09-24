#include "Algo.h"
#include "Grid.h"
#include "Node.h"
#include <SFML/System/Vector2.hpp>
//#include <algorithm>
//#include <cstddef>
//#include <iterator>
#include <vector>

Algo::Algo(Grid &grid)
    : grid(grid), memory(grid.getHeight(), std::vector<Node>(grid.getWidth())) {
}

//Breadth first search
void Algo::BFS() {
  if (!found) {
    sf::Vector2i neighbor, current;

    // If the starting and ending positions arent gathered yet get them
    if (!startingPos || !endingPos) {
      GetStartAndEnd();
      if (!startingPos || !endingPos) {
        return;
      }
      frontier.push(
          {startingPos->x, startingPos->y}); // Adding the starting coordinates
                                             // to the queue for processing
      memory[startingPos->y][startingPos->x].type = CellType::Start;
      memory[startingPos->y][startingPos->x].visited = true;
      memory[startingPos->y][startingPos->x].pos = *startingPos;
    }

    // Updating current with next coordinates to be processed from the queue
    // than popping the value since not needed
    if (frontier.empty()) {
      return;
    }
    current = frontier.front();
    frontier.pop();

    // Check neighboring celltypes from processing cell
    for (auto &move : movements()) {
      neighbor = current; // Neighbor gets the current position for all
                          // movements to run equally

      // If not in bounds or neighbor celltype is a wall or the next move is
      // already visited than go onto the next movement
      if (!grid.inBounds(neighbor.x + move.front(), neighbor.y + move.back())             ||
          grid.get(neighbor.x + move.front(), neighbor.y + move.back()) == CellType::Wall ||
          memory[current.y + move.back()][current.x + move.front()].visited) { 
            
            continue; 
        }

      // Set the neighbors coordinates by adding to current's coords
      neighbor += {move.front(), move.back()};
    
      //Set the pos in the memory vector
      memory[neighbor.y][neighbor.x].pos = neighbor;

      // If neighbor reaches end
      if (grid.get(neighbor.x, neighbor.y) == CellType::End) {
        memory[neighbor.y][neighbor.x].parent =
          &memory[current.y][current.x];
        found = true;
        break;
      }

      // Update the nodes type to match what's on the grid
      memory[neighbor.y][neighbor.x].type = CellType::Path;
      memory[neighbor.y][neighbor.x].visited = true;
      grid.set(neighbor.x, neighbor.y,
               CellType::Path); // Keep the grid up to date with path

      memory[neighbor.y][neighbor.x].parent =
          &memory[current.y][current.x]; // Set the parent of neighbor to
                                         // current (e.g. current <- neighbor)

      // Push neighbor to the queue to become the next processing current cell
      frontier.push(neighbor);
    }
  }
  if (found) {
    return;
  }
}

//Depth first search
void Algo::DFS() {
  if (!found) {
    sf::Vector2i neighbor, current;

    // If the starting and ending positions arent gathered yet get them
    if (!startingPos || !endingPos) {
      GetStartAndEnd();
      if (!startingPos || !endingPos) {
        return;
      }
      dfsFrontier.push(
          {startingPos->x, startingPos->y}); // Adding the starting coordinates
                                             // to the queue for processing
      memory[startingPos->y][startingPos->x].type = CellType::Start;
      memory[startingPos->y][startingPos->x].visited = true;
      memory[startingPos->y][startingPos->x].pos = *startingPos;
    }

    // Updating current with next coordinates to be processed from the queue
    // than popping the value since not needed
    if (dfsFrontier.empty()) {
      return;
    }
    current = dfsFrontier.top();
    dfsFrontier.pop();

    // Check neighboring celltypes from processing cell
    for (auto &move : movementsHz()) {
      neighbor = current; // Neighbor gets the current position for all
                          // movements to run equally

      // If not in bounds or neighbor celltype is a wall or the next move is
      // already visited than go onto the next movement
      if (!grid.inBounds(neighbor.x + move.front(), neighbor.y + move.back())             ||
          grid.get(neighbor.x + move.front(), neighbor.y + move.back()) == CellType::Wall ||
          memory[current.y + move.back()][current.x + move.front()].visited) { 
            
            continue; 
        }

      // Set the neighbors coordinates by adding to current's coords
      neighbor += {move.front(), move.back()};
    
      //Set the pos in the memory vector
      memory[neighbor.y][neighbor.x].pos = neighbor;

      // If neighbor reaches end
      if (grid.get(neighbor.x, neighbor.y) == CellType::End) {
        memory[neighbor.y][neighbor.x].parent =
          &memory[current.y][current.x];
        found = true;
        break;
      }

      // Update the nodes type to match what's on the grid
      memory[neighbor.y][neighbor.x].type = CellType::Path;
      memory[neighbor.y][neighbor.x].visited = true;
      grid.set(neighbor.x, neighbor.y,
               CellType::Path); // Keep the grid up to date with path

      memory[neighbor.y][neighbor.x].parent =
          &memory[current.y][current.x]; // Set the parent of neighbor to
                                         // current (e.g. current <- neighbor)

      // Push neighbor to the queue to become the next processing current cell
      dfsFrontier.push(neighbor);
    }
  }
  if (found) {
    return;
  }
}

// Gets the starting & ending position through traversing the grid
void Algo::GetStartAndEnd() {
  for (int y = 0; y < grid.getHeight(); y++) {
    for (int x = 0; x < grid.getWidth(); x++) {

      if (grid.get(x, y) == CellType::Start) {
        startingPos = {x, y};
      }

      else if (grid.get(x, y) == CellType::End) {
        endingPos = {x, y};
      }
    }
  }
}

void Algo::Trail() {
    if(endingPos) {
    //Start from the ending node
    Node *tempParent = &memory[endingPos->y][endingPos->x];
    //While the parent of the node starting from the end node isnt the start continue trailing back
    while (tempParent->parent->parent != nullptr) {
        //Temp parent becomes the next parent
        tempParent = tempParent->parent;
        //Update its type to trail
        tempParent->type = CellType::Trail;
        //Update the grid type to trail
        grid.set(tempParent->pos.x, tempParent->pos.y, CellType::Trail);
    }
}
}

//Resest everything
void Algo::Reset() {
    // Reset the memory vector with new Nodes
    for(int y = 0; y < grid.getHeight(); y ++) {
        for(int x = 0; x < grid.getWidth(); x++) {
            memory[y][x] = Node();
        }
    }

    // Reset the starting and ending positions
    startingPos.reset();
    endingPos.reset();

    //Clear the queue
    while (!frontier.empty()) {
        frontier.pop();
    }

    found = true;
}
