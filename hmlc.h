#pragma once


// hmlc - Highly Modular Linux Containers
// Set of tools for working with linux containers that at least tries to be simple.


struct hmlc_create_container_parameters_t {
  const char * fs_root;
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


