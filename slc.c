#include "slc.h"


// TODO: get rid of libc, use only linux headers and inline asm?
// TODO: http://git.musl-libc.org/cgit/musl/tree/arch/x86_64/syscall_arch.h

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

void slc_create_container(
    const struct slc_create_container_parameters * parameters,
    const struct slc_create_container_result * result
) {
  // TODO: handle all errors
  // TODO: check nulls in parameters
  // TODO: check result for null before every write to its fields

  // create new namespaces
  unshare(CLONE_NEWIPC | CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWUSER | CLONE_NEWUTS);

  // ensure that changes to our mount namespace do not "leak" to outside namespaces
  // (what mount --make-rprivate / does)
  mount("none", "/", NULL, MS_REC | MS_PRIVATE, NULL);

  // mount container's root file system
  mount(
    parameters->fs_root.source,
    parameters->fs_root.target,
    parameters->fs_root.filesystemtype,
    parameters->fs_root.mountflags,
    parameters->fs_root.data
  );

  // TODO: add ability to remount rootfs as readonly for http://lwn.net/Articles/281157

  // TODO: add array of mount() invocations to hmlc_create_container_parameters_t
  // TODO: mount all filesystems passed in parameters
  // TODO: support simplified mounting of 'special' filesystems like dev and proc

  // Change current directory to simplify code by avoiding allocating memory and building full path
  // to .slc directory. Performance penalty is negligible.
  chdir(parameters->fs_root.target);

  // TODO: report error if .slc doesn't exist
  // TODO: make dir name a global constant?
  // make current dir (parameters->fs_root.target) new /, .slc will contain old /
  pivot_root(".", ".slc");

  // man pivot_root recommends to change work dir to '/' after pivot_root
  chdir("/");

  // unmount old /
  umount2(".slc", MNT_DETACH);

  // TODO: drop capabilities
}

