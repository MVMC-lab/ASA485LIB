# Define library. Only source files here!
project(ASAComm LANGUAGES CXX)

set (CSERIAL_VERSION_MAJOR 1)
set (CSERIAL_VERSION_MINOR 0)
set (CSERIAL_VERSION_PATCH 0)

add_library(${PROJECT_NAME}
    src/asacomm.cpp
)

add_dependencies(${PROJECT_NAME} serial)

set(LIBS serial)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
message("ASAComm include : ${serial_INCLUDE_DIRS}")
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${serial_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# If we have compiler requirements for this library, list them
# here
target_compile_features(${PROJECT_NAME}
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file
target_link_libraries(${PROJECT_NAME} ${LIBS})

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Config"
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT "${PROJECT_NAME}Config" DESTINATION share/ASALib/cmake)

# Expose public includes to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Config.cmake")

# Every library has unit tests, of course
add_executable(testlib
    test/testlib.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(testlib
    ${PROJECT_NAME})

# does the usage message work?
add_test (CSerial_libtest testlib)

# add the install targets
install (TARGETS testlib DESTINATION "test")