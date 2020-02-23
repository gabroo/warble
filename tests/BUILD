cc_test(
  name = "kvstore_test",
  srcs = ["kvstore_test.cc"],
  copts = ["-Iexternal/gtest/include"],
  deps = [
    "@gtest//:main",
    "//kvstore:kvstore",
  ],
  timeout = "short",
)
