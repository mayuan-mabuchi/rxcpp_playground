//
// Created by mayuan-mabuchi on 9/19/20.
//

#include <rxcpp/rx.hpp>

int main()
{
  rxcpp::subjects::behavior<int> behavior_subject(0);

  auto observable = behavior_subject.get_observable();

  observable.subscribe([](int v) { std::cout << "1------" << v << std::endl; });

  observable.subscribe([](int v) { std::cout << "2------" << v << std::endl; });

  auto subscriber = behavior_subject.get_subscriber();
  subscriber.on_next(1);
  subscriber.on_next(2);

  int n = behavior_subject.get_value();

  std::cout << "Last Value ..." << n;

  return 0;
}
