//
// Created by teekay on 04/01/17.
//

#ifndef COURSEWORK_GHOST_H
#define COURSEWORK_GHOST_H


extern int gameTick;
extern Pacman pacman;
extern bool frighten;
extern int eatenCount;

typedef enum {SCATTER, CHASE, FRIGHTEN, LEAVE, DEATH, PEN} movement;

typedef enum {RED, BLUE, PINK, YELLOW} colour;
direction tempDir = NONE;

class Ghost {
public:
    float ghostX;
    float ghostY;
    direction currentDir;
    colour ghostColour;
    movement moveType;
    float speed;
    bool eaten;

    /**
     *
     * @param x set the ghosts x position
     * @param y set the ghosts y position
     * @param ghost set the colour of the ghost
     */
    Ghost(float x, float y, colour ghost) {
        ghostX = x;
        ghostY = y;
        switch (ghost) {
            case RED:
                currentDir = LEFT;
                moveType = SCATTER;
                break;
            case PINK:
                currentDir = DOWN;
                moveType = PEN;
                break;
            case BLUE:
                currentDir = UP;
                moveType = PEN;
                break;
            case YELLOW:
                currentDir = UP;
                moveType = PEN;
                break;
        }
        eaten = false;
        ghostColour = ghost;
        setSpeed();
    }

    /**
     * Draws the score added to the game when pacman eats the ghost. Thie is drawn at the ghosts x and y position at the time of eating
     * and the score also depends on how many ghosts, if any, had been eaten before it
     * @param x the ghosts X position at the time of eating
     * @param y the ghosts y position at the time of eating
     */
    void drawEatScore(float x, float y)
    {
        glPushMatrix();



        unsigned int eat_score_tex;

        switch(eatenCount) { // Pick which texture to draw depending on which number ghost is beign eaten
            case 1: eat_score_tex = score_200_tex;
                break;
            case 2: eat_score_tex = score_400_tex;
                break;
            case 3: eat_score_tex = score_800_tex;
                break;
            case 4: eat_score_tex = score_1600_tex;
                break;
        }

        translateBottomLeft();
        translateToMazeCoords(x, y); // Translate to correct part of the screen for drawing
        glTranslatef(-2.0f, 0.0f, 0.0f);

        if(eatenCount != 0) { // Only draw if a ghost has been eaten
            drawTex(eat_score_tex, 10, 8, 0);
        }

        glPopMatrix();
    }

    /**
     * Method to draw the ghost with the correct texture and the eyes facing the correct direction.
     */
    void draw() {
        glPushMatrix();

        unsigned int ghost_tex;
        unsigned int ghost_eye_tex;

        if (moveType != FRIGHTEN && moveType != DEATH) { // As long as the ghost is not in death or frighten mode, assign its relevant texture
            int tickDiv = gameTick % 20;
            if (tickDiv % 20 < 10) {
                switch (ghostColour) { // Check ghost colour in order to determine which tex file to use
                    case RED:
                        ghost_tex = ghost_r_0_tex;
                        break;
                    case BLUE:
                        ghost_tex = ghost_b_0_tex;
                        break;
                    case PINK:
                        ghost_tex = ghost_p_0_tex;
                        break;
                    case YELLOW:
                        ghost_tex = ghost_y_0_tex;
                        break;
                }
            } else {
                switch (ghostColour) {
                    case RED:
                        ghost_tex = ghost_r_1_tex;
                        break;
                    case BLUE:
                        ghost_tex = ghost_b_1_tex;
                        break;
                    case PINK:
                        ghost_tex = ghost_p_1_tex;
                        break;
                    case YELLOW:
                        ghost_tex = ghost_y_1_tex;
                        break;
                }
            }

            switch (currentDir) { // Eye position/tex file is dependent on direction the ghost is moving
                case LEFT:
                    ghost_eye_tex = eye_left_tex;
                    break;
                case UP:
                    ghost_eye_tex = eye_up_tex;
                    break;
                case RIGHT:
                    ghost_eye_tex = eye_right_tex;
                    break;
                case DOWN:
                    ghost_eye_tex = eye_down_tex;
                    break;
            }
        } else if(moveType == FRIGHTEN){ // If the ghost is frightened assign its relevant texture
            int tickDiv = gameTick % 40;
            if (tickDiv % 40 < 10) {
                ghost_tex = ghost_scared_0_tex;
            } else if (tickDiv % 40 < 20) {
                ghost_tex = ghost_scared_1_tex;
            } else if (tickDiv % 40 < 30) {
                ghost_tex = ghost_scared_2_tex;
            } else {
                ghost_tex = ghost_scared_3_tex;
            }
        } else  if(moveType == DEATH) {
            switch (currentDir) { // Eye position/tex file is dependent on direction the ghost is moving
                case LEFT:
                    ghost_eye_tex = eye_left_tex;
                    break;
                case UP:
                    ghost_eye_tex = eye_up_tex;
                    break;
                case RIGHT:
                    ghost_eye_tex = eye_right_tex;
                    break;
                case DOWN:
                    ghost_eye_tex = eye_down_tex;
                    break;
            }
        }


        translateBottomLeft(); // Translate to bottom left of screen
        translateToMazeCoords(ghostX, ghostY);

        glTranslatef(-3.0f, -3.0f, 0.0f);

        if(moveType != DEATH) { // If the ghost is not dead then draw its body texture
            drawTex(ghost_tex, 14, 14, 0);
        }

        if (moveType != FRIGHTEN) { // If the ghost is not frightened then draw the eye texture
            drawTex(ghost_eye_tex, 14, 14, 0);
        }

        glPopMatrix();

    }

