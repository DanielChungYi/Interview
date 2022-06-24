add_library(buggy_lib buggy.h buggy.cxx)
target_link_libraries(buggy_lib PUBLIC pthread)
