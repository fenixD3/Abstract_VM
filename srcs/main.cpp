#include <iomanip>
#include <string>
#include "Vm.h"

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

Vm InitVM(int ac, char** av)
{
    std::string filePath;
    if (ac > 1)
        filePath = av[1];
    else
    {
        filePath = "input.avm";
        CreateInput(filePath);
    }
    return Vm(std::move(filePath));
}

int main(int ac, char** av)
{
    Vm abstractVm = InitVM(ac, av);
    abstractVm.Process();
    std::cout << abstractVm.GetOutput().str();
	return 0;
}
