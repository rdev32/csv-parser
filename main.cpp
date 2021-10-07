#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

std::vector<std::string> getFileProperties(const std::string& csvFile)
{
    std::ifstream content{ csvFile };
    std::vector <std::string> properties;

    // The first line in the file has the properties of each column
    std::string columnNames{};
    // Read the first line of the CSV file
    std::getline(content, columnNames);
    // Removes all spaces from the line
    columnNames.erase(
        std::remove_if(columnNames.begin(), columnNames.end(), std::isspace),
        columnNames.end());

    // Removes all commas and adds the rest to the properties array
    std::string word{};
    for (auto& letter : columnNames) {
        if (letter == ',') {
            properties.push_back(word);
            word = "";
            continue;
        }
        word += letter;
    }
    properties.push_back(word);
    return properties;
}

// CSV PARSER
int parseCSVFile(const std::string& filename)
{
    std::ifstream content{ filename };

    if (!content) {
        std::cerr << "File not found." << std::endl;
        return 1;
    }

    std::vector<std::string> properties = getFileProperties(filename);
    bool flag{};
    
    // print contents on a fancy way
    std::cout << "=======================" << std::endl;

    while (content) {
        std::vector<std::string> lineContents;
        std::string line{};
        std::getline(content, line);

        // flag for skipping the first line
        if (!flag) { flag = !flag; continue; }
        // disables to count the last empty line
        if (line.empty()) continue;
        // we add the words to an array because we need them for displaying
        
        std::string word{};
        for (auto& letter : line) {
            if (letter == ',') {
                lineContents.push_back(word);
                word = "";
                continue;
            }
            word += letter;
        }
        lineContents.push_back(word);

        auto prop = properties.begin();
        for (auto& value : lineContents) {
            std::cout << *prop++ << ':' << value << std::endl;
        }
        std::cout << "=======================" << std::endl;

    }
    return 0;
}

int main(int argc, char* argv[])
{
    parseCSVFile("data.csv");
    return 0;
}