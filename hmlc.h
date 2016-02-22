#pragma once

// hmlc - Highly Modular Linux Containers
// A set of tools for working with linux containers that at least tries to be simple.

// dumblc - Dumb Linux Containers


struct hmlc_mount_t {
  const char *source;
  const char *target;
  const char *filesystemtype;
  unsigned long mountflags;
  const void *data;
};


struct hmlc_create_container_parameters_t {
  // fs_root.source must contain .dumblc directory
  struct hmlc_mount_t fs_root;
  // TODO: null-terminated array of additional hmlc_mount_t's
  // TODO: (null - hmlc_mount_t with all fields set to zero)
};


struct hmlc_join_container_parameters_t {

};


struct hmlc_create_container_result_t {
  const char * error;
};


struct hmlc_join_container_result_t {
  const char * error;
};



void hmlc_create_container(
        const struct hmlc_create_container_parameters_t * parameters,
        const struct hmlc_create_container_result_t * result
);

void hmlc_join_container(
        const struct hmlc_join_container_parameters_t * parameters,
        const struct hmlc_join_container_result_t * result
);


