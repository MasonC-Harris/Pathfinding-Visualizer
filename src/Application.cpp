#include "Application.h"
#include "Algo.h"
#include "Grid.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
//#include <format>
#include <iostream>
//#include <iterator>
#include <optional>
#include <ostream>
//#include <string>

Application::Application() : window(sf::VideoMode({
    (unsigned int)grid.getWidth() * 50,                             //Initialize window
    (unsigned int)grid.getHeight() * 50}), "Pathfinder"), algo(grid){}

void Application::run(){                // Event handling, and drawing
    while(window.isOpen()) {

        event();  //Event Handling

        render(); //Drawing

        window.display();
    }
}

void Application::event() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {                      //Closing Window
            window.close();
        }
        
                        //Makes sure mouse is in the window
        if (const auto* mouseInBounds = event->getIf<sf::Event::MouseEntered>()) {
            inBounds = true;
        }
        else if (const auto* mouseInBounds = event->getIf<sf::Event::MouseLeft>()) {
            inBounds = false;
        }

                        //Keyboard Ctrl Pressed
        if (const auto* keyButtonPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyButtonPressed->scancode == sf::Keyboard::Scancode::LControl) {
                std::cout << "ctrl on" << std::endl;
                ctrl = true;
            }
        }
                        //Keyboard Ctrl Released
        else if (const auto* keyButtonReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyButtonReleased->scancode == sf::Keyboard::Scancode::LControl) {
                std::cout << "ctrl off" << std::endl;
                ctrl = false;
            }
        }
                        //Mouse Clicked
        if (const auto* mouseButtonPressed  = event->getIf<sf::Event::MouseButtonPressed>()) {    
            if(mouseButtonPressed->button == sf::Mouse::Button::Left) {         //Left Click
                draggingL = true;
            }
            else if(mouseButtonPressed->button == sf::Mouse::Button::Right) {        //Right Click
                draggingR = true;
            }
        }
                        //Mouse Released
        else if (const auto* mouseButtonReleased  = event->getIf<sf::Event::MouseButtonReleased>()) {   
            if (mouseButtonReleased->button == sf::Mouse::Button::Left) {        //Left Click
                draggingL = false;
            }
            else if (mouseButtonReleased->button == sf::Mouse::Button::Right) {       //Right Click
                draggingR = false;
            }
        }
                    //Space Pressed
        if (const auto* spaceButtonPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (spaceButtonPressed->scancode == sf::Keyboard::Scancode::Space) {
                clearGrid = true;
            }
        }
                    //Space Released
        if (const auto* spaceButtonReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (spaceButtonReleased->scancode == sf::Keyboard::Scancode::Space) {
                clearGrid = false;
            }
        }
                    //1 Pressed
        if (const auto* oneButtonPressed = event->getIf<sf::Event::KeyPressed>()) {
            if(oneButtonPressed->scancode == sf::Keyboard::Scancode::Num1) {
                bfs = true;
            }
        }

                    //2 Pressed
        if (const auto* twoButtonPressed = event->getIf<sf::Event::KeyPressed>()) {
            if(twoButtonPressed->scancode == sf::Keyboard::Scancode::Num2) {
                dfs = true;
            }
        }
        
    }
}

//Draws everything
void Application::render() {
    drawGrid();
    drawWall();
    drawStart();
    drawEnd();
    reset();
    clearPath();

    //If breadth first search is requested and the path hasnt been found yet than run the algorithm frame by frame
    if (bfs && !algo.found) {
        algo.BFS();
    }

    if (dfs && !algo.found) {
        algo.DFS();
    }

    //If the path has been found than show the trail and set everything to false
    if(algo.found) {
        algo.Trail();
        bfs = false;
        dfs = false;
        dk = false;
        algo.found = false;
    }
    
}

void Application::drawGrid() {
    //Drawing squares for grid
    for(int y = 0; y < grid.getHeight(); y++){
        for(int x = 0; x < grid.getWidth(); x++){
            rect.setPosition(sf::Vector2f {x * 50.f, y * 50.f});
            rect.setSize(sf::Vector2f {50.f, 50.f});
            rect.setOutlineThickness(float {1.f});
            rect.setOutlineColor(sf::Color::Black);

            // Sets the color of the cell type for drawing
            switch (grid.get(x, y)) {
                case CellType::Empty: rect.setFillColor(sf::Color::White); break;
                case CellType::Wall: rect.setFillColor(sf::Color::Black);  break;
                case CellType::Start: rect.setFillColor(sf::Color::Green); break;
                case CellType::End: rect.setFillColor(sf::Color::Red);     break;
                case CellType::Path: rect.setFillColor(sf::Color::Cyan);   break;
                case CellType::Trail: rect.setFillColor(sf::Color::Yellow);   break;
            }

            window.draw(rect);
            
        }
    }
}

void Application::drawWall() {

    //Draws the wall
    if(inBounds && draggingL && !ctrl) {
        getMouseCoords();
        
        if (inBounds) {
            grid.set(mouseX/50, mouseY/50, CellType::Wall);
        }
    }
    //Erases the cell (makes cell empty)
    if(inBounds && draggingR && !ctrl) {
        getMouseCoords();

        if (inBounds) {
            grid.set(mouseX/50, mouseY/50, CellType::Empty);
        }
    }
}

void Application::drawStart() {
    getMouseCoords();

    if (inBounds && draggingL && ctrl) {
        grid.set(mouseX/50, mouseY/50, CellType::Start);
    }
}

void Application::drawEnd() {
    getMouseCoords();

    if (inBounds && draggingR && ctrl) {
        grid.set(mouseX/50, mouseY/50, CellType::End);
    }
}

void Application::getMouseCoords() {
    mouseX = sf::Mouse::getPosition(window).x;
    mouseY = sf::Mouse::getPosition(window).y;
}

void Application::reset() {
    //If space and ctrl is pressed than clear the grid
    if (clearGrid && ctrl) {
        std::cout << "cleared";
        grid = Grid();
        algo.Reset();
    }
}

void Application::clearPath() {
    //If space is pressed than clear the path (set path cell to empty)
    if (clearGrid) { 
        for(int x = 0; x < grid.getWidth(); x++ ) {
            for (int y = 0; y < grid.getHeight(); y++) {
                if(grid.get(x, y) == CellType::Path || grid.get(x, y) == CellType::Trail)
                    grid.set(x, y, CellType::Empty);
            }
        }
        algo.Reset();
    }
}