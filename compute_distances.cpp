#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <string>

using namespace std;

int main() 
{
	cout << "Reading input file names" << endl;
	string input_file, output_file;
	cin >> input_file >> output_file;

	// Read file describing the edges of the connected component graph
	cout << "Reading input file" << endl;
	ifstream cc_input;
	cc_input.open(input_file.c_str());
	if (cc_input.is_open()) 
	{
		cout << cc_input;
		cc_input.close();
	}
	else
	{
		cout << "Unable to open file: " << input_file;
	}

	ofstream output;
	output.open(output_file.c_str());
	output.close();


	return 0;
}