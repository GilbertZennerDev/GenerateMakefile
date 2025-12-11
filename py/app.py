"""
compiled: main.c helper.c
	cc main.c helper.c -o compiled
"""

import sys

def	main():
	av = sys.argv
	ac = len(av)
	if ac < 3: print("Missing args"); return
	compiled_name = av[1]
	req_files = ".c ".join(av[2:]) + ".c"
	comp_line = "\tcc " + ".c ".join(av[2:]) + ".c -o " + compiled_name
	line1 = compiled_name + ": " + req_files
	line2 = comp_line
	final = line1 + "\n" + line2
	print("Makefile written")
	open("Makefile", "w").write(final)
	print(final)

if __name__ == "__main__":main()
