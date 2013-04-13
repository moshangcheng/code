#include <GL/glut.h>

static int shoulder = 0, elbow = 0;

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef (-1.0, 0.0, 0.0);
	glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
	glTranslatef (1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef (2.0, 0.4, 1.0);
	glutWireCube (1.0);
	glPopMatrix();

	glTranslatef (1.0, 0.0, 0.0);
	glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
	glTranslatef (1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef (2.0, 0.4, 1.0);
	glutWireCube (1.0);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//glFrustum, gluPerspective, glOrtho的参数都是在视点坐标系中的坐标值，它们都定义了裁剪后保留的区域。
	//gluLookAt定义了视点坐标和视线方向，视线方向没有物理意义，只是定义了视点坐标系的一个坐标轴(z轴)
	//选择透视投影时，投影平面相当于glFrustum和gluPerspective定义的近平面，然后等比例放大到glViewPort定义的长方形
	//选择正交投影时，投影平面还是glOrtho定义的近平面，但采用平行投影的方法
	glFrustum(-5.0, 5.0, -5.0, 5.0, 1.0, 7.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 's':   /*  s key rotates at shoulder  */
			shoulder = (shoulder + 5) % 360;
			glutPostRedisplay();
			break;
		case 'S':
			shoulder = (shoulder - 5) % 360;
			glutPostRedisplay();
			break;
		case 'e':  /*  e key rotates at elbow  */
			elbow = (elbow + 5) % 360;
			glutPostRedisplay();
			break;
		case 'E':
			elbow = (elbow - 5) % 360;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
