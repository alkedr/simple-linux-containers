#include "hmlc.h"


// TODO: get rid of libc, use only linux headers?

// TODO: test security (container can't unmount root, remount it rw, doesn't have capabilities etc)


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <linux/capability.h>

/* can't find headers for these, but they're in glibc... */
int pivot_root(const char *new_root, const char *put_old);
int capset(cap_user_header_t h, cap_user_data_t d);
int capset(cap_user_header_t h, cap_user_data_t d);


// TODO: pass all parameters for fs_root mounting to allow squashfs and files that contain filesystems

void hmlc_create_container(
        const struct hmlc_create_container_parameters_t * parameters,
        const struct hmlc_create_container_result_t * result
) {
  // TODO: handle all errors
  // TODO: check nulls in parameters
  // TODO: check result for null before every write to its fields

  // create new namespaces
  unshare(CLONE_NEWIPC | CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUSER | CLONE_NEWUTS);

  // ensure that changes to our mount namespace do not "leak" to outside namespaces
  // (what mount --make-rprivate / does)
  mount("none", "/", NULL, MS_REC | MS_PRIVATE, NULL);

  // mount parameters->fs_root on top of itself in our new namespace
  // it will become our root filesystem
  // Probably because pivot_root needs new_root to be a mount point
  // TODO: why MS_NOSUID?
  // TODO: support squashfs and files that contain filesystems
  // TODO  (need to create directory and mount root there instead of mounting on top of itself)
  mount(parameters->fs_root, parameters->fs_root, NULL, MS_BIND | MS_RDONLY | MS_NOSUID, NULL);

  // TODO: add array of mount() invocations to hmlc_create_container_parameters_t
  // TODO: mount all filesystems passed in parameters
  // TODO: support simplified mounting of 'special' filesystems like dev and proc

  // Change current directory to simplify code by avoiding allocating memory and building full path
  // to .dumblc directory. Performance penalty is negligible.
  chdir(parameters->fs_root);

  // TODO: report error if .dumblc doesn't exist
  // make parameters->fs_root new /, .dumblc will contain old /
  pivot_root(".", ".dumblc");

  // man pivot_root recommends to change work dir to '/' after pivot_root
  chdir("/");

  // unmount old /
  umount2(".dumblc", MNT_DETACH);
}


void hmlc_join_container(
        const struct hmlc_join_container_parameters_t * parameters,
        const struct hmlc_join_container_result_t * result
) {
  // TODO: join all namespaces and change dir to root?
}

