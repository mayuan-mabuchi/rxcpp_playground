//
// Created by mayuan-mabuchi on 9/19/20.
//
#include <rxcpp/rx.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  // instantiate a ReplaySubject
  rxcpp::subjects::replay<int, rxcpp::observe_on_one_worker> replay_subject(
    10, rxcpp::observe_on_new_thread());
  // get the observable interface
  auto observable = replay_subject.get_observable();

  // Subscribe!
  observable.subscribe(
    [](int v) { std::cout << "1---------" << v << std::endl; });

  // Get the subscriber interface
  auto subscriber = replay_subject.get_subscriber();

  // Emit data
  subscriber.on_next(1);
  subscriber.on_next(2);

  // Add a new subscriber
  // A normal subject will drop data
  // Replay subject will not
  observable.subscribe([](int v) { std::cout << "2------" << v << std::endl; });

  // Wait for Two Seconds
  rxcpp::observable<>::timer(std::chrono::milliseconds(2000))
    .subscribe([&]([[maybe_unused]] long _) {});

  return 0;
}
