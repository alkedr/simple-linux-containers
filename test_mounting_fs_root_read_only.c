#include "slc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() {

  // does not work because of http://lwn.net/Articles/281157

  step("child: create container with separate mnt namespace");
  struct slc_create_container_parameters params;
  initialize_default_fs_root(&params.fs_root);
  params.fs_root.mountflags |= MS_RDONLY;
  slc_create_container(&params, 0);

  assertIntEquals("open return value", -1, open("/file", O_CREAT));
  assertIntEquals("open errno", EACCES, errno);

  return 0;
}

