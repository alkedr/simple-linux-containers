#include "hmlc.h"
#include "test_framework.h"

#include <unistd.h>

int main() {
  int old_uid = getuid();
  int old_gid = getgid();

  step("old uid: %d", old_uid);
  step("old gid: %d", old_gid);

  step("create container with separate user namespace");
  struct hmlc_create_container_parameters_t params;
  initialize_default_fs_root(&params.fs_root);
  hmlc_create_container(&params, 0);

  assertIntNotEquals("new uid", old_uid, getuid());
  assertIntNotEquals("new gid", old_gid, getgid());

  return 0;
}

