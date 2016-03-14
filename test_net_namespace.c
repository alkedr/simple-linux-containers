#include "slc.h"
#include "test_framework.h"

#include <ifaddrs.h>

int get_ifaddrs_count() {
  struct ifaddrs * ifaddrs = 0;
  getifaddrs(&ifaddrs);
  int count = 0;
  while (ifaddrs) {
    count++;
    ifaddrs = ifaddrs->ifa_next;
  }
  return count;
}

int main() {
  // Check that there are more than one network interfaces
  // If there is one interface outside the container then this test can't test anything
  assertGreaterThan("ifaddrs count outside container", 1, get_ifaddrs_count());

  step("create container with separate net namespace");
  struct slc_create_container_parameters params;
  initialize_default_fs_root(&params.fs_root);
  slc_create_container(&params, 0);

  assertIntEquals("ifaddrs count inside container", 1, get_ifaddrs_count());

  return 0;
}
