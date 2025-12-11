"""
compiled: main.c helper.c
	cc main.c helper.c -o compiled

clean: *.o
	echo "Clean called\n"
	rm *.o

fclean: compiled
	echo "FClean called\n"
	rm compiled

re: compiled main.c helper.c
	rm compiled
	cc main.c helper.c -o compiled
	echo "Re called\n"
"""

import sys
import subprocess as sp

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

def	main():
	av = sys.argv
	ac = len(av)
	if ac < 4: print("Missing args"); return
	file_names = [s for s in av[3:] if s[0] != '-']
	compiled_name = av[1]
	ftype = "." + av[2]
	req_files = f"{ftype} ".join(file_names) + ftype
	comp_line = "\tcc " + f"{ftype} ".join(file_names) + f"{ftype} -o " + compiled_name
	line1 = compiled_name + ": " + req_files
	line2 = comp_line
	final = line1 + "\n" + line2 + "\n" + "\n".join(clean()) + "\n" + "\n".join(fclean(compiled_name)) + "\n" + "\n".join(re(comp_line))
	print("Makefile written")
	open("Makefile", "w").write(final)
	print(final)
	if "-make" in av: sp.run("make", shell=True)

if __name__ == "__main__":main()
