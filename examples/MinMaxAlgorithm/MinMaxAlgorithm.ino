#include <ArduinoSTL.h>
#include <deque.h>
#include <vector.h>

using namespace std;

template <typename E>
class SlidingWindowMinMax final {

    /*-- Fields --*/

  private: etl::deque<E, 20> minDeque;
  private: etl::deque<E, 20> maxDeque;


    /*-- Methods --*/

  public: E getMinimum() {
      return minDeque.front();
    }


  public: E getMaximum() {
      return maxDeque.front();
    }


  public: void addTail(const E &val) {
      while (!minDeque.empty() && val < minDeque.back())
        minDeque.pop_back();
      minDeque.push_back(val);

      while (!maxDeque.empty() && val > maxDeque.back())
        maxDeque.pop_back();
      maxDeque.push_back(val);
    }


  public: void removeHead(const E &val) {
      if (val == minDeque.front())
        minDeque.pop_front();

      if (val == maxDeque.front())
        maxDeque.pop_front();
    }
};



static void TestSlidingWindowMinMax() {
  etl::vector<int, 1000> array;
  etl::vector<int, 20> window;
  size_t arrayLen = 1000;
  for (size_t i = 0; i < arrayLen; i++)
    array.push_back(random(100));
  SlidingWindowMinMax<int> swm;
  vector<int>::const_iterator start = array.begin();
  vector<int>::const_iterator end = array.begin();
  while (end < array.end()) {
    swm.addTail(*end);
    window.push_back(*end);
    ++end;
    if (end - start > 10) {
      window.erase(window.begin());
      swm.removeHead(*start);
      ++start;
    }
    cout << "window:";
    for (unsigned i = 0; i < window.size(); ++i)
      cout << ' ' << window[i];
    cout << endl;
    cout << "min=" << swm.getMinimum() << endl;
    cout << "max=" << swm.getMaximum() << endl;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  TestSlidingWindowMinMax();
}

void loop() {
}
