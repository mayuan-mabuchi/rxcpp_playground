//
// Created by Yuan Ma on 9/19/20.
//

#include <rxcpp/rx.hpp>

int main()
{
  // create a subscription object
  auto subscription = rxcpp::composite_subscription();
  // create a Subscription
  auto subscriber = rxcpp::make_subscriber<int>(
    subscription,
    [&](int v) {
      std::cout << "OnNext: --" << v << std::endl;
      if (v == 3) {
        subscription.unsubscribe();// Demonstrates UnSubscribe.
      }
    },
    []() { std::cout << "OnCompleted" << std::endl; });

  rxcpp::observable<>::create<int>([](const rxcpp::subscriber<int> &s) {
    for (int i = 0; i < 5; ++i) {
      if (!s.is_subscribed()) { break; }
      s.on_next(i);
    }
    s.on_completed();
  }).subscribe(subscriber);
  return 0;
}
