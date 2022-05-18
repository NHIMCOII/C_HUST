add_subdirectory(cgen)
include_directories(cgen)
add_executable(prog AnhDD_20205198.c)
target_link_libraries(prog bkc)