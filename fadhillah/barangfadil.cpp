#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char kode[10];
    char nama[50];
    int stok;
    float harga;
} Barang;

Barang daftarBarang[MAX];
int jumlahBarang = 0;

// Fungsi untuk simpan data ke file
void simpanKeFile() {
    FILE *fp = fopen("barang.txt", "w");
    if (fp == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }

    for (int i = 0; i < jumlahBarang; i++) {
        fprintf(fp, "%s|%s|%d|%.2f\n",
            daftarBarang[i].kode,
            daftarBarang[i].nama,
            daftarBarang[i].stok,
            daftarBarang[i].harga);
    }

    fclose(fp);
}

// Fungsi untuk baca data dari file
void bacaDariFile() {
    FILE *fp = fopen("barang.txt", "r");
    if (fp == NULL) {
        // File belum ada, anggap kosong
        return;
    }

    while (fscanf(fp, "%[^|]|%[^|]|%d|%f\n",
                  daftarBarang[jumlahBarang].kode,
                  daftarBarang[jumlahBarang].nama,
                  &daftarBarang[jumlahBarang].stok,
                  &daftarBarang[jumlahBarang].harga) != EOF) {
        jumlahBarang++;
    }

    fclose(fp);
}

void tambahBarang() {
    printf("\n--- Tambah Barang ---\n");
    printf("Kode Barang: ");
    scanf("%s", daftarBarang[jumlahBarang].kode);
    printf("Nama Barang: ");
    scanf(" %[^\n]", daftarBarang[jumlahBarang].nama);
    printf("Stok Barang: ");
    scanf("%d", &daftarBarang[jumlahBarang].stok);
    printf("Harga Barang: ");
    scanf("%f", &daftarBarang[jumlahBarang].harga);
    jumlahBarang++;
    simpanKeFile();
    printf("Barang berhasil ditambahkan dan disimpan!\n");
}

void tampilkanBarang() {
    printf("\n--- Daftar Barang ---\n");
    for (int i = 0; i < jumlahBarang; i++) {
        printf("%d. Kode: %s | Nama: %s | Stok: %d | Harga: %.2f\n", 
            i+1, daftarBarang[i].kode, daftarBarang[i].nama,
            daftarBarang[i].stok, daftarBarang[i].harga);
    }
    if (jumlahBarang == 0) {
        printf("Belum ada data barang.\n");
    }
}

void cariBarang() {
    char kode[10];
    printf("\n--- Cari Barang ---\n");
    printf("Masukkan kode barang: ");
    scanf("%s", kode);

    for (int i = 0; i < jumlahBarang; i++) {
        if (strcmp(daftarBarang[i].kode, kode) == 0) {
            printf("Barang ditemukan:\n");
            printf("Kode: %s | Nama: %s | Stok: %d | Harga: %.2f\n", 
                daftarBarang[i].kode, daftarBarang[i].nama,
                daftarBarang[i].stok, daftarBarang[i].harga);
            return;
        }
    }
    printf("Barang tidak ditemukan.\n");
}

void editBarang() {
    char kode[10];
    printf("\n--- Edit Barang ---\n");
    printf("Masukkan kode barang yang ingin diedit: ");
    scanf("%s", kode);

    for (int i = 0; i < jumlahBarang; i++) {
        if (strcmp(daftarBarang[i].kode, kode) == 0) {
            printf("Masukkan data baru:\n");
            printf("Nama Barang: ");
            scanf(" %[^\n]", daftarBarang[i].nama);
            printf("Stok Barang: ");
            scanf("%d", &daftarBarang[i].stok);
            printf("Harga Barang: ");
            scanf("%f", &daftarBarang[i].harga);
            simpanKeFile();
            printf("Barang berhasil diedit dan disimpan!\n");
            return;
        }
    }
    printf("Barang tidak ditemukan.\n");
}

void hapusBarang() {
    char kode[10];
    printf("\n--- Hapus Barang ---\n");
    printf("Masukkan kode barang yang ingin dihapus: ");
    scanf("%s", kode);

    for (int i = 0; i < jumlahBarang; i++) {
        if (strcmp(daftarBarang[i].kode, kode) == 0) {
            for (int j = i; j < jumlahBarang - 1; j++) {
                daftarBarang[j] = daftarBarang[j + 1];
            }
            jumlahBarang--;
            simpanKeFile();
            printf("Barang berhasil dihapus dari file!\n");
            return;
        }
    }
    printf("Barang tidak ditemukan.\n");
}

void menu() {
    int pilihan;
    do {
        printf("\n=== Menu Manajemen Barang ===\n");
        printf("1. Tambah Barang\n");
        printf("2. Tampilkan Barang\n");
        printf("3. Cari Barang\n");
        printf("4. Edit Barang\n");
        printf("5. Hapus Barang\n");
        printf("6. Keluar\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: tambahBarang(); break;
            case 2: tampilkanBarang(); break;
            case 3: cariBarang(); break;
            case 4: editBarang(); break;
            case 5: hapusBarang(); break;
            case 6: printf("Keluar dari program.\n"); break;
            default: printf("Pilihan tidak valid.\n"); break;
        }
    } while (pilihan != 6);
}

int main() {
    bacaDariFile();  // Baca data dari file saat program dimulai
    menu();
    return 0;
}