    /**
     * Method to reset the ghosts to their initial settings/ positions when the game is restarted
     */
    void reset() {
        switch (ghostColour) { // Different settings depending on the colour of the ghost
            case RED:
                ghostX = 13.5f;
                ghostY = 19.0f;
                currentDir = LEFT;
                moveType = SCATTER;
                break;
            case BLUE:
                ghostX = 11.5f;
                ghostY = 16.0f;
                currentDir = UP;
                if (pills <= 163) {
                    moveType = LEAVE;
                } else {
                    moveType = PEN;
                }
                break;
            case YELLOW:
                ghostX = 15.5f;
                ghostY = 16.0f;
                currentDir = UP;
                if (pills <= 214) {
                    moveType = LEAVE;
                } else {
                    moveType = PEN;
                }
                break;
            case PINK:
                ghostX = 13.5f;
                ghostY = 16.0f;
                currentDir = DOWN;
                moveType = LEAVE;
                break;
        }
        eaten = false; // Upon reset no ghost has been eaten
    }

    /**
     * Method determines what mode ghosts are in, and sets the speed accordingly
     */
    void setSpeed() {
        if (moveType == FRIGHTEN) { // Move slower if frightened
            speed = 0.05f;
        } else {
            speed = 0.1f;
        }
    }

    /**
     * Method determines the colour of the ghost and assigns the relevant movement technique to each ghost
     * @param ghost Variable used if a ghost needs to potentially use another ghosts position in its movement tehcnique
     */
    void move(Ghost ghost) {
        setSpeed();
        switch (ghostColour) {
            case RED:
                redGhostMove(ghost);
                break;
            case BLUE:
                blueGhostMove(ghost);
                break;
            case PINK:
                pinkGhostMove(ghost);
                break;
            case YELLOW:
                yellowGhostMove(ghost);
                break;
        }
    }

    /**
     * Returns the ghosts current X position
     * @return ghosts X position
     */
    int getGhostX() {
        return (int) floor(ghostX);
    }

    /**
     * Returns the ghosts current X position
     * @return ghosts Y position
     */
    int getGhostY() {
        return (int) floor(ghostY);
    }

    /**
     * Returns the number of possible exits from the specified position
     * @param x the X position to check
     * @param y the Y position to check
     * @return the number of exits from the current position that arent walls
     */
    int checkJuncs(float x, float y) {
        int exit = 0;
        if (!isWall(LEFT)) { // Check all directions and if its not a wall in that direction, increment the counter
            exit++;
        }
        if (!isWall(UP)) {
            exit++;
        }
        if (!isWall(RIGHT)) {
            exit++;
        }
        if (!isWall(DOWN)) {
            exit++;
        }

        return exit;
    }

    /**
     * Returns the tile type at the specified coordinates
     * @param x X position of the tile to check
     * @param y Y position of the tile to check
     * @return The type of the tile at the specified coordinates
     */
    tile getTile(float x, float y) {
        return maze[(int) floor(x)][(int) floor(y)];
    }

