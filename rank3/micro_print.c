#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


typedef struct mp_s
{
	int w;
	int h;
	char back;
	float f_x;
	float f_y;
	float f_w;
	float f_h;
	char front;
	char R_r;
} mp_t;

void ft_large(mp_t mp, char **ans);
void ft_small(mp_t mp, char **ans);

size_t ft_strlen(char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

void ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
	return ;
}

int ft_skip_space(FILE *f)
{
	char c;

	while(1)
	{
		if (fscanf(f, "%c", &c) <= 0)
			return 0;
		if (c == '\n')
			return 1;
		else if (c == ' ')
			continue ;
		else
			return 0;
	}
}

void ft_write_ans(char **ans)
{
	int i = 0;

	while (ans[i] != NULL)
		ft_putstr_fd(1, ans[i++]);
	return ;
}

int ft_micro_print(char *filename)
{
	FILE *f;
	mp_t mp;
	char **ans;
	int	i = 0;

	if (!(f = fopen(filename, "r")))
	{
		ft_putstr_fd(1, "Error: Operation file corrupted\n");
		return (1);
	}
	if (fscanf(f, "%d %d %c ", &(mp.w), &(mp.h), &(mp.back)) < 0)
	{
		ft_putstr_fd(1, "Error: Operation file corrupted\n");
		return (1);
	}
	ans = (char **)malloc(sizeof(char *) * (mp.h + 1));
	if (ans == NULL)
		return (1);
	while (i < mp.h)
	{
		ans[i] = (char *)malloc(sizeof(char) * (mp.w + 2));
		if (ans[i] == NULL)
			return (1); //ホントはfreeいる
		memset((void *)ans[i], mp.back, mp.w);
		ans[i][mp.w] = '\n';
		ans[i][mp.w + 1] = 0;
		i++;
	}
	ans[i] = NULL;
	// if (!ft_skip_space(f))
	// {
	// 	ft_putstr_fd(1, "Error: Operation file corrupted\n");
	// 	return (1);
	// }
	if (fscanf(f, "%c %f %f %f %f %c", &(mp.R_r), &(mp.f_x), &(mp.f_y), &(mp.f_w), &(mp.f_h), &(mp.front)) < 0)
	{
		ft_putstr_fd(1, "Error: Operation file corrupted\n");
		return (1);
	}
	if (mp.R_r == 'R')
		ft_large(mp, ans);
	else if (mp.R_r == 'r')
		ft_small(mp, ans);
	else
	{
		ft_putstr_fd(1, "Error: Operation file corrupted\n");
		return (1);
	}
	ft_write_ans(ans);
	return (0);
}

void ft_large(mp_t mp, char **ans)
{
	int x;
	int y;

	x = (int)mp.f_x;
	y = (int)mp.f_y;
	printf("x=%d y=%d", x, y);
	return ;
}

void ft_small(mp_t mp, char **ans)
{
	return ;
}

int main(int argc, char *argv[])
{
	int i = 1;

	if (argc != 2)
		ft_putstr_fd(1, "Error: argument\n");
	else
		i = ft_micro_print(argv[1]);
	return (i);
}
