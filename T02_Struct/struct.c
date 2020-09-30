#include <stdio.h>
#include <string.h>

/*
 * Hamdan Yuwafi Mastu Wijaya (NPM. 19081010092)
 * Judul        : Sistem Persediaan Bahan dalam Lemari Gudang
 * GitHub URL   : 
 * Note         : Source code ini ditulis di Linux Ubuntu 18.04 dan dikompilasi dengan GCC for Linux.
 */

struct gudang
{
    int   bhn_id;
    char  bhn_name[256];
    float bhn_mass;
    int   bhn_sum;
};

int main(int argc, char const *argv[])
{
    int i, n, sum, jenis, max_caps;
    float max_mass, total_mass;
    char selesai[1];
    struct gudang g[n];
    n = 1; sum = 0; total_mass = 0;
    printf("Masukkan jumlah jenis barang    : ");
    scanf("%i", &jenis);
    printf("Masukkan kapasitas maksimal     : ");
    scanf("%i", &max_caps);
    printf("Masukkan beban lemari maksimal  : ");
    scanf("%f", &max_mass);
    printf("\n");

    for (i = 0; i < jenis; i++)
    {
        g[i].bhn_id = i + 1;
        printf("Nama Bahan              : ");
        scanf(" %[^\n]", g[i].bhn_name);
        printf("Massa Bahan (dalam Kg)  : ");
        scanf("%f", &g[i].bhn_mass);
        printf("Jumlah Bahan            : ");
        scanf("%i", &g[i].bhn_sum);
        printf("\n");
        sum = sum + g[i].bhn_sum;
        total_mass = total_mass + g[i].bhn_mass;
    }

    
    printf("------------------------------------------------------------------------------\n");
    printf("Barang di Lemari:\n");
    for (i = 0; i < jenis; i++)
    {
        printf("\t %i. \t%s \t%i item \t%f Kg\n", i + 1, g[i].bhn_name, g[i].bhn_sum, g[i].bhn_mass);
    }
    printf("------------------------------------------------------------------------------\n");
    printf("Total Barang    : %i dari kapasitas %i item\n", sum, max_caps);
    printf("Total Beban     : %f Kg\n", total_mass);
    printf("Keadaan lemari  : %s dan %s\n", (sum > max_caps) ? "Melebihi kapasitas" : "Masih cukup", (total_mass > max_mass) ? "beban terlalu berat!" : "masih kuat menyimpan bahan.");
    
    return 0;
}
