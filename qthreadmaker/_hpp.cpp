#include <string>
#include <iostream>
using namespace std::literals;

const static char * _hpp=u8R"=!!=(/*TestA.hpp*/
#ifndef ____PRAGMA_ONCE_TESTA_HPP_
#define ____PRAGMA_ONCE_TESTA_HPP_() 1

#include <memory>
#include <QtCore/qobject.h>
#include <QtCore/qthread.h>

class TestA;
class ThreadOfTestA :
    public QThread,
    public std::enable_shared_from_this<ThreadOfTestA> {
    Q_OBJECT

private:
    TestA * const super_;
    friend class TestA;
public:
    void run()override;
    ThreadOfTestA(TestA *);
    ~ThreadOfTestA();

protected:
    void quitInThisThread();
    bool event(QEvent *) override;
};

class TestA :public QObject {
    Q_OBJECT
public:
    TestA();
    ~TestA();
protected:
    std::shared_ptr<ThreadOfTestA> thread_;
};

#endif // TEST_HPP

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
