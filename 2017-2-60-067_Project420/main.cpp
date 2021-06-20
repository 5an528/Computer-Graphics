#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
    double x,y,z;
} Point;
int retmp=0;
int doorangle = 0;
int tmp=0;
int drotate = 0;
bool drawAxes = true;
float tyreAngle = 0;
int doorrotate = 0;
float quadAngle = 0;
float boxAngle = 0;
float boxScaleFactor = 1;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;
float slidingDoor = 0;
int fu = 0;
float winup =0;

Point pos, u, r, l;

void displayAxes()
{
    if(drawAxes)
    {
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0, 0);

            glVertex3f( 500,0,0); // a point on pos x axis
            glVertex3f(-500,0,0); // a point on neg x axis

            glColor3f(0, 1.0, 0);

            glVertex3f(0,-500,0); // a point on pos y axis
            glVertex3f(0, 500,0); // a point on neg y axis

            glColor3f(0, 0, 1.0);

            glVertex3f(0,0, 500);  // a point on pos z axis
            glVertex3f(0,0,-500);   // a point on neg z axis
        }
        glEnd();
    }
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
    {
        Point l1 = func(l, r, -1);
        r = func(r, l, 1);
        l = l1;
        break;
    }
    case '2':
    {
        Point l1 = func(l, r, 1);
        r = func(r, l, -1);
        l = l1;
        break;
    }

    case '3':
    {
        Point u1 = func(u, l, -1);
        l = func(l, u, 1);
        u = u1;
        break;
    }
    case '4':
    {
        Point u1 = func(u, l, 1);
        l = func(l, u, -1);
        u = u1;
        break;
    }
    case '5':
    {
        Point r1 = func(r, u, -1);
        u = func(u, r, 1);
        r = r1;
        break;
    }
    case '6':
    {
        Point r1 = func(r, u, 1);
        u = func(u, r, -1);
        r = r1;
        break;
    }
    case '7':
    {
        tyreScaleFactor += 0.2;
        break;
    }
    case '8':
    {
        tyreScaleFactor -= 0.2;
        break;
    }
    case '9':
    {
        printf("Quad Angle %f\n", quadAngle);
        if (quadAngle == -54)
            break;
        else
        {
            quadAngle -= 2;
            break;
        }
    }
    case '0':
    {
        printf("Quad Angle %f\n", quadAngle);
        if (quadAngle == 0)
            break;
        else
        {
            quadAngle += 2;
            break;
        }
    }
    case 'l':
    {
        boxAngle -= 5;
        //printf("BoxAngle %f\n", boxAngle);
        break;
    }
    case 'L':
    {
        boxAngle -= 5;
        //printf("BoxAngle %f\n", boxAngle);
        break;
    }
    case 'r':
    {
        boxAngle += 5;
        //printf("BoxAngle %f\n", boxAngle);
        break;
    }
    case 'R':
    {
        boxAngle += 5;
        //printf("BoxAngle %f\n", boxAngle);
        break;
    }
    case 'U':
    {
        //printf("boxScaleFactor %f\n", boxScaleFactor);
        if (int(boxScaleFactor)== 2)
            break;
        else
        {
            boxScaleFactor= boxScaleFactor+ .1;
            break;
        }
    }
    case 'u':
    {
        // printf("boxScaleFactor %f\n", boxScaleFactor);
        if (int(boxScaleFactor)== 2)
            break;
        else
        {
            boxScaleFactor= boxScaleFactor+ .1;
            break;
        }
    }

    case 'd':
    {

        if (boxScaleFactor >0)
        {
            boxScaleFactor-= .1;
            if(boxScaleFactor<0)
                boxScaleFactor=0;
            // printf("boxScaleFactor %f\n", boxScaleFactor);
            break;
        }
    }
    case 'D':
    {

        if (boxScaleFactor >0)
        {
            quadAngle += 5;
            printf("Quad Angle %f\n", quadAngle);
            break;
            boxScaleFactor-= .1;
            if(boxScaleFactor<0)
                boxScaleFactor=0;
            break;
        }
    }
    default:
        break;
    }
}

