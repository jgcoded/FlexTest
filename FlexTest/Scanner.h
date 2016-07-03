#pragma once

#include <ostream>
#include <functional>

#include "Common.h"

/**
    Takes in as input a c++ file and generates events when
    a new token is recognized in the code.
*/
class Scanner
{
public:
    /**
        Callback signature when a new token is received from Flex.
        The callback has the following parameters:
        type - the type of token
        value - the semantic value of the token
        lineNumber - the lineNumber where the token appears
        columnNumber - the column in the line where the token appears
    */
    typedef std::function<void(TokenKind, const char*, int, int)> OnTokenCallback;

    /**
        Scans the C++ file and triggers callback when a new token is recognized

        \param file         The C++ file to parse
        \param callback     The event to trigger when a new callback is found
        \throw              Throws an exception if the C++ file is not found
    */
    static void Scan(std::string file, OnTokenCallback callback);

    /**
        This class receives tokens from Flex and passes the data via the
        OnTokenCallback
    */
    class ScannerStream : public std::ostream, std::streambuf
    {
    public:
        ScannerStream();
        // Invoked by Flex
        void ReceiveToken(TokenKind type, const char* value, int lineNumber, int columnNumber);
        // Set the OnTokenCallback
        void SetOnToken(Scanner::OnTokenCallback callback);

    private:
        Scanner::OnTokenCallback mOnTokenCallback;
    };

private:
    Scanner();
};
