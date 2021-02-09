#pragma once

#include "Lexer.h"

namespace Parser
{

class Parser
{
public:
    std::string_view GetError() const;

    void ParseLexemes(const std::vector<Lexer::Lexeme>& aLexemesList);

private:
    std::string mError;
    size_t mLineCount = 0;
    size_t mStackSize = 0;

private:
    bool CheckValueDiapason(const std::string& aValue, eOperandType aType) const;

    template<eOperandType TEnumType>
    auto ConvertNumberFromString(const std::string& aValue) const
    {
        if constexpr (TEnumType == eOperandType::Float || TEnumType == eOperandType::Double)
            return std::stold(aValue);
        else
            return std::stoll(aValue);
    }

};

constexpr std::array<std::string_view, 5> ArithmeticCommands = {
    "add",
    "sub",
    "mul",
    "div",
    "mod"
};

}