//
// Created by Yuan Ma on 9/19/20.
//

#include <rxcpp/rx.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  auto event_loop = rxcpp::observe_on_event_loop();
  // Create a Cold Observable
  // Convert Cold Observable to Hot Observable
  // using .Publish();
  auto values =
    rxcpp::observable<>::interval(std::chrono::seconds(2)).take(5)
      .publish_synchronized(event_loop);

  // Subscribe Twice
  values.subscribe_on(event_loop)
    .subscribe([](int v) { std::cout << "[1] onNext: " << v << std::endl; },
      []() { std::cout << "[1] onCompleted" << std::endl; });

  values.subscribe_on(event_loop)
    .subscribe([](int v) { std::cout << "[2] onNext: " << v << std::endl; },
      []() { std::cout << "[2] onCompleted" << std::endl; });

  // Connect to Start Emitting Values
  values.connect();

  // make a blocking subscription to see the results
  values.as_blocking().subscribe();

  // Wait for Two Seconds
  rxcpp::observable<>::timer(std::chrono::milliseconds(2000))
    .subscribe([&]([[maybe_unused]] long _) {});
}
