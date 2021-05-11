#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while(s[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*re;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) + ft_strlen(s2);
	re = (char *)malloc(sizeof(char) * (i + 1));
	if (re == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			re[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j] != '\0')
	{
		re[i] = s2[j];
		i++;
		j++;
	}
	re[i] = '\0';
	free(s1);
	return (re);
}

char *ft_makeline(char **box)
{
	size_t	i;
	size_t	j;
	char	*line;
	char	*nbox;

	i = 0;
	while (box[0][i] != '\n' && box[0][i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = box[0][j];
		j++;
	}
	line[j] = '\0';
	if (box[0][i] == '\0')
	{
		free(*box);
		*box = NULL;
		return (line);
	}
	j = ft_strlen(box[0]);
	nbox = (char *)malloc(sizeof(char) * (j - i));
	i++;
	j = 0;
	while(box[0][i] != '\0')
	{
		nbox[j] = box[0][i];
		i++;
		j++;
	}
	nbox[j] = '\0';
	free(*box);
	*box = nbox;
	return (line);
}

int ft_find_newline(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int get_next_line(int fd, char **line)
{
	char *pre;
	static char *box;
	int buf;

	pre = (char *)malloc(sizeof(char) * 100);
	if (pre == NULL || fd < 0)
		return (-1);
	if (!ft_find_newline(box))
	{
		while (1)
		{
			buf = read(fd, pre, 99);
			pre[buf] = '\0';
			box = ft_strjoin(box, pre);
			if (buf == 0 || ft_find_newline(box))
				break ;
		}
	}
	free(pre);
	*line = ft_makeline(&box);
	if (line == NULL)
		return (-1);
	if (box == NULL)
		return (0);
	return (1);
}


#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	char *line;

	int i;
	i = 1;
	while (i>0)
	{
		i = get_next_line(fd, &line);
		printf("%d | %s\n",i,line);
		free(line);
	}
	system("leaks a.out");
	return (0);
}

/*
#include <stdio.h>
int main(int argc, char *argv[])
{

	char *box;

	box = (char *)malloc(sizeof(char) * (11));
	box[0] = '1';
	box[1] = '1';
	box[2] = '1';
	box[3] = '1';
	box[4] = '1';
	box[5] = '1';
	box[6] = '\n';
	box[7] = '2';
	box[8] = '2';
	box[9] = '2';
	box[10] = '\0';
	char *line = ft_makeline(&box);
	printf("box = %s\n, line=%s\n", box, line);
	system("leaks a.out");
	
	if (argc != 3)
		return (0);
	char *re;

	char *s1 = NULL;
	char *s2 = "fa";
	re = ft_strjoin(s1, s2);
	printf("re= %s\n", re);
	return (0);
}
*/
