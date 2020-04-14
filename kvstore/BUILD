load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
  name = "store",
  srcs = ["store.cc"],
  hdrs = ["store.h"],
  includes = ["BAZEL_BUILD"],
  deps = [
    "@com_github_google_glog//:glog",
    "//protos:kvstore_grpc_library",
  ],
)

cc_library(
  name = "client",
  srcs = ["client.cc"],
  hdrs = ["client.h", "db.h"],
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
    "@com_github_google_glog//:glog",
    "@com_github_gflags_gflags//:gflags",
    "//protos:kvstore_grpc_library",
    ":store",
  ],
)
