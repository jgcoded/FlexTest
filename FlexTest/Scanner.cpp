#include <fstream>
#include <memory>

#include "FlexLexer.h"
#include "Scanner.h"

using namespace std;

Scanner::Scanner()
{
}

void Scanner::Scan(std::string file, OnTokenCallback callback)
{
    ifstream inputStream(file);

    if (!inputStream)
    {
        throw exception("Could not open input file");
    }

    shared_ptr<ScannerStream> scannerStream(new ScannerStream);
    scannerStream->SetOnToken(callback);
    shared_ptr<yyFlexLexer> lexer(new yyFlexLexer(&inputStream, scannerStream.get()));

    while (lexer->yylex() != 0) { }
}

void Scanner::ScannerStream::ReceiveToken(TokenKind type, const char* value, int lineNumber, int columnNumber)
{
    if (mOnTokenCallback)
    {
        mOnTokenCallback(type, value, lineNumber, columnNumber);
    }
}

void Scanner::ScannerStream::SetOnToken(Scanner::OnTokenCallback callback)
{
    mOnTokenCallback = callback;
}

Scanner::ScannerStream::ScannerStream() : std::ostream(this)
{
}
