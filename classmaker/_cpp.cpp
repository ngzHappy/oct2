#include <string>
#include <iostream>
using namespace std::literals;

const char * _cpp=u8R"=!!=(/*TestA cpp*/
#include "TestA.hpp"
#include "private/TestAData.hpp"
#include "private/TestAPrivateFunction.hpp"

/*zone_namespace_begin*/
template<>
inline auto getThisData<zone_data::TestAData *,0>(const TestA * arg) ->zone_data::TestAData *{
    return const_cast<TestA *>(arg)->thisData(); 
}

template<>
inline auto getThisData<const zone_data::TestAData *,1>(const TestA * arg) ->const zone_data::TestAData *{ 
    return arg->thisData();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * varThisData=getThisData<zone_data::TestAData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * varThisData=getThisData<const zone_data::TestAData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
TestAData::TestAData() {
    static_assert(
        has_virtual_destructor<TestAData>::value,
        "the class must has virtual destructor");
}


TestAData::~TestAData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

TestA::~TestA() {
}

TestA::TestA():TestA(ThisDataType(
                         new zone_data::TestAData,
                         [](auto *arg){delete arg;})) {
}

TestA::TestA(ThisDataType && _arg_):
    thisData_(std::move(_arg_)){
}

auto TestA::thisData()->zone_data::TestAData *{
    return static_cast<zone_data::TestAData *>(thisData_.get()); 
}

auto TestA::thisData() const->const zone_data::TestAData *{
    return static_cast<const zone_data::TestAData *>(thisData_.get());
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
