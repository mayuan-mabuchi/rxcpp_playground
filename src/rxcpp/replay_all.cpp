//
// Created by Yuan Ma on 9/18/20.
//

#include <rxcpp/rx.hpp>
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  auto values = rxcpp::observable<>::interval(
    std::chrono::milliseconds(50), rxcpp::observe_on_new_thread())
                  .take(5)
                  .replay();
  // Subscribe from the beginning
  values.subscribe(
    [](long v) { std::cout << "[1] OnNext: " << v << std::endl; },
    []() { std::cout << "[1] OnCompleted" << std::endl; });

  // Start emitting
  values.connect();

  // Wait before subscribing
  rxcpp::observable<>::timer(std::chrono::milliseconds(125))
    .subscribe([&]([[maybe_unused]] long _) {
      values.as_blocking().subscribe(
        [](long v) { std::cout << "[2] OnNext: " << v << std::endl; },
        []() { std::cout << "[2] OnCompleted" << std::endl; });
    });

  // Wait for Two Seconds
  rxcpp::observable<>::timer(std::chrono::milliseconds(2000))
    .subscribe([&]([[maybe_unused]] long _) {});
}
