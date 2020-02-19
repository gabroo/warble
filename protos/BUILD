package(default_visibility = ["//visibility:public"])

load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")

proto_library(
  name = "kvstore_proto",
  srcs = ["kvstore.proto"],
)

cpp_grpc_library(
  name = "kvstore_cpp_proto",
  srcs = ["kvstore.proto"],
  deps = [":kvstore_proto"], 
)