Point camerapos(Point vect, Point perp, int dir)
{
    //Point point;
    vect.x = (vect.x +  4* dir*perp.x);
    vect.y = (vect.y +  4* dir*perp.y);
    vect.z = (vect.z +  4* dir*perp.z);
    return vect;
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN: // down arrow
		    {
		        pos = camerapos(pos,l,-1);
                break;
		    }

		case GLUT_KEY_UP:   // up arrow
		    {
		        pos = camerapos(pos,l, 1);
                break;
		    }

		case GLUT_KEY_RIGHT:    // right arrow
		    {
		        pos = camerapos(pos,r,1);
                break;
		    }

		case GLUT_KEY_LEFT:     // left arrow
		    {
		        pos = camerapos(pos,r,-1);
                break;
		    }

		case GLUT_KEY_PAGE_UP:
		    {
                pos = camerapos(pos,u,1);
                break;
		    }

		case GLUT_KEY_PAGE_DOWN:
		    {
		        pos = camerapos(pos,u,-1);
                break;
		    }

		case GLUT_KEY_END:
    {
        if(slidingDoor == 0)
            break;
        else
        {
            slidingDoor += 5;
            break;
        }
    }

    case GLUT_KEY_HOME:
    {
        if(slidingDoor == -40)
            break;
        else
        {
            slidingDoor -= 5;
            break;
        }
    }
		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            printf("Mouse Left Button Clicked\n");
        }
        else if(state == GLUT_UP)
        {
            printf("Mouse Left Button Released\n");
        }
        break;
    default:
        break;
    }
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 10;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    if(fu == 0)
    {
        for(int i = 0; i< tyreSlices; i++)
        {
            if(i%2==0)
            {
                glColor3f(1, 0, 0);
            }
            else
            {
                glColor3f(0, 0, 1);
            }

            glPushMatrix();
            glRotatef(sliceAngle*i, 1, 0, 0);
            glBegin(GL_QUADS);
            {
                glVertex3f(halfTyreWidth,-tyreRadius/2, 0);
                glVertex3f(-halfTyreWidth, -tyreRadius/2, 0);
                glVertex3f(-halfTyreWidth, -tyreRadius, 0);
                glVertex3f(halfTyreWidth, -tyreRadius, 0);
            }
            glEnd();
            glPopMatrix(); //same again for another color

        }
    }



    /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, 0, tyreRadius);
        glVertex3f(halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, tyreRadius);
    }
    glEnd();*/


    glColor3f(0.25, 0.5, 1);
    for(int i=0; i<tyreSlices; i++)
    {
        if(i%2==0)
        {
            glColor3f(1, 1, 1);
        }
        else
        {
            glColor3f(0, 0, 0);
        }

        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();


    }
}

void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        /*glColor3f(1, 1, 0);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);*/

        /** Gradient Fill Quad **/


        if(fu == 1)
        {
            glColor3f(1, 1, 1);

            glVertex3f(halfQuadWidth, 0, halfQuadLength);
            glVertex3f(halfQuadWidth, 0, -halfQuadLength);

            glColor3f(0, 0, 1);

            glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
            glVertex3f(-halfQuadWidth, 0, halfQuadLength);
        }
        else if(fu == 2)
        {
            glColor3f(0, 0, 1);

            glVertex3f(halfQuadWidth, 0, halfQuadLength);
            glVertex3f(halfQuadWidth, 0, -halfQuadLength);

            glColor3f(1, 1, 1);

            glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
            glVertex3f(-halfQuadWidth, 0, halfQuadLength);
        }
        else if(fu == 3)
        {
            glColor3f(1, 1, 1);

            glVertex3f(-quadWidth, 0, halfQuadLength);
            glVertex3f(-quadWidth, 0, -halfQuadLength);

            glColor3f(0, 0, 1);

            glVertex3f(0,0, -halfQuadLength);
            glVertex3f(0, 0, halfQuadLength);
        }
        else if(fu == 4)
        {
            glColor3f(1, 1, 1);

            glVertex3f(quadWidth, 0, halfQuadLength);
            glVertex3f(quadWidth, 0, -halfQuadLength);

            glColor3f(0, 0, 1);

            glVertex3f(0,0, -halfQuadLength);
            glVertex3f(0, 0, halfQuadLength);
        }
        else
        {
            glColor3f(1, 1, 0);
            glVertex3f(0, halfQuadWidth, 0);
            glVertex3f(0, halfQuadWidth, -quadLength);
            glVertex3f(0, -halfQuadWidth, -quadLength);
            glVertex3f(0, -halfQuadWidth, 0);
        }

    }
    glEnd();
}

