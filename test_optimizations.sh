#!/bin/bash

echo -e "\n-O0"
g++ -g basic_comp.cpp -O0 
objdump -l -d a.out > O0_line.txt
./a.out

echo -e "\n-O1"
g++ -g basic_comp.cpp -O1 
objdump -l -d a.out > O1_line.txt
./a.out

echo -e "\n-O2"
g++ -g basic_comp.cpp -O2 
objdump -l -d a.out > O2_line.txt
./a.out

echo -e "\n-O3"
g++ -g basic_comp.cpp -O3 
objdump -l -d a.out > O3_line.txt
./a.out

echo -e "\n-fauto-inc-dec"
g++ -g basic_comp.cpp -fauto-inc-dec
objdump -l -d a.out > fauto-inc-dec_line.txt
./a.out

echo -e "\n-fcprop-registers"
g++ -g basic_comp.cpp -fcprop-registers
objdump -l -d a.out > fcprop-registers_line.txt
./a.out

echo -e "\n-fdce"
g++ -g basic_comp.cpp -fdce
objdump -l -d a.out > fdce_line.txt
./a.out

echo -e "\n-fdefer-pop"
g++ -g basic_comp.cpp -fdefer-pop
objdump -l -d a.out > fdefer-pop_line.txt
./a.out

echo -e "\n-fdelayed-branch"
g++ -g basic_comp.cpp -fdelayed-branch
objdump -l -d a.out > fdelayed-branch_line.txt
./a.out

echo -e "\n-fdse"
g++ -g basic_comp.cpp -fdse
objdump -l -d a.out > fdse_line.txt
./a.out

echo -e "\n-fguess-branch-probability"
g++ -g basic_comp.cpp -fguess-branch-probability
objdump -l -d a.out > fguess-branch-probability_line.txt
./a.out

echo -e "\n-fif-conversion2"
g++ -g basic_comp.cpp -fif-conversion2
objdump -l -d a.out > fif-conversion2_line.txt
./a.out

echo -e "\n-fif-conversion"
g++ -g basic_comp.cpp -fif-conversion
objdump -l -d a.out > fif-conversion_line.txt
./a.out

echo -e "\n-finline-small-functions"
g++ -g basic_comp.cpp -finline-small-functions
objdump -l -d a.out > finline-small-functions_line.txt
./a.out

echo -e "\n-fipa-pure-const"
g++ -g basic_comp.cpp -fipa-pure-const
objdump -l -d a.out > fipa-pure-const_line.txt
./a.out

echo -e "\n-fipa-reference"
g++ -g basic_comp.cpp -fipa-reference
objdump -l -d a.out > fipa-reference_line.txt
./a.out

echo -e "\n-fmerge-constant"
g++ -g basic_comp.cpp -fmerge-constant
objdump -l -d a.out > fmerge-constant_line.txt
./a.out

echo -e "\n-fsplit-wide-types"
g++ -g basic_comp.cpp -fsplit-wide-types
objdump -l -d a.out > fsplit-wide-types_line.txt
./a.out

echo -e "\n-ftree-ccp"
g++ -g basic_comp.cpp -ftree-ccp
objdump -l -d a.out > ftree-ccp_line.txt
./a.out

echo -e "\n-ftree-ch"
g++ -g basic_comp.cpp -ftree-ch
objdump -l -d a.out > ftree-ch_line.txt
./a.out

echo -e "\n-ftree-copyrename"
g++ -g basic_comp.cpp -ftree-copyrename
objdump -l -d a.out > ftree-copyrename_line.txt
./a.out

echo -e "\n-ftree-dce"
g++ -g basic_comp.cpp -ftree-dce
objdump -l -d a.out > ftree-dce_line.txt
./a.out

echo -e "\n-ftree-dominator-opts"
g++ -g basic_comp.cpp -ftree-dominator-opts
objdump -l -d a.out > ftree-dominator-opts_line.txt
./a.out

echo -e "\n-ftree-dse"
g++ -g basic_comp.cpp -ftree-dse
objdump -l -d a.out > ftree-dse_line.txt
./a.out

echo -e "\n-ftree-fre"
g++ -g basic_comp.cpp -ftree-fre
objdump -l -d a.out > ftree-fre_line.txt
./a.out

echo -e "\n-ftree-sra"
g++ -g basic_comp.cpp -ftree-sra
objdump -l -d a.out > ftree-sra_line.txt
./a.out

echo -e "\n-ftree-ter"
g++ -g basic_comp.cpp -ftree-ter
objdump -l -d a.out > ftree-ter_line.txt
./a.out

echo -e "\n-funit-at-a-tim"
g++ -g basic_comp.cpp -funit-at-a-time
objdump -l -d a.out > funit-at-a-tim_line.txt
./a.out