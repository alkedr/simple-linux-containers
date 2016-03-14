#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mount.h>


#define GREEN "\033[1;32m"
#define RED "\033[0;31m"
#define NORMAL "\033[0m"



#define pass(description, format, args...) {\
  fprintf(stdout, GREEN "PASS: %s: " format NORMAL "\n", description, ##args);\
}

#define fail(description, format, args...) {\
  fprintf(stdout, RED "FAIL: %s: " format NORMAL "\n", description, ##args);\
  exit(1);\
}

#define check(condition, description, format, args...) {\
  if (condition) {\
    pass(description, format, ##args);\
  } else {\
    fail(description, format, ##args);\
  }\
}


static void assertIntEquals(const char * description, int expected, int actual) {
  check(expected == actual, description, "expected %d, got %d", expected, actual);
}

static void assertIntNotEquals(const char * description, int expected, int actual) {
  check(expected != actual, description, "expected not %d, got %d", expected, actual);
}


static void assertStrEquals(const char * description, const char * expected, const char * actual) {
  check(!strcmp(expected, actual), description, "expected '%s', got '%s'", expected, actual);
}

static void assertStrNotEquals(const char * description, const char * expected, const char * actual) {
  check(strcmp(expected, actual), description, "expected not '%s', got '%s'", expected, actual);
}


static void assertGreaterThan(const char * description, int expected, int actual) {
  check(actual > expected, description, "expected >%d, got %d", expected, actual);
}

static void assertPtrEquals(const char * description, void * expected, void * actual) {
  check(expected == actual, description, "expected %p, got %p", expected, actual);
}

static void assertPtrNotEquals(const char * description, void * expected, void * actual) {
  check(expected != actual, description, "expected not %p, got %p", expected, actual);
}

static void assertNull(const char * description, void * actual) {
  assertPtrEquals(description, actual, 0);
}

static void assertNotNull(const char * description, void * actual) {
  assertPtrNotEquals(description, actual, 0);
}


static void assertFileExists(const char * description, const char * file_name) {
  check(access(file_name, F_OK) != -1, description, "file '%s' should exist", file_name);
}

static void assertFileDoesNotExist(const char * description, const char * file_name) {
  check(access(file_name, F_OK) == -1, description, "file '%s' should not exist", file_name);
}





#define step(message, args...) fprintf(stdout, "LOG : " message "\n", ## args);


#define FS_ROOT_SOURCE "build/fs_root_source"
#define FS_ROOT_TARGET "build/fs_root_target"

static void initialize_default_fs_root(struct slc_mount * mount) {
  mkdir(FS_ROOT_SOURCE, S_IRWXU | S_IRWXG | S_IRWXO);
  mkdir(FS_ROOT_SOURCE "/.slc", S_IRWXU | S_IRWXG | S_IRWXO);
  mkdir(FS_ROOT_TARGET, S_IRWXU | S_IRWXG | S_IRWXO);
  mount->source = FS_ROOT_SOURCE;
  mount->target = FS_ROOT_TARGET;
  mount->filesystemtype = NULL;
  mount->mountflags = MS_BIND;
  mount->data = NULL;
}


