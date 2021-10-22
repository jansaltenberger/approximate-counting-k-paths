project(experiments LANGUAGES CXX)

#add_compile_options(
 #   $<$<CONFIG:Release>:-O3>
  #  $<$<CONFIG:Debug>:-DDEBUG>
#)
add_compile_options(
  $<$<CONFIG:DEBUG>:>
  $<$<CONFIG:RELEASE>:-O3>
)

add_compile_definitions(
  $<$<CONFIG:DEBUG>:DEBUG>
)
add_executable(blsz_exact blsz_test.cpp)
target_link_libraries(blsz_exact BLSZ)
target_compile_definitions(blsz_exact PRIVATE BLSZ_EXACT=1)

add_executable(blsz blsz_test.cpp)
target_link_libraries(blsz BLSZ)
target_compile_definitions(blsz PRIVATE BLSZ=1)

add_executable(bdh_unordered_map bdh_test.cpp)
target_link_libraries(bdh_unordered_map BDH)
target_compile_definitions(bdh_unordered_map PRIVATE BDH_UNORDERED_MAP=1)

add_executable(bdh_linked_list bdh_test.cpp)
target_link_libraries(bdh_linked_list BDH)
target_compile_definitions(bdh_linked_list PRIVATE BDH_LINKED_LIST=1)