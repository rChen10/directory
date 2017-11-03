#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void advance(struct dirent **d, DIR *dr){
  *d = readdir(dr);
}

int stat_size(struct dirent *d){
  struct stat sb;
  stat(d->d_name, &sb);
  return sb.st_size;
}

int add_entry(char *s, char *name){
  strcat(s, "\t");
  strcat(s, name);
  strcat(s, "\n");
}

int main(){
  DIR *dr = opendir(".");
  struct dirent *data = readdir(dr);

  //set up
  char *dirs = malloc(200);
  strcpy(dirs, "Directories:\n");
  char *regs = malloc(800);
  strcpy(regs, "Regular files:\n");
  int size = 0;

  //print filenames
  while (data){
    if (data->d_type == DT_DIR){
      add_entry(dirs, data->d_name);
    }
    
    if (data->d_type == DT_REG){
      add_entry(dirs, data->d_name);
      
      size += stat_size(data);
    }

    if (data->d_type == DT_UNKNOWN){
      printf("%s\t\tDT_KNOWN\n", data->d_name);
      
      size += stat_size(data); //since my filesystem isn't assigning, I'll just add them all
    }
    
    advance(&data, dr);
  }

  printf("%s\n%s\n", dirs, regs);

  printf("Stats for directory: .\n");
  printf("Total Directory Size: %d Bytes\n", size);
  
  closedir(dr);
}
