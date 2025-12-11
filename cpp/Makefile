compiled: main.c helper.c 
	cc main.c helper.c -o compiled
clean: *.o
	echo "Clean called"
	rm *.o
fclean: compiled
	echo "FClean called"
	rm compiled
re: fclean
	echo "Re called"
	cc main.c helper.c -o compiled

