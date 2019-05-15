#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>

#define arrSize 70

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


float camPos[] = {0, 0, 3.42f};
float size = (float)arrSize;
float side = 2/size;
bool game = false; // Game on -> true; Paused -> false
float pixelSide = (682-117)/size;
bool fast = true;

int randXseed, randYseed;
float randX, randY;


static int grids[arrSize][arrSize];
static int nextGrids[arrSize][arrSize];




// Count the living neighbours
int countLiveNeighbour(int i,int j){
    int counter = 0;
    if ((0<=(i-1)<arrSize) && (0<=(j-1)<arrSize))
        if (grids[i-1][j-1] == 1)
            counter++;
    if ((0<=(i-1)<arrSize) && (0<=(j)<arrSize))
        if (grids[i-1][j] == 1)
            counter++;
    if ((0<=(i-1)<arrSize) && (0<=(j+1)<arrSize))
        if (grids[i-1][j+1] == 1)
            counter++;
    if ((0<=(i)<arrSize) && (0<=(j-1)<arrSize))
        if (grids[i][j-1] == 1)
            counter++;
    if ((0<=(i)<arrSize) && (0<=(j+1)<arrSize))
        if (grids[i][j+1] == 1)
            counter++;
    if ((0<=(i+1)<arrSize) && (0<=(j-1)<arrSize))
        if (grids[i+1][j-1] == 1)
            counter++;
    if ((0<=(i+1)<arrSize) && (0<=(j)<arrSize))
        if (grids[i+1][j] == 1)
            counter++;
    if ((0<=(i+1)<arrSize) && (0<=(j+1)<arrSize))
        if (grids[i+1][j+1] == 1)
            counter++;
    return counter;
}





void gameOn(){
    int liveNeighbour = 0;

    for (int i=0;i<arrSize;i++){
        for (int j=0;j<arrSize;j++){
            liveNeighbour = countLiveNeighbour(i,j);
            //printf("live nei for %i,%i is %i ",i,j,liveNeighbour );

            if (grids[i][j] == 1){ // alive now
                if ((liveNeighbour<2) || (liveNeighbour>3)){
                    nextGrids[i][j] = 0;
                   // printf("it's gonna die\n" );
                }
                else if (2<=liveNeighbour<=3){
                    nextGrids[i][j] = 1;
                   // printf("it's gonna live\n" );
                }
            }
            else{
                if (liveNeighbour == 3){
                    nextGrids[i][j] = 1;
                  //  printf("it's gonna rivive\n" );
                    }
                }    
                    
            }
        }

        
    
    /*printf("this is the next grid:\n");
    for (int i=0;i<arrSize;i++){
        for (int j=0;j<arrSize;j++){
            printf("%i ",nextGrids[i][j]);
       }
       printf("\n");
    }

    printf("\n");
    printf("\n");*/


    // Copy nextGrids to current grid to display
    for (int i=0;i<arrSize;i++){
        for (int j=0;j<arrSize;j++){
            grids[i][j] = nextGrids[i][j];
       }
    }

}

void motion(int x,int y){
    //printf("mouse montion coords:%i,%i\n",x,y);
}


void drawFilledSquare(float a, float b,std::string color){
    if (color.compare("green") == 0){
        glColor3f(0,1,0);
    }
    else if (color.compare("red") == 0){
        glColor3f(1,0,0);
    }
    else if ((color.compare("white") == 0)){
        glColor3f(1,1,1);
    }
    
    float startx = a;
    float starty = b;
    float endx = startx + side;
    float endy = starty - side;
    for (float i = startx; i<endx;i= i+0.001){
        for (float j = starty; j>endy;j= j-0.001){
            glBegin(GL_POINTS);
            //glColor3f(0,1,0);
            glVertex2f(i,j);
            glEnd();
        }
    }
}

void printArray(){
    for (int i=0;i<arrSize;i++){
        for (int j=0;j<arrSize;j++){
            printf("%i ",grids[i][j]);
        }
        printf("\n");
    }
}

void randSquares(){
    srand(time(NULL));
    int squareCount = rand() % (arrSize * arrSize);
    //printf("The number of squares is: %i\n",squareCount);
    for (int i=0;i<squareCount;i++){
        //printf("%i\n",i);
        
        int currentRandX = rand() % arrSize;
        int currentRandY = rand() % arrSize;
        //printf("%i,%i\n",currentRandX,currentRandY);
        grids[currentRandX][currentRandY] = 1; //mark as alive
        drawFilledSquare(-1+side*currentRandY,1-side*currentRandX,"white");
    }
     //printArray();
}

