#include "util_task5.hpp"
#include <sys/types.h>

std::string CdeclTranslate(const std::string& declaration) {
    const std::regex type("^(int|char|float|double)");
    const std::regex identifier("[a-zA-Z][a-zA-Z0-9]*");
    const std::regex pointer("\\*+");
    const std::regex array("\\[\\d*\\]");
    const std::regex function("\\(\\)");
    
    std::smatch match;
    std::string result;
    std::string remainder = declaration;
    
    if (remainder.back() == ';') {
        remainder.pop_back();
    }
    
    if (!std::regex_search(remainder, match, type)) {
        return "Syntax error: type is not valid.";
    }
    
    std::string foundType = match.str();
    remainder = remainder.substr(match.length());
    
    if (!std::regex_search(remainder, match, identifier)) {
        return "Syntax error: identifier is not valid or missing.";
    }
    
    std::string foundIdentifier = match.str();
    remainder = remainder.substr(match.length());
    
    result = "declare " + foundIdentifier + " as ";
}

void InterpreteFile(const std::string& filePath) {
    
}