void displayBox(float boxLength, float boxWidth, float boxHeight, float xcolor, float ycolor, float zcolor) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(xcolor, ycolor, zcolor);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(xcolor-0.37, ycolor-0.37, zcolor-0.37);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(xcolor-0.5, ycolor-0.5, zcolor-0.5);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayScene()
{
    //Primitive Object dimensions

    float quadLength = 100, quadWidth = 60;
    float largeBoxLength = 200, largeBoxWidth = 100, largeBoxHeight = 10;
    float smallBoxLength = 150, smallBoxWidth = 70, smallBoxHeight = 30;
    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float tyreRadius = 100, tyreWidth = 40;


    /** Principal Axes **/

    displayAxes();
    glRotatef(boxAngle, 0, 0, 1);

    /**/

    /** Quad **/


    /*glRotatef(quadAngle, 1, 0, 0); // rotates with respect to x axis
    glRotatef(quadAngle, 0, 1, 0); // rotates with respect to y axis
    glRotatef(quadAngle, 0, 0, 1); // rotates with respect to z axis
    displayQuad(quadLength, quadWidth);*/


    /**/
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    /** Single Box **/

    //base
    glPushMatrix();
    /*glTranslatef(150, 0, 0); // rotation applied first, translation applied second
    glRotatef(boxAngle, 1, 0, 0); // rotates with respect to x axis
    glRotatef(boxAngle, 0, 1, 0); // rotates with respect to y axis*/
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 0, 0);    // translation applied first, rotation applied second
    displayBox(300, 200, 20, 0, 0, 0.75);
    glPopMatrix();

    //house body
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 0, 90);    // translation applied first, rotation applied second
    displayBox(280, 180, 200, 0.75, 0, 0);
    glPopMatrix();

    //roof
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 0, 190);    // translation applied first, rotation applied second
    displayBox(300, 220, 10, 0, 0.75, 0);
    glPopMatrix();

    //1st stairs
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 50, -7);    // translation applied first, rotation applied second
    displayBox(100, 240, 7, 0.75, 0.75, 0.75);
    glPopMatrix();

    //2nd stair
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 50, 0);    // translation applied first, rotation applied second
    displayBox(80, 220, 6, 0, 0.75, 0.75);
    glPopMatrix();

    //3rd stair
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 50, 6);    // translation applied first, rotation applied second
    displayBox(60, 190, 8, 0.75, 0.75, 0);
    glPopMatrix();

    //1st window holder
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(128, 0, 100);    // translation applied first, rotation applied second
    displayBox(30, 60, 5, 0, 0.75, 0.75);
    glPopMatrix();

    //1st window-move
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(141, 0, 100);
    glRotatef(quadAngle, 0, 1, 0); // rotates with respect to z axis
    fu =0;
    displayQuad(40, 50);
    glPopMatrix();

    //2nd window holder
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(-128, 0, 100);    // translation applied first, rotation applied second
    displayBox(30, 60, 5, 0, 0.75, 0.75);
    glPopMatrix();

    //2nd window-move
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(-141, 0, 100);
    //glRotatef(0, 0, 0, 1); // rotates with respect to z axis
    glTranslatef( 0, 0,winup);
    fu =0;
    displayQuad(40, 50);
    glPopMatrix();

    //chimney
    glPushMatrix();
    //glRotatef(boxAngldisplayQuade, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, -20, 160);    // translation applied first, rotation applied second
    displayBox(100, 80, 320, 0.7, 0.7, 0.0);
    glPopMatrix();

    //roof above the door
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 0, 110);    // translation applied first, rotation applied second
    displayBox(80, 195, 5, 0, 0, 0.7);
    glPopMatrix();

    //1st door 1st part
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(slidingDoor, 0, 0);
    glTranslatef(-20, 91, 50);    // translation applied first, rotation applied second
    //displayBox(80, 185, 150, 0.5, 0.58, 1.0);
    fu =1;
    displayQuad(125, 40);
    glPopMatrix();

    //1st door 2nd part
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(-slidingDoor, 0, 0);
    glTranslatef(20, 91, 50);    // translation applied first, rotation applied second
    //displayBox(80, 185, 150, 0.5, 0.58, 1.0);
    fu =2;
    displayQuad(125, 40);
    glPopMatrix();

    //2nd door 1st part
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis


    glTranslatef(40, -91, 59);    // translation applied first, rotation applied second
    fu =3;
    glRotatef(doorangle,0,0,1);
    displayQuad(98, 40);
    glPopMatrix();

    //2nd door 2nd part
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(-40, -91, 59);    // translation applied first, rotation applied second
    fu =4;
    glRotatef(-doorangle,0,0,1);
    displayQuad(98, 40);
    glPopMatrix();

    /** Tyre **/
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 30, 250);
    //glRotatef(tyreAngle, 1, 0, 0); // roates the tyre w.r.t x axis
    glRotatef(tyreAngle, 0, 1, 0); // roates the tyre w.r.t y axis
    glRotatef(90, 0, 0, 1); // roates the tyre w.r.t z axis
    fu = 0;
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(45, 20);
    glPopMatrix();

    //small tyre
    glPushMatrix();
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    glTranslatef(0, 30, 250);
    //glRotatef(tyreAngle, 1, 0, 0); // roates the tyre w.r.t x axis
    glRotatef(tyreAngle, 0, 1, 0); // roates the tyre w.r.t y axis
    glRotatef(90, 0, 0, 1); // roates the tyre w.r.t z axis
    fu = 1;
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(22.5, 20);
    glPopMatrix();


}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background, background, background,0);	//sets background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

    glutSwapBuffers();
}

