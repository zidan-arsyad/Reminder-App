#include "stredit.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <math.h>

int loc_year, loc_mon, loc_date, loc_hour, loc_min;
int trem_year, trem_mon, trem_date, trem_hour, trem_min;

struct Data {
	struct Data *prev;
	char aktivitas [32];
	int tanggal; char bulan[10]; int bulan_val; int tahun;
	int jam; int menit;
	int total_trem;
	struct Data *next;
}*top=NULL, *bottom=NULL, *current1=NULL, *current2=NULL;

void add (char *in_aktivitas, int in_tanggal, char *in_bulan, int in_tahun, int in_jam, int in_menit){
	struct Data *add;
	add = (struct Data*)malloc(sizeof(struct Data));
	
	strcpy (add->aktivitas, in_aktivitas);
	add->tanggal = in_tanggal;
	strcpy (add->bulan, in_bulan);
	add->bulan_val = convert_mon(in_bulan);
	display_mon(add->bulan);
	add->tahun = in_tahun;
	add->jam = in_jam;
	add->menit = in_menit;
	add->total_trem = totalTime(add);
	
	if (add->bulan_val == 0){
		return;
	}
	else{
		if (top == NULL){
			add->next = NULL;
			add->prev = NULL;
			bottom = add;
			bottom->prev = top;
		}
		else {
			top->prev = add;
			add->next = top;
			add->prev = NULL;
		}
		top = add;
	}
}

int convert_mon (char *month){
	int i;
	
	for (i=0; i<strlen(month); i++){
		month[i] = tolower(month[i]);
	}
	
	if (strcmp(month, "januari") == 0){
		return 1;
	}
	else if (strcmp(month, "februari") == 0){
		return 2;
	}
	else if (strcmp(month, "maret") == 0){
		return 3;
	}
	else if (strcmp(month, "april") == 0){
		return 4;
	}
	else if (strcmp(month, "mei") == 0){
		return 5;
	}
	else if (strcmp(month, "juni") == 0){
		return 6;
	}
	else if (strcmp(month, "juli") == 0){
		return 7;
	}
	else if (strcmp(month, "agustus") == 0){
		return 8;
	}
	else if (strcmp(month, "september") == 0){
		return 9;
	}
	else if (strcmp(month, "oktober") == 0){
		return 10;
	}
	else if (strcmp(month, "november") == 0){
		return 11;
	}
	else if (strcmp(month, "desember") == 0){
		return 12;
	}
	else {
		printf ("\n\nGalat: Kesalahan penulisan nama bulan.\n");
		return 0;
	}
}

int countMon(int month, int year){
	if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
		return 31;
	}
	else if(month==4 || month==6 || month==9 || month==11){
		return 30;
	}
	
	if(month==2){
		if(year%4==0){
			return 29;
		}		
		else {
			return 28;
		}		
	}
}

void display (int loc_year, int loc_mon, int loc_date, int loc_hour, int loc_min){
	struct Data *display = bottom;
	
	printf ("Aktivitas\t\tTanggal\t\t\t\tJam\t\tTime Remaining\n\n");
	
	if (display == NULL){
		printf ("\t\t\t\t\t- Empty -\n");
	}
	
	while (display != NULL){
		trem_year = display->tahun;
		trem_mon = display->bulan_val;
		trem_date = display->tanggal;
		trem_hour = display->jam;
		trem_min = display->menit;
		timeRem (&trem_year, &trem_mon, &trem_date, &trem_hour, &trem_min);
		
		printf ("%s\t\t\t%2d-%.3s-%4d\t\t\t%02d:%02d\t\t", display->aktivitas, display->tanggal, display->bulan, display->tahun, display->jam, display->menit);
		
		if (trem_year > 0){
			printf ("%d year(s), %d month(s) remaining.\n", trem_year, trem_mon);
		}
		else if (trem_year == 0){
			if (trem_mon > 0){
				printf ("%d month(s), %d day(s) remaining.\n", trem_mon, trem_date);
			}
			else if (trem_mon == 0){
				if (trem_date > 0){
					printf ("%d day(s), %d hour(s) remaining.\n", trem_date, trem_hour);
				}
				else if (trem_date == 0){
					if (trem_hour > 0){
						printf ("%d hour(s), %d minute(s) remaining.\n", trem_hour, trem_min);
					}
					else if (trem_hour == 0){
						if (trem_min > 0){
							printf ("%d minute(s) remaining.\n", trem_min);
						}
						else if (trem_min == 0){
							printf ("Ringing...\n");
						}
					}
				}
			}
		}
		else {
			printf ("Passed.\n");
		}
		
		display = display->prev;
	}
}

