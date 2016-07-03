#include <iostream>

using namespace std;

class MyClass
{
public:
    void increaseJ() { j++; }
    int getJ() { return j; }
private:
    int j;
};

int main()
{
    MyClass myClass;
    myClass.increaseJ();
    if (myClass.getJ() >= 1)
    {
        cout << "j is: " << myClass.getJ() << endl;
    }

    return 0;
}
