#include <string>
#include <iostream>
using namespace std::literals;

const char * _cpp=u8R"=!!=(/*TestA.cpp*/
#include "TestA.hpp"
#include <cassert>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/qcoreapplication.h>
#include <QtGui/qevent.h>

namespace {
class TestAQuitEvent :public QEvent{
public:
    TestAQuitEvent() :QEvent(QEvent::MaxUser){}
};
}

void ThreadOfTestA::quitInThisThread() {
    QCoreApplication::postEvent(this,new TestAQuitEvent);
}

bool ThreadOfTestA::event(QEvent *e) {
    if (e->type()==QEvent::MaxUser) {
        if (dynamic_cast<TestAQuitEvent*>(e)) {
            assert(QThread::currentThread()==this);
            this->quit();
        }
    }
    return QThread::event(e);
}

void ThreadOfTestA::run() {

    try{
        auto varDelete=[var=shared_from_this()](auto * arg) {delete arg; };
        
    }catch(...){
        qDebug()<<"qthread run in error !!";
    }

    exec();
}
 
ThreadOfTestA::ThreadOfTestA(TestA *v):super_(v) {
    this->moveToThread(this);
    connect(/*delete in main thread*/
        this,&ThreadOfTestA::finished,
        qApp,[this]() {delete this; },
        Qt::QueuedConnection
    );
}

ThreadOfTestA::~ThreadOfTestA() {
}

TestA::TestA() {
    thread_=std::shared_ptr<ThreadOfTestA>(new ThreadOfTestA(this),
        [](ThreadOfTestA * arg) {arg->quitInThisThread();});
    this->moveToThread(thread_.get());
    thread_->start();
}

TestA::~TestA() {
    disconnect(thread_.get());
    thread_.reset();
}


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
