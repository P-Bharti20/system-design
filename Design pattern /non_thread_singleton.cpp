//Non thread safe singleton
//The reason it’s not thread safe is because if two threads call getInstance() method at the same time(concurrently) when instance is nullptr,
//both will proceed to create a new instance, violating the Singleton pattern.
class Singleton {
private:
    Singleton() {} // Private constructor to prevent direct instantiation

    Singleton(const Singleton&) = delete; // Prevent copy constructor
    Singleton& operator=(const Singleton&) = delete; // Prevent copy assignment

    static Singleton* instance; // Static pointer to the single instance

public:
    static Singleton* getInstance() {
 // ======================================
 // This is critical section
        if (instance == nullptr) { // race condition can happen here.
            instance = new Singleton(); // Create the instance on first call
        }
 // ======================================
        return instance;
    }
};

/*

even though I've defined the static member variable outside the class, 
it remains inaccessible directly because it's still declared as private 
within the class. The purpose of defining it outside the class is to 
allocate memory for it, but its access is still controlled by the class's 
access specifiers.
*/
Singleton* Singleton::instance = nullptr;
