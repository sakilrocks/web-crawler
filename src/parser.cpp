
#include "parser.hpp"

#include <regex>
#include <iostream>


std::string extractTitle(const std::string& html) {
    std::regex titleRegex("<title>(.*?)</title>", std::regex::icase);
    std::smatch match;
    if (std::regex_search(html, match, titleRegex))
        return match[1];
    return "(no title)";
}

std::vector<std::string> extractLinks(const std::string& html, const std::string& baseUrl) {
    std::vector<std::string> links;
    std::regex linkRegex(R"(<a\s+(?:[^>]*?\s+)?href="([^"]*)"), std::regex::icase;
    std::smatch match;
    std::string::const_iterator searchStart(html.cbegin());

    
    while (std::regex_search(searchStart, html.cend(), match, linkRegex)) {
        std::string link = match[1];
        if (link.rfind("http", 0) != 0) {
            if (link.front() == '/')
                link = baseUrl + link;
            else
                link = baseUrl + "/" + link;
        }
        links.push_back(link);
        searchStart = match.suffix().first;
    }
    return links;
}