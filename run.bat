::"C:\Program Files\Anaconda3\Scripts\activate.bat"

cls

::CALL python find_ccs.py graphs/testgraph.txt ccs/test_lscc.txt ccs/test_lwcc.txt
::CALL python find_ccs.py graphs/Wiki-Vote.txt ccs/wiki_lscc.txt ccs/wiki_lwcc.txt
::CALL python find_ccs.py graphs/soc-Epinions1.txt ccs/epin_lscc.txt ccs/epin_lwcc.txt
::CALL python find_ccs.py graphs/compacted_ego_gplus.txt ccs/gplus_lscc.txt ccs/gplus_lwcc.txt
::CALL python find_ccs.py graphs/soc-pokec-relationships.txt ccs/pokec_lscc.txt ccs/pokec_lwcc.txt
::CALL python find_ccs.py graphs/soc-LiveJournal1.txt ccs/live_lscc.txt ccs/live_lwcc.txt

::CALL g++ -Wall -pedantic -std=c++11 -g -o compute_distances.exe source/compute_distances.cpp
CALL C:/TDM-GCC-64/bin/x86_64-w64-mingw32-g++.exe -fopenmp -Wall -pedantic -std=c++11 -o compute_distances.exe source/compute_distances.cpp

::@echo ccs/test_lscc.txt distances/test_lscc_distances.txt > temp.txt
::compute_distances.exe < temp.txt

::@echo ccs/wiki_lscc.txt distances/wiki_lscc_distances.txt > temp.txt
::compute_distances.exe < temp.txt

@echo ccs/epin_lscc.txt distances/epin_lscc_distances.txt > temp.txt
compute_distances.exe < temp.txt

@echo off
del temp.txt
::del compute_distances.exe

