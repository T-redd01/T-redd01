#include "main.h"

int main( int ac, char **av) {
        int file_ret = 0;
        cache mm = {NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL};
		
		mm.name = av[0];
		if (ac == 2) {
                file_ret = file_arg(&mm, av[1], av[0]);
                if (file_ret)
                        return (EXIT_FAILURE);
                return (EXIT_SUCCESS);
        }
        init_environ();
        repl_loop(&mm);
        return (0);
}

