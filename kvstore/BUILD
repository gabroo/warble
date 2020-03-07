package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "kvstore",
  srcs = ["kvstore.cc"],
  hdrs = ["kvstore.h"],
)

cc_binary(
  name = "kvstore_server",
  srcs = ["kvstore_server.cc", "kvstore_server.h"],
  includes = ["BAZEL_BUILD"],
  deps = [
    "@com_github_grpc_grpc//:grpc++",
    "//protos:kvstore_grpc_library",
    ":kvstore",
  ],
)
