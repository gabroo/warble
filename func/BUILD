load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "server",
  srcs = ["server.cc", "server.h", "functions.h", "functions.cc"],
  includes = ["BAZEL_BUILD"],
  deps = [
    "@com_github_grpc_grpc//:grpc++",
    "//protos:func_grpc_library",
    "//protos:kvstore_grpc_library",
    "//protos:warble_grpc_library",
    "//kvstore:client",
  ],
)
