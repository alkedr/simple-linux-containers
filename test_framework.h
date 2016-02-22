#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


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




static const char * create_empty_fs_root_directory() {
  mkdir("build/test_dir", S_IRWXU | S_IRWXG | S_IRWXO);
  mkdir("build/test_dir/.dumblc", S_IRWXU | S_IRWXG | S_IRWXO);
  return "build/test_dir";
}


static const char * concat_path_segments(const char * segment1, const char * segment2) {
  char * result = malloc(strlen(segment1) + strlen(segment2) + 2);
  strcpy(result, segment1);
  strcat(result, "/");
  strcat(result, segment2);
  return result;
}


