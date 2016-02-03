#include <iostream>
#include "csv.hpp"

using namespace std;
int main()
{
    std::vector<std::vector<string>> csv;
    try{
        csv=CSVfromFile<std::string,',','"','\n'>(string("test.csv"));
    }
    catch(exception& e){
        std::cout<<e.what();
        return -1;
    }
    for(auto r:csv){
        for(auto f:r){
            std::cout<<f<<endl;
        }
        cout<<'@'<<endl;
    }
    return 0;
}
