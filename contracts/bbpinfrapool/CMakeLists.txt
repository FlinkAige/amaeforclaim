add_contract(bbpinfrapool bbpinfrapool ${CMAKE_CURRENT_SOURCE_DIR}/src/bbpinfrapool.cpp)

target_include_directories(bbpinfrapool
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(bbpinfrapool
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/bbpinfrapool.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/bbpinfrapool.contracts.md @ONLY )

target_compile_options( bbpinfrapool PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