    /**
     * Looks ahead one tile in the specified direction and returns that type of tile
     * @param dir The direction to look ahead in
     * @return The type of the tile at the specified position
     */
    tile getFollowingTile(direction dir) {
        switch (dir) {
            case LEFT:
                return getTile(getGhostX() - 1, getGhostY());
            case UP:
                return getTile(getGhostX(), getGhostY() + 1);
            case RIGHT:
                return getTile(getGhostX() + 1, getGhostY());
            case DOWN:
                return getTile(getGhostX(), getGhostY() - 1);
            default:
                return getTile(getGhostX(), getGhostY());
        }
    }

    /**
     * Returns a boolean on whether the ghost is currently at the centre of its tile
     * @return Whether it is at the centre of the tile
     */
    bool isAtCenter() {
        return (int) (ghostY * 10.0f) % 10 == 0 && (int) (ghostX * 10.0f) % 10 == 0;
    }

    /**
     *
     * @param x the given x position of a ghost
     * @param y the given y position of a ghost
     * @param ghostCol the ghost colour of the current ghost
     * @param ghost another ghost object as some ghosts need to use other ghosts in order to target their movement
     * @return returns the distance from the point given to the target tile
     */
    float getDistance(int x, int y, colour ghostCol, Ghost ghost) {
        std::vector<int> v = getTargetTile(ghostCol);
        int targetX = v.at(0);
        int targetY = v.at(1);

        if (ghostCol == BLUE && moveType == CHASE) {
            float tempX = ghost.getGhostX() - targetX;
            float tempY = ghost.getGhostY() - targetY;
            targetX = ghost.getGhostX() + 2 * tempX;
            targetY = ghost.getGhostY() + 2 * tempY;
        }

        return (sqrt(((targetX - x) * (targetX - x)) + ((targetY - y) * (targetY - y))));
    }

    /**
     * Method that handles when a ghost reaches a corner, which way it should turn
     */
    void cornerHandler() {
        if (isAtCenter()) { // Checks it is at the centre of its tile
            if (isWall(currentDir)) { // Checks whether if it were to keep moving in it current direction if it would hit a wall
                if (!isWall(LEFT) && currentDir != RIGHT) { // Checks its new direction wouldnt make it hit a wall AND that its not reversing direction
                    currentDir = LEFT;
                } else if (!isWall(UP) && currentDir != DOWN) {
                    currentDir = UP;
                } else if (!isWall(RIGHT) && currentDir != LEFT) {
                    currentDir = RIGHT;
                } else {
                    currentDir = DOWN;
                }
            }
        }
    }

    /**
     * Used to move ghosts back into the pen for the final move during the DEATH moveType.
     * Due to the fact that they see the ghost gate as a wall so the code moves them down until their X and Y coordinates satisfy
     * certain conditions and then their moveType is changed back to CHASE or SCATTER depending on the gameTick.
     */
    void moveToPen()
    {
        if (ghostX <= 13.55 && ghostX >= 13.45) { // Initially check they have the correct X coordinates
            if (ghostY >= 18.95f) { // If so move them up and out of the gate
                currentDir = DOWN;
            } else if (ghostY <= 17.0f){
                moveType = LEAVE;
            }
        } else { // If they dont have the correct x coordinates
            if (ghostX < 13.5f) { // Determine if they need to move left or right
                currentDir = RIGHT;
            } else if (ghostX > 13.5f) {
                currentDir = LEFT;
            }
        }
        // As on the final call to this method the moveType is changed they could still move 0.1f in a direciton when not needed, so necessary check for moveType
        switch (currentDir) {
            case LEFT:
                ghostX -= speed;
                break;
            case UP:
                ghostY += speed;
                break;
            case RIGHT:
                ghostX += speed;
                break;
            case DOWN:
                ghostY -= speed;
                break;
        }
    }

