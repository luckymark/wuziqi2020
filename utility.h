#ifndef UTILITY_H
#define UTILITY_H
#include"def.h"
#include"bign.h"
#include<string>
#include<map>
#include<unordered_map>
#include<algorithm>
using std::string;
using std::map;
using std::unordered_map;
using  std::min;
using std::max;
inline char bool2str(bool x){
    return x+'1';
}
inline char int2char(int x){
    return char(x)+'0';
}
#endif // UTILITY_H
