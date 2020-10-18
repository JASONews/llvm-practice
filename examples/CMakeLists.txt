add_library(rtlib OBJECT rtlib)
add_library(tmp OBJECT tmp)
add_executable(main)

set_target_properties(tmp PROPERTIES
    COMPILE_FLAGS "-Xclang -load -Xclang ../skeleton/libSkeletonPass.so"
)

# target_compile_options(tmp PUBLIC -Xclang -load -Xclang "../skeleton/libSkeletonPass.so")

target_link_libraries(main rtlib tmp)
