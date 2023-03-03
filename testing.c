#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char **tab_completion_generator(const char *text, int start, int end)
{
    // TODO: Implement tab completion logic here
    return NULL;
}

int main()
{
    // Set tab completion function
    rl_attempted_completion_function = &tab_completion_generator;

	while (1)
	{
		// Read input line
		char *line = readline("> ");

		// Add input line to history
		if (line != NULL && *line != '\0') {
			add_history(line);
		}
		 free(line);
	}
    // Free input line
   

    return 0;
}
