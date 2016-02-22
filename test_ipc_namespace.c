#include "hmlc.h"
#include "test_framework.h"

int main() {
  // TODO: create ipc object
  // TODO: check that ipc object is visible
  struct hmlc_create_container_parameters_t params;
  initialize_default_fs_root(&params.fs_root);
  hmlc_create_container(&params, 0);
  // TODO: check that ipc object is NOT visible
  return 0;
}
