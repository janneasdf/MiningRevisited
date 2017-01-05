::"C:\Program Files\Anaconda3\Scripts\activate.bat"

::call python find_ccs.py graphs/testgraph.txt ccs/test_lscc.txt ccs/test_lwcc.txt
::call python find_ccs.py graphs/Wiki-Vote.txt ccs/wiki_lscc.txt ccs/wiki_lwcc.txt

call g++ -Wall -pedantic -o compute_distances.exe compute_distances.cpp

echo ccs/test_lscc.txt distances/test_lscc_distances.txt
compute_distances.exe 
compute_distances.exe ccs/test_lwcc.txt distances/test_lwcc_distances.txt
