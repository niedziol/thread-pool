include_directories(..)

add_executable(test_defer defer.c)
add_test(test_defer test_defer)

add_executable(test_await await.c)
add_test(test_await test_await)

set_tests_properties(test_defer test_await PROPERTIES TIMEOUT 1)

configure_file(${CMAKE_SOURCE_DIR}/test/matrix.sh.in tmp/matrix.sh)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/tmp/matrix.sh DESTINATION . FILE_PERMISSIONS FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
configure_file(${CMAKE_SOURCE_DIR}/test/factorial.sh.in tmp/factorial.sh)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/tmp/factorial.sh DESTINATION . FILE_PERMISSIONS FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

add_test(test_matrix matrix.sh 1)

add_test(test_factorial factorial.sh 1)
