//Graphics Lab 7 Task 1 Koch Curve

#include <math.h>

#include<windows.h>
#include <GL/glut.h>


double cameraAngle;
double cameraRadius;
double cameraHeight;
double cameraAngleDelta;

double x;
double y;
double direction;
double ang;
double rot;


/*void drawXYZAxis(int length)
{
	// draw the three major AXIS
	glBegin(GL_LINES);

	//X axis
	glColor3f(0, 1, 0);//green
	glVertex3f(-length, 0, 0);
	glVertex3f(length, 0, 0);

	//Y axis
	glColor3f(0, 0, 1);//blue
	glVertex3f(0, -length, 0);
	glVertex3f(0, length, 0);

	//Z axis
	glColor3f(1, 1, 1);//white
	glVertex3f(0, 0, -length);
	glVertex3f(0, 0, length);
	glEnd();
}
*/
void drawGridLines(int length)
{
	//some gridlines along the field
	int i;

	glColor3f(0.5, 0.5, 0.5);//gray

	glBegin(GL_LINES);

	for( i = -(length / 10); i <= (length / 10); i++ )
	{
		if( i == 0 )
		{
			continue;//SKIP the MAIN axes
		}

		//lines parallel to X-axis
		glVertex3f(-length, i * 10, 0);
		glVertex3f(length, i * 10, 0);

		//lines parallel to Y-axis
		glVertex3f(i * 10, -length, 0);
		glVertex3f(i * 10, length, 0);
	}
	glEnd();
}

void leftRotate(double angle)
{
	direction += angle;
}

void rightRotate(double angle)
{
	direction -= angle;
}

void drawStraightLine(double length)
{
	double newX;
	double newY;

	newX = x + (length * cos(3.1416 * direction / 180));
	newY = y + (length * sin(3.1416 * direction / 180));

	glBegin(GL_LINES);
	{
		glColor3f(.5, .8, 1);

		glVertex2f(x, y);
		glVertex2f(newX, newY);
	}
	glEnd();

	x = newX;
	y = newY;
}

void kochCurve(int order, double length)
{
	if( order == 0 )
	{
		drawStraightLine(length);
		return;
	}

	kochCurve((order - 1), (length / 3));

	leftRotate(60);
	kochCurve((order - 1), (length / 3));

	rightRotate(120);
	kochCurve((order - 1), (length / 3));

	leftRotate(60);
	kochCurve((order - 1), (length / 3));
}

 void snowflake(int order,int length)
 {

     kochCurve(order,length);
     rightRotate(120);
     kochCurve(order,length);
     rightRotate(120);
     kochCurve(order,length);



 }
void reset()
{
	x = -50;
	y = 25;
	direction = 0;
}

void display()
{
	//codes for Models, Camera

	//clear the display
	//color black
	glClearColor(0, 0, 0, 0);

	//clear buffers to preset values
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/*** set-up camera (view) here ***/

	//load the correct matrix -- MODEL-VIEW matrix
	//specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	//gluLookAt(200 * sin(cameraAngle), -200 * cos(cameraAngle), 100, 0, 0, 50, 0, 0, 1);
	gluLookAt(cameraRadius * sin(cameraAngle), -cameraRadius * cos(cameraAngle), cameraHeight, 0, 0, 0, 0, 0, 1);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/*** Grid and axes Lines(You can remove them if you want) ***/



	//drawGridLines(200);//grid line length


	/*** Add your objects from here ***/
	reset();

	glRotatef(90, 1, 0, 0);
	glLineWidth(5);
	glColor3f(0, 0, 1);
    glRotatef(rot,0,0,1);
	snowflake(5,100);
	//drawStraightLine(200);

//drawXYZAxis(300);//axis length

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate()
{
	//codes for any changes in Models, Camera

	//camera will rotate at 0.0001 radians per frame.
	//cameraAngle += 0.0005;


	//codes for any changes in Models

	//this will call the display AGAIN
	rot+=.3;
	glutPostRedisplay();
}

void init()
{
	//codes for initialization

	//angle in radian
	cameraAngle = 0;
	cameraRadius = 200;
	cameraHeight = 100;
	cameraAngleDelta = 0.001;

	//clear the screen
	glClearColor(0, 0, 0, 0);


	/*** set-up projection here ***/

	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();
    rot=0;
	/*
	gluPerspective() — set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);
}

void keyboardListener(unsigned char key, int x, int y)
{
	if( key == '+' )
	{
		if( cameraRadius > 10 )
		{
			cameraRadius -= 10;
		}
	}
	if( key == '-' )
	{
		cameraRadius += 10;
	}

	else if( key == '0' )
	{
		//
	}
	else if( key == '1' )
	{
		//
	}
	else if( key == '2' )
	{
		//
	}
	else if( key == '3' )
	{
		//
	}
	else if( key == '4' )
	{
		//
	}
	else if( key == '5' )
	{
		//
	}
	else if( key == '6' )
	{
		//
	}
	else if( key == '7' )
	{
		//
	}
	else if( key == '8' )
	{
		//
	}
	else if( key == '9' )
	{
		//
	}
	else
	{
		//
	}
}

void specialKeyListener(int key, int x, int y)
{
	if( key == GLUT_KEY_UP )
	{
		cameraHeight += 10;
	}
	else if( key == GLUT_KEY_DOWN )
	{
		cameraHeight -= 10;
	}
	else if( key == GLUT_KEY_LEFT )
	{
		cameraAngle -= 0.05;
	}
	else if( key == GLUT_KEY_RIGHT )
	{
		cameraAngle += 0.05;
	}
	else if( key == GLUT_KEY_HOME )
	{
		cameraAngle = 0;
		cameraRadius = 200;
		cameraHeight = 100;
		cameraAngleDelta = 0.001;

		direction = 0;
	}
}

void mouseListener(int button, int state, int x, int y)
{
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		cameraAngleDelta = -cameraAngleDelta;
	}
	if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
	{
		//
	}
}

int main(int argc, char **argv)
{
	//initialize the GLUT library
	glutInit(&argc, argv);

	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Graphics Lab 7 Task 1 Koch Curve");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	//what you want to do in the idle time (when no drawing is occuring)
	glutIdleFunc(animate);


	//add keyboard listener:
	glutKeyboardFunc(keyboardListener);

	//add special keyboard listener:
	glutSpecialFunc(specialKeyListener);

	//add special keyboard listener:
	glutMouseFunc(mouseListener);


	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}
