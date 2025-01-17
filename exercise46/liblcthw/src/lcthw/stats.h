#ifndef lcthw_Stats_h
#define lcthw_Stats_h


typedef struct Stats {
	double			sum;
	double			sumsq;
	unsigned long	n;
	double			min;
	double			max;
} Stats;

Stats *Stats_recreate(double sum, double sumsq, unsigned long n, double min, double max);

Stats *Stats_create();

double Stats_mean(Stats *st);

double Stats_stddev(Stats *st);

void Stats_sample(Stats *st, double s);

void Stats_dump(Stats *st);

#endif
