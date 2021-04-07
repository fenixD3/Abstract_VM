#include "CodeAnalyzer.h"

CodeAnalyzer::CodeAnalyzer(std::string aFileName)
    : mLexer(std::make_unique<Lexer::Lexer>(std::move(aFileName)))
    , mParser(std::make_unique<Parser::Parser>())
{}

std::vector<Lexer::Lexeme> CodeAnalyzer::ProcessLexicographicAnalyzing(ErrorManager* aErrorManager)
{
    Lexer::LexerInfo lexemesInfo = mLexer->GetLexemes(aErrorManager);
    if (!aErrorManager->IsEmptyError())
        throw std::system_error();
    return std::move(lexemesInfo.LexemesList);
}

void CodeAnalyzer::ProcessCodeParsing(const std::vector<Lexer::Lexeme>& aLexemeList, ErrorManager* aErrorManager)
{
    mParser->ParseLexemes(aLexemeList, aErrorManager);
    if (!aErrorManager->IsEmptyError())
        throw std::system_error();
}
