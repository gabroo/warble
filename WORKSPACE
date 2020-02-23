# load http_archive rule
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# fetch grpc
http_archive(
  name = "com_github_grpc_grpc",
  urls = [
    "https://github.com/grpc/grpc/archive/v1.27.2.tar.gz",
  ],
  strip_prefix = "grpc-1.27.2",
)

# fetch googletest
http_archive(
  name = "gtest",
  url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
  sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
  build_file = "@//tests:gtest.BUILD",
  strip_prefix = "googletest-release-1.7.0",
)

# load grpc dependencies
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

# extra dependencies?
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()
