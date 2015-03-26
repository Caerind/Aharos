#include "ResourceHolder.hpp"

ResourceHolder ResourceHolder::gInstance;
bool ResourceHolder::gInitialised;

ResourceHolder* ResourceHolder::instance()
{
    return gInitialised ? &gInstance : nullptr;
}

ResourceHolder::ResourceHolder()
{
    gInitialised = true;
}

ResourceHolder::~ResourceHolder()
{
    gInitialised = false;
}

void ResourceHolder::setLoadingFailureStrategy(ResourceHolder::LoadingFailureStrategy strategy)
{
    if (instance() != nullptr)
    {
        if (strategy == ResourceHolder::ThrowException)
            instance()->mResources.setLoadingFailureStrategy(thor::Resources::ThrowException);
        if (strategy == ResourceHolder::ReturnNullPointer)
            instance()->mResources.setLoadingFailureStrategy(thor::Resources::ReturnNullPointer);
    }
}

void ResourceHolder::setReleaseStrategy(ResourceHolder::ReleaseStrategy strategy)
{
    if (instance() != nullptr)
    {
        if (strategy == ResourceHolder::AutoRelease)
            instance()->mResources.setReleaseStrategy(thor::Resources::AutoRelease);
        if (strategy == ResourceHolder::ExplicitRelease)
            instance()->mResources.setReleaseStrategy(thor::Resources::ExplicitRelease);
    }
}
