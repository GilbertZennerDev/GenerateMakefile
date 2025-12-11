#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sys/wait.h>

/*
def clean():
	return [
	"clean: *.o",
	"\techo \"Clean called\"",
	"\trm *.o"
	]
	
def fclean(compiled_name):
	return [
	"fclean: compiled",
	"\techo \"FClean called\"",
	f"\trm {compiled_name}"
	]

def re(comp_line):
	return [
	"re: fclean",
	"\techo \"Re called\"",
	f"{comp_line}"
	]

*/

std::string clean()
{
	return std::string("clean: *.o\n\techo \"Clean called\"\n\trm *.o\n");
}

std::string fclean(std::string compiled_name)
{
	return std::string("fclean: compiled\n\techo \"FClean called\"\n\trm " + compiled_name + "\n");
}

std::string re(std::string comp_line)
{
	return std::string("re: fclean\n\techo \"Re called\"\n" + comp_line + "\n");
}

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
	std::string ftype = std::string(av[2]);
	std::string compiler = std::string(av[3]);

	for(int i = 4; i < ac; i++)
		file_names.push_back(std::string(av[i]));

	std::string req_files;
	bool runMake = false;
	for(int i = 0; i < ac - 4; i++)
	{
		if (file_names[i] != "-make")
			req_files += file_names[i] + ".c ";
		else
			runMake = true;
	}
	std::string comp_line = "\t" + compiler + " " + req_files + "-o " + compiled_name + '\n';

	std::string line1 = compiled_name + ": " + req_files + "\n";
	std::string line2 = comp_line;
	std::string final_ = line1 + line2;
	
	final_ += clean() + fclean(compiled_name) + re(comp_line);
	
	std::cout << final_ + "\n";
	
	std::fstream Makefile("Makefile", std::ios::out);
	Makefile << final_;
	Makefile.close();
	std::cout << "Makefile written.\n";
	
	std::cout << (runMake ? "Running Make...\n" : "NOT Running Make...\n");
	if (runMake) runMakefile();
	return (0);
}
