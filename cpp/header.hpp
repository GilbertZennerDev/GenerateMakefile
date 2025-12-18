#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

typedef struct s_data
{
	string		ftype;
	string		final_;
	bool		runMake;	
	string		comp_name;
	string		req_files;
	string		comp_line;
	vector<string>	file_names;
	string		compiled_name;
}	t_data;
