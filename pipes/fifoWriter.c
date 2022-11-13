#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxLoops 12000 /* outer loop */
#define ChunkSize 16   /* how many written at a time */
#define IntsPerChunk 4 /* four 4-byte ints per chunk */
#define MaxZs 250      /* max microseconds to sleep */

int main()
{
  while (1)
  {
    const char *pipeName = "./pipes/fifoChannel";
    mkfifo(pipeName, 0666);                      /* read/write for user/group/others */
    int fd = open(pipeName, O_CREAT | O_WRONLY); /* open as write-only */
    if (fd < 0)
      return -1; /** error **/
    int i;
    for (i = 0; i < MaxLoops; i++)
    { /* write MaxWrites times */
      int j;
      for (j = 0; j < ChunkSize; j++)
      { /* each time, write ChunkSize bytes */
        int k;
        int chunk[IntsPerChunk];
        for (k = 0; k < IntsPerChunk; k++)
          chunk[k] = rand();
        write(fd, chunk, sizeof(chunk));
      }
      usleep((rand() % MaxZs) + 1); /* pause a bit for realism */ /* close pipe: generates an end-of-file */
    }
    close(fd);
    unlink(pipeName);
    printf("%i ints sent to the pipe.\n", MaxLoops * ChunkSize * IntsPerChunk); /* unlink from the implementing file */
  }

  return 0;
}
