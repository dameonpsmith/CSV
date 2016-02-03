#ifndef CSV_HPP_INCLUDED
#define CSV_HPP_INCLUDED
#include <vector>
#include <fstream>
#include <streambuf>

template<typename T=std::string,typename T::value_type DEL,typename T::value_type QUO,typename T::value_type NEW>
std::vector<std::vector<T>> CSVfromFile(std::string filename)
{
    using C=typename T::value_type;
    using namespace std;
    ifstream f(filename);
    if(!f.good())
    {
        throw runtime_error("Cannot open file.");
    }
    T raw=T((std::istreambuf_iterator<C>(f)),
            std::istreambuf_iterator<C>());
    auto toggle=0;
    auto s=raw.cend();
    vector<T> record;
    vector<vector<T>> records;
    for(auto c=raw.cbegin(); c!=raw.cend(); c++)
    {
        switch(*c)
        {
        case NEW:
            if(toggle&1)continue;
            record.push_back(s==raw.cend()?T():T(s,c));
            records.push_back(record);
            record.clear();
            s=raw.cend();
            break;
        case DEL:
            if(toggle&1)continue;
            record.push_back(s==raw.cend()?T():T(s,c));
            s=raw.cend();
            break;
        case QUO:
            toggle++;
            break;
        default:
            if(s==raw.cend()) s=c;
            break;
        }
    }
    return records;
}


#endif // CSV_HPP_INCLUDED
