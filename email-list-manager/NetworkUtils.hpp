#include <string>
#include <iostream>
#include <algorithm>
#include "StringUtils.hpp"
#include <boost/thread.hpp>

using namespace std;

class DLLM_LOCAL NetworkUtils {
    public:
 	    NetworkUtils(){};
 	    ~NetworkUtils(){};
        static bool isValidEmail(std::string email, int maxLength=0, bool allowSpacesInAOL=false);
        static std::string getDomainFromEmail(std::string email);
        static std::string validateEmail(std::string email);
        static std::string getCountryCode(std::string email);
    private:
       static boost::mutex _mutex;
};
