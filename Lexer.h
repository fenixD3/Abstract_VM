#pragma once

#include <fstream>
#include <vector>
#include <optional>
#include <memory>
#include <unordered_set>
#include <array>
#include <utility>

#include "IOperand.h"

namespace Lexer
{

struct Lexeme
{
	std::string Instruction, Value;
	eOperandType Type;
	bool isComment = false;
};

struct LexerInfo
{
	std::vector<Lexeme> LexemesList;
	std::string Error;
};

class Lexer
{
public:
	Lexer(std::string aFileName);

	LexerInfo GetLexemes();

private:
	const std::string mFileName;
	std::ifstream mFileStream;
	size_t mLineCount = 0;

private:
	std::optional<Lexeme> Tokenize(std::string_view aCommand, std::string& outError) const;
	std::string_view ReadToken(std::string_view& aCommand, char aDelimiter) const;
    std::pair<std::string_view, std::string_view> SplitTwo(
        std::string_view aCommand,
        char aDelimiter) const;
    std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(
        std::string_view aCommand,
        char aDelimiter) const;
    eOperandType ConvertTypeToEnum(const std::string_view& aType) const;

};

constexpr std::array<std::string_view, 11> Commands = {
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit"
};

constexpr std::array<std::string_view, 2> CommandsWithValue = {
	"push", "assert"
};

}
