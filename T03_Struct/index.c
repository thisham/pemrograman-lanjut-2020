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

void act_create(struct Mahasiswa mhs);
void act_read(char npm[16]);
void act_update();
void act_delete();

void data_create();
void data_read();
void data_update();
void data_delete();


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
            case 3: data_update(); break;
            case 4: data_delete(); break;
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
        sqlite3_close_v2(db);
    }


// READ MODULES

    void data_read() {
        int i;
        char npm[16];

        printf("Opsi:\n");
        printf("    [1] Baca Semua Data\n");
        printf("    [2] Baca Berdasarkan NPM\n");
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
        sqlite3_close_v2(db);
    }


// UPDATE DATA

    void data_update() {
        int i;
        char npm[16], str[32];
        struct Mahasiswa mhs;

        printf("\nNPM      : "); scanf("%s", mhs.npm);
        printf("Nama     : "); scanf(" %[^\n]", mhs.nama);
        printf("Angkatan : "); scanf("%i", &mhs.angkatan);
        printf("Jurusan  : "); scanf(" %[^\n]", mhs.jurusan);
        printf("Fakultas : "); scanf(" %[^\n]", mhs.fakultas);
        printf("Semester : "); scanf("%i", &mhs.semester);
        printf("Usia     : "); scanf("%i", &mhs.usia);
        printf("==============================================\n\n");
        act_update(mhs.npm, mhs);
        printf("\nData berhasil diperbarui!\n");
        printf("==============================================\n\n");
    }

    void act_update(char npm[16], struct Mahasiswa mhs) {
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

        char *sql = "UPDATE Mahasiswa SET nama = :nama, angkatan = :angkatan, jurusan = :jurusan, fakultas = :fakultas, semester = :semester, usia = :usia WHERE npm = :npm";
        sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
        sqlite3_bind_text(final_query, 1, mhs.nama, strlen(mhs.nama), NULL);
        sqlite3_bind_int(final_query, 2, mhs.angkatan);
        sqlite3_bind_text(final_query, 3, mhs.jurusan, strlen(mhs.jurusan), NULL);
        sqlite3_bind_text(final_query, 4, mhs.fakultas, strlen(mhs.fakultas), NULL);
        sqlite3_bind_int(final_query, 5, mhs.semester);
        sqlite3_bind_int(final_query, 6, mhs.usia);
        sqlite3_bind_text(final_query, 7, mhs.npm, strlen(mhs.npm), NULL);
        // printf("%s\n",sqlite3_expanded_sql(final_query));
        sqlite3_step(final_query);
        // sqlite3_finalize(final_query);
        // rc = sqlite3_exec(db, sql, callback, "Callback Called", &err_msg);
        

        // if (rc != SQLITE_OK)
        // {
        //     printf("SQLite Error: %s\n", err_msg);
        //     sqlite3_free(err_msg);
        // }
        

        /* if (npm == "all")
        {
            switch (item)
            {
            case 1:
                char *sql = "UPDATE Mahasiswa SET nama = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_text(final_query, 0, data, strlen(data), NULL);
                sqlite3_step(final_query);
                break;

            case 2:
                char *sql = "UPDATE Mahasiswa SET angkatan = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_int(final_query, 0, atoi(data));
                sqlite3_step(final_query);
                break;

            case 3:
                char *sql = "UPDATE Mahasiswa SET jurusan = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_text(final_query, 0, data, strlen(data), NULL);
                sqlite3_step(final_query);
                break;

            case 4:
                char *sql = "UPDATE Mahasiswa SET fakultas = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_text(final_query, 0, data, strlen(data), NULL);
                sqlite3_step(final_query);
                break;

            case 5:
                char *sql = "UPDATE Mahasiswa SET semester = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_int(final_query, 0, atoi(data));
                sqlite3_step(final_query);
                break;

            case 6:
                char *sql = "UPDATE Mahasiswa SET usia = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_int(final_query, 0, atoi(data));
                sqlite3_step(final_query);
                break;
            
            default:
                printf("Error");
                break;
            }
        }
        else
        {
            switch (item)
            {
            case 1:
                char *sql = "UPDATE Mahasiswa SET nama = :nama WHERE npm = :npm";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_text(final_query, 0, data, strlen(data), NULL);
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                break;

            case 2:
                char *sql = "UPDATE Mahasiswa SET angkatan = ? WHERE npm = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_int(final_query, 0, atoi(data));
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                break;

            case 3:
                char *sql = "UPDATE Mahasiswa SET jurusan = ? WHERE npm = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_text(final_query, 0, data, strlen(data), NULL);
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                break;

            case 4:
                char *sql = "UPDATE Mahasiswa SET fakultas = ? WHERE npm = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_text(final_query, 0, data, strlen(data), NULL);
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                break;

            case 5:
                char *sql = "UPDATE Mahasiswa SET semester = ? WHERE npm = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_int(final_query, 0, atoi(data));
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                break;

            case 6:
                char *sql = "UPDATE Mahasiswa SET usia = ? WHERE npm = ?";
                sqlite3_prepare_v2(db, sql, strlen(sql), &final_query, NULL);
                sqlite3_bind_int(final_query, 0, atoi(data));
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                break;
            
            default:
                printf("Error");
                break;
            }
        } */
        
        sqlite3_close_v2(db);
        
    }


