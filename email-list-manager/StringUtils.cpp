#ifndef STRING_UTILS_BODY
#define STRING_UTILS_BODY

#include "StringUtils.hpp"

string StringUtils::ltrim(string chain) {
    return boost::regex_replace(chain, boost::regex("^\\s+"), string(""));
}

string StringUtils::rtrim(string chain ) {
    return boost::regex_replace(chain, boost::regex("\\s+$"), string(""));
}

string StringUtils::trim(string chain) {
    return StringUtils::ltrim(StringUtils::rtrim(chain));
}

string StringUtils::toLower(string chain) {
    std::transform(chain.begin(), chain.end(), chain.begin(), ::tolower);
    return chain;
}

string StringUtils::removeBlankSpaces(string chain) {
    return boost::regex_replace(chain, boost::regex("\\s"), string(""));
}

#endif // STRING_UTILS_BODY
