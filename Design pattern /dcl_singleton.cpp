#include <mutex>
#include <atomic>

using namespace std;

class Singleton {
private:
    static atomic<Singleton*> instance;
    static mutex mtx;

    Singleton() {}

public:
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        Singleton* tmp = instance.load(memory_order_acquire);
        if (tmp == nullptr) { // First check
            lock_guard<mutex> lock(mtx);
            tmp = instance.load(memory_order_relaxed);
            if (tmp == nullptr) { // Second check
                tmp = new Singleton();
                instance.store(tmp, memory_order_release);
            }
        }
        return tmp;
    }
};

// Initialize static members
atomic<Singleton*> Singleton::instance{nullptr};
mutex Singleton::mtx;
