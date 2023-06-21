#include "main.h"

int main( int ac, __attribute__((unused)) char **av) {
        int file_ret = 0;
        cache mm = {NULL, NULL, NULL, NULL};

        if (ac == 2) {
                file_ret = file_arg(&mm, av[1], av[0]);
                if (file_ret)
                        return (EXIT_FAILURE);
                return (EXIT_SUCCESS);
        }
        init_environ();
        repl_loop(&mm, av[0]);
        return (0);
}

