#include <stdio.h>

//Zeller's Congruence
enum hari {SABTU, MINGGU, SENIN, SELASA, RABU, KAMIS, JUMAT};
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
    return hasil;
}


int main () {
    
    return 0;
}