// state.hpp
// Assignment: CIS425 Final Project
// Environment/Compiler:
//                  Visual Studio Community 2019 (Tested)
//                  Linux GCC (Tested)
//                  MacOS GCC (Not Tested)
// Date: May 14, 2021
// Official Name:  Sida Zhu
// E-mail:
//      szhu28@syr.edu
//      teamclouday@gmail.com
// File Description:
//      This header file defines the GameState enum
//      This file also contains the game logic designs written as comments
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

// #define GAME_TIMEOUT_STAGE1 20
// #define GAME_TIMEOUT_STAGE2 20
// #define GAME_TIMEOUT_STAGE3 20
// #define GAME_TIMEOUT_STAGE4 30

// shoot right balloon, score + 1
// if color specified and shoot wrong color, score - 2
// if missed shot, score - 1
// if accumulated score is negative, show "You LOSE!" with death picture, play funny music
// if complete all challenges and survive, show "You WIN!", fireworks in background,
//          play winning music, show list scrolling for contributors