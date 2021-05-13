#include <future>
#include <iostream>

// 耗時的工作
bool is_prime (int x) {
  std::cout << "Calculating. Please, wait...n";
  bool r = true;
  for (int i = 2; i < x; ++i) {
    if (x % i == 0) {
      r = false;
      break;
    }
  }
  std::cout << "We're done.n";
  return r;
}

// sleep 函數
void sleep(int milisec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
}

int main () {
  // 使用另外一個執行緒執行 is_prime(334214467)
  std::future<bool> fut = std::async (is_prime, 334214467);

  // 執行其他工作 ...
  sleep(200); std::cout << "Do something in main thread ...n";
  sleep(200); std::cout << "Do something in main thread ...n";
  sleep(1000); std::cout << "Do something in main thread ...n";

  // 等待並取回計算結果
  bool r = fut.get();
  if (r) {
    std::cout << "It is prime!n";
  } else {
    std::cout << "It is not prime.n";
  }
  return 0;
}