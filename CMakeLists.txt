cmake_minimum_required (VERSION 2.8)
project (pici-nms)

FIND_PACKAGE(LibXml2)
FIND_PACKAGE(OpenSSL)


if(LIBXML2_FOUND)
  INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
endif()

INCLUDE_DIRECTORIES(common)

if(NOT _WIN32)
  add_definitions(-Wall -Wextra -Wcomment -Wformat -Winit-self -Wno-long-long -Wmissing-include-dirs)
else()
  add_definitions(/W4)
endif()

add_subdirectory(common)
add_subdirectory(Daemon)
add_subdirectory(Dispatcher)
add_subdirectory(libnms)
add_subdirectory(Example)