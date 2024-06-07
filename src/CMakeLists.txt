cmake_minimum_required (VERSION 3.14)

if (NOT VCPKG_TOOLCHAIN)
  find_package(PkgConfig)
  pkg_check_modules(GTKMM_LIB gtkmm-4.0)
  include_directories(${GTKMM_INCLUDE_DIRS})
  link_directories(${GTKMM_LIBRARY_DIRS})
  link_libraries(${GTKMM_LIBRARIES})
else()
  find_package(PkgConfig REQUIRED)
  message(${PKG_CONFIG_FOUND})
  pkg_check_modules(GTKMM_LIB REQUIRED IMPORTED_TARGET gtkmm-4.0)
endif()

if (MSVC)
  set(GUI_OPTION WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4250 /wd4275 /wd4819 /wd26812")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

include_directories("C:/dev/vcpkg/installed/x64-windows/include")
link_directories("C:/dev/vcpkg/installed/x64-windows/lib")

add_executable (ClusterApp ${GUI_OPTION} "app.cpp" "app.h"  "file_management.h"   "file.h"  "global.h")

target_link_libraries(ClusterApp PRIVATE PkgConfig::GTKMM_LIB PRIVATE sqlite3 PRIVATE zlib)
target_compile_features(ClusterApp PRIVATE cxx_std_17)