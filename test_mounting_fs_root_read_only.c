#include "hmlc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() {
  step("child: create container with separate mnt namespace");
  struct hmlc_create_container_parameters_t params;
  params.fs_root = create_empty_fs_root_directory();
  hmlc_create_container(&params, 0);

  assertIntEquals("open return value", -1, open("/file", O_CREAT));
  assertIntEquals("open errno", EACCES, errno);

  return 0;
}

