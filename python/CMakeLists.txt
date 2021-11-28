
pybind11_add_module(_core MODULE module.cpp)

target_link_libraries(_core PRIVATE habucpp)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _core DESTINATION .)
