#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>

void printdir(char *dir, int depth)
{
    DIR *pdir;
    struct dirent *entry;
    struct stat statbuf;

    if((pdir=opendir(dir))==NULL){
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry=readdir(pdir))!=NULL){
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0){
                continue;
            }
            printf("%*s%s/\n",depth,"",entry->d_name);
            printdir(entry->d_name, depth+4);
        }
        else printf("%*s%s\n",depth, "",entry->d_name);
    }
    chdir("..");
    closedir(pdir);
}

int main(int argc, char *argv[])
{
    char *topdir = ".";
    if(argc >=2){
        topdir = argv[1];
    }
    printf("Directory scan of %s:\n", topdir);
    printdir(topdir,0);
    printf("done.\n");

    //exit(0);
    return 0;
}
