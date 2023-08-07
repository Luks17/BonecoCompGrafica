
#include "movimento.h"

// equivalente ao enum coord, ou seja:
// coordenadaEstaAumentando[0] = x
// coordenadaEstaAumentando[1] = y
// coordenadaEstaAumentando[2] = z
bool coordenadaEstaAumentando[] = {true, true, true};

char coordenadas[] = {'x', 'y', 'z'};

void ajustaCoordenada(float *valor, enum coordenada coord, bool tentaAumentar) {
  short multiplicador = tentaAumentar ? 1 : -1;

  // se coordenada estiver aumentando e chegar no limite, ela vai passar a
  // diminuir
  // se coordenada estiver diminuindo e chegar no -limite, ela vai passar a
  // aumentar
  // caso tentaAumentar for falso, o que foi dito acima sera invertido
  if (*valor >= (float)LIMITE) {
    coordenadaEstaAumentando[coord] = !tentaAumentar;
  } else if (*valor <= ((-1) * (float)LIMITE)) {
    coordenadaEstaAumentando[coord] = tentaAumentar;
  }

  if (coordenadaEstaAumentando[coord])
    *valor += MOVIMENTO * multiplicador;
  else {
    *valor -= MOVIMENTO * multiplicador;
  }

  // DEBUG
  //
  // if (coord != coordz) {
  //   printf("%c = %f - ", coordenadas[coord], *valor);
  //   if (coordenadaEstaAumentando[coord])
  //     printf("Esta Aumentando\n");
  //   else
  //     printf("Nao esta Aumentando\n");
  // }
}
