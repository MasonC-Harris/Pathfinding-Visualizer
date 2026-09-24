#pragma once

#include "Grid.h"
#include <SFML/System/Vector2.hpp>

struct Node {

        sf::Vector2i pos;

        CellType type;

        Node* parent = nullptr;

        bool visited = false;

        Node();
    
};