void display_mon (char *month){
	int i = 0;
    
    for (i=0; i<strlen(month); i++){
        if (i==0){
            month[i] = toupper(month[i]);
        }
        else{
		    month[i] = tolower(month[i]);
        }
	}
}

void ring (int freq, int dur, int loc_year, int loc_mon, int loc_date, int loc_hour, int loc_min){
	struct Data *data = top;
	
	while (data != NULL){
		trem_year = data->tahun;
		trem_mon = data->bulan_val;
		trem_date = data->tanggal;
		trem_hour = data->jam;
		trem_min = data->menit;
		timeRem (&trem_year, &trem_mon, &trem_date, &trem_hour, &trem_min);
		
		if (trem_year == 0 && trem_mon == 0 && trem_date == 0 && trem_hour == 0 && trem_min == 0){
				Beep (freq, dur);
		}
		data = data->next;
	}
}

void timeFetch (int *loc_year, int *loc_mon, int *loc_date, int *loc_hour, int *loc_min){
	time_t clock = time(NULL);
	struct tm tm = *localtime(&clock);
	*loc_year = tm.tm_year+1900; *loc_mon = tm.tm_mon+1; *loc_date = tm.tm_mday; *loc_hour = tm.tm_hour; *loc_min = tm.tm_min;
}

void timeRem (int *trem_year, int *trem_mon, int *trem_date, int *trem_hour, int *trem_min){
	timeFetch (&loc_year, &loc_mon, &loc_date, &loc_hour, &loc_min);
	
	int remain;
	remain = countMon(*trem_mon,*trem_year);
	
	*trem_year=*trem_year-loc_year;
	if (*trem_mon<=loc_mon){
		(*trem_year)--;
		*trem_mon+=12;
	}
	*trem_mon=*trem_mon-loc_mon;
	if (*trem_date<=loc_date){
		(*trem_mon)--;
		*trem_date+=remain;
	}
	*trem_date=*trem_date-loc_date;
	if (*trem_hour<=loc_hour){
		(*trem_date)--;
		*trem_hour+=24;
	}
	*trem_hour=*trem_hour-loc_hour;
	if (*trem_min<=loc_min){
		(*trem_hour)--;
		*trem_min+=60;
	}
	*trem_min=*trem_min-loc_min;
	
	if (*trem_min>=60){
		*trem_min-=60;
		(*trem_hour)++;
	}
	if (*trem_hour>=24){
		*trem_hour-=24;
		(*trem_date)++;
	}
	if (*trem_date>=remain){
		*trem_date-=remain;
		(*trem_mon)++;
	}
	if (*trem_mon>=12){
		*trem_mon-=12;
		(*trem_year)++;
	}
}

int totalTime (struct Data *data){
	trem_year = data->tahun;
	trem_mon = data->bulan_val;
	trem_date = data->tanggal;
	trem_hour = data->jam;
	trem_min = data->menit;
	timeRem (&trem_year, &trem_mon, &trem_date, &trem_hour, &trem_min);
	
	trem_mon+=(12*trem_year);
	
	while  (trem_mon != 0){
		trem_date += countMon((trem_mon%12+1), 1);
		trem_mon--;
	}
	trem_hour += trem_date*24;
	trem_min += 60*trem_hour;
	
	return trem_min;
}
