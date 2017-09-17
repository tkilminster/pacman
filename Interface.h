//
// Created by teekay on 05/01/17.
//

#ifndef COURSEWORK_INTERFACE_H
#define COURSEWORK_INTERFACE_H

extern int score;
extern int lives;

/**
 * Takes in the current score and draws it to the screen
 * @param scorePrint the current score in the game
 */
void drawScore(int scorePrint)
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(15.0, 32.5); // Translate to the correct area of the screen ready for drawing
    drawTex(score_tex, 40, 8, 0); // Draw the score_tex which is the word "SCORE"
    translateToMazeCoords(4, -1.0); // Translate to below "SCORE" ready to draw numbers
    std::string str = std::to_string(scorePrint); // Convert the current score to a string to enable iteration through number

    for(int i = str.length() -1; i>=0 ; i--) { // Iterate through the number and draw the correct digit
        switch(str[i]) {
            case '0':
                drawTex(num_0_tex, 8, 8, 0);
                break;
            case '1':
                drawTex(num_1_tex, 8, 8, 0);
                break;
            case '2':
                drawTex(num_2_tex, 8, 8, 0);
                break;
            case '3':
                drawTex(num_3_tex, 8, 8, 0);
                break;
            case '4':
                drawTex(num_4_tex, 8, 8, 0);
                break;
            case '5':
                drawTex(num_5_tex, 8, 8, 0);
                break;
            case '6':
                drawTex(num_6_tex, 8, 8, 0);
                break;
            case '7':
                drawTex(num_7_tex, 8, 8, 0);
                break;
            case '8':
                drawTex(num_8_tex, 8, 8, 0);
                break;
            case '9':
                drawTex(num_9_tex, 8, 8, 0);
                break;
        }
        translateToMazeCoords(-1, 0); // Translate when the ^10 index is increased by 1 to ensure number reads correctly
    }
    glPopMatrix();
}

/**
 * Draws the current number of lives to the screen
 * @param liveCount number of lives pacman has left in current game
 */
void drawLives(int liveCount)
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(2, -2); // Translate to the correct area of the screen ready for drawing
    for(int i = 0; i < liveCount - 1; i++) { // Draw as many as icons as pacman has lives left
        drawTex(pac_1_tex, 14, 14, 0);
        translateToMazeCoords(2, 0); // After drawing translate to the right ready for more potential icons to be drawn
    }
    glPopMatrix();
}

/**
 * Method to return the highscore from high_score.txt file. If the file doesnt exist it is created and the highscore is set to 0
 * @return the current high score
 */
int getHighScore()
{
    int highScore;
    std::fstream scoreFile("high_score.txt"); // Open a stream to the high score file
    if(scoreFile.good()) { // If the file exists get the value from inside
        scoreFile >> highScore;
        scoreFile.close(); // Close the stream
        return highScore; // Return the score
    } else { // If the file does not exist
        std::ofstream highScoreFile("high_score.txt"); // Create the file
        highScoreFile << 0; // Pass in the highscore of 0
        scoreFile.close(); // close the streams
        highScoreFile.close();
    }
    return 0; // Return 0 as the file hadnt previously existed
}

/**
 * Once the game is over the final score is compared to the current highscore and determines whether to overwrite the highscore wit the new
 * @param score the score at the end of the current game
 */
void setHighScore(int score)
{
    int currentHigh = getHighScore(); // Store the current high score
    if(currentHigh < score) { // Only update the high score if the current score is higher than the previous
        std::ofstream highFile("high_score.txt"); // Open the stream for the highscore file
        highFile.clear(); // clear the stream
        highFile << score; // write the new high score to the stream
        highFile.close(); // close the stream
    }
}

/**
 * Draws the "HIGH" text and the vale of the current highscore to the correct area of the screen
 */
void drawHigh()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(8.0, 32.5); // Translate to the correct area of the screen ready for drawing
    drawTex(high_tex, 32, 7, 0); // Draw the high_tex which is the word "HIGH"
    translateToMazeCoords(3, -1.0); // Translate to below "HIGH" ready to draw numbers
    std::string str = std::to_string(getHighScore()); // Convert the current score to a string to enable iteration through number

    for(int i = str.length() -1; i>=0 ; i--) { // Iterate through the number and draw the correct digit
        switch(str[i]) {
            case '0':
                drawTex(num_0_tex, 8, 8, 0);
                break;
            case '1':
                drawTex(num_1_tex, 8, 8, 0);
                break;
            case '2':
                drawTex(num_2_tex, 8, 8, 0);
                break;
            case '3':
                drawTex(num_3_tex, 8, 8, 0);
                break;
            case '4':
                drawTex(num_4_tex, 8, 8, 0);
                break;
            case '5':
                drawTex(num_5_tex, 8, 8, 0);
                break;
            case '6':
                drawTex(num_6_tex, 8, 8, 0);
                break;
            case '7':
                drawTex(num_7_tex, 8, 8, 0);
                break;
            case '8':
                drawTex(num_8_tex, 8, 8, 0);
                break;
            case '9':
                drawTex(num_9_tex, 8, 8, 0);
                break;
        }
        translateToMazeCoords(-1, 0); // Translate when the ^10 index is increased by 1 to ensure number reads correctly
    }
    glPopMatrix();
}

/**
 * Draw the ready text at the beginning of the game
 */
void drawReady()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(11.5f, 13.0f); // Translate to the correct area of the screen ready for drawing
    drawTex(ready_tex,40, 8, 0);
    glPopMatrix();
}

/**
 * Draw the game over text at the end of the game
 */
void drawGameOver()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(10.0f, 12.75f); // Translate to the correct area of the screen ready for drawing
    drawTex(gameover_tex,65, 10, 0);
    glPopMatrix();
}

/**
 * Calls methods to draw the score and lives to the screen
 */
void drawInterface()
{
    drawHigh();
    drawScore(score);
    drawLives(lives);
}

#endif //COURSEWORK_INTERFACE_H