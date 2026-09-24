#include "Grid.h"
#include <ranges>
#include <algorithm>

Grid::Grid() {
    std::ranges::fill(cells | std::views::join, CellType::Empty); // Fills cells with Empty (default)
}

int Grid::getWidth() const {
    return WIDTH;
}

int Grid::getHeight() const {
    return HEIGHT;
}

CellType Grid::get(int x, int y) const {
    return cells[x][y];
}

void Grid::set(int x, int y, CellType type) {
    cells[x][y] = type;
}

bool Grid::inBounds(int x, int y) const {
    return x < WIDTH && x >= 0 && y < HEIGHT && y >= 0;
}