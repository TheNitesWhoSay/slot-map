#include <slotmap/slotmap.h>
#include <cassert>
#include <iostream>

int main()
{
    slot_map<std::string> test {};
    auto a_key = test.push_back("A");
    auto b_key = test.push_back("B");
    std::cout << test << '\n';
    assert(test[a_key] == "A");
    assert(test[b_key] == "B");
    test.erase(0);
    assert(test[b_key] == "B");
    std::cout << test << '\n';
    auto c_key = test.push_back("C");
    assert(test[b_key] == "B");
    assert(test[c_key] == "C");
    std::cout << test << '\n';
    test.pop_back();
    assert(test[b_key] == "B");
    std::cout << test << '\n';
    test.pop_back();
    std::cout << test << '\n';

    return 0;
}