    /**
     * Sets the ghosts movement, dependent on colour, to take a route back to the ghost pen so that they can respawn and join the game again
     * @param colGhost The specified ghost colour
     * @param ghost Pass in a ghost object in case the chosen move technique must use another ghost to calculate where to move
     */
    void setDeath(colour colGhost, Ghost ghost)
    {
        float distance = 999.0f;
        bool move = true;
        if(ghostX <= 13.55 && ghostX >= 13.45 && ghostY >= 15.5f && ghostY <= 20.0f) {
            moveToPen();
        } else {
            if (checkJuncs(ghostX, ghostY) >= 3 && isAtCenter()) {
                if (currentDir != DOWN && !isOnlyWall(UP)) {
                    float d = getDistance(getGhostX(), getGhostY() + 1, colGhost, ghost);
                    if (d < distance) {
                        tempDir = UP;
                        distance = d;
                    }
                }
                if (currentDir != LEFT && !isOnlyWall(RIGHT)) {
                    float d = getDistance(getGhostX() + 1, getGhostY(), colGhost, ghost);
                    if (d < distance) {
                        tempDir = RIGHT;
                        distance = d;
                    }
                }
                if (currentDir != RIGHT && !isOnlyWall(LEFT)) {
                    float d = getDistance(getGhostX() - 1, getGhostY(), colGhost, ghost);
                    if (d < distance) {
                        tempDir = LEFT;
                        distance = d;
                    }
                }
                if (currentDir != UP && !isOnlyWall(DOWN)) {
                    float d = getDistance(getGhostX(), getGhostY() - 1, colGhost, ghost);
                    if (d < distance) {
                        tempDir = DOWN;
                        distance = d;
                    }
                }
                currentDir = tempDir;
            } else {
                cornerHandler();
            }

            if(move) {
                switch (currentDir) {
                    case LEFT:
                        ghostX -= speed;
                        ghostY = round(ghostY);
                        break;
                    case UP:
                        ghostY += speed;
                        ghostX = round(ghostX);
                        break;
                    case RIGHT:
                        ghostX += speed;
                        ghostY = round(ghostY);
                        break;
                    case DOWN:
                        ghostY -= speed;
                        ghostX = round(ghostX);
                        break;
                }
            }
        }


    };

    /**
     * Determines which direction to move by checking all potential moves around itself and comparing how close each
     * potential move will put it to the target tile. It then selects the move which puts it the closest to the
     * target tile
     * @param colGhost The colour of the current ghost
     * @param ghost Pass in a ghost object in case the chosen move technique must use another ghost to calculate where to move
     */
    void moveTargetTile(colour colGhost, Ghost ghost)
    {
        float distance = 999.0f;
        if (checkJuncs(ghostX, ghostY) >= 3 && isAtCenter()) {
            if (currentDir != DOWN && !isWall(UP)) {
                float d = getDistance(getGhostX(), getGhostY()+1, colGhost, ghost);
                if(d < distance){
                    tempDir = UP;
                    distance = d;
                }
            }
            if (currentDir != LEFT && !isWall(RIGHT)) {
                float d = getDistance(getGhostX()+1, getGhostY(), colGhost, ghost);
                if(d < distance){
                    tempDir = RIGHT;
                    distance = d;
                }
            }
            if (currentDir != RIGHT && !isWall(LEFT) ) {
                float d = getDistance(getGhostX()-1, getGhostY(), colGhost, ghost);
                if(d < distance){
                    tempDir = LEFT;
                    distance = d;
                }
            }
            if (currentDir != UP && !isWall(DOWN)) {
                float d = getDistance(getGhostX(), getGhostY()-1, colGhost, ghost);
                if(d < distance){
                    tempDir = DOWN;
                    distance = d;
                }
            }
            currentDir = tempDir;
        } else {
            cornerHandler();
        }


        switch (currentDir) {
            case LEFT:
                ghostX -= speed;
                ghostY = round(ghostY);
                break;
            case UP:
                ghostY += speed;
                ghostX = round(ghostX);
                break;
            case RIGHT:
                ghostX += speed;
                ghostY = round(ghostY);
                break;
            case DOWN:
                ghostY -= speed;
                ghostX = round(ghostX);
                break;
        }
    }

