#pragma once

#include <string>

class ErrorManager
{
public:
    void AddError(const char* aError);
    bool IsEmptyError() const;

    friend std::ostream& operator<<(std::ostream& outStream, const ErrorManager& aError);

private:
    std::string mError;

private:
    const std::string& GetError() const;

};
