
#include "modelo.h"

void quadril() {
  glPushMatrix();

  glScalef(BASE_WIDTH, BASE_HEIGHT, TORSO);
  glColor3f(0.0, 1.0, 1.0);
  glutWireCube(1.0);

  glPopMatrix();
}

void coxa() {
  glPushMatrix();

  glScalef(UP_LEG_JOINT_SIZE, UP_LEG_JOINT_SIZE, UP_LEG_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glTranslatef(0.0, -UP_LEG_HEIGHT * 0.75, 0.0);

  glPushMatrix();

  glScalef(UP_LEG_WIDTH, UP_LEG_HEIGHT, UP_LEG_WIDTH);
  glColor3f(0.5, 0.5, 0.5);
  glutWireCube(1.0);

  glPopMatrix();
}

void panturrilha() {
  glPushMatrix();

  // desenha joelho
  glScalef(LO_LEG_JOINT_SIZE, LO_LEG_JOINT_SIZE, LO_LEG_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glTranslatef(0.0, -LO_LEG_HEIGHT * 0.75, 0.0);

  glPushMatrix();

  glScalef(LO_LEG_WIDTH, LO_LEG_HEIGHT, LO_LEG_WIDTH);
  glColor3f(1.0, 0.0, 1.0);
  glutWireCube(1.0);

  glPopMatrix();
}

void pe() {
  glPushMatrix();

  // desenha tornozelo
  glScalef(FOOT_JOINT_SIZE, FOOT_JOINT_SIZE, FOOT_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutWireSphere(1.0, 8, 8);

  glPopMatrix();

  glTranslatef(0.0, -FOOT_HEIGHT * 0.75, FOOT_WIDTH * 0.5);

  glPushMatrix();

  glScalef(FOOT_WIDTH, FOOT_HEIGHT, FOOT);
  glColor3f(0.5, 0.0, 1.0);

  glutWireCube(1.0);

  glPopMatrix();
};

void perna() {
  glPushMatrix();

  // glRotatef(walking_angles[side][3], 1.0, 0.0, 0.0);
  coxa();
  glTranslatef(0.0, -UP_LEG_HEIGHT * 0.75, 0.0);
  // glRotatef(walking_angles[side][4], 1.0, 0.0, 0.0);

  panturrilha();
  glTranslatef(0.0, -LO_LEG_HEIGHT * 0.625, 0.0);
  // glRotatef(walking_angles[side][5], 1.0, 0.0, 0.0);

  pe();

  glPopMatrix();
}

void pernas() {
  glPushMatrix();

  // desenha o quadril na origem
  glTranslatef(0.0, 0.0, 0.0);
  quadril();

  // desce a altura para as pernas
  glTranslatef(0.0, -(BASE_HEIGHT), 0.0);

  // perna direita
  glPushMatrix();
  glTranslatef(TORSO_WIDTH * 0.33, 0.0, 0.0);
  perna();
  glPopMatrix();

  // perna esquerda
  glPushMatrix();
  glTranslatef(-TORSO_WIDTH * 0.33, 0.0, 0.0);
  perna();
  glPopMatrix();

  glPopMatrix();
}
