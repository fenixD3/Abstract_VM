#include "../includes/ErrorManager.h"

void ErrorManager::AddError(const char* aError)
{
    mError += aError;
}

bool ErrorManager::IsEmptyError() const
{
    return mError.empty();
}

std::ostream& operator<<(std::ostream& outStream, const ErrorManager& aError)
{
    outStream << aError.GetError();
    return outStream;
}

const std::string& ErrorManager::GetError() const
{
    return mError;
}
