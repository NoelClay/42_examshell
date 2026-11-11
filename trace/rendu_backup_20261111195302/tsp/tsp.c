#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct s_city
{
	float x;
	float y;
}	t_city;

float	ffabs(float data)
{
	if (data < 0)
		return ((float)(-data));
	return ((float)data);
}

/*
** You must implement this function
** It should return the Euclidean distance between 2 cities
*/
float	distance(t_city a, t_city b)
{
	float	dx = ffabs(a.x - b.x);
	float	dy = ffabs(a.y - b.y);

	return(sqrtf((dx * dx) + (dy * dy)));
}

/*
** You must implement this function
** It should compute total distance of the path
** including the return to the starting city
*/
float	total_distance(t_city *cities, int *path, int n)
{
	float	res = 0.0f;
	int	i;

	for (i = 0; i < n - 1; i++)
	{
		res += distance(cities[path[i]], cities[path[i + 1]]);
	}
	res += distance(cities[path[i]], cities[path[0]]);
	return (res);
}

/*
** You must implement this function
** Use backtracking to try all permutations
*/
void	solve(t_city *cities, int *path, int n, int pos, float *min)
{
	float	res;

	if (pos == n)
	{
		res = total_distance(cities, path, n);
		if (*min > res)
			*min = res;
		return ;
	}
	for (int i = pos; i < n; i++)
	{
		int	tmp = path[pos];
		path[pos] = path[i];
		path[i] = tmp;
		solve(cities, path, n, pos + 1, min);
		tmp = path[pos];
		path[pos] = path[i];
		path[i] = tmp;
	}
}

int	main(void)
{
	t_city	cities[11];
	int		n = 0;

	// Read input from stdin
	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;

	// If less than 2 cities → distance = 0
	if (n < 2)
	{
		printf("0.00\n");
		return (0);
	}

	// Initialize path: [0,1,2,...]
	int path[11];
	for (int i = 0; i < n; i++)
		path[i] = i;

	float min = FLT_MAX;

	/*
	** Optimization:
	** Fix first city → start from pos = 1
	*/
	solve(cities, path, n, 1, &min);

	printf("%.2f\n", min);
	return (0);
}