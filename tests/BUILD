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
