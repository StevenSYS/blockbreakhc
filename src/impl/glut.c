/* GLUT Implementation */
#ifdef __APPLE
	#include <glut.h>
#else
	#include <GL/glut.h>
#endif

#include "progInfo.h"
#include "glShared.h"

static void input(
	unsigned char key,
	int x, int y
) {
	random_increase();
	switch (key) {
		case '\r': /* Enter */
			reset();
			break;
		default:
			break;
	}
}

static void inputSpecial(
	int key,
	int x, int y
) {
	random_increase();
	switch (key) {
		case GLUT_KEY_UP:
			player.direction  = ENTITY_DIR_UP;
			timerStart = 1;
			break;
		case GLUT_KEY_DOWN:
			player.direction = ENTITY_DIR_DOWN;
			timerStart = 1;
			break;
		case GLUT_KEY_LEFT:
			player.direction = ENTITY_DIR_LEFT;
			timerStart = 1;
			break;
		case GLUT_KEY_RIGHT:
			player.direction = ENTITY_DIR_RIGHT;
			timerStart = 1;
			break;
		default:
			break;
	}
	return;
}

static void drawLoop(int msecs) {
	glutPostRedisplay();
	glutTimerFunc(1000 / MAX_FPS, drawLoop, 0);
	return;
}

void impl_loopEnd() {
	glFlush();
	return;
}

void impl_init(int argc, char *argv[]) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow(PROGRAM_NAME " v" PROGRAM_VERSION " - GLUT");
	glutReshapeWindow(RENDER_WIDTH, RENDER_HEIGHT);
	
	glSharedInit();
	
	glutKeyboardFunc(input);
	glutSpecialFunc(inputSpecial);
	glutDisplayFunc(draw);
	glutTimerFunc(1000 / MAX_FPS, drawLoop, 0);
	
	glutMainLoop();
	return;
}