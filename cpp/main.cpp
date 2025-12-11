#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sys/wait.h>

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
	}
}

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cout << "Missing args\n";
		return (1);
	}
	std::vector<std::string> file_names;
	std::string compiled_name = std::string(av[1]);

	for(int i = 2; i < ac; i++)
		file_names.push_back(std::string(av[i]));

	std::string req_files;
	bool runMake = false;
	for(int i = 0; i < ac - 2; i++)
	{
		if (file_names[i] != "-make")
			req_files += file_names[i] + ".c ";
		else
			runMake = true;
	}
	std::string comp_line = "\tcc " + req_files + "-o " + compiled_name;

	std::string line1 = compiled_name + ": " + req_files;
	std::string line2 = comp_line;
	std::string final_ = line1 + "\n" + line2;
	std::cout << final_ + "\n";
	
	std::fstream Makefile("Makefile", std::ios::out);
	Makefile << final_;
	Makefile.close();
	std::cout << "Makefile written.\n";
	
	std::cout << (runMake ? "Running Make...\n" : "NOT Running Make...\n");
	if (runMake) runMakefile();
	return (0);
}
