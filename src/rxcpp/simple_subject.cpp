//
// Created by Yuan Ma on 9/19/20.
//
#include <rxcpp/rx.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  // Create an instance of Subject
  rxcpp::subjects::subject<int> subject;

  // Retrieve the Observable attached to the Subject
  auto observable = subject.get_observable();

  // Subscribe Twice
  observable.subscribe([](int v) { std::cout << "1-----" << v << std::endl; });
  observable.subscribe([](int v) { std::cout << "2-----" << v << std::endl; });

  // Get the Subscriber Interface Attached to the Subject
  auto subscriber = subject.get_subscriber();

  // Emit Series of Values
  subscriber.on_next(1);
  subscriber.on_next(4);
  subscriber.on_next(9);
  subscriber.on_next(16);

  // Wait for Two Seconds
  rxcpp::observable<>::timer(std::chrono::milliseconds(2000))
    .subscribe([&]([[maybe_unused]] long _) {});

  return 0;
}
