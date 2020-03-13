load("@rules_cc//cc:defs.bzl", "cc_library")

# make gtest library
cc_library(
  name = "main",
  srcs = glob(
    ["src/*.cc"],
    exclude = ["src/gtest-all.cc"]
  ),
  hdrs = glob([
    "include/**/*.h",
    "src/*.h",
  ]),
  copts = ["-Iexternal/gtest/include"],
  linkopts = ["-pthread"],
  visibility = ["//visibility:public"],
)
