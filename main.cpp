#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>

float speedX, speedY, auxSpeedX, auxSpeedY, rotateBall = 0.0, ballAngle = 0.05;
int time1, time2 = 0, he = 3, xc = 2, yc = 0;

void field()
{
    GLfloat color[] = {0.0, 0.6, 0.2};
    GLfloat pointsField[4][3] = {
        {-2.0, -2.5, -0.01},
        {-2.0, 2.5, -0.01},
        {2.0, 2.5, -0.01},
        {2.0, -2.5, -0.01},
    };

    glColor3fv(color);
    glBegin(GL_QUADS);
        glVertex3fv(pointsField[0]);
        glVertex3fv(pointsField[1]);
        glVertex3fv(pointsField[2]);
        glVertex3fv(pointsField[3]);
    glEnd();

    GLfloat color2[] = {0.0, 0.55, 0.2};
    GLfloat pointsField2[4][3] = {
        {-2.0, -2.5, 0},
        {-2.0, -1.5, 0},
        {2.0, -1.5, 0},
        {2.0, -2.5, 0},
    };
    glColor3fv(color2);
    glBegin(GL_QUADS);
        glVertex3fv(pointsField2[0]);
        glVertex3fv(pointsField2[1]);
        glVertex3fv(pointsField2[2]);
        glVertex3fv(pointsField2[3]);
    glEnd();

    GLfloat pointsField3[4][3] = {
        {-2.0, -0.5, 0},
        {-2.0, 0.5, 0},
        {2.0, 0.5, 0},
        {2.0, -0.5, 0},
    };
    glColor3fv(color2);
    glBegin(GL_QUADS);
        glVertex3fv(pointsField3[0]);
        glVertex3fv(pointsField3[1]);
        glVertex3fv(pointsField3[2]);
        glVertex3fv(pointsField3[3]);
    glEnd();

    GLfloat pointsField4[4][3] = {
        {-2.0, 2.5, 0},
        {-2.0, 1.5, 0},
        {2.0, 1.5, 0},
        {2.0, 2.5, 0},
    };
    glColor3fv(color2);
    glBegin(GL_QUADS);
        glVertex3fv(pointsField4[0]);
        glVertex3fv(pointsField4[1]);
        glVertex3fv(pointsField4[2]);
        glVertex3fv(pointsField4[3]);
    glEnd();
}

void setView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(95, w / h, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
        (
        xc, yc, he,
        xc-1, yc, 0,
        0, 0, 1
        );
}

void drawString(char *message) {
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(2.3, -0.5, 1);
        glScalef(0.001, 0.001, 0.001);
        glRotated(90, 0, 0, 1);
        for(int i = 0; i < strlen(message); i++)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, message[i]);
    glPopMatrix();
}

void traves()
{
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-0.45, -2.1, 0.3);
        glScalef(0.2,0.2,3.0);
        glutSolidCube(.2);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.4, -2.1, 0.3);;
        glScalef(0.2,0.2,3.0);
        glutSolidCube(.2);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-0.02, -2.1, 0.62);;
        glScalef(4.5,0.2,0.2);
        glutSolidCube(.2);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-0.45, 2.1, 0.3);
        glScalef(0.2,0.2,3.0);
        glutSolidCube(.2);
    glPopMatrix();

     glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.4, 2.1, 0.3);;
        glScalef(0.2,0.2,3.0);
        glutSolidCube(.2);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-0.02, 2.1, 0.62);;
        glScalef(4.5,0.2,0.2);
        glutSolidCube(.2);
    glPopMatrix();
}

