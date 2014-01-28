# http://hi.baidu.com/_kouu/item/977755130f1f44fd756a84d9

# build libS.a
g++ -fPIC -c S.cpp
ar r libS.a S.o

# build libD.so
g++ -g -fPIC -shared D.cpp libS.a -o libD.so


# build Bin
g++ Bin.cpp libS.a libD.so -o Bin

# execute Bin
LD_LIBRARY_PATH=`pwd` ./Bin


