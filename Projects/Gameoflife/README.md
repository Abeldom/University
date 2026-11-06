# Conway's Game of Life

This Processing sketch simulates Conway's Game of Life on an 800 × 800 canvas. The canvas is divided into 20-pixel cells, creating a 40 × 40 grid. White cells are alive, and black cells are dead.

## Rules

Each generation updates based on the eight neighboring cells:

- A live cell survives with two or three live neighbors.
- A live cell with fewer than two or more than three live neighbors dies.
- A dead cell with exactly three live neighbors becomes alive.

## Run the sketch

Open `gameoflife.pde` in Processing and click **Run**.

## Screenshots

![Game of Life running in Processing](Screenshot%202026-11-06%20163230.png)

## Demo video

[Watch the Game of Life demo](gameoflife%202026-11-06%2016-32-57.mp4)

## Try a demo

1. Click cells in the grid to create an initial pattern. For example, make a line of three adjacent live cells.
2. Press **Space** to start the simulation. The three-cell line should alternate between horizontal and vertical as it evolves.
3. Press **Space** again to pause, then click cells to edit the pattern.
4. Press **Enter** to clear the grid and start over.

Any key other than **Enter** toggles the simulation, not just Space. The outermost row and column stay at the boundary and are not updated.
