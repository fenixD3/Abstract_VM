#include "ErrorManager.h"

void ErrorManager::AddError(const char* aError)
{
    mErrorStream += aError;
}

const std::string& ErrorManager::GetErrorStream() const
{
    return mErrorStream;
}

std::ostream& operator<<(std::ostream& outStream, const ErrorManager& aError)
{
    outStream << aError.GetErrorStream();
    return outStream;
}
