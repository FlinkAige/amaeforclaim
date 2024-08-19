add_contract(amaeforclaim amaeforclaim ${CMAKE_CURRENT_SOURCE_DIR}/src/amaeforclaim.cpp)

target_include_directories(amaeforclaim
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(amaeforclaim
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/amaeforclaim.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/amaeforclaim.contracts.md @ONLY )

target_compile_options( amaeforclaim PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
