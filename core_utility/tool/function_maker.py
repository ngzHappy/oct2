import os
import fileinput
import sys
import stat
import shutil


def cretae_file(fileName):
    return open(fileName,"w")

def get_endl():
    return "\n";
    pass

def get_namespace_begin():
    return """
/*namespace {*/
""";
    pass

def get_namespace_end():
    return """

/*}*/
"""

def get_zero():
    return """
template<std::size_t N=0>
class ApplyFunction {
public:
    static void apply() {
        std::cout<<"()"<<std::endl;
    }
};"""
    pass

def get_n(n):
    n_string=str(n);
    space_string="        ";
    ans_string="template<>";
    ans_string+=get_endl();
    ans_string+="class ApplyFunction<"+n_string+"> {";
    ans_string+=get_endl();
    ans_string+="public:"+get_endl();
    ans_string+="    template<"+get_endl();
    for i in range(n):
        if i==(n-1):
            ans_string+=space_string+"typename _T_"+str(i)+" "+get_endl();
        else:
            ans_string+=space_string+"typename _T_"+str(i)+","+get_endl();
    ans_string+="    >"+get_endl();
    ans_string+="    static void apply("+get_endl();
    for i in range(n):
        if i==(n-1):
            ans_string+=space_string+"_T_"+str(i)+" && _a_"+str(i)+" "+get_endl();
        else:
            ans_string+=space_string+"_T_"+str(i)+" && _a_"+str(i)+","+get_endl();   
    ans_string+="    ) {";    
    ans_string+=get_endl();
    #############################################################################
    ans_string+=space_string;
    ans_string+="""std::cout<<"(";""";
    ans_string+=get_endl();
    #############################################################################
    for i in range(n):
        i_string=str(i);
        ans_string+=space_string;
        template_string=None;
        if i==0:#the first
            template_string="""{std::cout<<std::forward<_T_N_N>(_a_N_N)<<",";}""";
        elif i==(n-1):#the last
            template_string="""{std::cout<<std::forward<_T_N_N>(_a_N_N);}""";
        else:
            template_string="""{std::cout<<std::forward<_T_N_N>(_a_N_N)<<",";}""";
        ans_string+=template_string.replace("N_N",i_string);
        ans_string+=get_endl();
        pass
    #############################################################################
    ans_string+=space_string;
    ans_string+="""std::cout<<")"<<std::endl;""";
    ans_string+=get_endl();
    #############################################################################
    ans_string+="    }";
    ans_string+=get_endl();
    ans_string+="};"+get_endl();
    ans_string+=get_endl();
    return ans_string;
    pass

def write_headers(fp):
    fp.write("#include <array>"+get_endl());
    fp.write("#include <tuple>"+get_endl());
    fp.write("#include <memory>"+get_endl());
    fp.write("#include <cstddef>"+get_endl());
    fp.write("#include <cstdint>"+get_endl());
    fp.write("#include <utility>"+get_endl());
    fp.write("#include <type_traits>"+get_endl());
    pass

def write_namespace_begin(fp):
    fp.write(get_namespace_begin());
    pass

def write_namespace_end(fp):
    fp.write(get_namespace_end());
    pass

def write_zero(fp):
    fp.write(get_zero());
    fp.write(get_endl());
    fp.write(get_endl());
    pass

def write_n(fp,n):
    fp.write(get_n(n));
    pass

if __name__=="__main__":

    fileName=None;
    if len(sys.argv)>1:
        fileName=sys.argv[1]
    else:
        fileName="ApplyFunction.hpp"

    fp=cretae_file(fileName);

    write_headers(fp);
    write_namespace_begin(fp);
    write_zero(fp);
    for n in range(1,257):
        write_n(fp,n);
        pass
    write_namespace_end(fp);
    fp.write(get_endl());
    pass

