/**
 *  单例模式C++实现
 */

std::mutex mtx;

class Singleton
{
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
    class Inside
    {
    public:
        ~Inside() {
            if (it != NULL) {
                delete it;
            }
        }
    };
private:
    Singleton() {}
    static Singleton *it;
    static Inside fordelete;
};

Singleton* Singleton::it = NULL;

/**
 *  C++11静态变量,部分编译器支持
 *  Visual Studio 2013 does not yet support it
 */
 
class Singleton
{
private:
    Singleton() {}
public:
    Singleton& getIt() {
        static Singleton instance;
        return instance;
    }
};