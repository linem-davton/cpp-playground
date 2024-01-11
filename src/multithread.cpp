#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <atomic>


std::mutex mtx;
std::atomic<int> counter = 0;

// By default jthread function receives a stop_token, and should auto stop when goes out of scope
void jthread_stop_token(std::stop_token stop)
{
    while (!stop.stop_requested())
    {
        std::cout << "jthread auto stop  " << counter++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "jthread_auto_stop stop requested" << std::endl;
}

// No stop token, can not be stopped, calling join which default on scope exit will block forever
void jthread_function_infinite()
{
    while (/* condition */true)
    {
        std::cout << "jthread infinite loop " << counter++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "Should never reach this point" << std::endl; 
        
}

// Manual stop, can be stopped by calling stop_source.request_stop()
void jthread_function_manualstop(std::stop_token stop)
{
    while (!stop.stop_requested())
    {
        std::cout << "jthread_manual_stop" << counter++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "jthread_manual_stop requested" << std::endl;
}

// Normal thread function, not calling .join() or .detach() before std::thread is destroyed will cause std::terminate to be called on main process
void thread_function()
{
    while (counter < 50)
    {
        std::cout << "thread function " << counter << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "thread function loop exited" << counter << std::endl;
    
}


int main(int argc, char* argv[])
{
    std::stop_source stop_source;

   { std::jthread t1 (jthread_stop_token);
    //std::jthread t2 (jthread_function_infinite);      // Exiting main will block as main will wait for t2 to finish which will never happen
    // std::thread t3 (thread_function);                // Without calling join exiting inner scope will call std::terminate on main process
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "exiting main" << std::endl;
   
   }
    std::jthread t3 (jthread_function_manualstop, stop_source.get_token());
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    stop_source.request_stop();
    
    std::this_thread::sleep_for(std::chrono::seconds(5));


    std::cout << "Exiting with final count" << counter << std::endl;
}