#pragma once

#include <memory>

#include "Lexer.h"
#include "Parser.h"

class CodeAnalyzer
{
public:


private:
    std::unique_ptr<Lexer::Lexer> mLexer;
    std::unique_ptr<Parser::Parser> mParser;

};
