#include <stdio.h>
#include  <glut.h>
#include <math.h>
#include <windows.h>
#include <Winuser.h>
#include <Winbase.h>

static int N = 20, M = 20;
static int Scale = 25;
static int W = 520;
static int H = 520;
static int Cursor = 24;
static int Scale1 = 25;
static int CourseX = 0;
static int CourseY = 0;
static int move = 1;
static int nX = 0, n0 = 0;
static int coord_x = 0;
static int coord_y = 0;

struct
{
	int x;
	int y;
}  s[1];

void DrawField()
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINES);

	for (int i = 0; i <= W; i += Scale1)
	{
		glVertex2f(i, 0); glVertex2f(i, H);
	}
	for (int j = 0; j <= H; j += Scale1)
	{
		glVertex2f(0, j); glVertex2f(W, j);
	}

	glEnd();
}

void DrawC(int mx, int my)
{
	//int x = s[0].x, y = s[0].y;
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2f(mx, 524-my);
	glVertex2f(mx, 524-(Cursor + my));
	glVertex2f(Cursor + mx, 524-(Cursor + my));
	glVertex2f(Cursor + mx, 524-my);
	glEnd();
}

void DrawX()
{
	int x = s[0].x, y = s[0].y;

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
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 10; i++)
	{
		double angle = 2.0 * 3.1415926 * i / 10.;
		double dx = 5 * cosf(angle);
		double dy = 5 * sinf(angle);
		glVertex2f(x + 12 + dx, y + 12 + dy);
	}
	glEnd();
}

void DrawMove()
{
	if (move != 0)
	{
		if (move == 2)
		{
			DrawX();
		}
		else if (move == 3)
		{
			Draw0();
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	DrawField();

	DrawC(coord_x, coord_y);

	DrawMove();

	glFlush();
}

/* void KeyboardEvent(unsigned char key, int x, int y)
{
switch (key)
{
case 'w': s[0].y += 24, CourseY += 1; break;
case 'd': s[0].x += 24, CourseX += 1; break;
case 'a': s[0].x -= 24, CourseX += -1; break;
case 's': s[0].y -= 24, CourseY += -1; break;

case 'z': move = 1; break;
case 'x': move = 2; break;
case 'c': move = 3; break;

case 13: move++ ; break;
}
}*/

void mouse()
{
	POINT cp;
	GetCursorPos(&cp);
	coord_x = cp.x/25*25 ;
	coord_y = ((cp.y / 25) -1) * 25;
	glutPostRedisplay();
	glutTimerFunc(10, mouse, 0);
}

void timer()
{
	display();
	glutTimerFunc(10, timer, 0);
}

int main(int argc, char **argv)
{
	SetCursorPos(20, 25);
	s[0].x = 200;
	s[0].y = 200;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutCreateWindow("Test");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, W, 0, H);
	glutDisplayFunc(display);
	//glutKeyboardFunc(KeyboardEvent);
	glutTimerFunc(10, timer, 0);
	glutTimerFunc(10, mouse, 0);
	glutMainLoop();
}
