#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/Grid.h"
#include "../include/BFS.h"
#include "../include/TextRenderer.h"


Grid grid(40, 40, 25);
BFS bfs;

bool running = false;

void drawCell(int r,int c,float R,float G,float B){
    float x = c * grid.cellSize;
    float y = r * grid.cellSize;

    glColor3f(R,G,B);
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+grid.cellSize,y);
    glVertex2f(x+grid.cellSize,y+grid.cellSize);
    glVertex2f(x,y+grid.cellSize);
    glEnd();
}


void mouse(GLFWwindow* win,int button,int action,int){
    if(action!=GLFW_PRESS) return;

    double mx,my;
    glfwGetCursorPos(win,&mx,&my);

    int c = mx / grid.cellSize;
    int r = my / grid.cellSize;

    if(r<0||r>=grid.rows||c<0||c>=grid.cols) return;

    if(glfwGetKey(win,GLFW_KEY_B)==GLFW_PRESS){
        grid.start={r,c};
        return;
    }

    if(glfwGetKey(win,GLFW_KEY_R)==GLFW_PRESS){
        grid.end={r,c};
        return;
    }

    if(button==GLFW_MOUSE_BUTTON_LEFT)
        grid.grid[r][c]=1;

    if(button==GLFW_MOUSE_BUTTON_RIGHT)
        grid.grid[r][c]=0;
}

int main(){
    glfwInit();

    GLFWwindow* win =
        glfwCreateWindow(1000,1000,"BFS Visualizer",0,0);

    glfwMakeContextCurrent(win);
    glfwSetMouseButtonCallback(win, mouse);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1000,1000,0,-1,1);

    glfwSwapInterval(0); // FAST FPS

    double last = glfwGetTime();

    while(!glfwWindowShouldClose(win)){
        glClear(GL_COLOR_BUFFER_BIT);

        if(running && !bfs.finished()){
            if(glfwGetTime()-last>0.005){
                bfs.step(grid);
                last = glfwGetTime();
            }
        }

        for(int r=0;r<grid.rows;r++){
            for(int c=0;c<grid.cols;c++){
                if(grid.grid[r][c]==1)
                    drawCell(r,c,0,0,0);
                else
                    drawCell(r,c,1,1,1);
            }
        }

        // save projection
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        // NORMAL OpenGL coordinates (bottom-left origin)
        glOrtho(0, 1000, 0, 1000, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();


        glColor3f(0, 0, 0);

        drawText(10, 960, "Time: " + std::to_string(bfs.timeTaken) + " ms", 2.0f);
        drawText(10, 920, "Distance: " + std::to_string(bfs.distance), 2.0f);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);


        for(auto& n:bfs.visited)
            drawCell(n.row,n.col,1,1,0);

        for(auto& n:bfs.path)
            drawCell(n.row,n.col,0.6f,0,1);

        if(grid.start.row!=-1)
            drawCell(grid.start.row,grid.start.col,0,0,1);

        if(grid.end.row!=-1)
            drawCell(grid.end.row,grid.end.col,1,0,0);

        if(glfwGetKey(win,GLFW_KEY_SPACE)==GLFW_PRESS &&
           !running &&
           grid.start.row!=-1 &&
           grid.end.row!=-1){
            grid.clearSearch();
            bfs.init(grid);
            running=true;
        }

        if(bfs.finished()){
            std::string title =
                "BFS Visualizer | Time: " +
                std::to_string(bfs.timeTaken) +
                " ms | Distance: " +
                std::to_string(bfs.distance);
            glfwSetWindowTitle(win,title.c_str());
        }

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
}
