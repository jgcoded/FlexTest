%option c++

%{
#include "Scanner.h"

int lineNumber = 1;
int columnNumber = 0;

#define OUTPUT(kind, value) \
 do { \
    columnNumber += strlen(value); \
    Scanner::ScannerStream* scannerStream = dynamic_cast<Scanner::ScannerStream*>(yyout); \
    if(scannerStream) \
    { \
        scannerStream->ReceiveToken(kind, value, lineNumber, columnNumber); \
    } \
    else \
    { \
        *yyout << value; \
    } \
} while(0) \

%}

string  \"[^\n"]+\"

ws      [ \t]+

alpha   [A-Za-z]
dig     [0-9]
name    ({alpha}|{dig}|\$)({alpha}|{dig}|[_.\-/$])*
num1    [-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2    [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number  {num1}|{num2}

%%

{ws}    columnNumber+=strlen(YYText());

"/*"    {
        int c;

        while((c = yyinput()) != 0)
            {
            if(c == '\n') {
                ++lineNumber;
                columnNumber = 0;
            }
            else if(c == '*')
                {
                if((c = yyinput()) == '/')
                    break;
                else
                    unput(c);
                }
            }
        }

{number}  OUTPUT(TokenKind::Number, YYText());

\n        lineNumber++; columnNumber = 0;

{name}    OUTPUT(TokenKind::Name, YYText());

{string}  OUTPUT(TokenKind::String, YYText());

%%
