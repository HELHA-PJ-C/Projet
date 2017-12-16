

#include<stdio.h>

#define TRUE    1
#define FALSE   0

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[]=
{
	" ",
	"\n\n\nJanvier",
	"\n\n\nFévrier",
	"\n\n\nMars",
	"\n\n\nAvril",
	"\n\n\nMai",
	"\n\n\nJuin",
	"\n\n\nJuillet",
	"\n\n\nAoût",
	"\n\n\nSeptembre",
	"\n\n\nOctobre",
	"\n\n\nNovembre",
	"\n\n\nDecembre"
};


int inputyear(void)
{
	int year;
	
	printf("Please enter a year (example: 1999) : ");
	scanf("%d", &year);
	return year;
}

int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}


int determineleapyear(int year)
{
	if(year% 4 == FALSE && year%100 != FALSE || year%400 == FALSE)
	{
		days_in_month[2] = 29;
		return TRUE;
	}
	else
	{
		days_in_month[2] = 28;
		return FALSE;
	}
}

void calendar(int year, int daycode,int mois)
{
	int month, day;
	
	for ( month = 1; month <= 12; month++ )
	{
		//printf("%s", months[month]);
		if(month == mois)
		{
		printf("%s %d",months[mois],year);
		printf("\n\nDim  Lun  Mar  Mer  Jeu  Ven  Sam\n" );
		
		// Correct the position for the first date
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}
		
		// Print all the dates for one month
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
			printf("%2d", day );
			
			// Is day before Sat? Else start next line Sun.
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
		}
			// Set position for next month
			daycode = ( daycode + days_in_month[month] ) % 7;
	}
}

int main(void)
{
	int year, daycode, leapyear;
	
	year = inputyear();
	daycode = determinedaycode(year);
	determineleapyear(year);
	int num;
	printf("Encodez le numéro du mois : ");
	scanf("%d",&num);
	calendar(year, daycode,num);
	printf("\n");
}

