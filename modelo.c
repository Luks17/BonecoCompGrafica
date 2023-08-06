
#include "modelo.h"

void quadril() {
  glPushMatrix();

  glScalef(BASE_WIDTH, BASE_HEIGHT, TORSO);
  glColor3f(0.0, 1.0, 1.0);
  glutSolidCube(1.0);

  glPopMatrix();
}

void coxa() {
  glPushMatrix();
  glScalef(UP_LEG_JOINT_SIZE, UP_LEG_JOINT_SIZE, UP_LEG_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutSolidSphere(1.0, 8, 8);
  glPopMatrix();
  glTranslatef(0.0, -UP_LEG_HEIGHT * 0.75, 0.0);
  glPushMatrix();
  glScalef(UP_LEG_WIDTH, UP_LEG_HEIGHT, UP_LEG_WIDTH);
  glColor3f(1.0, 1.0, 0.0);
  glutSolidCube(1.0);
  glPopMatrix();
}

void perna(int side) {
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

void panturrilha() {
  glPushMatrix();
  glScalef(LO_LEG_JOINT_SIZE, LO_LEG_JOINT_SIZE, LO_LEG_JOINT_SIZE);
  glColor3f(0.0, 1.0, 0.0);
  glutSolidSphere(1.0, 8, 8);
  glPopMatrix();
  glTranslatef(0.0, -LO_LEG_HEIGHT * 0.75, 0.0);
  glPushMatrix();
  glScalef(LO_LEG_WIDTH, LO_LEG_HEIGHT, LO_LEG_WIDTH);
  glColor3f(1.0, 0.0, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();
}

void pe() {
  glPushMatrix();

  glScalef(1.0, 0.5, 1.0);
  glColor3f(1.0, 1.0, 1.0);

  glutSolidCube(1.0);

  glPopMatrix();
};

void pernas(void) {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  quadril();
  glTranslatef(0.0, -(BASE_HEIGHT), 0.0);
  glPushMatrix();
  glTranslatef(TORSO_WIDTH * 0.33, 0.0, 0.0);
  perna(0);
  glPopMatrix();
  glTranslatef(-TORSO_WIDTH * 0.33, 0.0, 0.0);
  perna(0);
  glPopMatrix();
}
