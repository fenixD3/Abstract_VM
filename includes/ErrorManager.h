#pragma once

#include <string>

class ErrorManager
{
public:
	ErrorManager() = default;

	ErrorManager(const ErrorManager& aOther) = default;
	ErrorManager& operator=(const ErrorManager& aOther) = default;

    void AddError(const char* aError);
    bool IsEmptyError() const;

    friend std::ostream& operator<<(std::ostream& outStream, const ErrorManager& aError);

private:
    std::string mError;

private:
    const std::string& GetError() const;

};

class ErrorManagerException : public std::runtime_error
{
public:
	ErrorManagerException(std::string&& aError);
	~ErrorManagerException() = default;

	ErrorManagerException(const ErrorManagerException& aOther) = default;
	ErrorManagerException& operator=(const ErrorManagerException& aOther) = default;

};
