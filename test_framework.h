#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


#define GREEN "\033[1;32m"
#define RED "\033[0;31m"
#define NORMAL "\033[0m"

static const char * create_empty_fs_root_directory() {
  mkdir("test_dir", S_IRWXU | S_IRWXG | S_IRWXO);
  return "test_dir";
}


static void assertIntEquals(const char * description, int expected, int actual) {
  if (expected != actual) {
    fprintf(stdout, RED "FAIL: %s: expected %d, got %d" NORMAL "\n", description, expected, actual);
    exit(1);
  } else {
    fprintf(stdout, GREEN "PASS: %s: %d" NORMAL "\n", description, actual);
  }
}

static void assertIntNotEquals(const char * description, int expected, int actual) {
  if (expected == actual) {
    fprintf(stdout, RED "FAIL: %s: expected not %d, got %d" NORMAL "\n", description, expected, actual);
    exit(1);
  } else {
    fprintf(stdout, GREEN "PASS: %s: expected not %d, got %d" NORMAL "\n", description, expected, actual);
  }
}


static void assertStrEquals(const char * description, const char * expected, const char * actual) {
  if (strcmp(expected, actual)) {
    fprintf(stdout, RED "FAIL: %s: expected '%s', got '%s'" NORMAL "\n", description, expected, actual);
    exit(1);
  } else {
    fprintf(stdout, GREEN "PASS: %s: '%s'" NORMAL "\n", description, actual);
  }
}


static void assertGreaterThan(const char * description, int expected, int actual) {
  if (actual > expected) {
    fprintf(stdout, GREEN "PASS: %s: expected >%d, got %d" NORMAL "\n", description, expected, actual);
  } else {
    fprintf(stderr, RED "FAIL: %s: expected >%d, got %d" NORMAL "\n", description, expected, actual);
    exit(1);
  }
}

static void assertPtrEquals(const char * description, void * expected, void * actual) {
  if (expected != actual) {
    fprintf(stdout, RED "FAIL: %s: expected %p, got %p" NORMAL "\n", description, expected, actual);
    exit(1);
  } else {
    fprintf(stdout, GREEN "PASS: %s: %p" NORMAL "\n", description, actual);
  }
}

static void assertPtrNotEquals(const char * description, void * expected, void * actual) {
  if (expected == actual) {
    fprintf(stdout, RED "FAIL: %s: expected not %p" NORMAL "\n", description, actual);
    exit(1);
  } else {
    fprintf(stdout, GREEN "PASS: %s: expected not %p, got %p" NORMAL "\n", description, expected, actual);
  }
}

static void assertNull(const char * description, void * actual) {
  assertPtrEquals(description, actual, 0);
}

static void assertNotNull(const char * description, void * actual) {
  assertPtrNotEquals(description, actual, 0);
}


static void assertFileExists(const char * description, const char * file_name) {
  if (access(file_name, F_OK) == -1) {
    fprintf(stdout, RED "FAIL: %s: file '%s' should exist" NORMAL "\n", description, file_name);
    exit(1);
  } else {
    fprintf(stdout, GREEN "PASS: %s: file '%s' should exist" NORMAL "\n", description, file_name);
  }
}

static void assertFileDoesNotExist(const char * description, const char * file_name) {
  if (access(file_name, F_OK) == -1) {
    fprintf(stdout, GREEN "PASS: %s: file '%s' should not exist" NORMAL "\n", description, file_name);
    exit(1);
  } else {
    fprintf(stdout, RED "FAIL: %s: file '%s' should not exist" NORMAL "\n", description, file_name);
  }
}



#define step(message, args...) fprintf(stdout, "LOG : " message "\n", ## args);



static const char * concat_path_segments(const char * segment1, const char * segment2) {
  char * result = malloc(strlen(segment1) + strlen(segment2) + 2);
  strcpy(result, segment1);
  strcat(result, "/");
  strcat(result, segment2);
  return result;
}


