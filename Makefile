FLAGS= -std=gnu11 -Wall -Werror -pedantic -Wextra -Wconversion -g

make:
	@cppcheck ./
	@gcc $(FLAGS) src/swap_collect.c -o bin/swap_collect.o
	@gcc $(FLAGS) src/swap_analyzer.c -o bin/swap_analyzer.o
clean:
	@rm bin/* /var/log/swap_analysis.log
log:
	@cat /var/log/swap_analysis.log
