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

struct Data;

int main (){
	system ("color b0");
	char in_aktivitas[32] = "", in_bulan[10] = "";
	int in_tanggal = NULL, in_tahun = NULL, in_jam = NULL, in_menit = NULL;
	int i = 0;
	int bulan_val;
	int x = 0;
	int key;
	
	Main_Menu:
		system("cls");
		printf ("\tREMINDER APP\n\n"); //Tampilan Menu Awal.
		printf ("\tMAIN MENU\n");
		printf ("1. Tambahkan Pengingat\n");
		printf ("2. Lihat Jadwal\n");
		printf ("3. Keluar\n");
		printf ("\n\nPilih Menu: ");
		key = getch() - '0';
		system ("cls");
	
		switch (key){
			case 1:
				goto Input;
			case 2:
				goto Display;
			case 3:
				goto Exit;
			default:
				goto Main_Menu;
		}
	
	Input:
		system("cls");
		timeFetch (&loc_year, &loc_mon, &loc_date, &loc_hour, &loc_min);
		printf ("\t\tTAMBAHKAN PENGINGAT\n\n");
		printf ("Aktivitas\t: ", in_aktivitas);	gets (in_aktivitas);
		printf ("Tanggal\t\t: ", in_tanggal);	scanf ("%d", &in_tanggal);	getchar();
		printf ("Nama Bulan\t: ", in_bulan);		gets (in_bulan);
		printf ("Tahun\t\t: ", in_tahun);		scanf ("%d", &in_tahun);	getchar();
		printf ("Jam\t\t: ", in_jam);			scanf ("%d", &in_jam);		getchar();	
		printf ("Menit\t\t: ", in_menit);		scanf ("%d", &in_menit);	getchar();
		
		bulan_val = convert_mon(in_bulan);
		trem_year = in_tahun; trem_mon = bulan_val; trem_date = in_tanggal; trem_hour = in_jam; trem_min = in_menit;
		timeRem (&trem_year, &trem_mon, &trem_date, &trem_hour, &trem_min);
		
		if (in_aktivitas == NULL || trem_year<0 || trem_mon<0 || trem_date<0 || trem_hour<0 || trem_min<0 || in_jam>23 || in_menit>59){
			printf ("Galat: Kesalahan penulisan nama aktivitas atau waktu.\n");
			system ("pause");
		}
		else{
			add (in_aktivitas, in_tanggal, in_bulan, in_tahun, in_jam, in_menit);
			x++;
		}
		fflush(stdin);
		system("cls");
		goto Display;
	
	Display:
		system ("cls");
		while (kbhit() == 0){
			if (x == 0){
				display(loc_year, loc_mon, loc_date, loc_hour, loc_min);
			}
			else {
				timeFetch (&loc_year, &loc_mon, &loc_date, &loc_hour, &loc_min);
				display(loc_year, loc_mon, loc_date, loc_hour, loc_min);
				ring (750, 800, loc_year, loc_mon, loc_date, loc_hour, loc_min);
			}
			printf ("\n\n1. Tambahkan Pengingat\n");
			printf ("2. Main Menu\n");
			Sleep (1000);
			system ("cls");
		}
		key = getch() - '0';
		switch (key){
			case 1:
				goto Input;
			case 2:
				goto Main_Menu;
			default:
				goto Display;
		}
		
	Exit:
		printf ("Program telah ditutup.\n");
		return 0;
}
