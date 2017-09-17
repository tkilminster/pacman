//
// Created by teekay on 03/01/17.
//

#ifndef COURSEWORK_PACMAN_H
#define COURSEWORK_PACMAN_H

int pacTick = 0;

extern int score;
extern int pills;
extern int deathTick;
extern bool dead;
extern int eatenCount;
extern int fruitCounter;

bool begin = true;

typedef enum {LEFT, UP, RIGHT, DOWN, NONE} direction;

class Pacman
{
public:
    float pacmanX;
    float pacmanY;
    direction currentDir;
    direction dirStore;
    float angle;


    /**
     * Upon initialisation of pacman set his X and Y directions. Also set the current direction and the stored direction to NONE as he is stationary
     */
    Pacman()
    {
        pacmanX = 13.5f;
        pacmanY =  7.0f;
        currentDir = NONE;
        dirStore = NONE;
    }

    /**
     * Draw pacman relative to his current X and Y positions
     */
    void draw()
    {
        glPushMatrix();

        unsigned int pac_tex;
        int tickDiv;

        if(!dead) {
            tickDiv = pacTick % 30;
        }
        if(currentDir == NONE) {
            tickDiv = 0;
        }
        if(gameTick < 250) { // If the game is not in BEGIN mode
            pac_tex = pac_2_tex;
        } else {
            if (tickDiv % 30 < 10) {
                pac_tex = pac_0_tex;
            } else if (tickDiv % 30 < 20) {
                pac_tex = pac_1_tex;
            } else {
                pac_tex = pac_2_tex;
            }
        }

        switch(currentDir){ // Rotates pacman to face in his current travel direction
            case LEFT: angle = 0.0f;
                break;
            case UP: angle = 270.0f;
                break;
            case RIGHT: angle = 180.0f;
                break;
            case DOWN: angle = 90.0f;
                break;
            default: currentDir = NONE;
        }

        translateBottomLeft(); // Translate to bottom left of screen which is (0,0)
        translateToMazeCoords(pacmanX, pacmanY);

        glTranslatef(-3.0f, -3.0f, 0.0f); // Translate to take into account pacmans size

        drawTex(pac_tex, 14, 14, angle);

        glPopMatrix();

        pacTick++;

    }

    /**
     * Reset all of pacmans variables to that when he is initiliased
     */
    void reset()
    {
        pacmanX = 13.5f;
        pacmanY =  7.0f;
        currentDir = NONE;
        dirStore = NONE;
        angle = 0.0f;
        begin = true;
        dead = false;
        eatenCount = 0;
    }

    /**
     * Applying death animation and translating pacman to correct area upon death due to ghost encounter
     */
    void death()
    {
        glPushMatrix();

        unsigned int pac_tex;


        if (deathTick < 10) {                   // Depending on the deathTick, assign the corresponding death sprite
            pac_tex = dead_0_tex;
        } else if (deathTick % 110 < 20) {
            pac_tex = dead_1_tex;
        } else if (deathTick % 110 < 30) {
            pac_tex = dead_2_tex;
        } else if (deathTick % 110 < 40) {
            pac_tex = dead_3_tex;
        } else if (deathTick % 110 < 50) {
            pac_tex = dead_4_tex;
        } else if (deathTick % 110 < 60) {
            pac_tex = dead_5_tex;
        } else if (deathTick % 110 < 70) {
            pac_tex = dead_6_tex;
        } else if (deathTick % 110 < 80) {
            pac_tex = dead_7_tex;
        } else if (deathTick % 110 < 90) {
            pac_tex = dead_8_tex;
        } else if (deathTick % 110 < 100) {
            pac_tex = dead_9_tex;
        } else {
            pac_tex = dead_10_tex;
        }

        translateBottomLeft();  // Translate to bottom left of screen which is (0,0)
        translateToMazeCoords(pacmanX, pacmanY);

        glTranslatef(-3.0f, -3.0f, 0.0f);

        drawTex(pac_tex, 14, 14, 0);

        glPopMatrix();


    }

