macro(add_rxcpp_executable TARGET_NAME SOURCE_FILES)
    add_executable(${TARGET_NAME} ${SOURCE_FILES})
    target_link_libraries(${TARGET_NAME} PRIVATE project_warnings
                          project_options CONAN_PKG::rxcpp pthread)
endmacro()

# rxcpp test executable, with full warnings enabled
add_rxcpp_executable(ReplayAll replay_all.cpp)

add_rxcpp_executable(HotObservable hot_observable.cpp)

add_rxcpp_executable(Subscriber subscriber.cpp)

add_rxcpp_executable(SimpleSubject simple_subject.cpp)
add_rxcpp_executable(BehaviorSubject behavior_subject.cpp)
add_rxcpp_executable(ReplaySubject replay_subject.cpp)

add_rxcpp_executable(SchedulerOne scheduler_one.cpp)
add_rxcpp_executable(SchedulerTwo scheduler_two.cpp)
add_rxcpp_executable(ObservableOnScheduler observable_on_scheduler.cpp)
add_rxcpp_executable(SubscribeOnScheduler subscribe_on_scheduler.cpp)
add_rxcpp_executable(RunLoop run_loop.cpp)
