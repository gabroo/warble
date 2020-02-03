# check cmake version
cmake_minimum_required(VERSION 3.11)

project(Warble VERSION 1.0.0)

# put cmake output into bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# fetch grpc
include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.25.0
)
FetchContent_MakeAvailable(gRPC)

# check for Protobuf
find_package(Protobuf REQUIRED)
if(Protobuf_FOUND)
  message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}")
endif()

# function to make C++ files
function(GRPC_GENERATE_CPP SRCS HDRS DEST)
  if(NOT ARGN)
    message(SEND_ERROR "Error: GRPC_GENERATE_CPP() called without any proto files")
    return()
  endif()

  if(GRPC_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach(FIL ${ARGN})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component(ABS_PATH ${ABS_FIL} PATH)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  else()
    set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(DIR ${PROTOBUF_IMPORT_DIRS})
      get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  endif()

  set(${SRCS})
  set(${HDRS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND ${SRCS} "${DEST}/${FIL_WE}.grpc.pb.cc")
    list(APPEND ${HDRS} "${DEST}/${FIL_WE}.grpc.pb.h")

    add_custom_command(
      OUTPUT "${DEST}/${FIL_WE}.grpc.pb.cc"
             "${DEST}/${FIL_WE}.grpc.pb.h"
      COMMAND protobuf::protoc
      ARGS --grpc_out ${DEST} ${_protobuf_include_path} --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} ${ABS_FIL}
      DEPENDS ${ABS_FIL} protobuf::protoc gRPC::grpc_cpp_plugin
      COMMENT "Running C++ gRPC compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()

# generate .cc files for each .proto file
file(GLOB PROTOS ${CMAKE_CURRENT_SOURCE_DIR}/protos/*.proto)
foreach(proto ${PROTOS})
  get_filename_component(PROTO_NAME_WE ${proto} NAME_WE)
  get_filename_component(PROTO_NAME ${proto} NAME)
  message(STATUS "Generating Protobuf Code for ${PROTO_NAME}")
  protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_BINARY_DIR} ${proto})
  add_library(${PROTO_NAME_WE}.proto STATIC ${PROTO_SRCS} ${PROTO_HDRS})
  target_include_directories(${PROTO_NAME_WE}.proto PUBLIC ${Protobuf_INCLUDE_DIRS})
  message(STATUS "Generating gRPC Code for ${PROTO_NAME}")
  grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${CMAKE_CURRENT_BINARY_DIR} ${proto})
  add_library(${PROTO_NAME_WE}.grpc STATIC ${GRPC_SRCS} ${GRPC_HDRS} ${PROTO_SRCS} ${PROTO_HDRS})
  target_include_directories(${PROTO_NAME_WE}.grpc PUBLIC ${GRPC_INCLUDE_DIR})
  target_link_libraries(${PROTO_NAME_WE}.grpc grpc++)
endforeach()
