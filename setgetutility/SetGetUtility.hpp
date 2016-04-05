#ifndef SETGETUTILITY_HPP
#define SETGETUTILITY_HPP

#include <QString>
#include <memory>

class SetGetUtility
{
    QString className_;
    QString valueName_;
    QString valueType_;
public:
    SetGetUtility();
    SetGetUtility(QString cn_,QString vn_);
    ~SetGetUtility();

    const QString & getClassName()const{return className_;}
    const QString & getValueName()const{return valueName_;}
    const QString & getValueType()const{return valueType_;}
    void setClassName(const QString & v){className_=v;}
    void setValueName(const QString & v){valueName_=v;}
    void setValueType(const QString & v){valueType_=v;}
    void setClassName(QString && v){className_=std::move(v);}
    void setValueName(QString && v){valueName_=std::move(v);}
    void setValueType(QString && v){valueType_=std::move(v);}

    QString operator()();

};

#endif // SETGETUTILITY_HPP