    /**
     * Sets the ghosts movement during FRIGHTEN. When initially called the ghost reverses direction and then at every junction
     * the ghost will pick a random direction to move in aslong as that chosen direction does not cause it to hit a wall or reverse.
     * It then calls its relevant corner handler to handle corners correctly.
     */
    void setFrighten()
    {
        direction chosenDir = NONE;
        if (checkJuncs(ghostX, ghostY) >= 3) { // If at a junction
            do {
                int randNum = rand() % checkJuncs(ghostX, ghostY) - 1; // Select a random number between 0 and 3
                if(randNum == 0 && currentDir != RIGHT) {
                    chosenDir = LEFT;
                } else if(randNum == 1 && currentDir != DOWN) {
                    chosenDir = UP;
                } else if(randNum == 2 && currentDir != LEFT) {
                    chosenDir = RIGHT;
                } else if(currentDir != UP){
                    chosenDir = DOWN;
                }
            } while (isWall(chosenDir) && currentDir != NONE); // Only select the direction if it is not in a wall and the ghost is currently moving
        } else {
            cornerHandler();
        }

        if(isAtCenter() && chosenDir != NONE) {
            if(!isWall(chosenDir)){
                currentDir = chosenDir; // Only apply chosen direction if the ghost is at its centre, the chosen direction is NONE and the chosen direciton doesnt take it into a wal
            }
        }


        switch (currentDir) { // Move ghost in its chosen direction incrementally according to its speed
            case LEFT:
                ghostX -= speed;
                ghostY = round(ghostY);
                break;
            case UP:
                ghostY += speed;
                ghostX = round(ghostX);
                break;
            case RIGHT:
                ghostX += speed;
                ghostY = round(ghostY);
                break;
            case DOWN:
                ghostY -= speed;
                ghostX = round(ghostX);
                break;
        }
    }

    /**
     * Determines what movement technique each ghost should take depending on its colour
     * @param col the colour of the ghost
     * @param ghost pass in a ghost object in case the chosen move technique must use another ghost to calculate where to move
     */
    void setMove(colour col, Ghost ghost)
    {
        float distance = getDistance(ghostX, ghostY, RED, ghost); // Get the distance between the ghost and pacman
        switch(col) {
            case RED:
                moveTargetTile(RED, ghost);
                break;
            case PINK:
                moveTargetTile(RED, ghost);
                break;
            case YELLOW:
                if (distance >= 8.0f) { // Yellows movement switches depending on how close he is to pacman
                    moveTargetTile(RED, ghost);
                } else {
                    moveTargetTile(YELLOW, ghost);
                }
                break;
            case BLUE:
                moveTargetTile(BLUE, ghost);
                break;
        }
    }

