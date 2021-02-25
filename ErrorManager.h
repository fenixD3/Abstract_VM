#pragma once

#include <string>

class ErrorManager
{
public:
    void AddError(const char* aError);
    const std::string& GetErrorStream() const;
    friend std::ostream& operator<<(std::ostream& outStream, const ErrorManager& aError);

private:
    std::string mErrorStream;

};
