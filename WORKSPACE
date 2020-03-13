# load http_archive rule
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# fetch grpc
http_archive(
  name = "com_github_grpc_grpc",
  url = "https://github.com/grpc/grpc/archive/v1.27.2.tar.gz",
  sha256 = "49c1cca77d07877b878b396b42655c71a412dc14bb95d4f959d6c8971a6bb908",
  strip_prefix = "grpc-1.27.2",
)

# fetch googletest
http_archive(
  name = "gtest",
  url = "https://github.com/google/googletest/archive/release-1.7.0.tar.gz",
  sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
  strip_prefix = "googletest-release-1.7.0",
  build_file = "@//tests:gtest.BUILD",
)

# fetch gflags
http_archive(
  name = "com_github_gflags_gflags",
  url = "https://github.com/gflags/gflags/archive/v2.2.0.tar.gz",
  sha256 = "466c36c6508a451734e4f4d76825cf9cd9b8716d2b70ef36479ae40f08271f88",
  strip_prefix = "gflags-2.2.0",
)

# fetch glog
http_archive(
  name = "com_github_google_glog",
  url = "https://github.com/google/glog/archive/v0.4.0.tar.gz",
  sha256 = "f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c",
  strip_prefix = "glog-0.4.0",
  build_file = "@//tests:glog.BUILD",
)

# load grpc dependencies
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

# load extra dependencies
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()
