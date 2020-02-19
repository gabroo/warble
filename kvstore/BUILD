load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "kvstore",
  srcs = ["kvstore.cc"],
  hdrs = ["kvstore.h"],
)

cc_binary(
  name = "kvstore_service",
  srcs = ["kvstore_service.cc"],
  deps = [
    "//protos:kvstore_cpp_proto",
    ":kvstore",
  ]
)
