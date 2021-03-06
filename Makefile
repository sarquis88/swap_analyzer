FLAGS= -std=gnu11 -Wall -Werror -pedantic -Wextra -Wconversion -g

make:
	@cppcheck ./
	@gcc $(FLAGS) src/swap_collector.c src/swap_utilities.c -o bin/swap_collector.o
	@gcc $(FLAGS) src/swap_analyzer.c src/swap_utilities.c -o bin/swap_analyzer.o
clean:
	@rm bin/* /var/log/swap_analyzer.log
