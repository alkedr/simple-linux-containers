#include "slc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  step("parent: fork");
  if (fork()) {
    step("parent: wait for child to exit");
    int status = 0;
    do wait(&status); while (!WIFEXITED(status));
    assertFileExists("parent", FS_ROOT_SOURCE "/dir1");
    assertFileDoesNotExist("parent", FS_ROOT_SOURCE "/dir1/file");
    assertFileExists("parent", FS_ROOT_SOURCE "/dir2");
    assertFileExists("parent", FS_ROOT_SOURCE "/dir2/file");
  } else {
    step("child: create container with separate mnt namespace");
    struct slc_create_container_parameters params;
    initialize_default_fs_root(&params.fs_root);
    slc_create_container(&params, 0);

    step("child: create dir1");
    mkdir("dir1", S_IRWXU | S_IRWXG | S_IRWXO);

    step("child: create dir2");
    mkdir("dir2", S_IRWXU | S_IRWXG | S_IRWXO);

    step("child: create dir2/file");
    close(open("dir2/file", O_CREAT));

    step("child: mount dir2 over dir1");
    mount("dir2", "dir1", NULL, MS_BIND, NULL);

    assertFileExists("child", "dir1");
    assertFileExists("child", "dir1/file");
    assertFileExists("child", "dir2");
    assertFileExists("child", "dir2/file");
  }

  return 0;
}

