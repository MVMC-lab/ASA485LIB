include(CTest)

include(ExternalProject)

add_subdirectory(asacomm)
add_subdirectory(asa485lib)
add_subdirectory(asacore)
add_subdirectory(test)
add_subdirectory(serial)

message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
