load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
  name = "store",
  srcs = ["store.cc"],
  hdrs = ["store.h"],
)

cc_library(
  name = "client",
  srcs = ["client.cc"],
  hdrs = ["client.h"],
  includes = ["BAZEL_BUILD"],
  deps = [
    "@com_github_grpc_grpc//:grpc++",
    "//protos:kvstore_grpc_library",
  ]
)

cc_binary(
  name = "server",
  srcs = ["server.cc", "server.h"],
  includes = ["BAZEL_BUILD"],
  deps = [
    "@com_github_grpc_grpc//:grpc++",
    "//protos:kvstore_grpc_library",
    ":store",
  ],
)
