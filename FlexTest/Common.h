#pragma once

#include <string>

/**
    The kind of token
*/
enum class TokenKind
{
    Number,
    Name,
    String
};

static std::string ToString(TokenKind kind)
{
    switch (kind)
    {
    case TokenKind::Number:
        return "Number";
    case TokenKind::Name:
        return "Name";
    case TokenKind::String:
        return "String";
    }

    return "Invalid Token Kind";
}
