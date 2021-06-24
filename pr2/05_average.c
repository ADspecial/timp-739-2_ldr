#include <stdio.h>

int main()
{
	double sum = 0, prev = 0;
	int n,c,i;
	c = scanf("%d", &n);
	if(c == 1)
	{
		for(i=1; i<=n; i++)
		{
			c = 0;
			c = scanf("%lf", &prev);
			if(c == 1)
			{
				sum = sum + prev;
		    }			
		}
	} 
	printf("%lf", sum/n);
	return 0;
}
