#include <stdio.h>

int main()
{
	int i,c,n;
	double sum = 0, prev;
	c = scanf("%d", &n);
	if(c == 1)
	{
		for(i=1; i<=n; i++)
		{
			c = 0;
			c = scanf("%lf", &prev);
			if(c == 1 && i%2 == 0)
			{
				prev = prev*prev*prev;
				sum = sum + prev;
			}
		}
	}
	printf("%lf", sum);

	return 0;
}
