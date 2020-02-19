load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
  name = "kvstore_proto",
  srcs = ["kvstore.proto"],
)

cc_proto_library(
  name = "kvstore_cc_proto",
  deps = [":kvstore_proto"],
)
