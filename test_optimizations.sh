#!/bin/bash

echo -e "\n-O0"
g++ -g basic_comp.cpp -O0 
objdump -d a.out > O0.txt
./a.out

echo -e "\n-O1"
g++ -g basic_comp.cpp -O1 
objdump -d a.out > O1.txt
./a.out

echo -e "\n-O2"
g++ -g basic_comp.cpp -O2 
objdump -d a.out > O2.txt
./a.out

echo -e "\n-O3"
g++ -g basic_comp.cpp -O3 
objdump -d a.out > O3.txt
./a.out

echo -e "\n-fauto-inc-dec"
g++ -g basic_comp.cpp -fauto-inc-dec
objdump -d a.out > fauto-inc-dec.txt
./a.out

echo -e "\n-fcprop-registers"
g++ -g basic_comp.cpp -fcprop-registers
objdump -d a.out > fcprop-registers.txt
./a.out

echo -e "\n-fdce"
g++ -g basic_comp.cpp -fdce
objdump -d a.out > fdce.txt
./a.out

echo -e "\n-fdefer-pop"
g++ -g basic_comp.cpp -fdefer-pop
objdump -d a.out > fdefer-pop.txt
./a.out

echo -e "\n-fdelayed-branch"
g++ -g basic_comp.cpp -fdelayed-branch
objdump -d a.out > fdelayed-branch.txt
./a.out

echo -e "\n-fdse"
g++ -g basic_comp.cpp -fdse
objdump -d a.out > fdse.txt
./a.out

echo -e "\n-fguess-branch-probability"
g++ -g basic_comp.cpp -fguess-branch-probability
objdump -d a.out > fguess-branch-probability.txt
./a.out

echo -e "\n-fif-conversion2"
g++ -g basic_comp.cpp -fif-conversion2
objdump -d a.out > fif-conversion2.txt
./a.out

echo -e "\n-fif-conversion"
g++ -g basic_comp.cpp -fif-conversion
objdump -d a.out > fif-conversion.txt
./a.out

echo -e "\n-finline-small-functions"
g++ -g basic_comp.cpp -finline-small-functions
objdump -d a.out > finline-small-functions.txt
./a.out

echo -e "\n-fipa-pure-const"
g++ -g basic_comp.cpp -fipa-pure-const
objdump -d a.out > fipa-pure-const.txt
./a.out

echo -e "\n-fipa-reference"
g++ -g basic_comp.cpp -fipa-reference
objdump -d a.out > fipa-reference.txt
./a.out

echo -e "\n-fmerge-constant"
g++ -g basic_comp.cpp -fmerge-constant
objdump -d a.out > fmerge-constant.txt
./a.out

echo -e "\n-fsplit-wide-types"
g++ -g basic_comp.cpp -fsplit-wide-types
objdump -d a.out > fsplit-wide-types.txt
./a.out

echo -e "\n-ftree-ccp"
g++ -g basic_comp.cpp -ftree-ccp
objdump -d a.out > ftree-ccp.txt
./a.out

echo -e "\n-ftree-ch"
g++ -g basic_comp.cpp -ftree-ch
objdump -d a.out > ftree-ch.txt
./a.out

echo -e "\n-ftree-copyrename"
g++ -g basic_comp.cpp -ftree-copyrename
objdump -d a.out > ftree-copyrename.txt
./a.out

echo -e "\n-ftree-dce"
g++ -g basic_comp.cpp -ftree-dce
objdump -d a.out > ftree-dce.txt
./a.out

echo -e "\n-ftree-dominator-opts"
g++ -g basic_comp.cpp -ftree-dominator-opts
objdump -d a.out > ftree-dominator-opts.txt
./a.out

echo -e "\n-ftree-dse"
g++ -g basic_comp.cpp -ftree-dse
objdump -d a.out > ftree-dse.txt
./a.out

echo -e "\n-ftree-fre"
g++ -g basic_comp.cpp -ftree-fre
objdump -d a.out > ftree-fre.txt
./a.out

echo -e "\n-ftree-sra"
g++ -g basic_comp.cpp -ftree-sra
objdump -d a.out > ftree-sra.txt
./a.out

echo -e "\n-ftree-ter"
g++ -g basic_comp.cpp -ftree-ter
objdump -d a.out > ftree-ter.txt
./a.out

echo -e "\n-funit-at-a-tim"
g++ -g basic_comp.cpp -funit-at-a-time
objdump -d a.out > funit-at-a-tim.txt
./a.out