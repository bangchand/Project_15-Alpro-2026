#include "core.hpp"

void tampilkanMenuKasirUI(string nama);

int main() {
    int jumlahPengguna = 0;
    Akun dataPengguna[MAX_PENGGUNA];
    muatDataAkun(dataPengguna, jumlahPengguna);

    int productCount = 0;
    Product products[MAX_PRODUCT];
    muatDataProduk(products, productCount);

    int transactionCount = 0;
    Transaction transactions[MAX_TRANSACTION];
    muatDataTransaksi(transactions, transactionCount);

    Kas cash;
    muatDataKas(&cash);

    Akun userAktif;

    while (true) {
        string role = prosesLogin(userAktif, dataPengguna, jumlahPengguna);
        
        if (role == "Exit") {
            break;
        } 
        else if (role == "Admin") {
            menuAdmin(userAktif, products, productCount, dataPengguna, jumlahPengguna, transactions, transactionCount);
        } 
        else if (role == "Kasir") {
            string cashierId = userAktif.username;
            int pilihan;

            do {
                bersihkanLayar();
                tampilkanMenuKasirUI(userAktif.nama);
                pilihan = inputChoice(0, 3);

                switch (pilihan) {
                    case 1:
                        startTransaction(
                            products,
                            productCount,
                            transactions,
                            transactionCount,
                            &cash,
                            cashierId
                        );
                        simpanDataKas(&cash);
                        break;

                    case 2:
                        tampilkanMenuKas(&cash);
                        break;

                    case 3:
                        Stokmenu(products, productCount);
                        break;

                    case 0:
                        simpanDataKas(&cash);
                        cout << GREEN << "\n[+] Anda berhasil logout dari Kasir.\n" << RESET;
                        jedaLayar();
                        break;

                    default:
                        cout << RED << "\n[!] Pilihan tidak valid.\n" << RESET;
                        jedaLayar();
                }

            } while (pilihan != 0);
        } 
        else {
            cout << RED << "\n[!] Login gagal! Username atau password salah.\n" << RESET;
            jedaLayar();
        }
    }

    simpanDataKas(&cash);
    simpanDataAkun(dataPengguna, jumlahPengguna);
    simpanDataProduk(products, productCount);
    simpanDataTransaksi(transactions, transactionCount);
    cout << GREEN << "\n[+] Program selesai. Terima kasih!\n" << RESET;
    return 0;
}

void tampilkanMenuKasirUI(string nama) {
    cout << CYAN << "=========================================\n";
    cout << "               MENU KASIR                \n";
    cout << "=========================================\n" << RESET;
    cout << BOLD << "Halo, " << nama << "!\n\n" << RESET;
    cout << "  [1] Transaksi Baru\n";
    cout << "  [2] Manajemen Kas\n";
    cout << "  [3] Manajemen Stok\n";
    cout << "  [0] Logout\n";
    cout << "-----------------------------------------\n";
}