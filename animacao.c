
#include "modelo.h"

// quando alguem anda, ele realiza um leve deslocamento vertical de cima para
// baixo com cada passo, isso é calculado nesta função
double movimentacao_vertical(double angulo_coxa_esq, double angulo_panturr_esq,
                             double angulo_coxa_dir,
                             double angulo_panturr_dir) {

  double movimentacao_coxa, movimentacao_panturrilha, mov_perna_esquerda,
      mov_perna_direita, mov_coxa_rad, mov_panturrilha_rad;

  // converte angulos para radianos
  // calcula movimentacao vertical da perna ESQUERDA
  mov_coxa_rad = (PI * angulo_coxa_esq) / 180.0;
  mov_panturrilha_rad = (PI * angulo_panturr_esq - angulo_coxa_esq) / 180.0;

  movimentacao_coxa =
      (UP_LEG_HEIGHT + 2 * UP_LEG_JOINT_SIZE) * cos(mov_coxa_rad);
  movimentacao_panturrilha =
      (LO_LEG_HEIGHT + 2 * (LO_LEG_JOINT_SIZE + FOOT_JOINT_SIZE) +
       FOOT_HEIGHT) *
      cos(mov_panturrilha_rad);
  mov_perna_esquerda =
      LEG_HEIGHT - (movimentacao_coxa + movimentacao_panturrilha);

  // converte angulos para radianos
  // calcula movimentacao vertical da perna DIREITA
  mov_coxa_rad = (PI * angulo_coxa_dir) / 180.0;
  mov_panturrilha_rad = (PI * angulo_panturr_dir - angulo_coxa_dir) / 180.0;

  movimentacao_coxa =
      (UP_LEG_HEIGHT + 2 * UP_LEG_JOINT_SIZE) * cos(mov_coxa_rad);
  movimentacao_panturrilha =
      (LO_LEG_HEIGHT + 2 * (LO_LEG_JOINT_SIZE + FOOT_JOINT_SIZE) +
       FOOT_HEIGHT) *
      cos(mov_panturrilha_rad);
  mov_perna_direita =
      LEG_HEIGHT - (movimentacao_coxa + movimentacao_panturrilha);

  // compara a movimentação vertical de ambas as pernas, a que tiver menor
  // deslocamento é a perna que está tocando o chão, logo é retornada
  return (mov_perna_esquerda <= mov_perna_direita) ? (-mov_perna_esquerda)
                                                   : (-mov_perna_direita);
}
