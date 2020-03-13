load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
	name = "functions",
	srcs = ["functions.cc"],
	hdrs = ["functions.h"],
	includes = ["BAZEL_BUILD"],
	deps = [
		"@com_github_grpc_grpc//:grpc++",
		"@com_github_google_glog//:glog",
		"//protos:func_grpc_library",
		"//protos:warble_grpc_library",
		"//kvstore:client",
	],
)

cc_library(
	name = "cli",
	srcs = ["cli.cc"],
	hdrs = ["cli.h"],
	includes = ["BAZEL_BUILD"],
	deps = [
		"@com_github_grpc_grpc//:grpc++",
		"@com_github_gflags_gflags//:gflags",
		"@com_github_google_glog//:glog",
		"//protos:func_grpc_library",
		"//protos:warble_grpc_library",
	],
)

cc_binary(
	name = "warble",
	srcs = ["warble.cc"],
	deps = [
		":cli",
	],
)