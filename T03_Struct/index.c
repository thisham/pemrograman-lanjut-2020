#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

struct Mahasiswa
{
    char npm[16];
    char nama[32];
    int angkatan;
    char jurusan[32];
    char fakultas[32];
    int semester;
    int usia;
};

void act_create();
void act_read();
// int act_update();
// int act_delete();

void data_create();
void data_read();
// void data_update();
// void data_delete();


int main()
{
    int pilih;
    menu:
        printf("Menu:\n");
        printf("    [1] Tambahkan Data\n");
        printf("    [2] Tampilkan Data\n");
        printf("    [3] Perbarui Data\n");
        printf("    [4] Kurangi Data\n");
        printf("    [5] Keluar dari Aplikasi\n");
        printf("\nPilihan Anda : "); scanf("%i", &pilih);
        printf("==============================================\n");
        // printf("%i", pilih);
        switch (pilih)
        {
            case 1: data_create(); break;
            case 2: data_read(); break;
            // case 'C': data_update(); break;
            // case 'D': data_delete(); break;
            case 5: exit(1); break;
            
            default:
                printf("\nPilihan tak ditemukan!\n");
                printf("==============================================\n\n");
                goto menu;
                break;
        }
        goto menu;
    return 0;
}

// CREATE MODULES FIX NO REVISI!!

    void data_create() {
        int i;
        struct Mahasiswa mhs;

        printf("NPM      : "); scanf("%s", mhs.npm);
        printf("Nama     : "); scanf(" %[^\n]", mhs.nama);
        printf("Angkatan : "); scanf("%i", &mhs.angkatan);
        printf("Jurusan  : "); scanf(" %[^\n]", mhs.jurusan);
        printf("Fakultas : "); scanf(" %[^\n]", mhs.fakultas);
        printf("Semester : "); scanf("%i", &mhs.semester);
        printf("Usia     : "); scanf("%i", &mhs.usia);
        
        act_create(mhs);
        printf("\nData berhasil ditambahkan!\n");
        printf("==============================================\n\n");
        
    }

    void act_create(struct Mahasiswa mhs) {
        sqlite3 *db;
        sqlite3_stmt *final_query;
        char *err_msg = 0;
        
        int rc = sqlite3_open("db_mhs.db", &db);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Can\'t load database: %s", sqlite3_errmsg(db));
            sqlite3_close(db);
        }

        char *sql = "INSERT INTO Mahasiswa VALUES (:npm, :nama, :angkatan, :jurusan, :fakultas, :semester, :usia)";

        sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
        sqlite3_bind_text(final_query, 1, mhs.npm, strlen(mhs.npm), NULL);
        sqlite3_bind_text(final_query, 2, mhs.nama, strlen(mhs.nama), NULL);
        sqlite3_bind_int(final_query, 3, mhs.angkatan);
        sqlite3_bind_text(final_query, 4, mhs.jurusan, strlen(mhs.jurusan), NULL);
        sqlite3_bind_text(final_query, 5, mhs.fakultas, strlen(mhs.fakultas), NULL);
        sqlite3_bind_int(final_query, 6, mhs.semester);
        sqlite3_bind_int(final_query, 7, mhs.usia);
        sqlite3_step(final_query);
    }


// READ MODULES

    void data_read() {
        int i;
        char npm[16];

        printf("Opsi:\n");
        printf("    [1] Semua Data\n");
        printf("    [2] Berdasarkan NPM\n");
        printf("\nPilihan Anda : "); scanf("%i", &i);
        printf("==============================================\n\n");

        switch (i)
        {
        case 1:
            act_read("all");
            break;

        case 2:
            printf("Masukkan NPM : "); scanf("%s", npm);
            printf("==============================================\n\n");
            act_read(npm);
            break;
        
        default:
            printf("Pilihan tidak tersedia!\n");
            break;
        }

        printf("==============================================\n\n");
    }

    void act_read(char npm[16]) {
        sqlite3 *db;
        sqlite3_stmt *final_query;
        char *err_msg = 0;
        int i = 1;

        int rc = sqlite3_open("db_mhs.db", &db);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Can\'t load database: %s", sqlite3_errmsg(db));
            sqlite3_close(db);
        }

        if (npm == "all")
        {
            char *sql = "SELECT * FROM Mahasiswa";
            sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
            while (sqlite3_step(final_query) == SQLITE_ROW) {
                printf("Data ke-%i:\n", i++);
                printf("\tNPM\t\t: %s\n", sqlite3_column_text(final_query, 0));
                printf("\tNama\t\t: %s\n", sqlite3_column_text(final_query, 1));
                printf("\tAngkatan\t: %i\n", sqlite3_column_int(final_query, 2));
                printf("\tJurusan\t\t: %s\n", sqlite3_column_text(final_query, 3));
                printf("\tFakultas\t: %s\n", sqlite3_column_text(final_query, 4));
                printf("\tSemester\t: %i\n", sqlite3_column_int(final_query, 5));
                printf("\tUsia\t\t: %i tahun\n\n", sqlite3_column_int(final_query, 6));
            }
            // printf("%16s|%32s|%8s|%32s|%32s|%8s|%4s\n", "NPM", "Nama", "Angkatan", "Jurusan", "Fakultas", "Semester", "Usia");
            // printf("----------------+--------------------------------+--------+--------------------------------+--------------------------------+--------+----\n");
            // while (sqlite3_step(final_query) == SQLITE_ROW) {
            //     printf("%16s|%32s|%8i|%32s|%32s|%8i|%4i\n", sqlite3_column_text(final_query, 0), sqlite3_column_text(final_query, 1), sqlite3_column_int(final_query, 2), sqlite3_column_text(final_query, 3), sqlite3_column_text(final_query, 4), sqlite3_column_int(final_query, 5), sqlite3_column_int(final_query, 6));
            // }
        }
        else
        {
            char *sql = "SELECT * FROM Mahasiswa WHERE npm = :npm";
            sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
            sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
            while (sqlite3_step(final_query) == SQLITE_ROW) {
                printf("Data ke-%i:\n", i++);
                printf("\tNPM\t\t: %s\n", sqlite3_column_text(final_query, 0));
                printf("\tNama\t\t: %s\n", sqlite3_column_text(final_query, 1));
                printf("\tAngkatan\t: %i\n", sqlite3_column_int(final_query, 2));
                printf("\tJurusan\t\t: %s\n", sqlite3_column_text(final_query, 3));
                printf("\tFakultas\t: %s\n", sqlite3_column_text(final_query, 4));
                printf("\tSemester\t: %i\n", sqlite3_column_int(final_query, 5));
                printf("\tUsia\t\t: %i tahun\n\n", sqlite3_column_int(final_query, 6));
            }
            // printf("%16s|%32s|%8s|%32s|%32s|%8s|%4s\n", "NPM", "Nama", "Angkatan", "Jurusan", "Fakultas", "Semester", "Usia");
            // printf("----------------+--------------------------------+--------+--------------------------------+--------------------------------+--------+----\n");
            // while (sqlite3_step(final_query) == SQLITE_ROW) {
            //     printf("%16s|%32s|%8i|%32s|%32s|%8i|%4i\n", sqlite3_column_text(final_query, 0), sqlite3_column_text(final_query, 1), sqlite3_column_int(final_query, 2), sqlite3_column_text(final_query, 3), sqlite3_column_text(final_query, 4), sqlite3_column_int(final_query, 5), sqlite3_column_int(final_query, 6));
            // }
        }
        
    }