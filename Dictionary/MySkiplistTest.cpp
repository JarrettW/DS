#include <iostream>
#include <string>
#include "MySkiplist.cpp"


int main(){
    //电话号码簿
    //Entry<std::string, int> entry("Lee", 000000);
    MySkiplist<std::string, int> AddressList;
    AddressList.put("Lee", 138000);
    AddressList.put("Wong", 139000);
    AddressList.put("Liu", 137000);
    std::cout << "Lee's phone number: " << *AddressList.get("Lee") << std::endl;;
    std::cout << "size: " << AddressList.size() << std::endl;
    std::cout << "Level: " << AddressList.level() << std::endl;
    std::cout << "remove(\"Lee\")true/1, false/0: " << AddressList.remove("Lee") << std::endl;
    std::cout << "size: " << AddressList.size();
    
    return 0;
}