#include "hmlc.h"
#include "test_framework.h"

int main() {
  // TODO: create ipc object
  // TODO: check that ipc object is visible
  struct hmlc_create_container_parameters_t params;
  params.fs_root = create_empty_fs_root_directory();
  hmlc_create_container(&params, 0);
  // TODO: check that ipc object is NOT visible
  return 0;
}
