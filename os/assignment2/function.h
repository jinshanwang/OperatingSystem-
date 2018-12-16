// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#define	YES	1
#define	NO	0
// default function
char *next_cmd(FILE* fp);
char	**splitline(char *);
void	freelist(char **);
void	*emalloc(size_t);
void	*erealloc(void *, size_t);
int		execute(char **);
void	fatal(char *, char *, int );
