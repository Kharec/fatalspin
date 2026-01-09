#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int *get_running_processes(int *count) {
  DIR *proc_dir = opendir("/proc");
  if (!proc_dir) {
    perror("Failed to open /proc");
    return NULL;
  }

  struct dirent *entry;
  struct stat statbuf;
  char path[512];
  char *endptr;
  int *processes = malloc(sizeof(int) * 1024);
  *count = 0;

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
      processes[(*count)++] = atoi(entry->d_name);
    }
  }

  closedir(proc_dir);
  return processes;
}

int main(void) { return 0; }
