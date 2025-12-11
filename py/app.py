"""
compiled: main.c helper.c
	cc main.c helper.c -o compiled
"""

import sys
import subprocess as sp

def	main():
	av = sys.argv
	ac = len(av)
	if ac < 3: print("Missing args"); return
	file_names = [s for s in av[2:] if s[0] != '-']
	compiled_name = av[1]
	req_files = ".c ".join(file_names) + ".c"
	comp_line = "\tcc " + ".c ".join(file_names) + ".c -o " + compiled_name
	line1 = compiled_name + ": " + req_files
	line2 = comp_line
	final = line1 + "\n" + line2
	print("Makefile written")
	open("Makefile", "w").write(final)
	print(final)
	if "-make" in av: sp.run("make", shell=True)

if __name__ == "__main__":main()
