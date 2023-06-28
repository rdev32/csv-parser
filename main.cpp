#include <vector>
#include <type_traits>
#include <iomanip>
#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <charconv>
#include <exception>
#include <cstdlib>

int main()
{
    auto readline =[](const std::string& line)
    {
        std::vector<std::string_view> cols;
        char mode = ',';
        char del =',';
        char quote = '"';
        size_t lastdel =0;
        bool isquote = false;
        size_t i = 0;
        for(; i < line.size();++i)
        {
            //const char cur = ;
            if(line[i]==mode)
            {
                if(mode == quote)
                    ++lastdel;
                if(mode == quote || (mode == del && !isquote))
                {
                cols.emplace_back(&line[lastdel],i-lastdel);
                lastdel = i;
                if(i + 1 < line.size())
                    lastdel++;
                }
                else if(mode == del && isquote)
                {
                    isquote = false;
                    lastdel++;
                }
            }
            if(line[i]==quote)
            {
                switch(mode)
                {
                case ',':
                    mode = quote;
                    isquote = true;
                    break;
                case '"':
                    mode = del;
                    break;
                }
            }
        }
        if(!isquote)
          cols.emplace_back(&line[lastdel],i-lastdel);
        return cols;
    };
    std::string line = "colname1,,col2,col3,,,\"col4\",col5,column6,\"columninquote\"";
    auto vec = readline(line);
    for(auto v:vec)
    {
        if(v.empty())
          std::cout << "empty column\n";
        else std::cout << v << '\n';
    }
}
