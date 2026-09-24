//Render the Window
//Display Grid
//Color Change for respective cell type
//Click to add start, end, and walls
#pragma once

#include "Grid.h" // Builds off Grid
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Algo.h>
//#include <SFML/Graphics/RenderWindow.hpp>

//enum class color { White, Black, Green, Red, Blue };

class Application {
    private:
    Grid grid;
    sf::RenderWindow window;
    sf::RectangleShape rect;

    Algo algo;

    float mouseX, mouseY;

    bool draggingL = false, draggingR = false, inBounds, ctrl = false, clearGrid = false, bfs = false, dfs = false, dk = false;

    public:
        Application(); // Create the Window

        
        void run();


        void event();

        void render();
        void drawGrid();
        void drawWall();
        void drawStart();
        void drawEnd();
        void getMouseCoords();


        void reset();

        void clearPath();


        //bool mouseBounds(int x, int y) const;

};