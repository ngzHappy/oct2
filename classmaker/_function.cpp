#include <string>
#include <iostream>
using namespace std::literals;

const static char * _function=u8R"=!!=(/*TestA hpp*/
#if !defined(____PRAGMA_ONCE_HPP_TESTA_FUNCTION__)
#define ____PRAGMA_ONCE_HPP_TESTA_FUNCTION__() 1

#include "TestAData.hpp"

/*zone_namespace_begin*/
class TestA;

namespace zone_private_function {

}

/*zone_namespace_end*/

#endif

)=!!=";

void write_function(
    std::ostream & out,
    const std::string & class_name,
    const std::string & upper_class_name
) {
    if (class_name.empty()) { return; }
    std::string file(_function);
    if (class_name=="TestA"s) {
        out<<file;return;}

    auto find_pos=file.find("TestA"s);
    while (find_pos!=std::string::npos) {
        file.replace(find_pos,5,class_name);
        find_pos=file.find("TestA"s);
    }

    find_pos=file.find("TESTA"s);
    while (find_pos!=std::string::npos) {
        file.replace(find_pos,5,upper_class_name+"_0_");
        find_pos=file.find("TESTA"s);
    }

    out<<file;
}

