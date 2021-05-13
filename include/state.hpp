// This header defines the game state
// also shows the game logic designs
#pragma once

enum GameState
{
    // at beginning stage, title shows tutorial
    // teach basic commands
    BEGINNING = 0, // show welcome message
    BEGINNING_SPACE = 1, // ask to hit space to enter control mode
    BEGINNING_LEFT = 2, // ask to left click to shoot
    BEGINNING_RIGHT = 3, // ask to right click and hold to aim
    BEGINNING_SCORE = 4, // show score information
    BEGINNING_SHOOT = 5, // ask to shoot the balloons on the wall to enter first challenge
    // first challenge
    // shoot balloons appearing on the wall (timeout 20s, score accumulated)
    STAGE1 = 6,
    // second challenge
    // shoot balloons with specific colors (timeout 20s, score accumulated)
    STAGE2 = 7,
    // third challenge
    // shoot balloons falling from the sky (timeout 20s, score accumulated)
    STAGE3 = 8,
    // last challenge
    // shoot balloons with specific color falling from sky
    // with wind blowing (timeout 30s, score accumulated)
    STAGE4 = 9,

    LOSS = 20,
    WIN = 21,
};

#define GAME_TIMEOUT_STAGE1 20
#define GAME_TIMEOUT_STAGE2 20
#define GAME_TIMEOUT_STAGE3 20
#define GAME_TIMEOUT_STAGE4 30

// shoot right balloon, score + 1
// if color specified and shoot wrong color, score - 2
// if missed shot, score - 1
// if accumulated score is negative, jump scare and show "You LOSE!" (black screen)
// if complete all challenges and survive, show "You WIN! Score = " (fireworks in background)