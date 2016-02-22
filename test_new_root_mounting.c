#include "hmlc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  const char * fs_root = create_empty_fs_root_directory();

  step("create file in container's fs root directory");
  close(open(concat_path_segments(fs_root, "file"), O_CREAT));
  
  step("create container");
  struct hmlc_create_container_parameters_t params;
  params.fs_root = create_empty_fs_root_directory();
  hmlc_create_container(&params, 0);

  assertStrEquals("current directory", "/", get_current_dir_name());
  assertFileExists("", "/file");

  return 0;
}

