#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <memory>
#include <string>

#include <Thor/Resources.hpp>

class ResourceHolder
{
    public:
        static ResourceHolder* instance();

        template <typename T>
        static std::shared_ptr<T> get(thor::ResourceKey<T> key);

        template <typename T>
        static std::shared_ptr<T> get(std::string const& filename);

        template <typename T>
        static void release(thor::ResourceKey<T> key);

        template <typename T>
        static void release(std::string const& filename);

        enum LoadingFailureStrategy
        {
            ThrowException,
            ReturnNullPointer,
        };

        enum ReleaseStrategy
        {
            AutoRelease,
            ExplicitRelease,
        };

        static void setLoadingFailureStrategy(LoadingFailureStrategy strategy);
		static void setReleaseStrategy(ReleaseStrategy strategy);

    private:
        ResourceHolder();
        ~ResourceHolder();

        static ResourceHolder gInstance;
        static bool gInitialised;

        thor::MultiResourceCache mResources;
};

template <typename T>
std::shared_ptr<T> ResourceHolder::get(thor::ResourceKey<T> key)
{
    if (instance() != nullptr)
    {
        return instance()->mResources.acquire(key);
    }
    return nullptr;
}

template <typename T>
std::shared_ptr<T> ResourceHolder::get(std::string const& filename)
{
    if (instance() != nullptr)
    {
        return instance()->mResources.acquire(thor::Resources::fromFile<T>(filename));
    }
    return nullptr;
}

template <typename T>
void ResourceHolder::release(thor::ResourceKey<T> key)
{
    if (instance() != nullptr)
    {
        return instance()->mResources.release(key);
    }
}

template <typename T>
void ResourceHolder::release(std::string const& filename)
{
    if (instance() != nullptr)
    {
        return instance()->mResources.release(thor::Resources::fromFile<T>(filename));
    }
}

#endif // RESOURCEHOLDER_HPP
