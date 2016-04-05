#include "SetGetUtility.hpp"
#include <memory>

SetGetUtility::SetGetUtility(){}
SetGetUtility::~SetGetUtility(){}

SetGetUtility::SetGetUtility(QString cn_, QString vn_):
    className_(std::move(cn_)),
    valueName_(std::move(vn_))
{

}

QString SetGetUtility::operator()(){
    do{
        if( className_.isEmpty() ){break;}
        if( valueName_.isEmpty() ){break;}
        if( valueType_.isEmpty() ){break;}
        QString functionValueName_=valueName_;
        if(functionValueName_[0].isLower()){
            functionValueName_[0] = functionValueName_[0].toUpper();
        }
        const QString commentValeName_=" /*"+valueName_+"*/";
        const QString typenameValueTypeName_="_t_" +valueName_.toUpper()+ "_t__";
        const QString valueNameVar_="_"+valueName_+"_";
        const QString space_("    ");
        QString ans_("public:\n") ;

        ans_+=space_+"void set"+functionValueName_+"(const ";
        ans_+=valueType_+"&"+commentValeName_+");\n";

        ans_+=space_+"void set"+functionValueName_+"(";
        ans_+=valueType_+"&&"+commentValeName_+");\n";

        ans_+=space_+"const "+valueType_+" & get";
        ans_+=functionValueName_+"() const;\n";

        ans_+=space_+"const "+valueType_+" & ";
        ans_+=valueName_+"() const{ return get" +functionValueName_+ "();}\n";

        ans_+="private: template<typename "+typenameValueTypeName_+">\n";
        ans_+=space_+"void _p_set"+functionValueName_+"(";
        ans_+=typenameValueTypeName_+" &&"+commentValeName_+");\n";

        ans_+="\n\n";

        ans_+="const "+valueType_+" & "+className_+"::get";
        ans_+=functionValueName_+"() const{\n"+space_+"\n}\n";

        ans_+="\n";

        ans_+="template<typename "+typenameValueTypeName_+">\n";
        ans_+="void "+className_+"::_p_set"+functionValueName_+"(";
        ans_+=typenameValueTypeName_+" &&"+valueNameVar_+"){\n"+space_+"\n}\n";

        ans_+="\n";

        ans_+="void "+className_+"::set"+functionValueName_+"(const ";
        ans_+=valueType_+"&"+valueNameVar_+"){\n"
                +space_+"_p_set"+functionValueName_+"("+valueNameVar_+");\n"
+"}\n";

        ans_+="\n";

        ans_+="void "+className_+"::set"+functionValueName_+"(";
        ans_+=valueType_+"&&"+valueNameVar_+"){\n"
                +space_+"_p_set"+functionValueName_+"(std::move("+valueNameVar_+"));\n"
+"}\n";

        ans_+="\n";

        return std::move(ans_);

    }while(0);
    return QString("/*null*/");
}
