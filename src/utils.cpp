
#include "utils.hpp"

#include <regex>

std::string getBaseUrl(const std::string& fullUrl) {
    std::regex baseRegex(R"(^(https?://[^/]+))");
    std::smatch match;
    if (std::regex_search(fullUrl, match, baseRegex))
        return match[1];
    return fullUrl;
}
