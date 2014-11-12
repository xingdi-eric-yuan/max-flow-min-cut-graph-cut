project( gcut )
#ADD_DEFINITIONS(
#    -std=c++11 # Or -std=c++0x
#    # Other flags
#)
find_package( OpenCV REQUIRED )
aux_source_directory( src/. src_list )
add_executable( gcut ${src_list} )
target_link_libraries (gcut ${OpenCV_LIBS})