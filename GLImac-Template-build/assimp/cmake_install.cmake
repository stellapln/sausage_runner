# Install script for directory: /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template/assimp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp4.0.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-4.0" TYPE FILE FILES
    "/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/assimp-config.cmake"
    "/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/assimp-config-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp4.0.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/assimp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/contrib/cmake_install.cmake")
  include("/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/code/cmake_install.cmake")
  include("/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/tools/assimp_cmd/cmake_install.cmake")
  include("/home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/test/cmake_install.cmake")

endif()

