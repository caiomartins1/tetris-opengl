#ifndef _COMPLEX_H
#define _COMPLEX_H 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <time.h>
using namespace glm;

// shaders header file
#include "./projectCommon/shader.hpp"

/*
    Types:
       1: 'I' - 2 variações
       2: 'J' - 4 variações    
       3: 'L' - 4 variações
       4: 'O' - 1 variação
       5: 'S' - 4 variações
       6: 'Z' - 4 variações
       7: 'T' - 4 variações

    Variations:
        1: 'l' - Left
        2: 'r' - Right
        3: 'b' - Bottom
        4: 't' - Top
*/


class Tetromino {
    public:
        int shapes[7][4][4][2] = 
        {
            { // I         
                { // straight
                    {4, 0},
                    {4, 1},
                    {4, 2},
                    {4, 3}
                },
                {
                    {3, 0},
                    {4, 0},
                    {5, 0},
                    {6, 0}
                },
                {
                    {4, 0},
                    {4, 1},
                    {4, 2},
                    {4, 3}
                },
                {
                    {3, 0},
                    {4, 0},
                    {5, 0},
                    {6, 0}
                },
            },
            { // J       
                {
                    {4,0},
                    {4,1},
                    {4,2},
                    {3,2},
                },
                {
                    {4,0},
                    {4,1},    
                    {5,1},
                    {6,1},
                },
                {
                    {5,0},
                    {4,0},
                    {4,1},
                    {4,2},
                },
                {
                    {3,0},
                    {4,0},
                    {5,0},
                    {5,1},
                },
            },
            { // L
                {
                    {4,0},
                    {4,1},
                    {4,2},
                    {5,2},
                },
                {
                    {4,0},
                    {4,1},    
                    {5,0},
                    {6,0},
                },
                {
                    {4,0},
                    {5,0},
                    {5,1},
                    {5,2},
                },
                {
                    {5,0},
                    {5,1},
                    {4,1},
                    {3,1},
                },
            },
            { //O
                { // straight
                    {4, 0},
                    {4, 1},
                    {5, 0},
                    {5, 1}
                },
                {
                    {4, 0},
                    {4, 1},
                    {5, 0},
                    {5, 1}
                },
                {
                    {4, 0},
                    {4, 1},
                    {5, 0},
                    {5, 1}
                },
                {
                    {4, 0},
                    {4, 1},
                    {5, 0},
                    {5, 1}
                },        
            },
            { // S
                { // straight
                    {6, 0},
                    {5, 0},
                    {5, 1},
                    {4, 1}
                },
                {
                    {4, 0},
                    {4, 1},
                    {5, 1},
                    {5, 2}
                },
                {
                    {6, 0},
                    {5, 0},
                    {5, 1},
                    {4, 1}
                },
                {
                    {4, 0},
                    {4, 1},
                    {5, 1},
                    {5, 2}
                },     
            },
            { // Z
                { // straight
                    {4, 0},
                    {5, 0},
                    {5, 1},
                    {6, 1}
                },
                {
                    {5, 0},
                    {5, 1},
                    {4, 1},
                    {4, 2}
                },
                { // straight
                    {4, 0},
                    {5, 0},
                    {5, 1},
                    {6, 1}
                },
                {
                    {5, 0},
                    {5, 1},
                    {4, 1},
                    {4, 2}
                }
            },
            { // T
                { // straight
                    {4, 0},
                    {5, 0},
                    {5, 1},
                    {6, 0}
                },
                {
                    {6, 0},
                    {6, 1},
                    {5, 1},
                    {6, 2}
                },
                {
                    {5, 0},
                    {5, 1},
                    {4, 1},
                    {6, 1}
                },
                {
                    {4, 0},
                    {4, 1},
                    {5, 1},
                    {4, 2}
                }, 
            }
        };
        // Variables -------------------------------- //
        int shape;
        int rot;
        int prevX;
        int prevY;
        bool finished;
        int x[4] = {0, 0, 0, 0};
        int y[4] = {0, 0, 0, 0};
        // ------------------------------------------- //
        // Constructor --------------------------------- //
        Tetromino() {
            prevX = 0;
            prevY = 0;
            shape = rand() % 7 + 1;
            rot = rand() % 4;
            finished = false;

            for(int i = 0; i < 4; i++)
            {
                x[i] = shapes[shape-1][rot][i][0];
                y[i] = shapes[shape-1][rot][i][1];
            }
        };
        // ------------------------------------------- //
        // Draw -------------------------------------- //
        // ------------------------------------------- //
};

#endif

