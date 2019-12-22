#ifndef STREDIT_H_
#define STREDIT_H_

struct Data;
void add (char *in_aktivitas, int in_tanggal, char *in_bulan, int in_tahun, int in_jam, int in_menit);
int convert_mon (char *month);
int countMon(int month, int year);
void display (int loc_year, int loc_mon, int loc_date, int loc_hour, int loc_min);
void display_mon (char *month);
void ring (int freq, int dur, int loc_year, int loc_mon, int loc_date, int loc_hour, int loc_min);
void timeFetch (int *loc_year, int *loc_mon, int *loc_date, int *loc_hour, int *loc_min);
void timeRem (int *trem_year, int *trem_mon, int *trem_date, int *trem_hour, int *trem_min);
int totalTime (struct Data *data);

#endif
