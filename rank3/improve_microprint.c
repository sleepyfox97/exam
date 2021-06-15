#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_mp
{
	int w;
	int h;
	char back;
} t_mp;

typedef struct s_rec
{
	float x;
	float y;
	float w;
	float h;
	char front;
	char type;
} t_rec;

int ft_strlen(char *s)
{
	int i = 0;

	if (s == NULL)
		return (i);
	while(s[i] != '\0')
		i++;
	return (i);
}

int ft_put_error(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

int ft_free_all(FILE *f, char *s)
{
	free(f);
	free(s);
	return (1);
}

int ft_get_zone(FILE *f, t_mp *mp)
{
	if (fscanf(f, "%d %d %c\n", &mp->w, &mp->h, &mp->back) == -1)
		return (0);
	if (0 < mp->w && mp->w <= 300 && 0 < mp->h && mp->h <= 300)
		return (1);
	return (0);
}

void ft_set_back(char *s, t_mp *mp)
{
	int i = 0;
	int j;

	while (i < mp->h)
	{
		j = 0;
		while (j < mp->w)
		{
			s[i * mp->w + j] = mp->back;
			j++;
		}
		i++;
	}
	return ;
}

void ft_print(char *ans, t_mp *mp)
{
	int i = 0;

	while(i < mp->h)
	{
		write(1, &ans[mp->w * i], mp->w);
		write(1, "\n", 1);
		i++;
	}
	return ;
}

void	ft_set_front(ans, &mp)
{
	t_rec rec;

	
}

int main(int argc, char *argv[])
{
	FILE *f;
	t_mp mp;
	char *ans;

	if (argc != 2)
		return (ft_put_error("Error: argument\n"));
	if ( !(f = fopen(argv[1], "r")))
		return (ft_put_error("Error: Operation file corrupted\n"));
	if (ft_get_zone(f, &mp) == 0)
		return (ft_free_all(f, NULL) && ft_put_error("Error: Operation file corrupted\n"));
	if (!(ans = (char *)malloc(sizeof(char) * (mp.w * mp.h))))
		return (ft_free_all(f, NULL) && ft_put_error("Error: operation file corrupted\n"));
	ft_set_back(ans, &mp);
	ft_set_front(ans, &mp);
	ft_print(ans, &mp);
	printf("%d %d %c", mp.w, mp.h, mp.back);
printf("good\n");
	return (0);
}
