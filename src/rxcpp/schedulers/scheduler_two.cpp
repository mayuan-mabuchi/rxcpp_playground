//
// Created by mayuan-mabuchi on 9/19/20.
//
#include "rxcpp/rx.hpp"

int main()
{
  // Create a coordination function
  auto coordination = rxcpp::identity_current_thread();

  // Instantiate a coordinator and create a worker
  auto worker = coordination.create_coordinator().get_worker();

  // Start and the period
  auto start = coordination.now() + std::chrono::milliseconds(1);
  auto period = std::chrono::milliseconds(1);

  // Create an Observable (Replay)
  auto values = rxcpp::observable<>::interval(start, period)
                  .take(5)
                  .replay(2, coordination);

  // Subscribe first time using a Worker
  worker.schedule(
    [&]([[maybe_unused]] const rxcpp::schedulers::schedulable &_) {
      values.subscribe(
        [](long v) {
          std::cout << "#1 -- " << std::this_thread::get_id() << " : " << v
                    << std::endl;
        },
        []() { std::cout << "#1 --- onCompleted" << std::endl; });
    });

  worker.schedule(
    [&]([[maybe_unused]] const rxcpp::schedulers::schedulable &_) {
      values.subscribe(
        [](long v) {
          std::cout << "#2 -- " << std::this_thread::get_id() << " : " << v
                    << std::endl;
        },
        []() { std::cout << "#2 --- onCompleted" << std::endl; });
    });

  // Start the emission of values
  worker.schedule(
    [&]([[maybe_unused]] const rxcpp::schedulers::schedulable &_) {
      values.connect();
    });

  // Add blocking subscription to see results
  values.as_blocking().subscribe();

  return 0;
}
