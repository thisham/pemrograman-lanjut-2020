#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Hamdan Yuwafi Mastu Wijaya (NPM. 19081010092)
 * Judul        : CRUD-C with bubble sort and selection sort
 * GitHub URL   : https://github.com/thisham/pemrograman-lanjut-2020/tree/master/T05_UTS
 * Note         : Source code ini ditulis di Linux Ubuntu 18.04 dan dikompilasi dengan GCC for Linux.
 */

typedef struct
{
	char sku[8];
	char namaBarang[256];
	char kategori[256];
	int harga;
	int stok;
} Barang;

int menu();
int rd_menu();
void b_sort();
void rd_data();
void sekat();

int main(int argc, char const *argv[])
{
	char sku[8];
	bool found; int d = 0;
	int opt, max, data, rawStok = 0;
	printf("Masukkan jumlah maksimal jenis barang : "); scanf("%d", &max); 
    Barang brg[max], srt_brg[max], tmp_brg;

	Repeat:
		switch (menu()) 
		{
			case 1: 
				sekat();
				printf("Jumlah jenis barang: %d / %d\n\n", data, max);
                if (data < max) {
                    data = data + 1;
                    printf("SKU        : "); scanf("%s", brg[data - 1].sku);
                    printf("Nama Barang: "); scanf(" %[^\n]", brg[data - 1].namaBarang);
                    printf("Kategori   : "); scanf(" %[^\n]", brg[data - 1].kategori);
                    printf("Harga      : "); scanf("%d", &brg[data - 1].harga);
                    brg[data - 1].stok = 0;
                } else {
                    printf("Error: Jumlah maksimal jenis barang terpenuhi!\n");
                }
				break;

			case 2:
				sekat();
				printf("Jumlah jenis barang: %d\n\n", data);
				if (data == 0) {
					sekat();
					printf("Tidak ada data yang dapat ditampilkan.\n");
					sekat();
				} else {
					sekat();
					switch (rd_menu())
					{
						case 1:
							b_sort(brg, data, 1);
							break;

						case 2:
							b_sort(brg, data, 2);
							break;
						
						case 3:
							b_sort(brg, data, 3);
							break;

						case 4:
							printf("Cari SKU : "); scanf("%s", sku);
                            printf("\n");
							found = false;
                            for (int i = 0; i < data; i++) {
                                if (!strncmp(brg[i].sku, sku, sizeof(sku))) {
                                    rd_data(brg[i]);
                                    found = true;
                                }
                            }

                            // printf("%d\n", found);

                            if (!found) {
                                printf("Data tidak ditemukan!\n");
                            }
							break;
						
						default:
							printf("Option is unavailable!\n");
							break;
					}
					sekat();
				}
				break;

			case 3:
				sekat();
				printf("Cari SKU : "); scanf("%s", sku);
				printf("\n");
				found = false;
				for (int i = 0; i < data; i++) {
					if (strncmp(brg[i].sku, sku, sizeof(sku)) == 0) {
						found = true;
						d = i;
					}
				}

				if (found) {
					printf("Catatan: Mohon jangan dibiarkan kosong. Masukkan ulang untuk mencegah perubahan.\n");
					printf("\tSKU        : (%s)\n", brg[d].sku);
					printf("\tNama Barang: (%s) => ", brg[d].namaBarang); scanf(" %[^\n]", brg[d].namaBarang);
					printf("\tKategori   : (%s) => ", brg[d].kategori); scanf(" %[^\n]", brg[d].kategori);
					printf("\tHarga      : (%d) => ", brg[d].harga); scanf("%d", &brg[d].harga);
					printf("\tStok       : (%d) => ", brg[d].stok);
					printf("\n");
					printf("Pembaruan data berhasil! Data telah berubah.\n");
				} else {
					printf("Data tak ditemukan!\n");
				}
				break;

			case 4:
				sekat();
				printf("Cari SKU : "); scanf("%s", sku);
				printf("\n");
				found = false;
				for (int i = 0; i < data; i++) {
					if (strncmp(brg[i].sku, sku, sizeof(sku)) == 0) {
						for (int j = i; j < data; j++) {
							brg[j] = brg[j + 1];
						}
						data = data - 1;
						printf("Penghapusan data berhasil! Data telah dihapus.\n"); 
						found = true;
					}
				}

				if (!found) {
					printf("Data not found!\n");
				}
				break;

			case 5:
				sekat();
				printf("Cari SKU : "); scanf("%s", sku);
				printf("\n");
				found = false;

				for (int i = 0; i < data; i++) {
					if (strcmp(brg[i].sku, sku) == 0) {
						found = true;
						d = i;
					}
					printf("%d", strcmp(brg[i].sku, sku));
				}

				if (found) {
					printf("Catatan: Mohon jangan dibiarkan kosong. Masukkan '0' (nol) untuk mencegah perubahan.\n");
					printf("\tSKU        : (%s)\n", brg[d].sku);
					printf("\tNama Barang: (%s)\n", brg[d].namaBarang);
					printf("\tStok Masuk : (sekarang: %d) => ", brg[d].stok); scanf("%d", &rawStok);
					printf("\n");
					brg[d].stok = brg[d].stok + rawStok;
					printf("Barang masuk berhasil dicatat! Stok bertambah %d.\n", rawStok);
				} else {
					printf("Data tak ditemukan!\n");
				}
				break;

			case 6:
				sekat();
				printf("Cari SKU : "); scanf("%s", sku);
				printf("\n");
				found = false;

				for (int i = 0; i < data; i++) {
					if (strncmp(brg[i].sku, sku, sizeof(sku)) == 0) {
						found = true;
						d = i;
					}
				}

				if (found) {
					printf("Catatan: Mohon jangan dibiarkan kosong. Masukkan '0' (nol) untuk mencegah perubahan.\n");
					printf("\tSKU        : (%s)\n", brg[d].sku);
					printf("\tNama Barang: (%s)\n", brg[d].namaBarang);
					printf("\tStok Keluar: (sekarang: %d) => ", brg[d].stok); scanf("%d", &rawStok);
					printf("\n");
					if (rawStok > brg[d].stok) {
						printf("Error: Stok kurang! Stok tersedia: %d.\n", brg[d].stok);
					} else {
						brg[d].stok = brg[d].stok - rawStok;
						printf("Barang keluar berhasil dicatat! Stok berkurang %d.\n", rawStok);
					}
				} else {
					printf("Data tak ditemukan!\n");
				}
				break;
		}
		goto Repeat; 
	return 0;
}

