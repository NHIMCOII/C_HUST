# Install script for directory: C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/cgen/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/TDM-GCC-64/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/benchmarks/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/ext/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/OOP/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/bns/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/arr/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/rbm/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/hfunc/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/p1w/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/hmap/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/gsl/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/gvec/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/hset/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/rbs/cmake_install.cmake")
  include("C:/Users/PC/OneDrive - Hanoi University of Science and Technology/Documents/C Programming/C BASIC/demo_cgen_new/build/cgen/examples/gtype/cmake_install.cmake")

endif()

