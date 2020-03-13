# load http_archive rule
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# fetch grpc
http_archive(
  name = "com_github_grpc_grpc",
  url = "https://github.com/grpc/grpc/archive/v1.27.2.tar.gz",
  strip_prefix = "grpc-1.27.2",
)

# fetch googletest
http_archive(
  name = "gtest",
  url = "https://github.com/google/googletest/archive/release-1.7.0.tar.gz",
  strip_prefix = "googletest-release-1.7.0",
  build_file = "@//tests:gtest.BUILD",
)

# fetch gflags
http_archive(
  name = "com_github_gflags_gflags",
  url = "https://github.com/gflags/gflags/archive/v2.2.0.tar.gz",
  strip_prefix = "gflags-2.2.0",
)

# fetch glog
http_archive(
  name = "com_github_google_glog",
  url = "https://github.com/google/glog/archive/v0.4.0.tar.gz",
  strip_prefix = "glog-0.4.0",
  build_file = "@//tests:glog.BUILD",
)

# load grpc dependencies
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

# load extra dependencies
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()
