# Get all project files
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)


add_custom_target(
        lint
        COMMAND /usr/bin/clang-tidy 2> lint.out 1> lint.out  
        ${ALL_SOURCE_FILES}
        
)


#find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
#set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")# "-checks=-*,modernize-*")
#set_target_properties(main PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy";
#  -format-style='file';
#  -header-filter=${CMAKE_CURRENT_SOURCE_DIR};
#  -p build)

#file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
#add_custom_target(lint
#    COMMAND bash -c "clang-tidy ../src/main.cpp  >lint.out 2>lint.err; echo \"hello\";"
#    
   # WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#)
