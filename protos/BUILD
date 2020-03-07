package(default_visibility = ["//visibility:public"])

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

cc_grpc_library(
  name = "kvstore_grpc_library",
  srcs = ["kvstore.proto"],
  deps = [],
)

cc_grpc_library(
  name = "func_grpc_library",
  srcs = ["func.proto"],
  deps = [],
  well_known_protos = True,
)
