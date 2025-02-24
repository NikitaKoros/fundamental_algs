#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <stdexcept>

using namespace std;

std::string cdecl_translate(const std::string& declaration) {
    // Regular expressions for parsing
    const std::regex basicTypeRegex("^(int|char|float|double)\\b");
    const std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
    const std::regex pointerRegex("^\\*");
    const std::regex arrayRegex("^\\[\\d*\\]");
    const std::regex functionRegex("^\\(\\)");

    std::smatch match;
    std::string result;
    std::string remainder = declaration;

    // Trim input and remove semicolon
    if (!remainder.empty() && remainder.back() == ';') {
        remainder.pop_back();
    }

    // Match the basic type
    if (!std::regex_search(remainder, match, basicTypeRegex)) {
        return "Syntax error: expected a valid type";
    }
    std::string basicType = match.str();
    remainder = remainder.substr(match.length());

    // Match the identifier
    if (!std::regex_search(remainder, match, identifierRegex)) {
        return "Syntax error: expected an identifier";
    }
    
    std::string identifier = match.str();
    size_t identifierPos = remainder.find(identifier); // Находим позицию идентификатора
    if (identifierPos == std::string::npos) {
        return "Syntax error: identifier position not found";
    }
    
    std::cout << remainder << 1 << std::endl;
    
    remainder = remainder.substr(0, identifierPos) + remainder.substr(identifierPos + identifier.length());
    while(remainder.back() == ' ') remainder.pop_back();
    while(remainder.front() == ' ') remainder.erase(0, 1);
    
    std::cout << remainder << 2 << std::endl;
    
    

    result = "declare " + identifier;

    // Helper function to interpret the rest of the declaration
    auto interpret = [&](std::string& decl, std::string& desc) {
        while (!decl.empty()) {
            cout << 123 << decl << 456;
            if (std::regex_search(decl, match, arrayRegex)) {
                std::cout << "i found" << std::endl;
                
                std::string arraySize = match.str().substr(1, match.str().length() - 2);
                if (arraySize.empty()) arraySize = "unspecified size";
                desc = "array of " + arraySize + " elements of " + desc;
                decl = decl.substr(match.length());
            } else if (std::regex_search(decl, match, functionRegex)) {
                desc = "function returning " + desc;
                decl = decl.substr(match.length());
            } else if (std::regex_search(decl, match, pointerRegex)) {
                desc = "pointer to " + desc;
                decl = decl.substr(match.length());
                while(decl.back() == ' ') decl.pop_back();
                while(decl.front() == ' ') decl.erase(0, 1);
                cout << "lsls";
            } else {
                
                break;
            }
        }
    };

    std::string description = basicType;

    // Process the remainder of the declaration
    while (!remainder.empty()) {
        if (remainder[0] == '(') {
            // Handle nested parentheses
            size_t closingParen = remainder.find(')');
            if (closingParen == std::string::npos) {
                return "Syntax error: unmatched parentheses";
            }

            std::string insideParens = remainder.substr(1, closingParen - 1);
            std::string nestedDesc = description;
            interpret(insideParens, nestedDesc);
            description = "pointer to " + nestedDesc;
            remainder = remainder.substr(closingParen + 1);
        } else {
            interpret(remainder, description);
        }
    }

    result += " as " + description;
    return result;
}

int main() {
    std::string testDeclarations[] = {
        "char* a;",
        "char** b;",
        "float* d[10];",
        "int (*func)();"
    };

    for (const auto& decl : testDeclarations) {
        std::cout << cdecl_translate(decl) << std::endl;
    }

    return 0;
}
