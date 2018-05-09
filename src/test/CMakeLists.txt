# USE VCP driver OR libusb driver to communction with 485 adaptor
option(USE_VCP
    "Use USB Virtual com port Drvier" ON
)

# add the binary tree to the search path for include files
# so that we will find ASA485BB_config.h
include_directories("${PROJECT_BINARY_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include")
set(LIBS serial)
# add the executable for test
add_executable(Test1 test/test.cxx)
target_link_libraries(Test1 ${LIBS})

# add the install targets
install (TARGETS Test1 DESTINATION "test")

# does the usage message work?
add_test (APP_Message_Test Test1)
set_tests_properties (APP_Message_Test
  PROPERTIES
  PASS_REGULAR_EXPRESSION "Usage: --find-devices --help --version"
  )
