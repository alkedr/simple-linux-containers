#define _GNU_SOURCE
#include <unistd.h>

#include "slc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  step("create file in container's fs root directory (" FS_ROOT_SOURCE "/file)");
  close(open(FS_ROOT_SOURCE "/file", O_CREAT));
  
  step("create container");
  struct slc_create_container_parameters params;
  initialize_default_fs_root(&params.fs_root);
  slc_create_container(&params, 0);

  assertStrEquals("current directory", "/", get_current_dir_name());
  assertFileExists("", "/file");

  return 0;
}