void printBoard(){
    for (int i=0;i<arrSize;i++){
        for (int j=0;j<arrSize;j++){
            if(grids[i][j] == 1){
                drawFilledSquare(-1+side*j,1-side*i,"white");
            }
            
        }
    }
}




void grid(){
    // OUTLINE
    for (float x=-1;x<=1;x+= 0.001){
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        glVertex2f(x, 1);
        glEnd();
    }
    for (float y=-1;y<=1;y+= 0.001){
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        glVertex2f(1, y);
        glEnd();
    }
    // GRIDS
    // Vertical
    for (float i=-1; i<1;i = i+side){
        for (float j=-1;j<1;j+=0.001){
            glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2f(i, j);
            glEnd();
        }
    }
    // Horizontal
    for (float j=-1; j<1;j = j+side){
        for (float i=-1;i<1;i+=0.001){
            glBegin(GL_POINTS);
            glColor3f(1,1,1);
            glVertex2f(i, j);
            glEnd();
        }
    }
}

void init(void)
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,100);
}

void drawOrigin(){
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glColor3f(1,1,1);
        
        glVertex2f(0,0);
    glEnd();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
    //glColor3f(1,1,1);
    //drawOrigin();  
    glPointSize(1.0f);
    grid();
    printBoard();
    //glFlush();
    glutSwapBuffers();
}

void FPS(int val){
    //glutPostRedisplay();

    if(game){
        gameOn();
        glutDisplayFunc(display);
        glutPostRedisplay();
        if (fast){ // speed control
            glutTimerFunc(16,FPS,0); 
        }
        else{
            glutTimerFunc(200,FPS,0); 
        }
        glutSwapBuffers();


    }
}

void mouse(int btn, int state, int x,int y){
    if (state == GLUT_UP){
        //printf("mouse coords:%i,%i\n",x,y);
    int stateChangeX = (y-120)/pixelSide;
    int stateChangeY = (x-117)/pixelSide;
    //printf("%i,%i\n",stateChangeX,stateChangeY);
    if ((0<=stateChangeX<arrSize)&(0<=stateChangeY<arrSize)){
        if (grids[stateChangeX][stateChangeY] == 1)
            grids[stateChangeX][stateChangeY] = 0;
        else
            grids[stateChangeX][stateChangeY] = 1;
    }
    //printArray();
    glutPostRedisplay();
    glutSwapBuffers();

    }
    
}



void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)((w+0.0f)/h), 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void gridClear(){
    for (int i =0;i<arrSize;i++){
        for (int j=0;j<arrSize;j++){
            grids[i][j] = 0;
            nextGrids[i][j] = 0;
        }
    }
}



void keyboard(unsigned char key, int xIn, int yIn)
{
    switch (key)
    {
        case 'q':
        case 27:    //27 is the esc key
            exit(0);
            break;
        case 'p':
            game = !game;
            if (game){
                glutTimerFunc(0,FPS,0);
            }
            break;
        case 'n': // next stage
            gameOn();
            //printArray();
            glutPostRedisplay();
            //glutDisplayFunc(display);
            break;
        case 'f':
            fast = !fast;
            break;
        case 'c':
            gridClear();
            glutPostRedisplay();
            break;
        case 'r':
            gridClear();
            randSquares();
            glutPostRedisplay();
            break;

    }
}

void callBackInit(){
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    //glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(0 , FPS, 0);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);      //starts up GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Game of Life");   //creates the window
    glutReshapeFunc(reshape);
    
    printf("\n");
    printf("\n");

    printf("**** WELCOME TO GAME OF LIFE ****\n");
    printf("\n");
    printf("\n");
    printf("Press c to clean all grids\n");
    printf("Press p to run/pause the simulation\n");
    printf("Press f for speed control fast/slow \n");
    printf("Press r re-randomnize the whole grid\n");
    printf("Press n for next stage\n");

    printf("Click on the cell to change its state\n");
    printf("Press esc/q to quit");
    printf("\n");
    printf("\n");
    printf("To change the grid size: change the value of arrSize in line 6 in file Conway.cpp. Recommended value for grid size: 5 - 150. \n");
    printf("\n");
    printf("\n");
   
    //glutKeyboardFunc(keyboard);
    randSquares();
    callBackInit();

    //glutDisplayFunc(display);
    
   // creatOurMenu();

    init();
    glutMainLoop();             //starts the event glutMainLoop

    return(0);  
}
