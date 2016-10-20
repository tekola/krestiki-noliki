#include  <GL/glut.h>
#include <math.h>

static int N = 5, M = 5; 
static int Scale = 100; 
static int W = 506; 
static int H = 506; 
static int Cursor = 100 ;
static int Scale1 = 101;
static int CourseX = 0;
static int CourseY = 0;
static int move = 1;
static int nX = 0, n0 = 0;

struct
	{int x;
	int y;}  s[1];

void DrawField()
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINES);

		for (int i = 0; i <= W; i += Scale1)
			{glVertex2f(i,0); glVertex2f(i,H);} 
		for (int j = 0; j <= H; j += Scale1)
			{glVertex2f(0,j); glVertex2f(W,j);} 

	glEnd();
}

void DrawC()
{
	int x= s[0].x, y= s[0].y;
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(x + CourseX, y + CourseY);
		glVertex2f(x + CourseX, y + Cursor + CourseY);
		glVertex2f(x + Cursor + CourseX, y + Cursor + CourseY);
		glVertex2f(x+ Cursor + CourseX, y + CourseY);
	glEnd();
}

void DrawX()
{
	int x= s[0].x, y= s[0].y;

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINES);

		glVertex2f(x + CourseX + 5, y + CourseY + 5);
		glVertex2f(x + Cursor + CourseX - 5, y + Cursor + CourseY - 5);

		glVertex2f(x + CourseX + 5, y + Cursor + CourseY - 5);
		glVertex2f(x + Cursor + CourseX - 5, y + CourseY + 5);

	glEnd();
	
}

void Draw0()
{
	int x = s[0].x, y = s[0].y;

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 10; i++)
	{
		double angle = 2.0 * 3.1415926 * i / 10.;
		double dx = 45 * cosf(angle);
		double dy = 45 * sinf(angle);
		glVertex2f(x + 50 + dx, y + 50 + dy);
	}
	glEnd();
}

void DrawMove()
{
	if(move!=0)
	{
		if (move == 2)
		{
			DrawX();
		}
		else if (move ==3)
		{
			Draw0();
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	
	DrawField();

	DrawC();

	DrawMove();

	glFlush();
}

void KeyboardEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': s[0].y += 100, CourseY += 1; break;
	case 'd': s[0].x += 100, CourseX += 1; break;
	case 'a': s[0].x -= 100, CourseX += -1; break;
	case 's': s[0].y -= 100, CourseY += -1; break;
	
	case 'z': move = 1; break;
	case 'x': move = 2; break;
	case 'c': move = 3; break;
	
	case 13: move++ ; break;
	}
}

void timer()
{
	display();

	

	glutTimerFunc(10, timer, 0);
}

int main(int argc, char **argv)
{
	s[0].x = 203;
	s[0].y = 203;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutCreateWindow("Test");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, W, 0, H);
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyboardEvent);
	glutTimerFunc(10, timer, 0);
	glutMainLoop();
}
