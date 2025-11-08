
#ifndef PARSRER_HPP
#define PARSRER_HPP

#include <string>
#include <vector>


std::string extractTitle(const std::string& html);
std::vector<std::string> extractLinks(const std::string& html, const std::string& baseUrl);


#endif