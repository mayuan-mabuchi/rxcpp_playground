# rxcpp test executable, with full warnings enabled
macro(add_rxcpp_executable TARGET_NAME SOURCE_FILES)
    add_executable(${TARGET_NAME} ${SOURCE_FILES})
    target_link_libraries(${TARGET_NAME} PRIVATE project_warnings
                          project_options CONAN_PKG::rxcpp pthread)
endmacro()

add_rxcpp_executable(ReplayAll replay_all.cpp)

add_rxcpp_executable(HotObservable hot_observable.cpp)

add_rxcpp_executable(Subscriber subscriber.cpp)



add_subdirectory(subjects)
add_subdirectory(schedulers)

