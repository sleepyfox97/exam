#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct s_mp
{
	int w;
	int h;
	char back;
} t_mp;

typedef struct s_rec
{
	float r_w;
	float r_h;
	float r_x;
	float r_y;
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

int ft_all_free(FILE *f, char *s)
{
	fclose(f);
	free(s);
	return (1);
}

int  ft_error(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

int ft_check_zone(FILE *f, t_mp *mp)
{
	int i;

	i = fscanf(f, "%d %d %c\n", &mp->w, &mp->h, &mp->back);
	if (i != 3)
		return (1);
	if (mp->w <= 0 || 300 < mp->w || mp->h <= 0 || 300 < mp->h)
		return (1);
	return (0);
}

void ft_put(char *s, t_mp *mp)
{
	int i = 0;

	while (i < mp->h)
	{
		write(1, &s[i * mp->w], mp->w);
		write(1, "\n", 1 );
		i++;
	}
	return ;
}

int place_point(float x, float y, t_rec *rec)
{
	if ((x < rec->r_x || (rec->r_x + rec->r_w) < x) || (y < rec->r_y || (rec->r_y + rec->r_h) < y))
		return (0);
	if (((x - rec->r_x < 1.00000000) || ((rec->r_x + rec->r_w) - x < 1.00000000)) || ((y - rec->r_y < 1.00000000) || ((rec->r_y + rec->r_h) - y < 1.0000000)))
			return (2);
	return (1);
}

void ft_make_rec_sub(t_mp *mp,char *map, t_rec *rec)
{
	int i = 0;
	int j;
	int tmp;

	while (i < mp->w)
	{
		j = 0;
		while(j < mp->h)
		{
			tmp = place_point(j, i, rec);
			if ((rec->type == 'r' && tmp == 2) || (rec->type == 'R' && tmp))
				map[(i * mp->w + j)] = rec->front;
			j++;
		}
		i++;
	}
	printf("%c %f %f %f %f %c\n", rec->type, rec->r_x, rec->r_y, rec->r_w, rec->r_h, rec->front);
	return ;
}

int ft_make_rec(FILE *f, t_mp *mp, char *map)
{
	int i;
	t_rec rec;

	while ((i = fscanf(f, "%c %f %f %f %f %c\n", &rec.type, &rec.r_x, &rec.r_y, &rec.r_w, &rec.r_h, &rec.front) == 6))
	{
		if (rec.r_w < 0.0000000 || rec.r_h < 0.00000000 || (rec.type != 'R' && rec.type != 'r'))
			return (1);
		ft_make_rec_sub(mp, map, &rec);
	}
	if (i == -1)
		return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	FILE *f;
	t_mp mp;
	char *map;

	if (argc != 2)
		return (ft_error(1, "Error: argument\n"));
	if (!(f = fopen(argv[1], "r")))
		return (ft_error(1, "Error: Operation file corrupted\n"));
	if (ft_check_zone(f, &mp))
		return (ft_all_free(f, NULL) && ft_error(1, "Error: Operation file corrupted\n"));
	map = (char *)malloc(sizeof(char) * (mp.h * mp.w));
	if (map == NULL)
		return (ft_all_free(f, map) && ft_error(1, "Error: Operation file corrupted\n"));
	memset((void*)map, mp.back, (mp.h * mp.w));
	if (ft_make_rec(f, &mp, map))
		return (ft_all_free(f, map) && ft_error(1, "Error: Operation file corrupted\n"));
	ft_put(map, &mp);
	free(map);
	return (0);
}