    /**
     * Method called to check pacmans current position and, if present, eat the pill occupying that tile or translate him to other portal
     */
    void checkTile()
    {
        switch(getTile(pacmanX, pacmanY)) {
            case o:                                                     // If pacman is on a small pill, increment score accordingly and remove it from the map
                maze[(int) floor(pacmanX)][(int) floor(pacmanY)] = e;
                score += 10;
                pills--;
                break;
            case O:                                                     // If pacman is on a large pill, increment score accordingly and remove it from the map
                maze[(int) floor(pacmanX)][(int) floor(pacmanY)] = E;
                score += 50;
                pills--;
                break;
            case P:
                if (getPacX() >=
                    26.5) {                             // If pacman is on a portal tile, translate his position to the other side of the map
                    pacmanX = 1.0f;
                } else {
                    pacmanX = 26.5f;
                }
                break;
            case F:                                     // If pacman is on a fruit, increment score accordingly and remove it from the map
                maze[(int) floor(pacmanX)][(int) floor(pacmanY)] = e;
                fruitCounter++; // Increment counter for fruits eaten
                if(fruitCounter == 1) { // Determine how much to increment the score by
                    score += 100;
                } else {
                    score += 300;
                }

        }
    }

    /**
     * Return pacmans x position
     * @return pacmans X coordinate
     */
    int getPacX()
    {
        return (int)floor(pacmanX);
    }

    /**
     * Return pacmans y position
     * @return pacmsn Y coordinate
     */
    int getPacY()
    {
        return (int)floor(pacmanY);
    }

    /**
     * Returns the type of type pacmans is in
     * @return The tile type that pacman is currently occupying
     */
    tile getTile(float x, float y)
    {
        return maze[(int)floor(x)][(int)floor(y)];
    }

    /**
     * Checks what the tile type is one ahead of pacman in the direction specified
     * @param dir direction to check the tile of
     * @return the tile type in the direction specified
     */
    tile getFollowingTile(direction dir)
    {
        switch(dir) {
            case LEFT: return getTile(getPacX() - 1, getPacY());
            case UP: return getTile(getPacX(), getPacY() + 1);
            case RIGHT: return getTile(getPacX() +1, getPacY());
            case DOWN: return getTile(getPacX(), getPacY() - 1);
            default: return getTile(getPacX(), getPacY());
        }
    }

    /**
     * Checks if pacman is in the center of his current tile
     * @return true or false depending on if he is in the centre
     */
    bool isAtCenter()
    {
        return (int)(pacmanY * 10.0f) % 10 == 0 && (int)(pacmanX * 10.0f) % 10 == 0;
    }

    /**
     * Used to pass the user pressed direction to the dirStore variable for later use
     * @param pressedDir The direction the user has pressed
     */
    void setDirStore(direction pressedDir)
    {
        dirStore = pressedDir;
    }

    /**
     * Checks if the tile in the specified direction is a wall
     * @param dir The direction to check
     * @return true or false depending on if it is a wal
     */
    bool isWall(direction dir)
    {
        if (getFollowingTile(dir) == W || getFollowingTile(dir) == G) {
            return true;
        }

        return false;
    }

    /**
     * Checks what pacmans current direction is set as and translates accordingly
     * Furthermore, will not move pacman if his next tile in his current direction is a wall.
     *
     * Also checks to see if the last pressed direction button from the user will cause pacman to face a wall, if it does not
     * move pacman in that direction.
     */
    void move()
    {
        if(isAtCenter()) { // Only move if pacman is at the centre of the tile
            if (!isWall(dirStore)) { // If the direction pacman wants to go in is not a wall, set that direction
                currentDir = dirStore;
            } else if (isWall(currentDir)) {
                currentDir = NONE; // If the direction pacman wants to travel in is a wall and the direction he is currently travelling is a wall, stop his movement
            }
        }
        if(!isAtCenter() && dirStore != NONE && begin && !isWall(dirStore)){ // Check to not cause pacman to jump at the very beginning of the game
            currentDir = dirStore;
            begin = false;
        }

        switch (currentDir) {
            case LEFT:
                pacmanX -= 0.1f;
                pacmanY = round(pacmanY);
                break;
            case UP:
                pacmanY += 0.1f;
                pacmanX = round(pacmanX);
                break;
            case RIGHT:
                pacmanX += 0.1f;
                pacmanY = round(pacmanY);
                break;
            case DOWN:
                pacmanY -= 0.1f;
                pacmanX = round(pacmanX);
                break;
            default:
                if(!begin) { // Do not round pacman if it is the very start as he begin between two tiles
                    pacmanX = round(pacmanX);
                    pacmanY = round(pacmanY);
                }
        }
    }
};

#endif //COURSEWORK_PACMAN_H
