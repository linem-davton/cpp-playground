#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

std::atomic<int> counter = 0;

// By default jthread function receives a stop_token
// in destructor of jthread, stop_token.request_stop() is called followed by
// .join()
void jthread_stop_token(std::stop_token stop) {
  while (!stop.stop_requested()) {
    std::cout << "jthread auto stop  " << counter++ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << "jthread_auto_stop stop requested" << std::endl;
}

// Manual stop, can be stopped by calling stop_source.request_stop()
void jthread_function_manualstop(std::stop_token stop) {
  while (!stop.stop_requested()) {
    std::cout << "jthread_manual_stop" << counter++ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "jthread_manual_stop requested" << std::endl;
}

// No stop token, can not be stopped, calling join which default on scope exit
// will block forever
void jthread_function_infinite() {
  while (/* condition */ true) {
    std::cout << "jthread infinite loop " << counter++ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Should never reach this point" << std::endl;
}

// Normal thread function, not calling .join() or .detach() before std::thread
// is destroyed will cause std::terminate to be called on main process
void thread_function() {
  while (counter < 50) {
    std::cout << "thread function " << counter << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << "thread function loop exited" << counter << std::endl;
}

int main(int argc, char *argv[]) {
  std::stop_source stop_source;

  { // t1 stop token is signaled by scope exit
    std::jthread t1(jthread_stop_token);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "exiting main inner scope" << std::endl;
  }
  std::jthread t3(jthread_function_manualstop, stop_source.get_token());
  std::this_thread::sleep_for(std::chrono::seconds(10));

  stop_source.request_stop();
  // not calling join or detach will cause std::terminate
  std::thread thread(thread_function);
  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout << "Exiting with final count" << counter << std::endl;
}
