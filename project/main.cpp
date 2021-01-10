#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// shaders header file
#include "./projectCommon/shader.hpp"
#include "./Board.cpp"
#include "./Tetromino.cpp"

#include "stb_image.h"

// Vertex array object (VAO)
GLuint VertexArrayID;

// Vertex buffer object (VBO)
GLuint boardbuffer;
GLuint blockbuffer;

GLuint hlinebuffer;
GLuint vlinebuffer;

// color buffer object (CBO)
GLuint gridcolorbuffer;
GLuint colorbuffer;
GLuint yellowcolorbuffer;
GLuint redcolorbuffer;
GLuint greencolorbuffer;
GLuint bluecolorbuffer;
GLuint purplecolorbuffer;
GLuint cyancolorbuffer;
GLuint orangecolorbuffer;

// GLSL program from the shaders
GLuint programID;

GLint WindowWidth = 800;
GLint WindowHeight = 600;

// -------
int m_clock = 0; // iteration counter
float posX = 0.0f; // graphics postionX
float posY = 0.0f; // graphics postiionY
int timer = 10; // time to next iteration
Board board; // board
Tetromino t; // current tetromino

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{ 
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    programID = LoadShaders( "/Users/vinicius/Desktop/CG/outro/project/shaders/VertexShader.vertexshader", "/Users/vinicius/Desktop/CG/outro/project/shaders/FragmentShader.fragmentshader" );
 
    // Board --------------------------------------------- // 
    static const GLfloat quadro_g_vertex_buffer_data[] = {
        -25.0f,  -50.0f,  0.0f,       25.0f,  -50.0f, 0.0f,
         25.0f,  -50.0f,  0.0f,       25.0f,  50.0f,  0.0f,
         25.0f,  50.0f,   0.0f,       -25.0f, 50.0f,  0.0f,
         -25.0f, 50.0f,   0.0f,       -25.0f, -50.0f, 0.0f,
    };

    static const GLfloat quadro_g_color_buffer_data[] = {
        1.0f, 1.0f,  1.0f,     1.0f, 1.0f,  1.0f,
        1.0f, 1.0f,  1.0f,     1.0f, 1.0f,  1.0f,
        1.0f, 1.0f,  1.0f,     1.0f, 1.0f,  1.0f,
        1.0f, 1.0f,  1.0f,     1.0f, 1.0f,  1.0f,
    };

    // --------------------------------------------------- // 
    
    // Block --------------------------------------------- //
    static const GLfloat block_g_vertex_buffer_data[] = {
        -2.5f,  -2.5f,  0.0f,        2.5f,  -2.5f,  0.0f,
         2.5f,  -2.5f,  0.0f,        2.5f,  -2.5f,  0.0f,
         2.5f,  2.5f,   0.0f,       -2.5f,   2.5f,  0.0f,
         -2.5f, 2.5f,   0.0f,       -2.5f,  -2.5f,  0.0f,
    };

    static const GLfloat horizontal_line_buffer[] ={
        -25.0f,  0.0f,   0.0f,        
        -25.0f,  0.2f,   0.0f,    
        25.0f,   0.0f,   0.0f,
        25.0f,   0.2f,   0.0f,       
        -25.0f,  0.2f,   0.0f,     
        25.0f,   0.0f,   0.0f,       
    };

    static const GLfloat vertical_line_buffer[] = {
        -0.2f, 50.0f,  0.0f, 
        0.0f,  50.0f,  0.0f, 
        -0.2f, -50.0f, 0.0f,
        -0.2f, -50.0f, 0.0f,
        0.0f,  -50.0f, 0.0f,
        0.0f,  50.0f,  0.0f,
         
    };

    //Grid color buffer 
    static const GLfloat grid_color_buffer[] ={
        0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f,
    };
    // Yellow
    static const GLfloat yellow_color_buffer[] = {
        1.0f, 1.0f,  0.0f,     1.0f, 1.0f,  0.0f,
        1.0f, 1.0f,  0.0f,     1.0f, 1.0f,  0.0f,
        1.0f, 1.0f,  0.0f,     1.0f, 1.0f,  0.0f,
        1.0f, 1.0f,  0.0f,     1.0f, 1.0f,  0.0f,

    };

    static const GLfloat red_color_buffer[] = {
        1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,
        1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,
        1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,
        1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,
    };

    static const GLfloat green_color_buffer[] = {
        0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,
        0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,
        0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,
        0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,
    };

    static const GLfloat blue_color_buffer[] = {
        0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,
    };

    static const GLfloat purple_color_buffer[] = {
        1.0f, 0.0f,  1.0f,     1.0f, 0.0f,  1.0f,
        1.0f, 0.0f,  1.0f,     1.0f, 0.0f,  1.0f,
        1.0f, 0.0f,  1.0f,     1.0f, 0.0f,  1.0f,
        1.0f, 0.0f,  1.0f,     1.0f, 0.0f,  1.0f,
    };

    static const GLfloat cyan_color_buffer[] = {
        0.0f, 1.0f,  1.0f,     0.0f, 1.0f,  1.0f,
        0.0f, 1.0f,  1.0f,     0.0f, 1.0f,  1.0f,
        0.0f, 1.0f,  1.0f,     0.0f, 1.0f,  1.0f,
        0.0f, 1.0f,  1.0f,     0.0f, 1.0f,  1.0f,
    };

    static const GLfloat orange_color_buffer[] = {
        1.0f, 0.4f,  0.0f,     1.0f, 0.4f,  0.0f,
        1.0f, 0.4f,  0.0f,     1.0f, 0.4f,  0.0f,
        1.0f, 0.4f,  0.0f,     1.0f, 0.4f,  0.0f,
        1.0f, 0.4f,  0.0f,     1.0f, 0.4f,  0.0f,
    };

  
    // Board --------------------------------------------- // 
    glGenBuffers(1, &boardbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, boardbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadro_g_vertex_buffer_data), quadro_g_vertex_buffer_data, GL_STATIC_DRAW);
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadro_g_color_buffer_data), quadro_g_color_buffer_data, GL_STATIC_DRAW);
    // ----------------------------------------------------- //
    // Lines  --------------------------------------------- // 
    
        //Horizontal
    glGenBuffers(1, &hlinebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, hlinebuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(horizontal_line_buffer), horizontal_line_buffer, GL_STATIC_DRAW);
        // Color
    glGenBuffers(1, &gridcolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gridcolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grid_color_buffer), grid_color_buffer, GL_STATIC_DRAW);
        // Vertical
    glGenBuffers(1, &vlinebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vlinebuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertical_line_buffer), vertical_line_buffer, GL_STATIC_DRAW);

    // ----------------------------------------------------- //

    // Block --------------------------------------------- //
    glGenBuffers(1, &blockbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, blockbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(block_g_vertex_buffer_data), block_g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &yellowcolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, yellowcolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(yellow_color_buffer), yellow_color_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &redcolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, redcolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(red_color_buffer), red_color_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &greencolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, greencolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(green_color_buffer), green_color_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &bluecolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bluecolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blue_color_buffer), blue_color_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &purplecolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, purplecolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(purple_color_buffer), purple_color_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &cyancolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cyancolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cyan_color_buffer), cyan_color_buffer, GL_STATIC_DRAW);

    glGenBuffers(1, &orangecolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, orangecolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(orange_color_buffer), orange_color_buffer, GL_STATIC_DRAW);

    // ----------------------------------------------------- //
}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    glDeleteBuffers(1,&boardbuffer);
    glDeleteBuffers(1,&blockbuffer);
    glDeleteBuffers(1,&colorbuffer);
    glDeleteBuffers(1,&yellowcolorbuffer);
    glDeleteBuffers(1,&redcolorbuffer);
    glDeleteBuffers(1,&bluecolorbuffer);
    glDeleteBuffers(1,&cyancolorbuffer);
    glDeleteBuffers(1,&gridcolorbuffer);
    glDeleteBuffers(1,&vlinebuffer);
    glDeleteBuffers(1,&hlinebuffer);
    glDeleteBuffers(1,&orangecolorbuffer);
    glDeleteBuffers(1,&greencolorbuffer);
    glDeleteBuffers(1,&purplecolorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

//--------------------------------------------------------------------------------
void draw (float x, float y, GLuint buffer, GLuint corbuffer, GLenum primitiva, int pontos)
{
    glUseProgram(programID);
    
    //glm::mat4 mvp = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f);
    glm::mat4 mvp = glm::ortho(-65.0f, 65.0f, -60.0f, 60.0f);
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    glm::mat4 trans = glm::translate(mat4(1.0), glm::vec3(x, y, 0.0f));
    
    unsigned int m = glGetUniformLocation(programID, "trans");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, corbuffer);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    glDrawArrays(primitiva, 0, pontos);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int num = 2;
    if (xpos > num)
        t = board.move_piece_right(t);
    if (xpos < num)
        t = board.move_piece_left(t);
}

