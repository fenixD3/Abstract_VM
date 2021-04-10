#include "Lexer.h"
#include "Error.h"

#include <algorithm>
#include <tuple>

#include <iostream>

namespace Lexer
{

Lexer::Lexer(std::string aFileName)
        : mFileName(std::move(aFileName))
{
    mFileStream = std::ifstream(mFileName);
}

LexerInfo Lexer::Lexer::GetLexemes(ErrorManager* aErrorManager)
{
    LexerInfo resultInfo;
    for (std::string line; std::getline(mFileStream, line);)
    {
        ++mLineCount;
        if (line.empty())
            continue;
        std::optional<Lexeme> lexeme;
        try
        {
            lexeme = Tokenize(line);
        }
        catch (const LexerException& aError)
        {
            aErrorManager->AddError(aError.what());
        }
        if (lexeme.has_value())
            resultInfo.LexemesList.push_back(std::move(lexeme.value()));
    }
    return resultInfo;
}

std::optional<Lexeme> Lexer::Tokenize(std::string_view aCommand) const
{
    Lexeme lexeme;
    auto instruction = ReadToken(aCommand, ' ');
    if (instruction.empty())
    {
        lexeme.isComment = true;
        return lexeme;
    }

    if (auto commandIt = std::find(Commands.begin(), Commands.end(), instruction);
            commandIt == Commands.end())
        throw LexerException("Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::UnknownCommand);
    lexeme.Instruction = std::string(instruction);

    if (auto commandIt = std::find(CommandsWithValue.begin(), CommandsWithValue.end(), instruction);
            commandIt != CommandsWithValue.end())
    {
        auto type = ReadToken(aCommand, '(');
        if (type.empty())
            throw LexerException("Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::WrongCommandOrder);
        auto operandType = ConvertTypeToEnum(type);
        if (operandType == eOperandType::Unknown)
            throw LexerException("Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::UnknownType);
        lexeme.Type = operandType;

        auto value = ReadToken(aCommand, ')');
        if (value.empty())
            throw LexerException("Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::WrongCommandOrder);
        lexeme.Value = std::string(value);
    }
    return lexeme;
}

std::string_view Lexer::ReadToken(std::string_view& aCommand, char aDelimiter) const
{
    aCommand.remove_prefix(std::min(aCommand.find_first_not_of(" \n\t\r\f\v"), aCommand.size()));
    auto[token, secondPartCommand] = SplitTwo(aCommand, aDelimiter);
    aCommand = secondPartCommand;
    auto rightSpacePos = token.find_first_of(" \n\t\r\f\v");
    if (rightSpacePos != std::string::npos)
        token.remove_suffix(token.size() - rightSpacePos);
    if (token == ";" || token.find(';') != std::string::npos || token == ";;")
        return "";
    return token;
}

std::pair<std::string_view, std::string_view> Lexer::SplitTwo(
    std::string_view aCommand,
    char aDelimiter) const
{
    size_t position = aCommand.find(aDelimiter);
    if (position == std::string::npos)
        return {aCommand.substr(0, position), ""};
    return {aCommand.substr(0, position), aCommand.substr(position + 1)};
}

eOperandType Lexer::ConvertTypeToEnum(const std::string_view& aType) const
{
    if (aType == "int8")
        return eOperandType::Int8;
    if (aType == "int16")
        return eOperandType::Int16;
    if (aType == "int32")
        return eOperandType::Int32;
    if (aType == "float")
        return eOperandType::Float;
    if (aType == "double")
        return eOperandType::Double;
    return eOperandType::Unknown;
}

LexerException::LexerException(std::string&& aError)
    : std::logic_error(aError)
{}

}
