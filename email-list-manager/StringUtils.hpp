#ifndef STRING_UTILS_HEADER
#define STRING_UTILS_HEADER

#include <string>
#include <boost/regex.hpp>
#include <algorithm>
#include "DLLModuleMacro.hpp"

using namespace std;

class DLLM_LOCAL StringUtils {
    public:
        static string trim(string chain);
        static string toLower(string chain);
        static string removeBlankSpaces(string chain);
    private:
        static string ltrim(string chain);
        static string rtrim(string chain);
};
#endif // STRING_UTILS_HEADER
