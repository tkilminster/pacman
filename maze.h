/**
 * Header file responsible for storing and drawing the game map.
 *
 */

#ifndef COURSEWORK_MAZE_H
#define COURSEWORK_MAZE_H

extern unsigned int maze_tex;
extern unsigned int pill_tex;
extern unsigned int bigPill_tex;
extern int gameTick;
extern int fruitSpawned;
extern int fruitCounter;

/**
 * Tile defined as an enum where each type is defined as:
 *      W: Wall
 *      G: Ghost Pen Gate
 *      P: Portal
 *      u: Empty path
 *      o: Pill
 *      e: Eaten Pill
 *      O: Big Pill
 *      E: Eaten Big Pill
 */
typedef enum {W, G, P, u, o, e, O, E, F} tile;

// 2D array defines the size of the maze and also what each tile contains
tile maze[28][31] =
        {
                {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W},
                {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W}
        };

/**
 *
 * Translates objects x and y coordinates into translatable values to be placed on the maze
 *
 * @param x objects current X coordinate
 * @param y objects current Y coordinate
 * @param angle objects current facing
 */
void translateToMazeCoords(float x, float y)
{
    glTranslatef(x * 8, y * 8, 0.0f);
}

/**
 * Translates the current position of drawing to the bottom left corner of the map.
 */
void translateBottomLeft()
{
    glTranslatef(38.0f, 26.0f, 0.0f);
}

/**
 * Returns the type of tile at a specified coordinate
 * @param x the x coordinate specified
 * @param y the y coordinate specified
 * @return the tile type at the coordinate
 */
tile getTile(float x, float y)
{
    return maze[(int) floor(x)][(int) floor(y)];
}

/**
 * Draw the score that appears when a afruit is eaten
 * @param x the x coordinate of the fruit
 * @param y the y coordinate of the fruit
 */
void eatFruitScore(int x, int y)
{
    glPushMatrix();


    unsigned int eat_score_tex;

    switch(fruitCounter) { // Pick which texture to draw depending on which number fruit is being eaten
        case 1: eat_score_tex = score_100_tex;
            break;
        case 2: eat_score_tex = score_300_tex;
            break;
    }

    translateBottomLeft();
    translateToMazeCoords(x, y); // Translate to correct part of the screen for drawing
    glTranslatef(-2.0f, 0.0f, 0.0f);

    if(fruitCounter != 0) { // Only draw the fruit score if the fruit has been eaten
        drawTex(eat_score_tex, 15, 8, 0);
    }

    glPopMatrix();
}

/**
 * Iterates through the maze to set any fruits back to an empty tile if pacman dies
 */
void fruitReset()
{
    for(int x=0;x<28;x++) {            // Iterate through the maze
        for(int y=0;y<31;y++) {
            switch(maze[x][y]) {
                case F:
                    maze[x][y] = e; // If a fruit tile is found reset it
                    break;
            }
        }
    }
}

/**
 * Determine where to spawn a fruit by randomly selecting a tile in the lower porition of the maze
 * Validate the x and y position by making sure they are of tile type e. If they are not, select the
 * x and y coordinates and try again
 */
void locationFruit()
{
    int x, y;
    do {
        x = rand() % 27;
        y = rand() % 12;
    } while(getTile(x, y) != e);

    maze[(int) floor(x)][(int) floor(y)] = F; // Set the new tile type to be F
    fruitSpawned++; // Increment counter
}

/**
 * Method to draw the fruit texture
 */
void drawFruit()
{
    glTranslatef(-2.0f, -2.0f, 0.0f); // Encountered bug(?) where putting a push and pop matrix here would cause a black seen therefore I had to translate and
                                        // Reverse the translation at the end of the method
    if(fruitCounter == 0) { // Determine which texture to draw
        drawTex(cherry_tex, 14, 14, 0);
    } else {
        drawTex(strawberry_tex, 14, 14, 0);
    }
    glTranslatef(2.0f, 2.0f, 0.0f); // Reverse translation
}

/**
 * Iterates through the map array, drawing all pills. Also draws map as a sprite.
 */
void drawMaze()
{
    glPushMatrix();

    translateBottomLeft();              // Translate to bottom left of screen
    drawTex(maze_tex, 224, 248, 0);     // Draw the map walls using the sprite
    for(int x=0;x<28;x++) {             // Insert pills, big pills and fruits in the loop
        glPushMatrix();

        for(int y=0;y<31;y++) {
            switch(maze[x][y]) {
                case o:                 // Draw pills as sprites
                    drawTex(pill_tex, 8, 8, 0);
                    break;
                case O:                 // Draw big pills as sprites
                    if(gameTick % 30 <= 15) {
                        drawTex(bigPill_tex, 8, 8, 0);
                    }
                    break;
                case F:
                    drawFruit();
                    break;
            }

            glTranslatef(0.0f, 8.0f, 0.0f); // Increment Y position
        }
        glPopMatrix();

        glTranslatef(8.0f, 0.0f, 0.0f);     // Increment X position
    }
    glPopMatrix();
}

/**
 * Method to refill all pills in the maze that had previously been eaten. Used for when a new level begins.
 */
void resetMaze()
{
    for(int x=0;x<28;x++) {             // Loop populates map
        for (int y = 0; y < 31; y++) {
            switch (maze[x][y]) {
                case e:                 // Draw pills as sprites
                    maze[x][y] = o;
                    break;
                case E:                 // Draw big pills as sprites
                    maze[x][y] = O;
                    break;
            }
        }
    }
}

#endif //COURSEWORK_MAP_H
