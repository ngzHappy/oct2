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
    pass

def get_zero():
    return """
template<std::size_t N=0>
class Apply {
public:
    template<typename _U_,typename ..._A_>
    static decltype(auto) apply(_U_ &&u,_A_&&...) {
        u<<"()"<<std::endl;
        return std::forward<_U_>(u);
    }
};"""
    pass

def get_n(n):
    n_string=str(n);
    space_string="        ";
    ans_string="template<>";
    ans_string+=get_endl();
    ans_string+="class Apply<"+n_string+"> {";
    ans_string+=get_endl();
    ans_string+="public:"+get_endl();
    ans_string+="    template<typename _U_,typename _Tuple_>";
    ans_string+=get_endl();
    ans_string+="    static decltype(auto) apply(_U_&&u,_Tuple_ &&argTuple) {";
    ans_string+=get_endl();
    #############################################################################
    ans_string+=space_string;
    ans_string+="""u<<"(";""";
    ans_string+=get_endl();
    #############################################################################
    for i in range(n):
        i_string=str(i);
        ans_string+=space_string;
        template_string=None;
        if i==0:#the first
            template_string="""{u<<std::get<N_N>(std::forward<_Tuple_>(argTuple))<<",";}""";
        elif i==(n-1):#the last
            template_string="""{u<<std::get<N_N>(std::forward<_Tuple_>(argTuple));}""";
        else:
            template_string="""{u<<std::get<N_N>(std::forward<_Tuple_>(argTuple))<<",";}""";
        ans_string+=template_string.replace("N_N",i_string);
        ans_string+=get_endl();
        pass
    #############################################################################
    ans_string+=space_string;
    ans_string+="""u<<")"<<std::endl;""";
    ans_string+=get_endl();
    ans_string+=space_string;
    ans_string+="""return std::forward<_U_>(u);""";
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

def write_zero(fp):
    fp.write(get_zero());
    fp.write(get_endl());
    fp.write(get_endl());
    pass

def write_n(fp,n):
    fp.write(get_n(n));
    pass

def write_namespace_end(fp):
    fp.write(get_namespace_end());
    pass

if __name__=="__main__":

    fileName=None;
    if len(sys.argv)>1:
        fileName=sys.argv[1]
    else:
        fileName="Apply.hpp"

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


