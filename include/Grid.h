// What would be in grid?
// Size (x and y) 

//#include <array>
#pragma once

enum class CellType { Empty, Wall, Start, End, Path, Trail };

class Grid {
    private:
        static constexpr int WIDTH = 20;
        static constexpr int HEIGHT = 20;
        CellType cells[WIDTH][HEIGHT];

    public:
        Grid(); // Fills everything with empty

        int getWidth() const;
        int getHeight() const;

        CellType get(int x, int y) const;
        void set(int x, int y, CellType type);

        bool inBounds(int x, int y) const;
};