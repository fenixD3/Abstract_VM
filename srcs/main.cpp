#include <iomanip>

#include "../includes/Vm.h"

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

void Test()
{
    /// TODO research IO manipulators for string equaling
    std::cout << std::setprecision(2) << std::to_string(0.) << std::endl
              << std::to_string(0.0) << std::endl
              << std::to_string(0.00) << std::endl
              << std::to_string(0) << std::endl;
    std::cout << std::boolalpha << (std::string("0") == std::to_string(0.)) << std::endl
              << (std::string("0.") == std::to_string(0.)) << std::endl
              << (std::string("0.000000") == std::to_string(0.)) << std::endl;
}

int main(int ac, char** av)
{
//    Test();
    Vm abstractVm = InitVM(ac, av);
    abstractVm.Process();
    std::cout << abstractVm.GetOutput().str();
	return 0;
}
