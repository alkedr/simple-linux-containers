#include "slc.h"
#include "test_framework.h"

int main() {
  // TODO: create ipc object
  // TODO: check that ipc object is visible
  struct slc_create_container_parameters params;
  initialize_default_fs_root(&params.fs_root);
  slc_create_container(&params, 0);
  // TODO: check that ipc object is NOT visible
  return 0;
}
