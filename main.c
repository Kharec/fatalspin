#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void list_running_processes(void) {
  DIR *proc_dir = opendir("/proc");
  if (!proc_dir) {
    perror("Failed to open /proc");
    return;
  }

  struct dirent *entry;
  struct stat statbuf;
  char path[512];
  char *endptr;

  while ((entry = readdir(proc_dir))) {
    if (entry->d_name[0] == '.') {
      continue;
    }

    strtol(entry->d_name, &endptr, 10);
    if (*endptr != '\0') {
      continue;
    }

    snprintf(path, sizeof(path), "/proc/%s", entry->d_name);
    if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
      printf("%s\n", entry->d_name);
    }
  }

  closedir(proc_dir);
}

int main(void) {
  list_running_processes();
  return 0;
}
