#include "main.h"

int count_inp_vects(char *inp) {
        int i, arg_count = 0;

        if (!inp)
                return (0);

        for (i = 0; inp[i]; i++) {
                if ((inp[i] == '\n' && inp[i + 1] == '\0') || inp[i + 1] == '\0') {
                        arg_count++;
                        continue;
                }
                if (inp[i] == '\n')
                        arg_count++;
        }
        return (arg_count);
}

size_t count_line(char *inp, size_t idx) {
        size_t len = 0;

        if (!inp)
                return (0);

        while (inp[idx] && inp[idx] != '\n') {
                len++;
                idx++;
        }
        return (len);
}

char **create_arg_vect(int num_args, char *inp) {
        char **new = NULL;
        size_t i, j = 0, k, sen;

        if (!inp || num_args == 0)
                return (NULL);

        new = malloc((num_args + 1) * sizeof(char *));
        if (!new) {
                perror("create_arg_vect: new");
                return (NULL);
        }

        for (i = 0; inp[i]; i++) {
                if (inp[i] && inp[i] != '\n') {
                        sen = count_line(inp, i);
                        new[j] = malloc((sen + 1) * sizeof(char));
                        if (!new[j]) {
                                perror("create_arg_vect: *new");
                                free_matrix(new);
                        }
                        k = 0;
                        while (inp[i] && inp[i] != '\n')
                                new[j][k++] = inp[i++];
                        new[j++][k] = '\0';
                }
                if (inp[i] == '\0')
                        i--;
        }
        new[j] = NULL;
        return (new);
}

void eval_file(__attribute__((unused)) cache *mm, __attribute__((unused)) char **vect, __attribute__((unused)) char *prog) {
        size_t i;

        if (!(mm->file_vect))
			return;

		for (i = 0; mm->file_vect[i]; i++) {
                mm->calls = call_no(prog, (i + 1));
                parser(mm, mm->file_vect[i]);
                free(mm->calls);
        }
        free_alias_list(mm->als);
}

int file_arg(cache *mm, char *file_name, char *prog) {
        ssize_t g;
        int fd, arg_count = 0;
        char *f_inp = NULL;

        if (!file_name)
                return (1);

        fd = open(file_name, O_RDONLY);
        if (fd == -1) {
            _puts(prog, 2);
            _puts(": 0: Can't open ", 2);
            _puts(file_name, 2);
            _puts("\n", 2);
            return (1);
        }
        g = _getline(&f_inp, fd);
        if (g == -1) {
        	close(fd);
        	return (1);
        }
        arg_count = count_inp_vects(f_inp);
        mm->file_vect = create_arg_vect(arg_count, f_inp);
        free(f_inp);
        init_environ();
        eval_file(mm, mm->file_vect, prog);
        free_matrix(environ);
        free_matrix(mm->file_vect);
        return (0);
}

