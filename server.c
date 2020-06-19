#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <moving.h>
#include <reading.h>
#include <pthread.h>

#define PORT 8080
#define DEFAULT_MAP "./maps/86.txt"

pthread_t producert, consumert;
pthread_cond_t  empt  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  full  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

char *map_name;

void *producer();
void *consumer();

int socketfd;
int ret;
char buff[255];
bool quitting = false;
bool error = false;
int counterino = 0;
int **maze;
int *pos;
struct sockaddr_in server;
struct sockaddr_in client;
int len = sizeof(struct sockaddr_in);

int main(int argc, char* argv[])
{
  // Create socket
  socketfd = socket(AF_INET, SOCK_DGRAM, 0);//domain,type,protocolo
  if (socketfd < 0)
  { printf("Socket error\n"); return 1; }

  // Wildcards
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");
  server.sin_port = htons(PORT);//htons(8000);

  // Bind
  ret = bind(socketfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
  if (ret)
  { printf("Error while binding\n"); return 1; }

  system("clear");

  // Get map from 1st argument, use DEFAULT MAP if none is given
  map_name = (argc > 1 ? argv[1] : DEFAULT_MAP);
  maze = read_map(map_name);
  pos = map_setup(maze);

  while(quitting == false) {
    pthread_create(&producert, NULL, producer, NULL);
    pthread_create(&consumert, NULL, consumer, NULL);
    pthread_join(producert, NULL);
    pthread_join(consumert, NULL);
  }

  close(socketfd);
  exit(error ? 1 : 0);
}

void *producer()
{
  pthread_mutex_lock(&mutex);
  while (counterino == 1) { pthread_cond_wait(&empt, &mutex); }

  // Receive message from client
  ret = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&client, &len);
  if (ret < 0)
  {
    printf("Error when receiving\n");
    quitting = true;
    error = true;
  }

  counterino++;
  pthread_cond_signal(&full);
  pthread_mutex_unlock(&mutex);
}

void *consumer()
{
  pthread_mutex_lock(&mutex);

  while (counterino == 0) { pthread_cond_wait(&full, &mutex); }

  // Now we need to handle the client message.

  // Print it on the server:
  printf("<= CLIENT: %s\n", buff);

  // 50 millisecond simulated delay
  // FIXME
  usleep(50 * 1000);
  //sleep(0.5)

  // W,A,S,D,Q,NO,OK are just an example of what kinds of codes the server
  // and client could use to communicate. Our message buffer has a size of
  // 255 so we could for instance send some simple serialized data
  // though, in JSON for example.

  // HELLO - Hail message from the client.
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

  counterino--;
  pthread_cond_signal(&empt);
  pthread_mutex_unlock(&mutex);
}
