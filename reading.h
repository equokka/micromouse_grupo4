#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLUMNS 67
#define ROWS 32

int **read_map(char filename[200])
{
  FILE *fp;
  char buff[COLUMNS];
  char c;

  // Reads text until newline is encountered
  if ((fp = fopen(filename, "r")) == NULL)
  {
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }

  // Cria um apontador
  int **maze;

  // O malloc aloca a memoria dinamicamente no apontador
  maze = malloc(sizeof(int*) * COLUMNS);
  for (int i = 0; i < COLUMNS; i++)
  { maze[i] = malloc(sizeof(int*) * ROWS); }

  FILE *fs;
  fs = fopen(filename, "r");

  // Valores:
  // Espaço vazio - 0 (int)
  // Limites - 1 (int)
  // Start - 2 (int)
  // Goal - 3 (int)

  for (int i = ROWS; i >= 0; i--){ //(!feof(fp))
    fgets(buff, COLUMNS, (FILE*)fs);

    printf("%s", buff);

    for (int j = 0; j < COLUMNS; j++)
    {
      if (buff[j] ==  ' ')
      { maze[i][j] = 0; }
      else if (buff[j] == 'S')
      { maze[i][j] = 2; }
      else if (buff[j] == 'G')
      { maze[i][j] = 3; }
      else
      { maze[i][j] = 1; }
    }
  }

  fclose(fp);

  // Retorna o apontador que aponta para a matriz
  return maze;
}

bool check_collision(int direction, int **maze, int *pos)
{
  int newpos;

  switch (direction)
  {
    case 0: newpos = maze[(pos[1] + 1) - 1][(pos[0]    ) - 1]; break;
    case 1: newpos = maze[(pos[1] - 1) - 1][(pos[0]    ) - 1]; break;
    case 2: newpos = maze[(pos[1]    ) - 1][(pos[0] + 1) - 1]; break;
    case 3: newpos = maze[(pos[1]    ) - 1][(pos[0] - 1) - 1]; break;
  }
  return (bool) newpos != 1;
}
