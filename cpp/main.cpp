#include "header.hpp"

void	runMakefile()
{
	pid_t		pid;
	vector<char *>	cmds;
	char		**cmds_c;

	cmds.push_back((char *) string("make").c_str());
	cmds.push_back(NULL);
	cmds_c = &cmds[0];
	pid = fork();
	if (pid == 0)
		execvp(cmds_c[0], cmds_c);
	else
	{
		wait(NULL);
		cout << "make run...\n";
	}
}

string getCompName(char **av)
{
	string ftype = string(av[2]);
	if (ftype == "cpp") return string("c++");
	return string("cc");
}

void	genLines(t_data *d)
{
	d->comp_line = "\t" + d->comp_name + " " + d->req_files + "-o " + d->compiled_name;
	d->final_ = d->compiled_name + ": " + d->req_files + "\n" + d->comp_line;
}

void	genMakefile(string final_)
{
	cout << final_ + "\n";
	fstream Makefile("Makefile", ios::out);
	Makefile << final_;
	Makefile.close();
	cout << "Makefile written.\n";

	runMakefile();
}	

int main(int ac, char **av)
{
	t_data		d;

	if (ac < 4)
	{
		cout << "Missing args\n";
		return (1);
	}

	d.ftype = string(av[2]);
	d.comp_name = getCompName(av);
	d.compiled_name = string(av[1]);	

	for(int i = 3; i < ac; i++)
		d.file_names.push_back(string(av[i]));

	for(int i = 0; i < d.file_names.size(); i++)
		d.req_files += d.file_names[i] + "." + d.ftype + " ";
	
	genLines(&d);
	genMakefile(d.final_);
	return (0);
}
