#include <string>
#include <iostream>

const static char * _hpp=u8R"=!!=(/*hpp*/
#if !defined(__PRIVATE__DATA__TESTA__0x00)
#define __PRIVATE__DATA__TESTA__0x00() 1

#include <memory>

/*zone_namespace_begin*/

namespace zone_data{

class TestA  {
public:
    TestA();
    ~TestA();

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

    if (class_name=="TestA") {
        out<<_hpp; return;
    }

    if (class_name.empty()) { return; }

    std::string file(_hpp);
    auto find_pos=file.find("TestA");
    while (find_pos!=std::string::npos) {
        file.replace(find_pos,5,class_name);
        find_pos=file.find("TestA");
    }

    find_pos=file.find("TESTA");
    while (find_pos!=std::string::npos) {
        file.replace(find_pos,5,upper_class_name+"_0_");
        find_pos=file.find("TESTA");
    }

    out<<file;

}