void animate()
{
    //tinyBoxAngle += 0.05;

    if (tmp==1)
        tyreAngle -= 1;
    else if (tmp==2)
        tyreAngle+=1;
    else if( tmp==0)
        tyreAngle = tyreAngle;

    if(retmp==1)
    {
        if(winup==40)
            winup=40;
        else
            winup+=0.5;
    }
    else if(retmp==2)
    {
        if(winup<=0)
            winup=0;
        else
            winup-=0.5;
    }

    if (doorrotate ==1)
    {
        if(doorangle>=145)
            doorangle=145;
        else
            doorangle+=1;
    }
    else if (doorrotate ==2)
    {
        if (doorangle<=0)
            doorangle=0;
        else
            doorangle-=1;
    }
    glutPostRedisplay();
}

void tyre_moving_clockwise()
{
    tyreAngle +=0.05;
    glutPostRedisplay();

}
void tyre_moving_anticlockwise()
{
    tyreAngle -=0.05;
    glutPostRedisplay();

}

void init()
{
    glClearColor(background, background, background,0); 	//sets background color

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

    // to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
    if(id == 3)
    {
        retmp=1;

    }
    else if(id == 4)
    {
        retmp=2;

    }
}

void FanMenu(int id)
{
    if(id == 5)
    {
        tmp=1;
    }
    else if(id == 6)
    {
        tmp=2;
    }
    else if(id == 7)
    {
        tmp=0;
    }
}

void Door(int id)
{
    if (id == 8)
    {
        doorrotate=1;
    }
    else if (id == 9)
    {
        doorrotate = 2;
    }
}

void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    int subMenuNo = glutCreateMenu(subMenu);
    glutAddMenuEntry("Slide Up", 3);
	glutAddMenuEntry("Slide Down", 4);
	int FanMenuNo = glutCreateMenu(FanMenu);
    glutAddMenuEntry("Clockwise", 5);
	glutAddMenuEntry("Anti-Clockwise", 6);
    glutAddMenuEntry("Stop", 7);
    int doorNo = glutCreateMenu(Door);
    glutAddMenuEntry("Open", 8);
	glutAddMenuEntry("Close", 9);

    glutCreateMenu(mainMenu);
    glutAddSubMenu("WindowSlide", subMenuNo);
    glutAddSubMenu("Rotating Door", doorNo);
    glutAddSubMenu("Exhaust Fan", FanMenuNo);
    glutAddMenuEntry("Original Size", 10);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();		//The main loop of OpenGL, this function never returns

    return 0;
}
