//
// Created by mayuan-mabuchi on 9/20/20.
//
#include <rxcpp/rx.hpp>

int main()
{
  // Print the Main Thread Id
  std::cout << "Main Thread Id is " << std::this_thread::get_id() << std::endl;
  // Instantiate a run_loop object
  // Which will loop in the main thread
  rxcpp::schedulers::run_loop rlp;
  // Create a Coordination function for run loop
  auto main_thread = rxcpp::observe_on_run_loop(rlp);
  auto worker_thread = rxcpp::synchronize_new_thread();
  rxcpp::composite_subscription scr;
  rxcpp::observable<>::range(0, 15)
    .map([](int i) {
      //  This will get executed in worker
      std::cout << "Map " << std::this_thread::get_id() << " : " << i
                << std::endl;
      return i;
    })
    .take(5)
    .subscribe_on(worker_thread)
    .observe_on(main_thread)
    .subscribe(scr, [&](int i) {
      // This will get executed in main thread
      std::cout << "Sub " << std::this_thread::get_id() << " : " << i
                << std::endl;
    });

  // Execute the Run Loop
  while (scr.is_subscribed() || !rlp.empty()) {
    while (!rlp.empty() && rlp.peek().when < rlp.now()) { rlp.dispatch(); }
  }

  return 0;
}
