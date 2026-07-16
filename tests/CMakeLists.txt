# might add later

add_executable(elfparser_tests test_main.cpp)
target_link_libraries(elfparser_tests PRIVATE elfparser_lib)
add_dependencies(elfparser_tests elfparser)

target_compile_definitions(elfparser_tests PRIVATE
    "TEST_ELF_BINARY=\"$<TARGET_FILE:elfparser>\""
)

add_test(NAME elfparser_tests COMMAND elfparser_tests)
