# Pathfinding Visualizer by Mason Harris

A C++ pathfinding visualizer built from scratch to demonstrate my algorithmic understanding, clean architecture, and strong grasp of C++ fundamentals.

## Controls
Pressing 1 will run breadth first search
Pressing 2 will run depth first search
Spacebar will clear the path
Ctrl Spacebar will clear the grid
Ctrl Left/Right Click will place a starting/ending point (Dont place more than one each)
Left Click places a wall
Right Click makes a grid cell empty

## Tech Stack

- **C++**
- C++23
- CMake
- SFML 3

## Planned Features

- [X] Interactive grid (draw walls, set start/end)
- [X] Step-by-step algorithm visualization
- [ ] A* pathfinding
- [ ] Dijkstra's algorithm
- [X] BFS / DFS 
- [ ] Adjustable grid size and animation speed

## Getting Started

### Prerequisites

- Windows 10 or newer
- CMake 3.28 or newer
- A C++23 compiler (developed with MinGW-w64 UCRT GCC 15.2)
- Git

**SFML does not need to be installed.** CMake fetches SFML 3.1.0 from source
during configure and builds it with the same compiler as the project, so there
is no version mismatch, nothing to add to `PATH`, and no DLLs to copy.

### Build & Run

From the project root:

```powershell
cmake -S . -B build
cmake --build build
```

The first configure clones and compiles SFML and its dependencies, so it takes
a few minutes. Later builds reuse that work and are fast.

Run:

```powershell
.\build\PathfindingVisualizer.exe
```

SFML and the MinGW runtime are linked statically, so the resulting `.exe` is
self-contained and runs without any accompanying DLLs.

## My Journey

Has been a real struggle but I'm glad because without it than there wouldnt have been any real learning involved.
Getting the grid up took me some real effort because reading the documentation, figuring out what I need, all took 
some time. I originally planned to build this with no AI assistance, but partway through I changed my rule to serve
me better. I could use AI but as a tutor, not something that would do things for me. I found this as a real challenge 
that would be too time consuming to do all my own for something so simple.

To get better use out of my time I thought I would try on everything myself first, and if I was struggling for ~20-30 
minutes on something then I would ask AI for a hint or to point me in the right direction. For example when I got stuck 
first using SFML for generating the grid I asked it where in the documentation should I look to find what I'm after. 
I also got stuck up on references and why a reference needs to be bound at construction and cant be reassigned later.
Than if I was absolutley stuck after continuous trial then I would ask it to walk me through the concept from the 
ground up rather than just answer the specific question I asked since a few times the question I was asking wasnt
even the right question. This happened for example when I was trying to implement a queue for my node memory and 
why using a flat vector was the wrong idea since I needed a way to work with updating nodes and a way to store this 
node memory. 

When I was debugging sometimes I had to trace things out by hand to understand, for example I realized that I had 
my axis swapped between my grid and my node memory; I solved this by picking a move value ({-1, 0}, "left") and  
solving what the expression actually evaluates to, than I saw that it was computing the cell above current instead
of the cell to its left. I found myself constantly on paper mapping out how my algorithms worked such as breadth 
first search needing a current position as a fixed position to check the different movements against (neighbor), 
the updated left, right, up, down displacements. At one point during testing I found a solution that 
bested the explanation of what the AI was telling me which was how I would stop the algorithm from running when I 
wanted to reset the path. I did this by following what sequence of if blocks get triggered to see what gaurds made
the scheme safe which is what the AI had gotten backwards because it didnt tace the frame sequence itself.

After this project I can say that I learned a bit more about modularity for example including a file in multiple 
places would cause multiple instances and that #pragma once made it so the other times a file is referenced it would 
get silently skipped over. I got a refresher on reference semantics and how a reference binds once at construction 
and can never be reseated, I had a few problems with this during the use of my grid and algorithm objects when I 
didn't understand why couldnt just declare it and use it. I learned a bit about SFML and its graphics generation
along with SFML's window events (e.g. buttons pressed, mouse clicking). I used some different templates and libraries 
such as std::ranges, std::optional, and the algorithm library for the first time after finishing the book 
Mastering STL in C++23: New Features Updates, and Best Practices. I learned about some different concepts such as
enums and structs which I haven't used before. 

I feel that I improved at designing by thinking about and mapping what my application would need ahead of time and the 
finer details that specific parts could have before implementation such as what in general would my application do, 
what parts should have specific variables and functions. Down the line as I got deeper in the project I still found pieces 
that I should have included and missed or skipped earlier which helped me find why planning before even beginning is so 
important for a project. This has been my first project that I've dug into documentation, reading about the new things 
that I may use and I've learned that being able to read, understand, and incorporate documentation into the codebase is 
a skill itself. Not only was this a great learning opportunity, but a great refresher over all and Im excited to keep 
learning and do new things in the future.

If I were to continue this project, I would fix bugs such as the continuation of pressing a button that triggers an 
algorithm would do nothing when the path has been found. I would implement more algorithms such as A* and Dijkstra. 
I would also look into more advanced code and attempt to improve what I currently have.


## License

MIT — see [LICENSE](LICENSE).
