/* GLUT Implementation */
#include "glShared.h"

#ifdef __APPLE
	#include <glut.h>
#else
	#define GLUT_DISABLE_ATEXIT_HACK
	#include <GL/glut.h>
#endif

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
			main_player->direction  = ENTITY_DIR_UP;
			*main_timerStart = 1;
			break;
		case GLUT_KEY_DOWN:
			main_player->direction = ENTITY_DIR_DOWN;
			*main_timerStart = 1;
			break;
		case GLUT_KEY_LEFT:
			main_player->direction = ENTITY_DIR_LEFT;
			*main_timerStart = 1;
			break;
		case GLUT_KEY_RIGHT:
			main_player->direction = ENTITY_DIR_RIGHT;
			*main_timerStart = 1;
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

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player
) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow(PROGRAM_NAME " v" PROGRAM_VERSION " - GLUT");
	glutReshapeWindow(RENDER_WIDTH, RENDER_HEIGHT);
	
	glSharedInit(timerStart, player);
	
	glutKeyboardFunc(input);
	glutSpecialFunc(inputSpecial);
	glutDisplayFunc(draw);
	glutTimerFunc(1000 / MAX_FPS, drawLoop, 0);
	
	glutMainLoop();
	return;
}