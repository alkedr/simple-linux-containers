#pragma once

// slc - Simple Linux Containers


// TODO: get rid of libc
// TODO: mock syscalls in tests
// TODO: leave some tests with real syscalls to test assumptions about syscalls (test syscalls)

// TODO: what to do if programs that run in container change their namespaces?
// TODO: do namespaces form trees?

// TODO: what happens with environment variables?


struct slc_mount {
  const char *source;
  const char *target;
  const char *filesystemtype;
  unsigned long mountflags;
  const void *data;
};



struct slc_create_container_parameters {
  // fs_root.source must contain .slc directory
  struct slc_mount fs_root;
  // TODO: null-terminated array of additional slc_mount's
  // TODO: (null - slc_mount with all fields set to zero)

  // TODO: ability to leave old root mounted somewhere in new root
  // TODO: ability to not use some namespaces (a flag for each namespace)
  // TODO: devices
  // TODO: network
  // TODO: ability to change container's hostname?
  // TODO: interaction with other containers!
  // TODO: cgroups
  // TODO: selinux
};



struct slc_create_container_result {
  const char * error;
};


// TODO: slc_create_container:
// - unshare(PID)
// - create temp dirs
// - fork
// - child unshares everything else
// - child uses temp dirs to mount file systems
// - child exec's
// - parent waits for child to stop using temp dirs and removes them
//   (it can wait for pivot_root to make tempdir a mount point)
// - parent either
//   - exits and leaves the child daemonized
//   - (docker run -it, docker attach) attaches stdin/stdout/stderr of child


// you will need to fork() to make pid equal to 1
void slc_create_container(
    const struct slc_create_container_parameters * parameters,
    const struct slc_create_container_result * result
);

