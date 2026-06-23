#include "core.hpp"

void tampilkanMenuLoginUI();
void tampilkanMenuAdminUI(string nama);

// ================= FUNGSI SISTEM (LOGIN & MENU) =================

string prosesLogin(Akun &userAktif, Akun dataPengguna[], int jumlahPengguna) {
    bersihkanLayar();
    tampilkanMenuLoginUI();
    
    string uname, pwd;
    cout << "Username : "; cin >> uname;
    
    if (uname == "exit") {
        return "Exit"; 
    }

    cout << "Password : "; cin >> pwd;

    // Cek username, kecocokan password, lalu kembalikan rolenya
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == uname && dataPengguna[i].password == pwd) {
            userAktif = dataPengguna[i]; 
            
            if (dataPengguna[i].role == "Admin") {
                return "Admin";
            } else if (dataPengguna[i].role == "Kasir") {
                return "Kasir";
            }
        }
    }
    
    return "Gagal"; 
}

void menuAdmin(Akun adminAktif, Product products[], int& productCount, Akun dataPengguna[], int& jumlahPengguna, Transaction transactions[], int transactionCount) {
    bool sesiAktif = true;
    while (sesiAktif) {
        bersihkanLayar();
        tampilkanMenuAdminUI(adminAktif.nama);
        
        int pilihanInt = inputChoice(0, 4);
        string pilihan = to_string(pilihanInt);

        if (pilihan == "1") {
            menuManajemenAkun(dataPengguna, jumlahPengguna);
        } 
        else if (pilihan == "2") {
            menuProduk(products, productCount);
        }
        else if (pilihan == "3") {
            Stokmenu(products, productCount);
        }
        else if (pilihan == "4") {
            tampilkanMenuLaporan(transactions, transactionCount);
        }
        else if (pilihan == "0") {
            cout << GREEN << "\n[+] Anda berhasil logout dari Admin.\n" << RESET;
            jedaLayar();
            return; 
        }
    }
}

void tampilkanMenuLoginUI() {
    cout << CYAN << "=========================================\n";
    cout << "               MENU LOGIN                \n";
    cout << "=========================================\n" << RESET;
    cout << YELLOW << "Ketik 'exit' pada Username untuk keluar program.\n\n" << RESET;
}

void tampilkanMenuAdminUI(string nama) {
    cout << CYAN << "=========================================\n";
    cout << "               MENU ADMIN                \n";
    cout << "=========================================\n" << RESET;
    cout << BOLD << "Halo, " << nama << "!\n\n" << RESET;
    cout << "  [1] Manajemen Akun\n";
    cout << "  [2] Manajemen Produk\n";
    cout << "  [3] Manajemen Stok\n";
    cout << "  [4] Laporan\n";
    cout << "  [0] Logout\n";
    cout << "-----------------------------------------\n";
}
