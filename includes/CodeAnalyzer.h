#pragma once

#include <memory>

#include "Lexer.h"
#include "Parser.h"

class ErrorManager;

class CodeAnalyzer
{
public:
	CodeAnalyzer() = default;
    CodeAnalyzer(std::string aFileName);

    CodeAnalyzer(const CodeAnalyzer& aOther) = delete;
    CodeAnalyzer& operator=(const CodeAnalyzer& aOther) = delete;

	CodeAnalyzer(CodeAnalyzer&& aOther) = default;
	CodeAnalyzer& operator=(CodeAnalyzer&& aOther) = default;

    std::vector<Lexer::Lexeme> ProcessLexicographicAnalyzing(ErrorManager* aErrorManager);
    void ProcessCodeParsing(const std::vector<Lexer::Lexeme>& aLexemeList, ErrorManager* aErrorManager);

private:
    std::unique_ptr<Lexer::Lexer> mLexer;
    std::unique_ptr<Parser::Parser> mParser;

};
