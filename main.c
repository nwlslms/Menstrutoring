#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

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
            printf("\n\n");
        } else if (i == harian[bulan-1]) {
            printf("\n\n");
        }
    }
    printf("===========================\n");
}

void menu();

//Registration function
void createAccount();
void Login();
void forgotPass();

//
void panelUtama();
int tahunAnc;
int bulanAnc;
void monitor(int tahun);
int main () {
    menu();
    return 0;
}

void menu() {
    char cmd;
    do {
        system("CLS");
        FILE *rf = fopen("user.txt", "r");
        printf("M E N S T R U T O R I N G\n");
        printf("=========================\n");
        if (rf == NULL) {
            printf("1. Buat akun\n2. Exit\n[?] ");
            cmd = getch();
            switch(cmd) {
                case '1': createAccount(); break;
                case '2': break;
                default: break;
            }
        } else {
            printf("1. Masuk\n2. Lupa password\n3. Exit\n[?] ");
            cmd = getch();
            switch(cmd) {
                case '1': fclose(rf);Login(); break;
                case '2': fclose(rf);forgotPass(); cmd = '1'; break;
                case '3': break;
                default: break;
            }
        }
        fclose(rf);
    } while (cmd == '1');
}

void createAccount() {
    system("CLS");
    printf("M E N S T R U T O R I N G\n");
    printf("=========================\n");
    printf("[!]Username: ");
    char usn[21];
    scanf("%s", usn);
    printf("[!]Password: ");
    char pass[21];
    scanf("%s", pass);
    printf("[+] Lengkapi Informasi tambahan\n");
    printf("[!] Tanggal lahir [dd/mm/yyyy]: ");
    int tanggal, bulan, tahun;
    scanf("%d/%d/%d", &tanggal, &bulan, &tahun);
    printf("[!] Umur saat ini: ");
    int umur;
    scanf("%d", &umur);
    printf("[!] Umur pertama kali menstruasi: ");
    int awal;
    scanf("%d", &awal);
    int buatBulan, buatTahun;
    printf("[!] Waktu pembuatan akun [mm/yyyy]: ");
    scanf("%d/%d", &buatBulan, &buatTahun);
    printf("[!] Simpan informasi berikut untuk masuk:\nUsername: %s\nPassword: %s\n", usn, pass);
    FILE *wf = fopen("user.txt", "w");
    fprintf(wf, "%s#%s\n", usn, pass);
    fprintf(wf, "%d#%d#%d\n", tanggal, bulan, tahun);
    fprintf(wf, "%d#%d", umur, awal);
    fclose(wf);
    wf = fopen("data.txt", "w");
    fprintf(wf, "%d-%d\n", buatBulan, buatTahun);
    fclose(wf);
    system("PAUSE");
}

void Login() {
    int kesempatan = 4;
    FILE *rf = fopen("user.txt", "r");
    char username[21], password[21];
    fscanf(rf, "%[^#]#%s\n", username, password);
    fclose(rf);
    while (kesempatan > 0) {
        system("CLS");
        printf("M E N S T R U T O R I N G\n");
        printf("=========================\n");
        printf("[!] Masukkan username: ");
        char nama[21], pass[21];
        scanf("%s", nama);
        printf("[!] Masukkan password: ");
        scanf("%s", pass);
        if (strcmp(username, nama) == 0 && strcmp(password, pass) == 0) {
            printf("[+] Berhasil masuk!\n");
            panelUtama();
            break;
        } else {
            kesempatan--;
            printf("[-] Password atau username salah!\n[-] %d kesempatan lagi!\n", kesempatan);
            system("PAUSE");
        }
    }
    system("PAUSE");
}

void forgotPass() {
    system("CLS");
    printf("M E N S T R U T O R I N G\n");
    printf("=========================\n");
    printf("[!] Masukkan username: ");
    char nama[21];
    scanf("%20s", nama);
    char password[21];
    printf("[!] Masukkan password baru: ");
    scanf("%20s", password);

    int tanggal, bulan, tahun, umur, awal;

    FILE *rwf = fopen("user.txt", "r");
    fscanf(rwf, "%*[^#]#%*s");
    fscanf(rwf, "%d#%d#%d\n", &tanggal, &bulan, &tahun);
    fscanf(rwf, "%d#%d", &umur, &awal);
    fclose(rwf);

    rwf = fopen("user.txt", "w");
    fprintf(rwf, "%s#%s\n", nama, password);
    fprintf(rwf, "%d#%d#%d\n", tanggal, bulan, tahun);
    fprintf(rwf, "%d#%d", umur, awal);
    fclose(rwf);

    printf("[!] Simpan informasi berikut:\nUsername: %s\nPassword baru: %s\n", nama, password);
    system("PAUSE");
}

void panelUtama() {
    FILE *rf = fopen("data.txt", "r");
    fscanf(rf, "%d-%d\n", &bulanAnc, &tahunAnc);
    fclose(rf);
    char cmd;
    do {
        system("CLS");
        printf("M E N S T R U T O R I N G\n");
        printf("=========================\n");
        printf("1. Monitor\n2. Logout\n[?] ");
        cmd = getch();
        switch(cmd) {
            case '1':
                printf("\n[!] Masukkan tahun (-1 untuk kembali): ");
                int tahun;
                scanf("%d",&tahun);
                if (tahun < 0) {
                    continue;
                } else {
                    if (tahun < tahunAnc) {
                        printf("[!] Tahun tidak bisa kurang dari tahun pembuatan (Tahun pembuatan akun: %d)\n", tahunAnc);
                        system("PAUSE");
                        continue;
                    } else {
                        monitor(tahun);
                    }
                }
                break;
            default: break;
        }
    } while (cmd != '2');
    return;
}

void monitor(int tahun) {
    int cmd;
    do {
        system("CLS");
        printf("M E N S T R U T O R I N G\n");
        printf("=========================\n");
        printf("1. Januari\n2. Februari\n3. Maret\n4. April\n5. Mei\n6. Juni\n7. Juli\n8. Agustus\n9. September\n10. Oktober\n11. November\n12. Desember\n0. Kembali\n[?] ");
        scanf("%d", &cmd);

        if (cmd >= 1 && cmd <= 12) {
            system("CLS");
            printCalendar(cmd, tahun);
            system("PAUSE");
        }
    } while (cmd != 0);
}