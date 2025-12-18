#include "header.hpp"

void	runMakefile()
{
	pid_t	pid;
	char	**cmds;

	cmds = (char **)malloc(sizeof(char *) * 2);
	cmds[0] = strdup("make");
	cmds[1] = NULL;
	pid = fork();
	if (pid == 0)
		execvp(cmds[0], cmds);
	else
	{
		wait(NULL);
		free(cmds[0]);
		free(cmds[1]);
		free(cmds);
		cout << "make run...\n";
	}
}

string getCompName(char **av)
{
	string ftype = string(av[2]);
	if (ftype == "cpp") return string("c++");
	return string("cc");
}

void	genLine1(t_data *d)
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
	
	genLine1(&d);
	genMakefile(d.final_);
	return (0);
}
