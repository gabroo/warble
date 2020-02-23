package(default_visibility = ["//visibility:public"])

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
  name = "kvstore_proto",
  srcs = ["kvstore.proto"],
)

cc_proto_library(
  name = "kvstore_cc_proto",
  deps = [":kvstore_proto"],
)

cc_grpc_library(
  name = "kvstore_grpc_library",
  srcs = ["kvstore.proto"],
  deps = [],
)
