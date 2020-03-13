load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
  name = "kvstore",
  srcs = ["kvstore.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    "@gtest//:main",
    "//kvstore:store",
  ],
  timeout = "short",
)

cc_test(
  name = "funcs",
  srcs = ["funcs.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    "@gtest//:main",
    "//kvstore:store",
    "//warble:functions",
  ],
  timeout = "short",
)

exports_files(["gtest.BUILD", "glog.BUILD"])