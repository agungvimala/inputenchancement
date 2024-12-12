#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 256 // Jumlah maksimum karakter dalam set karakter

// Fungsi untuk menghasilkan Tabel Karakter Buruk
void generateBadCharacterTable(char *pattern, int m, int badChar[MAX]) {
    for (int i = 0; i < MAX; i++) {
        badChar[i] = m; // Inisialisasi semua pergeseran dengan panjang pola
    }
    for (int j = 0; j < m - 1; j++) {
        badChar[(unsigned char)pattern[j]] = m - 1 - j; // Atur pergeseran berdasarkan posisi karakter
    }
}

// Fungsi untuk menghasilkan Tabel Sufiks Baik
void generateGoodSuffixTable(char *pattern, int m, int goodSuffix[m]) {
    int suffix[m]; // Array untuk menyimpan panjang sufiks

    // Inisialisasi Tabel Sufiks Baik
    for (int i = 0; i < m; i++) {
        goodSuffix[i] = m;
    }

    // Hitung array sufiks
    for (int i = m - 2; i >= 0; i--) {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - (i - j)]) {
            j--;
        }
        suffix[i] = i - j;
    }

    // Isi Tabel Sufiks Baik
    for (int i = 0; i < m - 1; i++) {
        goodSuffix[m - 1 - suffix[i]] = m - 1 - i;
    }

    for (int i = m - 2; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (int j = 0; j < m - 1 - i; j++) {
                if (goodSuffix[j] == m) {
                    goodSuffix[j] = m - 1 - i;
                }
            }
        }
    }
}

// Fungsi untuk melakukan pencocokan string dengan Boyer-Moore
int boyerMoore(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    if (m > n) return -1; // Pola lebih panjang daripada teks

    int badChar[MAX];
    int goodSuffix[m];

    // Praproses
    generateBadCharacterTable(pattern, m, badChar);
    generateGoodSuffixTable(pattern, m, goodSuffix);

    // Pencocokan
    int i = 0; // Posisi ujung kiri pola dalam teks
    while (i <= n - m) {
        int j = m - 1; // Mulai membandingkan dari karakter paling kanan dalam pola

        // Bandingkan pola dengan teks dari kanan ke kiri
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            return i; // Pola ditemukan pada indeks i
        } else {
            int badShift = badChar[(unsigned char)text[i + j]];
            int goodShift = goodSuffix[j];
            i += (badShift > goodShift) ? badShift : goodShift; // Ambil pergeseran maksimum
        }
    }

    return -1; // Pola tidak ditemukan
}

int main() {
    char text[1000], pattern[100];

    printf("Masukkan teks: ");
    fgets(text, 1000, stdin);
    text[strcspn(text, "\n")] = '\0'; // Hapus karakter newline

    printf("Masukkan pola: ");
    fgets(pattern, 100, stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Hapus karakter newline

    int result = boyerMoore(text, pattern);

    if (result != -1) {
        printf("Pola ditemukan pada indeks %d\n", result);
    } else {
        printf("Pola tidak ditemukan\n");
    }

    return 0;
}