void sekat() {
	printf("===================================================\n\n");
}

int menu () {
	int x;
	sekat();
	printf("Selamat datang di aplikasi inventarisasi! Silakan pilih salah satu:\n");
	printf("\t[1] Tambah Data\n");
	printf("\t[2] Tampilkan Data\n");
	printf("\t[3] Update Data\n");
	printf("\t[4] Hapus Data\n");
	printf("\t====================\n");
	printf("\t[5] Tambah Stok\n");
	printf("\t[6] Stok Keluar\n");
	printf("Pilihan Anda : "); scanf("%d", &x);
	printf("\n");
	return x;
}

int rd_menu () {
	int x;
	sekat();
	printf("Tampilkan data menurut:\n");
	printf("\t[1] SKU terkecil\n");
	printf("\t[2] Harga termurah\n");
	printf("\t[3] Stok paling sedikit\n");
	printf("\t[4] Spesifik ke data\n");
	printf("Pilihan Anda : "); scanf("%d", &x);
	printf("\n");
	return x;
}

void rd_data (Barang brg) {
	printf("\tSKU        : %s\n", brg.sku);
	printf("\tNama Barang: %s\n", brg.namaBarang);
	printf("\tKategori   : %s\n", brg.kategori);
	printf("\tHarga      : %d\n", brg.harga);
	printf("\tStok       : %d\n", brg.stok);
}

void b_sort (Barang brg[], int length, int opsi) {
	Barang tmp_brg, loc_brg[length];

	switch (opsi) {
		case 1:
			for (int i = 0; i < length; i++) {
				loc_brg[i] = brg[i];
			}

			for (int i = 0; i < length; i++) {
				for (int j = 1; j < length; j++) {
					if (strcmp(loc_brg[j-1].sku, loc_brg[j].sku) > 0) {
						tmp_brg = loc_brg[j-1];
						loc_brg[j-1] = loc_brg[j];
						loc_brg[j] = tmp_brg;
					}
										
				}
			}
								
			for (int i = 0; i < length; i++) {
				printf("Data number %i :\n", i+1);
				rd_data(loc_brg[i]);
				printf("\n");
			}
			break;

		case 2:
			for (int i = 0; i < length; i++) {
				loc_brg[i] = brg[i];
			}

			for (int i = 0; i < length; i++) {
				for (int j = 1; j < length; j++) {
					if (loc_brg[j-1].harga > loc_brg[j].harga) {
						tmp_brg = loc_brg[j-1];
						loc_brg[j-1] = loc_brg[j];
						loc_brg[j] = tmp_brg;
					}
										
				}
			}
								
			for (int i = 0; i < length; i++) {
				printf("Data number %i :\n", i+1);
				rd_data(loc_brg[i]);
				printf("\n");
			}
			break;

		case 3:
			for (int i = 0; i < length; i++) {
				loc_brg[i] = brg[i];
			}

			for (int i = 0; i < length; i++) {
				for (int j = 1; j < length; j++) {
					if (loc_brg[j-1].stok > loc_brg[j].stok) {
						tmp_brg = loc_brg[j-1];
						loc_brg[j-1] = loc_brg[j];
						loc_brg[j] = tmp_brg;
					}				
				}
			}
								
			for (int i = 0; i < length; i++) {
				printf("Data number %i :\n", i+1);
				rd_data(loc_brg[i]);
				printf("\n");
			}
			break;
		
		default:
			break;
	}
}