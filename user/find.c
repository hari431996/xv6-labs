#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



// Note its important pass the file path exaclty as its in  the file system else stat will return 0.

void find(char* path, char *fileName){

    char buf[512], *p;
    struct stat buffer;
    struct dirent de;
    int fd = open(path, O_RDONLY);
  

  

   
   
    
    
   
    strcpy(buf, path);
	p = buf + strlen(buf);
   
    *p++ = '/';
   
   
    while(read(fd, &de, sizeof(de)) == sizeof(de)){

     

        if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name , "..") == 0){
                    continue;

        }
       
        memmove(p, de.name, DIRSIZ);  // copies the de.name from its location de.name to p starting point , this does not change the pointer.
		p[DIRSIZ] = 0;

       


        printf("This is file path passed to stat%s \n", de.name);
        stat(buf, &buffer);

        

        




       

      
        if( T_FILE == buffer.type){
            
            if (strcmp(de.name, fileName) == 0){
                printf("%s/%s \n",path,  de.name);
            }
            
        }

        if( T_DIR == buffer.type){
                   
            
            printf("Calling subdir %s", de.name);
            find(buf, fileName);
            
        }


        
    }
    close(fd);
    

    
}

int main(int argc, char *argv[]){

    if (argc < 3){
        printf("The right usage \nfind <directory_name> <file_name>\n");
    }

    char *dirName; 
    dirName = argv[1];
    char *fileName = argv[2];

    find(dirName, fileName); 

    return 0;
    

}
