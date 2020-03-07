package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
  name = "func_server",
  srcs = ["func_server.cc", "func_server.h"],
  includes = ["BAZEL_BUILD"],
  deps = [
    "@com_github_grpc_grpc//:grpc++",
    "//protos:func_grpc_library",
  ],
)
