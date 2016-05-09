import os
import fileinput
import sys
import stat
import shutil

def write_ascii(fileName):
    fp=open(fileName,"w")
    for r in range(16) :
        for c in range(16) :
            value=(r*16+c);
            if value<32:
                fp.write("char("+str(value)+"),");
            elif value>=127:
                fp.write("char("+str(value)+"),");
            elif value==39:#'
                fp.write("'\\"+chr(value)+"'"+",");
            elif value==92:#\
                fp.write("'\\"+chr(value)+"'"+",");
            else:
                fp.write("'"+chr(value)+"'"+",");
            pass
        fp.write("\n")
    pass


if __name__=="__main__":
    if len(sys.argv)>1:
        write_ascii(sys.argv[1])
        pass
    else:
        write_ascii("ascii.txt")
        pass


