//
// Created by mayuan-mabuchi on 9/20/20.
//
#include <rxcpp/rx.hpp>

int main()
{
  // Print the main thread id
  std::cout << "Main Thread Id is " << std::this_thread::get_id() << std::endl;
  // We are using subscribe_on here.
  // The Map and subscribed Lambda will
  // use the secondary thread
  rxcpp::observable<>::range(0, 15)
    .map([](int i) {
      std::cout << "Map " << std::this_thread::get_id() << " : " << i
                << std::endl;
      return i;
    })
    .take(5)
    .subscribe_on(rxcpp::synchronize_new_thread())
    .subscribe([&](int i) {
      std::cout << "Subs " << std::this_thread::get_id() << " : " << i
                << std::endl;
    });

  // Wait for Two Seconds to see result
  rxcpp::observable<>::timer(std::chrono::milliseconds(2000))
    .subscribe([&]([[maybe_unused]] long _) {});

  return 0;
}
