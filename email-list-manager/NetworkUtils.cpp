#include "NetworkUtils.hpp"

boost::mutex NetworkUtils::_mutex;
bool NetworkUtils::isValidEmail(string email, int maxLength, bool allowSpacesInAOL)
{
	if (((maxLength > 0) && (email.length() > maxLength)) || email.size() <= 0) {
		return false;
	}
	//string pattern = "^[a-z0-9]+[a-z0-9\\._-]+@[a-z0-9\\._-]+\\.[a-z]+$";
	string pattern = "^[a-z]+[a-z0-9\\._-]+@[a-z0-9\\._-]+\\.[a-z]+$";
	string patternWithSpaces = "^[a-z]+[a-z0-9\\.\\s_-]+@[a-z0-9\\._-]+\\.[a-z]+$";
	string domain = "";

	email = StringUtils::toLower(email);
	domain = NetworkUtils::getDomainFromEmail(email);


	if (domain == "aol.com" && allowSpacesInAOL) {
		pattern = patternWithSpaces;
	}

	//printf(pattern);
	bool match = boost::regex_search(email,boost::regex(pattern));
	return match;
}

string NetworkUtils::getDomainFromEmail(string email) {

	int atIndex = email.find_first_of('@');
    string domain = "";
    if (atIndex != string::npos) {
        domain = email.substr(atIndex+1);
    }
    return domain;
}

string NetworkUtils::validateEmail(string email) {
	boost::mutex::scoped_lock lock(_mutex);
    email = StringUtils::toLower(email);
    email = StringUtils::trim(email);
    return StringUtils::removeBlankSpaces(email);
}

std::string NetworkUtils::getCountryCode(std::string email)
{
	std::size_t pos = email.find_last_of('.');
	if( pos != std::string::npos
			&& pos < email.size() )
	{
		return email.substr(pos);
	}
	else
	{
		return std::string("");
	}
}