    /**
     * Calls the correct method for movement depending on what the current MoveType of the ghost is.
     * @param ghost used for certain movement techniques for certain ghosts
     */
    void redGhostMove(Ghost ghost)
    {
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(RED, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(RED, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH:
                setDeath(RED, ghost);
                break;
            case LEAVE:
                leaveMove();
                break;
        }
    }

    /**
     * Calls the correct method for movement depending on what the current MoveType of the ghost is.
     * @param ghost used for certain movement techniques for certain ghosts
     */
    void blueGhostMove(Ghost ghost)
    {
        if(pills == 163){
            moveType = LEAVE;
        }
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(BLUE, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(BLUE, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH:
                setDeath(BLUE, ghost);
                break;
            case LEAVE:
                leaveMove();
                break;
            case PEN: penMove();
                break;
        }
    }

    /**
     * Calls the correct method for movement depending on what the current MoveType of the ghost is.
     * @param ghost used for certain movement techniques for certain ghosts
     */
    void yellowGhostMove(Ghost ghost)
    {
        if(pills == 214){
            moveType = LEAVE;
        }
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(YELLOW, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(YELLOW, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH: setDeath(YELLOW, ghost);
                break;
            case LEAVE: leaveMove();
                break;
            case PEN: penMove();
                break;
        }
    }

    /**
     * Calls the correct method for movement depending on what the current MoveType of the ghost is.
     * @param ghost used for certain movement techniques for certain ghosts
     */
    void pinkGhostMove(Ghost ghost)
    {
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(PINK, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(PINK, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH: setDeath(PINK, ghost);
                break;
            case LEAVE: leaveMove();
                break;
            case PEN: penMove();
                break;
        }
    }

    /**
     * Boolean function which returns if the next tile in the ghosts direction is a wall
     * @param dir the ghosts current direction
     * @return boolean value which is true if it is a wall in front of the ghost
     */
    bool isWall(direction dir)
    {
        if (getFollowingTile(dir) == W || getFollowingTile(dir) == G) {
            return true;
        }

        return false;
    }

    /**
     * Boolean function which returns if the next tile in the ghosts direction is a wall (not including ghost gate)
     * @param dir the ghosts current direction
     * @return boolean value which is true if it is a wall in front of the ghost
     */
    bool isOnlyWall(direction dir)
    {
        if (getFollowingTile(dir) == W) {
            return true;
        }

        return false;
    }

    /**
     * Moves the ghosts up and down inside the ghost pen until they are told to leave
     */
    void penMove()
    {
        if(ghostY <= 15.5f && currentDir == DOWN) {
            if(ghostColour == PINK && moveType == PEN) {
                moveType = LEAVE;
            } else {
                currentDir = UP;
            }
        } else if(ghostY >= 16.5f && currentDir == UP) {
            currentDir = DOWN;
        }

        switch (currentDir) {
            case UP:
                ghostY += speed;
                break;
            case DOWN:
                ghostY -= speed;
                break;
        }
    }

    /**
     * Checks whether the ghost is currently on a portal tile. If they are, translate them to the other side of the maze respectively
     */
    void portalCheck()
    {
        switch(getTile(ghostX, ghostY)){
            case P: if(getGhostX() >= 26.5) {
                        ghostX = 1.0f;
                    } else {
                        ghostX = 26.5;
                }
        }
    }

    /**
     * Method that allows the ghosts to move from the ghost pen and enter the maze, no matter where in the pen they are
     */
    void leaveMove()
    {
        if (ghostX <= 13.55 && ghostX >= 13.45) { // Initially check they have the correct X coordinates
            if (ghostY < 19.0f) { // If so move them up and out of the gate
                currentDir = UP;
            }
        } else { // If they dont have the correct x coordinates
            if (ghostX < 13.5f) { // Determine if they need to move left or right
                currentDir = RIGHT;
            } else if (ghostX > 13.5f) {
                currentDir = LEFT;
            }
        }

        if(ghostY >= 19.0f) {
            currentDir = LEFT;
            if(isAtCenter()){
                moveType = SCATTER;
            }
        }

        if(moveType == LEAVE) { // As on the final call to this method the moveType is changed they could still move 0.1f in a direciton when not needed, so necessary check for moveType
            switch (currentDir) {
                case LEFT:
                    ghostX -= speed;
                    break;
                case UP:
                    ghostY += speed;
                    break;
                case RIGHT:
                    ghostX += speed;
                    break;
                case DOWN:
                    ghostY -= speed;
                    break;
            }
        }
    }

    /**
     * Creates the vectors for the relevant target tiles depending on which mode the ghost is in and also what colour the ghost is
     * @param ghostCol the colour of the ghost
     * @return vector containing the x and y coordinate of the target tile
     */
    std::vector<int> getTargetTile(colour ghostCol)
    {
        std::vector<int> v;
        switch(moveType) {
            case CHASE:
                        switch (ghostCol) {
                            case RED:
                                v.push_back(pacman.getPacX());
                                v.push_back(pacman.getPacY());
                                break;
                            case BLUE:
                                switch(pacman.currentDir) {
                                    case LEFT:
                                        v.push_back(pacman.getPacX() - 2);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case UP:
                                        v.push_back(pacman.getPacX() );
                                        v.push_back(pacman.getPacY() + 2);
                                        break;
                                    case RIGHT:
                                        v.push_back(pacman.getPacX() + 2);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case DOWN:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY() - 2);
                                        break;
                                    default:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY());
                                }
                                break;
                            case YELLOW:
                                v.push_back(0);
                                v.push_back(0);
                                break;
                            case PINK:
                                switch(pacman.currentDir) {
                                    case LEFT:
                                        v.push_back(pacman.getPacX() - 4);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case UP:
                                        v.push_back(pacman.getPacX() );
                                        v.push_back(pacman.getPacY() + 4);
                                        break;
                                    case RIGHT:
                                        v.push_back(pacman.getPacX() + 4);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case DOWN:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY() - 4);
                                        break;
                                    default:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY());
                                }
                                break;
                        }
                break;
            case SCATTER:
                    switch (ghostColour) {
                        case RED:
                            v.push_back(100);
                            v.push_back(100);
                            break;
                        case BLUE:
                            v.push_back(20);
                            v.push_back(0);
                            break;
                        case YELLOW:
                            v.push_back(0);
                            v.push_back(0);
                            break;
                        case PINK:
                            v.push_back(0);
                            v.push_back(100);
                            break;
                    }
                break;
            case DEATH:
                v.push_back(13.5);
                v.push_back(19);
                break;
        }

        return v;
    }

};

#endif //COURSEWORK_GHOST_H