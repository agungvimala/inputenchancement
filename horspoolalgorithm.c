#include <stdio.h>
#include <string.h>
#define SIZE 256 // Jumlah karakter dalam tabel ASCII

// Fungsi untuk mengisi tabel shift
void ShiftTable(char pattern[], int m, int table[])
{
    // Inisialisasi semua nilai tabel dengan panjang pola
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = m;
    }

    // Isi tabel dengan shift yang dihitung berdasarkan pola
    for (int j = 0; j < m - 1; j++)
    {
        table[(unsigned char)pattern[j]] = m - 1 - j;
    }
}

// Fungsi untuk algoritma Horspool's string matching
int HorspoolMatching(char text[], char pattern[])
{
    int n = strlen(text);    // Panjang teks
    int m = strlen(pattern); // Panjang pola
    int table[SIZE];         // Tabel shift

    // Generate tabel shift
    ShiftTable(pattern, m, table);

    int i = m - 1; // Posisi ujung kanan pola pada teks

    while (i < n)
    {
        int k = 0; // Jumlah karakter yang cocok

        // Periksa kecocokan pola dengan teks dari kanan ke kiri
        while (k < m && pattern[m - 1 - k] == text[i - k])
        {
            k++;
        }

        // Jika semua karakter cocok, kembalikan indeks awal pola pada teks
        if (k == m)
        {
            return i - m + 1;
        }

        // Geser pola berdasarkan tabel shift
        i += table[(unsigned char)text[i]];
    }

    return -1; // Jika tidak ditemukan
}

int main()
{
    char text[100], pattern[50];

    printf("Masukkan teks: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Masukkan pola: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0; 

    // Cari pola dalam teks menggunakan Horspool's Algorithm
    int result = HorspoolMatching(text, pattern);

    if (result != -1)
    {
        printf("Pola ditemukan pada indeks: %d\n", result);
    }
    else
    {
        printf("Pola tidak ditemukan dalam teks.\n");
    }

    return 0;
}
