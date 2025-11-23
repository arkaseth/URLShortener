#include <iostream>
#include <unordered_map>
#include <string>
#include <random>

class URLShortener
{
private:
    std::unordered_map<std::string, std::string> links;
    std::string baseURL;

    std::string generateRandomTrail(int length)
    {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, chars.size() - 1);

        std::string trail;
        trail.reserve(length);
        for (int i = 0; i < length; i++)
        {
            trail.push_back(chars[distribution(generator)]);
        }
        return trail;
    }

public:
    URLShortener(const std::string &baseURL) : baseURL(baseURL) {}

    std::string shortenLink(const std::string &ogLink)
    {
        std::string trail;

        do
        {
            trail = generateRandomTrail(6);
        } while (links.find(baseURL + trail) != links.end());

        std::string shortenedLink = baseURL + trail;
        links[shortenedLink] = ogLink;

        return shortenedLink;
    }

    std::string getOriginalLink(const std::string &shortenedLink)
    {
        auto it = links.find(shortenedLink);
        if (it == links.end())
            return "";
        return it->second;
    }
};

int main()
{
    try
    {
        std::cout << "Enter the base URL: ";
        std::string baseUrl = "";
        std::cin >> baseUrl;
        std::cout << "The base URL is: " << baseUrl << std::endl;

        URLShortener shortener(baseUrl);

        std::cout << "Enter the URL to be shortened: ";
        std::string originalLink;
        std::cin >> originalLink;

        std::string shortenedLink = shortener.shortenLink(originalLink);
        std::cout << "The shortened link is: " << shortenedLink << std::endl;

        std::string retrievedLink = shortener.getOriginalLink(shortenedLink);
        if (retrievedLink.empty())
            std::cout << "Invalid or non-existent shortened link." << std::endl;
        else
            std::cout << "The original link is: " << retrievedLink << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Error occurred: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error occurred." << std::endl;
    }

    system("pause");

    return 0;
}