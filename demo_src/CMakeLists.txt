set(SOURCE_FILES main.c)
add_executable(matlib_demo ${SOURCE_FILES})
target_link_libraries (matlib_demo LINK_PUBLIC matlib)