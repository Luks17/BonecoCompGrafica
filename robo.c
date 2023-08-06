
#include "modelo.c"

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutCreateWindow("Trabalho de Comp Grafica");

  init();

  glutMainLoop();

  return -1;
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  quadril();
  pernas();

  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1.0, 0.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
