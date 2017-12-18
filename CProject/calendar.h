int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[] =
{
	" ",
	"\nJanvier",
	"\nFévrier",
	"\nMars",
	"\nAvril",
	"\nMai",
	"\nJuin",
	"\nJuillet",
	"\nAoût",
	"\nSeptembre",
	"\nOctobre",
	"\nNovembre",
	"\nDécembre"
};

int determineday(int year)
{
	int daycode;
	int d1,d2,d3;

	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.) / 100.;
	d3 = (year - 1.)/ 400.;
