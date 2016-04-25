#include <string>
#include <iostream>
using namespace std::literals;

const char * _cpp= u8R"=!!=(/*cpp*/
#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * var_this_data=_v_->data_.get()
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * var_this_data=_v_->data_.get()
#endif

#include "TestA.hpp"
#include "TestAData.hpp"
#include "TestAPrivateFunction.hpp"

/*zone_namespace_begin*/

namespace zone_data {
/********************************zone_data********************************/
TestAData::TestAData() {
}


TestAData::~TestAData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

TestA::TestA():data_(std::make_shared<zone_data::TestA>()) {
}


TestA::~TestA() {
}



/*zone_namespace_end*/


)=!!=";

void write_cpp(
    std::ostream & out,
    const std::string & class_name,
    const std::string & upper_class_name
) {
    if (class_name.empty()) { return; }
    std::string file(_cpp);
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
