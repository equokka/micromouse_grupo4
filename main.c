#include <stdio.h>
#include <moving.h>
#include <reading.h>

int main(int argc, char* argv[])
{
  int **maze;

  // Limpar o ecrã
  clearscreen();

  // Colocar o terminal no modo cbreak ou rare
  cbreak();

  // Retorna a matriz
  maze = ler(argc, argv);

  // Inicia o movimento do cursor utilizando a matriz
  mapa(maze);

  // Por o terminal de volta no modo cooked
  nocbreak();

  clearscreen();

  return 0;
}

