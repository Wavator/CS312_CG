#include<GL/glut.h>
#include<gl/gl.h>
#include<gl/GLU.h>

void myDisplay()
{
	glClear(0x00004000);
	//glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("11612908 zhaoyu");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}