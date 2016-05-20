#include <string>
#include <iostream>
using namespace std::literals;

const static char * _hpp=u8R"=!!=(/*TestA hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_TESTA_0x00)
#define ____PRAGMA_ONCE_HPP_DATA_TESTA_0x00() 1

#include <memory>

/*zone_namespace_begin*/

namespace zone_data{

class TestAData  {
public:
    TestAData();
    virtual ~TestAData();
public:
};

}

/*zone_namespace_end*/

#endif

)=!!=";

void write_data(
    std::ostream & out,
    const std::string & class_name,
    const std::string & upper_class_name
) {

    if (class_name=="TestA"s) {
        out<<_hpp; return;
    }

    if (class_name.empty()) { return; }

    std::string file(_hpp);
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

