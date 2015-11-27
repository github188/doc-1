#include <iostream>

using namespace std;

typedef int (*callback)();

class CallbackTest
{
public:
    CallbackTest(){}

    static int thunk()
    {
        if (0 != is)
            std::cout << "callback test" << std::endl;
    }

    callback getEntry()
    {
        return (callback)thunk;
    }
    int get_ab() {
        return lyt;
    }
    static int is;
private:
    const  static int lyt=2;
};

int CallbackTest::is = 1;
int main(int argc, const char *argv[])
{
    class CallbackTest test;

    //std::cout << CallbackTest::is << std::endl;

    callback fp = test.getEntry();
    fp();

    cout << "is: " << CallbackTest::is << endl;
    CallbackTest::is ++;
    cout << "is: " << CallbackTest::is << endl;
    cout << "ab: " << test.get_ab() << endl;
    return 0;
}
