#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>


// The program is correct but its failling dont know why though.

int
main(){

    int p[2];

    pipe(p);

    int pid = fork();

    if (pid == 0){
        // this is child process
        char child_buf[2];
        read(p[0], child_buf, 2);
        printf("%d: received ping\n", getpid(), child_buf);
        close(p[0]);
        write(p[1], "a\n", 5);
      
        exit(0);

    }else{
        // this is parent process
        write(p[1], "a\n", 1); // writing to the pipe ping.
        close(p[1]); // close writing part of the pipe so that child can execute and exit
        wait((int *) 0 ); // wait till child returns.

        char main_buf[1];
        read(p[0], main_buf, 1); // read from the buffer and then exit.
        printf("%d: received pong\n", getpid());
        close(p[0]);
        exit(0);

        

    }

    














    exit(0);
}