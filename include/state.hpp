// This header defines the game state
// also shows the game logic designs
#pragma once

enum GameState
{
    // at beginning stage, title shows tutorial
    // teach basic commands
    BEGINNING = 0,
    // first challenge
    // shoot balloons appearing on the wall (timeout 20s, score accumulated)
    STAGE1 = 1,
    // second challenge
    // shoot balloons with specific colors (timeout 20s, score accumulated)
    STAGE2 = 2,
    // third challenge
    // shoot balloons falling from the sky (timeout 20s, score accumulated)
    STAGE3 = 3,
    // last challenge
    // shoot balloons with specific color falling from sky
    // with wind blowing (timeout 30s, score accumulated)
    STAGE4 = 4,

    LOSS = 5,
    WIN = 6,
};

#define GAME_TIMEOUT_STAGE1 20
#define GAME_TIMEOUT_STAGE2 20
#define GAME_TIMEOUT_STAGE3 20
#define GAME_TIMEOUT_STAGE4 30

// shoot right balloon, score + 1
// if color specified and shoot wrong color, score - 2
// if accumulated score is negative, jump scare and show "You LOSE!" (black screen)
// if complete all challenges and survive, show "You WIN! Score = " (fireworks in background)