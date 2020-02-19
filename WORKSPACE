# load http_archive rule
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# rules_proto defines abstract rules for building Protocol Buffers.
http_archive(
  name = "rules_proto",
  strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
  urls = [
    "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
  ],
)

# rules_cc defines rules for generating C++ code from Protocol Buffers.
http_archive(
  name = "rules_cc",
  strip_prefix = "rules_cc-8f87c5e364f00d6473040a47184298656b5d64c9",
  urls = [
    "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/8f87c5e364f00d6473040a47184298656b5d64c9.tar.gz",
    "https://github.com/bazelbuild/rules_cc/archive/8f87c5e364f00d6473040a47184298656b5d64c9.tar.gz",
  ],
)

# load dependencies for rules_cc and rules_proto
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
rules_cc_dependencies()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()
