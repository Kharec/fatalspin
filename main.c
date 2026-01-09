#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
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

int pick_random_process(int *processes, int count) {
  return processes[rand() % count];
}

int main(void) {
  srand(time(NULL) ^ getpid());
  int count;
  int *processes = get_running_processes(&count);
  if (!processes || count == 0) {
    return 1;
  }
  int process = pick_random_process(processes, count);
  printf("Process %d is nominated for termination.\n", process);
  free(processes);
  return 0;
}
