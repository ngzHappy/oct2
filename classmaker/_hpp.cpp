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

/*
#if !defined(macro_no_copy)
#define macro_no_copy(_t_class_name_) private:_t_class_name_(const _t_class_name_ &)=delete; \
_t_class_name_(_t_class_name_ &&)=delete; \
_t_class_name_&operator=(const _t_class_name_ &)=delete; \
_t_class_name_&operator=(_t_class_name_ &&)=delete
#endif
*/

namespace zone_data{
class TestAData;
}
class TestA;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const TestA *)->_TYPE_TAG_ ;

class TestA {
/*macro_no_copy(TestA);*/
protected:
    std::shared_ptr<zone_data::TestAData> thisData_;
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const TestA *)->_TYPE_TAG_ ;
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
