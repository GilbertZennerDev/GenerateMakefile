compiled: main.c
	cc main.c -o compiled
fclean: compiled
	echo "FClean called"
	rm compiled