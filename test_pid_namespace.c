#include "hmlc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>


int main() {
  step("parent: create container with separate pid namespace");
  struct hmlc_create_container_parameters_t params;
  params.fs_root = create_empty_fs_root_directory();
  hmlc_create_container(&params, 0);

  step("parent: fork");
  int cpid = fork();

  if (cpid) {
    assertIntNotEquals("parent: child process pid", 1, cpid);
    // in old process wait for new process to exit and return its error code
    int status = 0;
    do wait(&status); while (!WIFEXITED(status));
    return WEXITSTATUS(status);
  } else {
    assertIntEquals("child: child process pid", 1, getpid());
  }
  
  return 0;
}

