add_library (matlib
        ml_mult.c ml_mult.h
        ml_display.h ml_display.c
        ml_mat.c ml_mat.h
        ml_debugger.c ml_debugger.h ml_mult2.c ml_mult2.h)

target_include_directories (matlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})