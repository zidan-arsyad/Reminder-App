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
	
struct Data {
	struct Data *prev;
	char aktivitas [32];
	int tanggal; char bulan[10]; int bulan_val; int tahun;
	int jam; int menit;
	struct Data *next;
}*top=NULL, *bottom=NULL, *current = NULL;

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

//void display_mon (char *month){ //Draft biar display di list aktivitas->bulan rapi (error).
//	int i;
//	
//	for (i=0; i<strlen(month); i++){
//		*month = tolower(month[i]);
//	}
//	*month = (month[0]-32);
//}

void add (char *in_aktivitas, int in_tanggal, char *in_bulan, int in_tahun, int in_jam, int in_menit){
//	char conv_mon;
	struct Data *add;
	add = (struct Data*)malloc(sizeof(struct Data));
//	display_mon(in_bulan);
	
	strcpy (add->aktivitas, in_aktivitas);
	add->tanggal = in_tanggal;
	strcpy (add->bulan, in_bulan);
	add->bulan_val = convert_mon(in_bulan);
	add->tahun = in_tahun;
	add->jam = in_jam;
	add->menit = in_menit;
	
	if (add->bulan_val == 0){
		return;
	}
	else{
		if (top == NULL){
			add->next = NULL;
			add->prev = NULL;
			bottom = add;
		}
		else {
			top->prev = add;
			add->next = top;
			add->prev = NULL;
		}
		top = add;
	}
}

void ring (int freq, int dur, int loc_year, int loc_mon, int loc_date, int loc_hour, int loc_min){
	struct Data *data = top;
	int trem_year, trem_mon, trem_date, trem_hour, trem_min;
	
	trem_year = abs(data->tahun - loc_year);
	trem_mon = abs(data->bulan_val - loc_mon);
	trem_date = abs(data->tanggal - loc_date);
	trem_hour = abs(data->jam - loc_hour);
	trem_min = abs(data->menit - loc_min);
	
	if (trem_year == 0 && trem_mon == 0 && trem_date == 0 && trem_hour == 0 && trem_min == 0){
			Beep (freq, dur);
	}
	else {
		return;
	}
}

void display (int loc_year, int loc_mon, int loc_date, int loc_hour, int loc_min){
	struct Data *display = top;
	int trem_year, trem_mon, trem_date, trem_hour, trem_min;
		
	printf ("Aktivitas\t\tTanggal\t\t\t\tJam\t\tTime Remaining\n\n");
	
	if (display == NULL){
		printf ("\t\t\t\t\t- Empty -\n");
	}
	
	while (display != NULL){
		
//		if (display->tahun > loc_date){ //Draft buat pengurangan remaining yg ribet (masih belum lengkap).
//			if (display->bulan_val > loc_mon){
//				if (display->tanggal > loc_date){
//					trem_year = display->tahun - loc_year;
//					trem_mon = display->bulan_val - loc_mon;
//					trem_date = display->tanggal - loc_date;
//				}
//			}
//		}
//		if (display->jam < loc_hour && display->tanggal){
//			trem_hour = (display->jam - loc_hour) - 1;
//			trem_min = 60 - loc_min;
//		}
//		else {
//			trem_hour = display->jam - loc_hour;
//			trem_min = display->menit - loc_min;
//		}
		
		trem_year = abs(display->tahun - loc_year);
		trem_mon = abs(display->bulan_val - loc_mon);
		trem_date = abs(display->tanggal - loc_date);
		trem_hour = abs(display->jam - loc_hour);
		trem_min = abs(display->menit - loc_min);
		
		printf ("%s\t\t\t%d-%s-%d\t\t\t%d:%d\t\t", display->aktivitas, display->tanggal, display->bulan, display->tahun, display->jam, display->menit);
		
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
						else {
							printf ("%d minute(s) ago.", trem_min);
						}
					}
					else {
						printf ("%d hour(s), %d minute(s) ago.\n", trem_hour, trem_min);
					}
				}
				else {
					printf ("%d day(s), %d hour(s) ago.\n", trem_date, trem_hour);
				}
			}
			else {
				printf ("%d month(s), %d day(s) ago.\n", trem_mon, trem_date);
			}
		}
		else {
			printf ("%d year(s), %d month(s) ago.\n", trem_year, trem_mon);
		}
		
		display = display->next;
	}
}

int main (){
	int trem_year, trem_mon, trem_date, trem_hour, trem_min;
	int loc_year, loc_mon, loc_date, loc_hour, loc_min;
	system ("color b0");
	
	char in_aktivitas[32] = "", in_bulan[10] = "";
	int in_tanggal = NULL, in_tahun = NULL, in_jam = NULL, in_menit = NULL;
	int i = 0;
	
	for (i=0; i<3; i++){
		time_t clock = time(NULL);
		struct tm tm = *localtime(&clock);
		loc_year = tm.tm_year+1900; loc_mon = tm.tm_mon+1; loc_date = tm.tm_mday; loc_hour = tm.tm_hour; loc_min = tm.tm_min;
		
		display(loc_year, loc_mon, loc_date, loc_hour, loc_min);
		printf ("\n\n\n\t\tTAMBAHKAN PENGINGAT\n\n");
		printf ("Aktivitas\t: ", in_aktivitas);	gets (in_aktivitas);
		printf ("Tanggal\t\t: ", in_tanggal);	scanf ("%d", &in_tanggal);	getchar();
		printf ("Bulan\t\t: ", in_bulan);		gets (in_bulan);
		printf ("Tahun\t\t: ", in_tahun);		scanf ("%d", &in_tahun);	getchar();
		printf ("Jam\t\t: ", in_jam);			scanf ("%d", &in_jam);		getchar();	
		printf ("Menit\t\t: ", in_menit);		scanf ("%d", &in_menit);	getchar();
		
		add (in_aktivitas, in_tanggal, in_bulan, in_tahun, in_jam, in_menit);
		fflush(stdin);
		system("cls");
	}
	
	while (kbhit() == 0){
		time_t clock = time(NULL);
		struct tm tm = *localtime(&clock);
		loc_year = tm.tm_year+1900; loc_mon = tm.tm_mon+1; loc_date = tm.tm_mday; loc_hour = tm.tm_hour; loc_min = tm.tm_min;
		
		display(loc_year, loc_mon, loc_date, loc_hour, loc_min);
		ring (750, 850, loc_year, loc_mon, loc_date, loc_hour, loc_min);
//		Beep(750, 800);
		Sleep (2000);
		system ("cls");
	}
	
	return 0;
}

/*
List:
	Multiple data connect
	
	Search for registered "Aktivitas"
	Sort "Tanggal dan Jam"
	
	Buat "Main Menu"
	Buat User Interface
	Convert ke background application
*/
