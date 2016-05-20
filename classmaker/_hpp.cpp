#include <string>
#include <iostream>
using namespace std::literals;

const static char * _hpp=u8R"=!!=(/*TestA hpp*/
#if !defined(____PRAGMA_ONCE_HPP_TESTA__HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_TESTA__HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

/*zone_namespace_begin*/

namespace zone_data{
class TestAData;
}
class TestA;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const TestA *)->_TYPE_TAG_ ;

class TestA {
    TestA(const TestA&)=delete;
    TestA&operator=(const TestA&)=delete;
    TestA(TestA&&)=delete;
    TestA&operator=(TestA&&)=delete;
protected:
    using ThisDataType=std::unique_ptr<zone_data::TestAData,void(*)(zone_data::TestAData *)>;
    ThisDataType thisData_{nullptr,nullptr};
    TestA(ThisDataType && _arg_);
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const TestA *)->_TYPE_TAG_ ;
    zone_data::TestAData * thisData();
    const zone_data::TestAData * thisData() const;
public:
    explicit TestA(decltype(nullptr)) {}
    TestA();
    ~TestA();

};

/*zone_namespace_end*/

#endif



)=!!=";

void write_hpp(
    std::ostream & out,
    const std::string & class_name,
    const std::string & upper_class_name
) {
    if (class_name.empty()) { return; }
    std::string file(_hpp);
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
