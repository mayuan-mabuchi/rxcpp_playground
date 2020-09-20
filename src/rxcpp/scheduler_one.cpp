//
// Created by mayuan-mabuchi on 9/19/20.
//
#include "rxcpp/rx.hpp"

int main()
{
  // Get a Coordination
  auto coordination = rxcpp::serialize_new_thread();

  // Create a Worker instance through a factory method
  auto worker = coordination.create_coordinator().get_worker();

  auto sub_action = rxcpp::schedulers::make_action(
    []([[maybe_unused]] const rxcpp::schedulers::schedulable &_) {
      std::cout << "Action Executed in Thread # : "
                << std::this_thread::get_id() << std::endl;
    });

  // Create a Schedulable and Schedule the Action
  auto scheduled = rxcpp::schedulers::make_schedulable(worker, sub_action);
  scheduled.schedule();

  // Wait for One Second to see result
  rxcpp::observable<>::timer(std::chrono::milliseconds(1000))
    .subscribe([&]([[maybe_unused]] long _) {});

  return 0;
}
