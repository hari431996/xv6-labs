// // #include<stdio.h>
// // #include<stdlib.h>
// // #include<sys/wait.h>
// // #include<unistd.h>

// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"


// void new_process(int pfd[]){
//     close(pfd[1]); // should close the write  end of the pipe
//     int flag;
//     int n;
//     int prime;
//     read(pfd[0], &prime, 4); // This is the first read after creating the process.
//     printf("prime %d\n", prime);

//     // keep reading new values . If the values.
//     flag = read(pfd[0], &n, 4);
//     if(flag){
       
//         int newP[2];
//         pipe(newP);
//          // create a new process.
//          if (fork() == 0){
//             new_process(newP);

//          }else{
//             // if in this process keep reading the values 
//             // if not divisible by prime then write to newP[1];
//             close(newP[0]);
//             do
//             {
//                if (n % prime){
//                     // if n is not divisble by prime then send to the next child process.
//                     write(newP[1], &n, 4);
//                 }
//             } while (read(pfd[0], &n, 4) > 0);
//             close(pfd[0]);
//             close(newP[1]); // close the read side of the newP.
//             wait(0); // wait for the process to complete.
            
            
//          }
      


    

   
        

// }

// exit(0);

// }



// int main(){
//     int p[2];

//     pipe(p);

//     int pid = fork();

//     if (pid == 0){
//         new_process(p);
//     }else{
//         close(p[0]);
//         for (int i = 2; i <= 10; i++){
            
           
           
//             write(p[1],&i , 4);

//         }

//         close(p[1]);
//         wait(0);
//         exit(0);


//     }


// }



#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void new_proc(int p[2]){
	int prime;
	int flag;
	int n;
	close(p[1]);
	if(read(p[0], &prime, 4) != 4){
		fprintf(2, "child process failed to read\n");
		exit(1);
	}
	printf("prime %d\n", prime);

	flag = read(p[0], &n, 4);
	if(flag){
		int newp[2];
		pipe(newp);
		if (fork() == 0)
		{
			new_proc(newp);
		}else
		{
			close(newp[0]);
			if(n%prime)write(newp[1], &n, 4);
			
			while(read(p[0], &n, 4)){
				if(n%prime)write(newp[1], &n, 4);
			}
			close(p[0]);
			close(newp[1]);
			wait(0);
		}
	}
	exit(0);
}

int main(int argc, char const *argv[])
{
	int p[2];
	pipe(p);
	if (fork() == 0)
	{
		new_proc(p);
	}else
	{
		close(p[0]);
		for(int i = 2; i <= 35; i++)
		{
			if (write(p[1], &i, 4) != 4)
			{
				fprintf(2, "first process failed to write %d into the pipe\n", i);
				exit(1);
			}
		}
		close(p[1]);
		wait(0);
		exit(0);
	}
	return 0;
}