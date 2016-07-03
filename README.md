# FlexTest
A simple scanner using the Flex library

Source.cpp demonstrates the API:

```cpp
#include <iostream>
#include "Scanner.h"

using namespace std;

int main()
{
    Scanner::Scan("testfile.cpp", 
        [](TokenKind kind, const char* value, int line, int column)
        {
            cout << "---- New token ----" << endl
                << "Kind: "   << ToString(kind) << endl
                << "Value: "  << value << endl
                << "Line: "   << line << endl
                << "Column: " << column << endl << endl;
        });
    getchar();
    return 0;
}
```
