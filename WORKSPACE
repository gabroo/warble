# load http_archive rule
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# fetch rules for building protos
http_archive(
  name = "build_stack_rules_proto",
  urls = ["https://github.com/stackb/rules_proto/archive/734b8d41d39a903c70132828616f26cb2c7f908c.tar.gz"],
  strip_prefix = "rules_proto-734b8d41d39a903c70132828616f26cb2c7f908c",
)

# load dependencies for rules_proto
load("@build_stack_rules_proto//cpp:deps.bzl", "cpp_grpc_library")
cpp_grpc_library()
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
