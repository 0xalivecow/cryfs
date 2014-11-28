#pragma once
#ifndef TEST_FSPP_FUSE_STATFS_FUSESTATFSTEST_H_
#define TEST_FSPP_FUSE_STATFS_FUSESTATFSTEST_H_

#include "gmock/gmock.h"

#include <string>
#include <functional>
#include <sys/statvfs.h>

#include "test/testutils/FuseTest.h"

// This class offers some utility functions for testing statfs().
class FuseStatfsTest: public FuseTest {
protected:
  const char *FILENAME = "/myfile";

  // Set up a temporary filesystem (using the fsimpl mock in FuseTest as filesystem implementation)
  // and call the statfs syscall on the given (filesystem-relative) path.
  void Statfs(const std::string &path);
  // Same as Statfs above, but also return the result of the statfs syscall.
  void Statfs(const std::string &path, struct ::statvfs *result);

  // These two functions are the same as Statfs above, but they don't fail the test when the statfs syscall
  // crashes. Instead, they return the result value of the statfs syscall.
  int StatfsAllowErrors(const std::string &path);
  int StatfsAllowErrors(const std::string &path, struct ::statvfs *result);

  // You can specify an implementation, which can modify the (struct statfs *) result,
  // our fuse mock filesystem implementation will then return this to fuse on an statfs call.
  // This functions then set up a temporary filesystem with this mock, calls statfs on a filesystem node
  // and returns the (struct statfs) returned from an statfs syscall to this filesystem.
  struct ::statvfs CallStatfsWithImpl(std::function<void(struct ::statvfs*)> implementation);
};

#endif
