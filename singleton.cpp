/**
 *  单例模式C++实现
 *  带双检锁,C++11
 */

class Singleton
{
private:
    Singleton() {}
    static std::mutex mtx;
    static Singleton *it;
public:
    static Singleton* getIt() {
        if (it == NULL) {
            std::unique_lock<std::mutex> lock(mtx);
            if (it == NULL) {
                it = new Singleton;
            }
        }
        return it;
    }
    static void releaseIt() {
        delete it;
    }
};

Singleton* Singleton::it = NULL;