int main( void )
{
    std::cout << "==========================" << "\n";
    std::cout << "       Start Game"<< "\n";
    std::cout << "==========================" << "\n";
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow( WindowWidth, WindowHeight, "Tetriz 2D ", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = true; 
    glewInit();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
    transferDataToGPUMemory();

    do 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        draw(0.0f, 0.0f, boardbuffer, colorbuffer, GL_TRIANGLE_FAN, 9);
        

        if(m_clock == timer)
        {
            t = board.move_piece_down(t);
            m_clock = 0;            
        }
        m_clock++;
        
        if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS) 
        {
            if(m_clock == timer)
            {
                t = board.move_piece_left(t);          
            }
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS) 
        {
            if(m_clock == timer)
            {
                t = board.move_piece_down(t);          
            }
        }
        
        if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS) 
        {
            if(m_clock == timer)
            {
                t = board.move_piece_right(t);          
            }
        }

        if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS) 
        {
            if(m_clock == timer)
            {
                t = board.move_piece_rotate(t);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS) 
        {
            if(m_clock == timer)
            {
                while(t.finished == false)
                {
                    t = board.move_piece_down(t);
                }    
            }
        }

        if (glfwGetKey(window, GLFW_KEY_R ) == GLFW_PRESS)
        {
            board.score = 0;
            board.clear_board();
            Tetromino newPiece;
            t = newPiece;
            std::cout << "Start Game" << "\n";
            std::cout << "Score: " << board.score << "\n";
        }
        
        if(m_clock == timer)
        {
            glfwSetCursorPosCallback(window, cursor_position_callback);
        }
        
        if(t.finished)
        {
            board.verification_lines();
            Tetromino newPiece;
            
            while(newPiece.shape == t.shape)
            {
                Tetromino newPiece2;
                newPiece = newPiece2;
            }
            t = newPiece;
            if(!board.validation_move_down(t,0))
            {
                std::cout << "==========================" << "\n";
                std::cout << "GAME OVER" << "\n";
                std::cout << "Final Score: " << board.score << "\n";
                std::cout << "==========================" << "\n";
                //board.clear_board();
                break;

            }
            std::cout << "==========================" << "\n";
            std::cout << "Score: " << board.score << "\n";
            std::cout << "==========================" << "\n";
        }

        for (int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                if(board.game_board[i][j] != 0)
                {
                    // i corresponde a altura e j corresponde a largura DO TABULEIRO
                    if (j == 0) posX = -25.0f;
                    if (j == 1) posX = -20.0f;
                    if (j == 2) posX = -15.0f;
                    if (j == 3) posX = -10.0f;
                    if (j == 4) posX = -5.0f;
                    if (j == 5) posX =  0.0f;
                    if (j == 6) posX =  5.0f;
                    if (j == 7) posX =  10.0f;
                    if (j == 8) posX =  15.0f;
                    if (j == 9) posX =  20.0f;
                    
                    if (i == 0) posY = 50.0f;
                    if (i == 1) posY = 45.0f;
                    if (i == 2) posY = 40.0f;
                    if (i == 3) posY = 35.0f;
                    if (i == 4) posY = 30.0f;
                    if (i == 5) posY = 25.0f;
                    if (i == 6) posY = 20.0f;
                    if (i == 7) posY = 15.0f;
                    if (i == 8) posY = 10.0f;
                    if (i == 9) posY = 5.0f;
                    if (i == 10) posY = 0.0f;
                    if (i == 11) posY = -5.0f;
                    if (i == 12) posY = -10.0f;
                    if (i == 13) posY = -15.0f;
                    if (i == 14) posY = -20.0f;
                    if (i == 15) posY = -25.0f;
                    if (i == 16) posY = -30.0f;
                    if (i == 17) posY = -35.0f;
                    if (i == 18) posY = -40.0f;
                    if (i == 19) posY = -45.0f;

                    switch(board.game_board[i][j]) {
                        case 1:
                            draw(posX+2.5, posY-2.5, blockbuffer, yellowcolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                        case 2: 
                            draw(posX+2.5, posY-2.5, blockbuffer, redcolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                        case 3:
                            draw(posX+2.5, posY-2.5, blockbuffer, greencolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                        case 4:
                            draw(posX+2.5, posY-2.5, blockbuffer, bluecolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                        case 5:
                            draw(posX+2.5, posY-2.5, blockbuffer, purplecolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                        case 6:
                            draw(posX+2.5, posY-2.5, blockbuffer, cyancolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                        case 7:
                            draw(posX+2.5, posY-2.5, blockbuffer, orangecolorbuffer, GL_TRIANGLE_FAN, 6);
                            break;
                    }
                }
            }
        }

        for(int i = 0; i < 55; i = i + 5)
        {
            draw(i-25.0f, 0.0f, vlinebuffer, gridcolorbuffer, GL_TRIANGLES, 6);
        }

        for(int i = 0; i < 100; i = i + 5)
        {
            draw(0.0f, i-50.0f, hlinebuffer, gridcolorbuffer, GL_TRIANGLE_FAN, 6);
        }
            
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    cleanupDataFromGPU();
    glfwTerminate();

    return 0;
}