// DELETE DATA

    void data_delete() {
        int i;
        char npm[16];

        printf("Opsi:\n");
        printf("    [1] Hapus Semua Data\n");
        printf("    [2] Hapus Berdasarkan NPM\n");
        printf("\nPilihan Anda : "); scanf("%i", &i);
        printf("==============================================\n\n");

        switch (i)
        {
        case 1:
            act_delete("all");
            break;

        case 2:
            printf("Masukkan NPM : "); scanf("%s", npm);
            printf("==============================================\n\n");
            act_delete(npm);
            break;
        
        default:
            printf("Pilihan tidak tersedia!\n");
            break;
        }

        printf("==============================================\n\n");
    }

    void act_delete (char npm[16]) {
        sqlite3 *db;
        sqlite3_stmt *final_query;
        char *err_msg = 0;
        char nama[32];
        int i = 1;
        int yakin;

        int rc = sqlite3_open("db_mhs.db", &db);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Can\'t load database: %s", sqlite3_errmsg(db));
            sqlite3_close(db);
        }

        if (npm == "all")
        {
            char *sql_a = "SELECT COUNT(*) AS jumlah FROM Mahasiswa";
            sqlite3_prepare_v2(db, sql_a, strlen(sql_a), &final_query, NULL);
            sqlite3_step(final_query);
            printf("\nAnda yakin ingin menghapus sebanyak %i data? Tekan [1] untuk perintah \'Ya\' : ", sqlite3_column_int(final_query, 0)); scanf("%i", &yakin);
            
            if (yakin == 1) {
                char *sql_b = "DELETE FROM Mahasiswa";
                sqlite3_prepare_v2(db, sql_b, strlen(sql_b), &final_query, NULL);
                sqlite3_step(final_query);
                printf("\nSemua data telah dihapus!\n");
            } else {
                printf("\nTidak ada data yang dihapus.\n");
            }
            
            
        }
        else
        {
            char *sql_c = "SELECT * FROM Mahasiswa WHERE npm = ?";
            sqlite3_prepare_v2(db, sql_c, strlen(sql_c), &final_query, NULL);
            sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
            sqlite3_step(final_query);
            strcpy(nama, sqlite3_column_text(final_query, 1));
            printf("Anda yakin ingin data dari %s dengan NPM %s? Tekan [1] untuk perintah \'Ya\' : ", nama, npm); scanf("%i", &yakin);

            if (yakin == 1) {
                char *sql_d = "DELETE FROM Mahasiswa WHERE npm = ?";
                sqlite3_prepare_v2(db, sql_d, strlen(sql_d), &final_query, NULL);
                sqlite3_bind_text(final_query, 1, npm, strlen(npm), NULL);
                sqlite3_step(final_query);
                printf("\nData dari %s dengan NPM %s telah dihapus!\n", nama, npm);
            } else {
                printf("\nTidak ada data yang dihapus.\n");
            }
        }
        sqlite3_close_v2(db);
    }