#include "slc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>


int main() {
  step("parent: create container with separate pid namespace");
  struct slc_create_container_parameters params;
  initialize_default_fs_root(&params.fs_root);
  slc_create_container(&params, 0);

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

