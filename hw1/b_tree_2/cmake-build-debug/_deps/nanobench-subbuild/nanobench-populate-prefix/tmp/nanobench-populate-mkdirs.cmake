# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-src"
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-build"
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix"
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix/tmp"
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix/src/nanobench-populate-stamp"
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix/src"
  "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix/src/nanobench-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix/src/nanobench-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/tath/Desktop/University/apal/hw1/b_tree_2/cmake-build-debug/_deps/nanobench-subbuild/nanobench-populate-prefix/src/nanobench-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
