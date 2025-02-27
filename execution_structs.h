
#include "common_structs.h"

typedef struct s_operator
{
	/*
	# Cases:
	- (<)
		* fd of file opened in RDONLY mode
		* Added to prev operator
		* Does not use pipe
	- (>)
		* fd of file opened in WRONLY and trucated
		* Added to next operator
		* Does not use pipe
	- (<<) 
		* fd of dupped command stdin
		* Added to next operator
		* 
	- (>>)
		* fd of file opended in APPEND mode
		* Added to prev operator
		* Does not use pipe
	- (|)
		* fd of next stdin program dupped fd
		* Added to both operators
		* uses pipe
	*/
	int fd;
	int pipe[2];
	operator_type type;
}		t_operator;

typedef struct s_cmd
{
	char	*path;
	char	**argv;

	/*
	# Used with:
		1) <
		2) <<
	### Nullable
	*/
	t_operator *prev_operator;

	/*
	# Used with:
		1) >
		2) >>
		3) |
	### Nullable
	*/
	t_operator *next_operator;
} t_cmd;

typedef struct s_exe
{
	t_cmd *commands;
	size_t command_count;
}		t_exe;
