load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
	name = "cli",
	srcs = ["cli.cc", "cli.h"],
	includes = ["BAZEL_BUILD"],
	deps = [
		"@com_github_grpc_grpc//:grpc++",
		"@com_github_gflags_gflags//:gflags",
		"//protos:func_grpc_library",
		"//protos:warble_grpc_library",
	],
)