void draw_pixel(float x, float y, float z)
{
    glPointSize(2.0);
    GLfloat lines[] = {1, 1, 1};
    glColor3fv(lines);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void bresenhamLine(int xa, int ya, int xb, int yb)
{
    int dx = xb - xa;
    int dy = yb - ya;
    int x = xa;
    int y = ya;


    int d = 2*dy - dx;
    int de = 2*dy;
    int dne = 2*(dy-dx);
    
    while(x < xb){
        if(d <= 0){
            d = d + de;
            x = x + 1;
        }
        else{
            d = d + dne;
            y = y + 1;
            x = x + 1;
        }

        draw_pixel((float)x/100, (float)y/100, 0.1);
        draw_pixel((float)x/100, (float)-y/100, 0.1);
    }
    
}

void fastLine(int xa, int ya, int xb, int yb)
{
    int x = xa;
    int y = ya;

    if(ya == yb){
        while(x<xb){
            draw_pixel((float)x/100, (float)y/100, 0.1);
            x = x + 1;
        }
    }

    else if(xa == xb){
        while(y<yb){
            draw_pixel((float)x/100, (float)y/100, 0.1);
            y = y + 1;
        }
    }
}

void drawSemiCircle(float xc, float yc, float x, float y, int p){
    if(p == 1){
        draw_pixel(xc+x, yc+y, 0.1);
        draw_pixel(xc-x, yc+y, 0.1);
        draw_pixel(xc+y, yc+x, 0.1);
        draw_pixel(xc-y, yc+x, 0.1);
    }
    else{
        draw_pixel(xc+x, yc-y, 0.1);
        draw_pixel(xc-x, yc-y, 0.1);
        draw_pixel(xc+y, yc-x, 0.1);
        draw_pixel(xc-y, yc-x, 0.1);
    }
}

void drawCircle(float xc, float yc, float x, float y)
{
    draw_pixel(xc+x, yc+y, 0.1);
    draw_pixel(xc-x, yc+y, 0.1);

    draw_pixel(xc+x, yc-y, 0.1);
    draw_pixel(xc-x, yc-y, 0.1);
    
    draw_pixel(xc+y, yc+x, 0.1);
    draw_pixel(xc-y, yc+x, 0.1);

    draw_pixel(xc+y, yc-x, 0.1);
    draw_pixel(xc-y, yc-x, 0.1);
    
}

void semiCircleBres(int xc, int yc, int r, int p){
    int x = 0, y = r;
    float d = 5/4 - r;
    drawCircle(xc, yc, x, y);
    while (y > x)
    {
        if(d < 0){
            d = d + 2 * x + 3;
            x++;
        }
        else{
            d = d + 2 * (x - y) + 5;
            x++;
            y--;
        }
        drawSemiCircle((float) xc/100, (float) yc/100, (float) x/100, (float) y/100, p);
    }
}
 
void circleBres(int xc, int yc, int r)
{
    int x = 0, y = r;
    float d = 5/4 - r;
    drawCircle(xc, yc, x, y);
    while (y > x)
    {
        if(d < 0){
            d = d + 2 * x + 3;
            x++;
        }
        else{
            d = d + 2 * (x - y) + 5;
            x++;
            y--;
        }
        drawCircle((float) xc/100, (float) yc/100, (float) x/100, (float) y/100);
    }
}

void drawThings()
{    
    fastLine(-1.5*100, 2.1*100, 1.5*100, 2.1*100);
    fastLine(-1.5*100, -2.1*100, 1.5*100, -2.1*100);
    fastLine(-1.5*100, -2.1*100, -1.5*100, 2.1*100);
    fastLine(1.5*100, -2.1*100, 1.5*100, 2.1*100);
    fastLine(-1.5*100, 0*100, 1.5*100, 0*100);
    fastLine(0.8*100, 1.25*100, 0.8*100, 2.1*100);
    fastLine(-0.8*100, 1.25*100, -0.8*100, 2.1*100);
    fastLine(-0.8*100, 1.25*100, 0.8*100, 1.25*100);
    fastLine(0.4*100, 1.7*100, 0.4*100, 2.1*100);
    fastLine(-0.4*100, 1.7*100, -0.4*100, 2.1*100);
    fastLine(-0.4*100, 1.7*100, 0.4*100, 1.7*100);

    fastLine(0.8*100, -2.1*100, 0.8*100, -1.25*100);
    fastLine(-0.8*100, -2.1*100, -0.8*100, -1.25*100);
    fastLine( -0.8*100, -1.25*100, 0.8*100, -1.25*100);
    fastLine(0.4*100, -2.1*100, 0.4*100, -1.7*100);
    fastLine(-0.4*100, -2.1*100, -0.4*100, -1.7*100);
    fastLine( -0.4*100, -1.7*100, 0.4*100, -1.7*100);

    bresenhamLine(1.2*100, -2.1*100, 1.5*100, -1.9*100);
    bresenhamLine(-1.5*100, 1.9*100, -1.2*100, 2.1*100);

    semiCircleBres(0*100,-1.25*100, 30, 1);
    semiCircleBres(0*100,1.25*100, 30, 0);

    circleBres(0, 0, 60);
}

void ball()
{
    glPushMatrix();
        glRotatef(rotateBall, 0, 0, 1);
        glTranslatef(speedX, speedY, 0);
        glColor3f(0.0,0.9,0.9);
        glScalef(0.06,0.06,0.06);
        glutSolidSphere(1,50,50);
    glPopMatrix();
}

void placar()
{
    char str[30];
    glLineWidth(2);
    sprintf(str, "%d X %d", time1, time2);

    drawString(str);
}

void display()
{
    glClearColor(.4, .4, .9, .8);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setView();
    field();
    //drawLines();
    drawThings();
    traves();
    //curves();
    ball();
    placar();
    glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 97:
            auxSpeedY = -0.025;
            break;
        case 100:
            auxSpeedY = 0.025;
            break;
        case 115:
            auxSpeedX = 0.025;
            break;
        case 119:
            auxSpeedX = -0.025;
            break;
        case 104:
            he = he + 1;
            break;
        case  110:
            he = he - 1;
            break;
        case 105:
            xc = xc - 1;
            break;
        case 107:
            xc = xc + 1;
            break;
        case 106:
            yc = yc - 1;
            break;
        case 108:
            yc = yc + 1;
            break;
        case 27:
            exit(0);

        glutPostRedisplay();
    }
}

void KeyboardUpHandler(unsigned char key, int x, int y) {
    switch (key) {
        case 97:
            auxSpeedY = 0;
            break;
        case 100:
            auxSpeedY = 0;
            break;
        case 115:
            auxSpeedX = 0;
            break;
        case 119:
            auxSpeedX = 0;
            break;
        case 27:
            exit(0);
    }
}

void update(int value)
{
    speedX += auxSpeedX;
    speedY += auxSpeedY;

    if (auxSpeedY != 0 || auxSpeedX != 0)
    {
        rotateBall  += ballAngle;
    }

    if (rotateBall > 8 || rotateBall < -8)
    {
        ballAngle = - ballAngle;
    }

    if ((speedX > -0.4 && speedX < 0.3) && speedY <= -2.1)
    {
        time2 += 1;
        speedX = speedY = 0;
    }

    if ((speedX > -0.4 && speedX < 0.3) && speedY >= 2.1)
    {
        time1 += 1;
        speedX = speedY = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("FIFA");
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(KeyboardUpHandler);
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
