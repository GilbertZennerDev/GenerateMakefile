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
	arr = [
	"fclean: compiled",
	"\techo \"FClean called\"",
	f"\trm {compiled_name}"
	]
	result = "\n".join(arr)
	return result

def getCompName(av):
	ftype = av[2]
	if ftype == "cpp": return "c++"
	return "cc"

def getFType(av):
	return "." + av[2]

def getFinal(av):
	comp_name = getCompName(av)
	file_names = [s for s in av[3:] if s[0] != '-']
	compiled_name = av[1]
	ftype = getFType(av)
	req_files = f"{ftype} ".join(file_names) + ftype
	comp_line = f"\t{comp_name} " + f"{ftype} ".join(file_names) + f"{ftype} -o " + compiled_name

	line1 = compiled_name + ": " + req_files + "\n"
	line2 = comp_line + "\n"

	final = line1 + line2 + fclean(compiled_name)
	return final

def	main():
	av = sys.argv
	ac = len(av)
	if ac < 4: print("Missing args: compiled_name language main"); return
	final = getFinal(av)
	open("Makefile", "w").write(final)
	print("Makefile written")
	print(final)
	if "-make" in av: sp.run("make", shell=True)

if __name__ == "__main__":main()
