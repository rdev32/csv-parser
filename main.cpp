#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

auto readLine(const std::string &line)
{
    std::vector<std::string> lineContent{};
    
    std::string word{};
    for (auto &letter : line) {
        if (letter == ',') {
            lineContent.push_back(word);
            word = "";
            continue;
        }
        word += letter;
    }
    lineContent.push_back(word);

    return lineContent;
}

void removeSpaces(std::string &line)
{
    line.erase(
        std::remove_if(
            line.begin(), 
            line.end(), 
            [](unsigned char c) {
                return std::isspace(c);
            }), 
        line.end());
}

auto headers(std::ifstream &file) 
{ 
    std::string attributes{};
    std::getline(file, attributes);

    removeSpaces(attributes);
    return readLine(attributes);
}

auto contents(std::ifstream &file) 
{
    std::map<std::string, std::string> content;
    auto headersDone { true };

    while(file) 
    {    
        std::string line{};
        std::getline(file, line);
        removeSpaces(line);

        if (headersDone) { 
            std::make_pair(readLine(line), );
            headersDone = false; 
            continue; 
        }

        content.push_back(readLine(line));
    }

    return content;
}

int main(int argc, char* argv[])
{
    std::ifstream file{ std::string(argv[argc -1]) };
    
    if (!file) { 
        std::cerr << "File not found.\n";
        return 1;
    }

    auto head = headers(file);
    auto content = contents(file);

    for (auto &attribute : head) {
        std::cout << attribute << " : ";
        for (auto &value : content) {
            
        }
        std::cout << std::endl;
    }

    return 0;
}