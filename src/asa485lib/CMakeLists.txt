# does this system provide specific functions?
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

# Check for system, is provide ASA485_init function
check_function_exists (ASA485_init HAVE_ASA_INIT)
