#include <stdio.h>

//Zeller's Congruence
enum Hari {MINGGU, SENIN, SELASA, RABU, KAMIS, JUMAT, SABTU};
int awalBulan(int hari, int bulan, int tahun) {
    if (bulan == 1) {
        bulan = 13;
        tahun--;
    } else if (bulan == 2) {
        bulan = 14;
        tahun--;
    }
    int belakang = tahun % 100;
    int abad = tahun/100;

    int hasil = (hari + (13*(bulan + 1))/5 + belakang + (belakang/4) + (abad/4) - (2*abad)) % 7;
    return (hasil + 6 )%7;
}

//Print calendar
void printCalendar(int bulan, int tahun) {
    //Check leap
    const char *bulanan [] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    int harian[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int kabisat = 0;
    if (tahun % 400 == 0) {
        kabisat = 1;
        harian[1] = 29;
    } else if (tahun % 4 == 0 && tahun % 100 != 0) {
        kabisat = 1;
        harian[1] = 29;
    } else {
        kabisat = 0;
    }

    enum Hari hari = awalBulan(1, bulan, tahun);
    printf("%d - %s - %d\n", harian[bulan-1], bulanan[bulan-1], tahun);
    printf("===========================\n");
    printf("AHD SEN SEL RAB KAM JUM SAB\n");
    for (int i = 0; i < hari; i++) {
        printf("    ");
    }
    for (int i = 1; i <= harian[bulan-1]; i++) {
        printf("%3d ", i);
        if ((i + hari) % 7 == 0) {
            printf("\n");
        }
    }
    printf("===========================\n");
}
int main () {
    printCalendar(1, 2026);
    return 0;
}