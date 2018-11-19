#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    int children[2];
    printf("Beginning PARENT...\n");

    int file = open("/dev/random", O_RDONLY);
    unsigned int time;

    for (int child = 0 ; child < 2 ; child++) {

        if ( !(children[child] = fork()) ) {

            read( file , &time , sizeof(int) );
            close( file );
            time = abs((time % 16) + 5);

            printf("CHILD %d going to sleep...\n", child);
            sleep( time );
            printf("CHILD %d slept for %d seconds\n", child , time);
            exit( time );
        }

    }
    int pid = wait( &time );
    printf("CHILD PID: %d slept for %d seconds\n", pid, time / 255);
    printf("Ending PARENT...\n");

    return 0;

}
