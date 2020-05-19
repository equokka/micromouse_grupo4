#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> // for usleep()

#include <moving.h>
#include <reading.h>

#define DEFAULT_MAP "./maps/86.txt"

int main(int argc, char* argv[])
{
  int socketfd;
  int ret;
  char buff[255];
  bool quitting = false;
  bool error = false;
  int **maze;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int len = sizeof(struct sockaddr_in);
  char *map_name = (argc > 1 ? argv[1] : DEFAULT_MAP);

  // Get map from 1st argument, use DEFAULT MAP if none is given
  maze = read_map(map_name);

  // Create socket
  socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketfd < 0)
  { printf("Socket error\n"); return 1; }

  // Wildcards
  server.sin_family = AF_INET;
  server.sin_port = htons(8000);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Bind
  ret = bind(socketfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
  if (ret)
  { printf("Error while binding\n"); return 1; }

  int *pos = map_setup(maze);

  system("clear");

  do
  {
    // Receive message from client
    ret = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&client, &len);
    // Error handling
    if (ret < 0)
    {
      printf("Error when receiving\n");
      quitting = true;
      error = true;
    }

    // Now we need to handle the client message.

    // Print it on the server:
    printf("<= CLIENT: %s\n", buff);

    // 50 millisecond simulated delay
    // FIXME
    usleep(50 * 1000);

    // W,A,S,D,Q,NO,OK are just an example of what kinds of codes the server
    // and client could use to communicate. Our message buffer has a size of
    // 255 so we could for instance send some simple serialized data
    // though, in JSON for example.

    // HELLO - Hail message from client.
    if (strcmp(buff, "HELLO") == 0)
    {
      // Reply with the map filename
      strcpy(buff, map_name);
    }
    // q - Quit
    else if (strcmp(buff, "q") == 0 || strcmp(buff, "Q") == 0)
    {
      snprintf(buff, sizeof(buff), "OK");
      quitting = true;
    }
    else if (
      strcmp(buff, "w") == 0 ||
      strcmp(buff, "s") == 0 ||
      strcmp(buff, "d") == 0 ||
      strcmp(buff, "a") == 0 )
    {
      if      ((strcmp(buff, "w") == 0 || strcmp(buff, "W") == 0) && check_collision(0, maze, pos))
      {
        pos[1] += 1;
        snprintf(buff, sizeof(buff), "OK");
      }
      else if ((strcmp(buff, "s") == 0 || strcmp(buff, "D") == 0) && check_collision(1, maze, pos))
      {
        pos[1] -= 1;
        snprintf(buff, sizeof(buff), "OK");
      }
      else if ((strcmp(buff, "d") == 0 || strcmp(buff, "S") == 0) && check_collision(2, maze, pos))
      {
        pos[0] += 1;
        snprintf(buff, sizeof(buff), "OK");
      }
      else if ((strcmp(buff, "a") == 0 || strcmp(buff, "A") == 0) && check_collision(3, maze, pos))
      {
        pos[0] -= 1;
        snprintf(buff, sizeof(buff), "OK");
      }
      else
      { snprintf(buff, sizeof(buff), "NO"); }
    }
    else
    {
      printf("No behavior defined for message received:\n%s\n", buff);
      snprintf(buff, sizeof(buff), "ERROR");
      quitting = true;
      error = true;
    }

    // Print the server's response on the server:
    printf("=> SERVER: %s (%d, %d)\n", buff, pos[0], pos[1]);

    // Send the response to the client:
    ret = sendto(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&client, sizeof(client));
    // Error handling
    if (ret < 0)
    {
      printf("Error when sending\n");
      quitting = true;
      error = true;
    }
  } while (quitting == false);

  close(socketfd);

  return (error ? 1 : 0);
}

