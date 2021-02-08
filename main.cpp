#include <iostream>
#include <fstream>

#include "Operand.h"
#include "Lexer.h"
#include "Parser.h"

void CreateInput(const std::string& aPath, std::istream& aInput = std::cin)
{
	std::ofstream toFile = std::ofstream(aPath);
	for (std::string inputLine; std::getline(aInput, inputLine); )
	{
		if (inputLine.empty())
			continue;
		if (inputLine == ";;")
		    break;
		toFile << inputLine << std::endl;
	}
}

std::vector<Lexer::Lexeme> ProcessLexicographicAnalysis(std::string& aFilePath)
{
    Lexer::Lexer lexer(std::move(aFilePath));
    Lexer::LexerInfo lexemesInfo = lexer.GetLexemes();
    if (!lexemesInfo.Error.empty())
    {
        std::cout << lexemesInfo.Error << std::endl;
        exit(1);
    }
    return std::move(lexemesInfo.LexemesList);
}

void ProcessParsing(const std::vector<Lexer::Lexeme>& aLexemeList)
{
    Parser::Parser parser;
    parser.ParseLexemes(aLexemeList);
    if (!parser.GetError().empty())
    {
        std::cout << parser.GetError() << std::endl;
        exit(1);
    }
}

int main(int ac, char** av)
{
	std::string filePath;
	if (ac > 1)
        filePath = av[1];
	else
	{
        filePath = "input.avm";
		CreateInput(filePath);
	}
	auto lexemesList = ProcessLexicographicAnalysis(filePath);
    ProcessParsing(lexemesList);
	return 0;
}
