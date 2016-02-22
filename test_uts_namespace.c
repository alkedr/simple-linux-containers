#include "hmlc.h"
#include "test_framework.h"

#include <unistd.h>
#include <sys/wait.h>

const char * get_domain_name() {
  char * result = malloc(1000);
  getdomainname(result, 1000);
  return result;
}

const char * get_host_name() {
  char * result = malloc(1000);
  gethostname(result, 1000);
  return result;
}


int main() {
  const char * old_domain_name = get_domain_name();
  const char * old_host_name = get_host_name();

  step("parent: old domainname: %s", old_domain_name);
  step("parent: old hostname: %s", old_host_name);

  step("parent: fork");
  if (fork()) {
    step("parent: wait for child to exit");
    int status = 0;
    do wait(&status); while (!WIFEXITED(status));

    assertStrEquals("parent: domain name", old_domain_name, get_domain_name());
    assertStrEquals("parent: host name", old_host_name, get_host_name());
  } else {
    step("child: create container with separate uts namespace");
    struct hmlc_create_container_parameters_t params;
    initialize_default_fs_root(&params.fs_root);
    hmlc_create_container(&params, 0);

    const char * new_domain_name = "new_domain_name";
    const char * new_host_name = "new_host_name";
    
    step("child: set domain name to '%s'", new_domain_name);
    setdomainname(new_domain_name, strlen(new_domain_name));
    assertStrEquals("child: domain name", new_domain_name, get_domain_name());
    
    step("child: set host name to '%s'", new_host_name);
    sethostname(new_host_name, strlen(new_host_name));
    assertStrEquals("child: host name", new_host_name, get_host_name());
  }

  return 0;
}

