#include "core.hpp"

const string FILE_TRANSAKSI = "data_transaksi.txt";

void muatDataTransaksi(Transaction transactions[], int &transactionCount) {
    ifstream file(FILE_TRANSAKSI);
    if (!file.is_open()) return;
    
    transactionCount = 0;
    string id, cid, d;
    double t, p, c;
    while (file >> id >> cid >> d >> t >> p >> c) {
        transactions[transactionCount].id = id;
        transactions[transactionCount].cashierId = cid;
        transactions[transactionCount].date = d;
        transactions[transactionCount].total = t;
        transactions[transactionCount].payment = p;
        transactions[transactionCount].change = c;
        transactionCount++;
    }
    file.close();
}

void simpanDataTransaksi(Transaction transactions[], int transactionCount) {
    ofstream file(FILE_TRANSAKSI);
    if (!file.is_open()) return;
    for (int i = 0; i < transactionCount; i++) {
        file << transactions[i].id << " "
             << transactions[i].cashierId << " "
             << transactions[i].date << " "
             << transactions[i].total << " "
             << transactions[i].payment << " "
             << transactions[i].change << "\n";
    }
    file.close();
}

void tampilkanPetunjukUI();
void headerRiwayatTransaksiUI();
void headerDaftarProdukTerjualUI();
void tampilkanMenuLaporanUI();

void Transaction::setTransaction(string trxId, string userId, string trxDate, double trxTotal) {
    id = trxId;
    cashierId = userId;
    date = trxDate;
    total = trxTotal;
    payment = 0;
    change = 0;
}

bool Transaction::pay(double money) {
    if (money < total) {
        return false;
    }

    payment = money;
    change = payment - total;
    return true;
}

void checkout(
    Product products[],
    int productCount,
    CartItem cart[],
    int cartCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
) {
    if (cartCount == 0) {
        cout << RED << "\n[!] Keranjang masih kosong. Tidak ada yang bisa dicheckout.\n" << RESET;
        return;
    }

    Transaction trx;
    trx.setTransaction(
        "TRX" + to_string(transactionCount + 1),
        cashierId,
        getCurrentDate(),
        calculateTotal(cart, cartCount)
    );

    double money;
    cout << CYAN << "\n=========================================\n";
    cout << "               CHECKOUT                  \n";
    cout << "=========================================\n" << RESET;
    cout << BOLD << "Total Tagihan : Rp " << (long long)trx.total << RESET << endl;
    cout << "Masukkan Uang : Rp ";
    cin >> money;

    while (!trx.pay(money)) {
        cout << RED << "[!] Uang tidak cukup. Masih kurang Rp " << (trx.total - money) << RESET << "\n";
        cout << "Masukkan Uang : Rp ";
        cin >> money;
    }

    // Update stok
    for (int i = 0; i < cartCount; i++) {
        Product* product = findProduct(products, productCount, cart[i].productId);
        if (product != nullptr) {
            product->stock -= cart[i].quantity;
        }
    }

    cash->saldo += trx.total;
    simpanDataKas(cash);
    transactions[transactionCount] = trx;
    transactionCount++;
    
    simpanDataTransaksi(transactions, transactionCount);
    simpanDataProduk(products, productCount);

    cout << GREEN << "\n[+] Transaksi berhasil!\n" << RESET;
    cout << "Kembalian Anda: Rp " << trx.change << "\n";
    cout << CYAN << "=========================================\n" << RESET;
}

void startTransaction(
    Product products[],
    int productCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
) {
    CartItem cart[MAX_CART];
    int cartCount = 0;

    string input;
    string lastProductId = "";

    while (true) {
        bersihkanLayar();
        cout << CYAN << "=========================================\n";
        cout << "             TRANSAKSI BARU              \n";
        cout << "=========================================\n" << RESET;
        
        showCart(cart, cartCount);

        tampilkanPetunjukUI();
        
        cout << "\n>> Input: ";
        cin >> input;

        if (input == "q") {
            if (lastProductId == "") {
                cout << RED << "[!] Belum ada barang yang dipilih sebelumnya.\n" << RESET;
                jedaLayar();
                continue;
            }
            
            CartItem* item = findCartItem(cart, cartCount, lastProductId);

            if (item != nullptr) {
                int qty;
                cout << "Masukkan jumlah baru untuk " << BOLD << item->productName << RESET << " : ";
                cin >> qty;
                
                item->quantity = 0;
                item->subtotal = 0;

                addToCart(products, productCount, cart, cartCount, lastProductId, qty);
            }
        }
        else if (input == "c") {
            checkout(
                products,
                productCount,
                cart,
                cartCount,
                transactions,
                transactionCount,
                cash,
                cashierId
            );
            jedaLayar();
            break;
        }
        else if (input == "x") {
            cout << YELLOW << "\n[!] Transaksi dibatalkan.\n" << RESET;
            jedaLayar();
            break;
        }
        else {
            addToCart(products, productCount, cart, cartCount, input, 1);
            lastProductId = input;
        }
    }
}

void transactionHistory(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << YELLOW << "\n[-] Belum ada transaksi yang tercatat.\n" << RESET;
        return;
    }

    headerRiwayatTransaksiUI();
    
    for (int i = 0; i < transactionCount; i++) {
        cout << left << setw(10) << transactions[i].id 
             << setw(10) << transactions[i].cashierId 
             << setw(15) << transactions[i].date 
             << setw(12) << transactions[i].total 
             << setw(12) << transactions[i].payment 
             << transactions[i].change << endl;
    }
    cout << "=================================================================\n";
}

void totalSales(Transaction transactions[], int transactionCount) {
    double total = 0;
    for (int i = 0; i < transactionCount; i++) {
        total += transactions[i].total;
    }
    cout << CYAN << "\n=========================================\n";
    cout << "            TOTAL PENJUALAN              \n";
    cout << "=========================================\n" << RESET;
    cout << "Keseluruhan Penjualan : " << GREEN << BOLD << "Rp " << (long long)total << RESET << endl;
    cout << "=========================================\n";
}

void soldProducts(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << YELLOW << "\n[-] Belum ada transaksi, belum ada produk terjual.\n" << RESET;
        return;
    }

    headerDaftarProdukTerjualUI();
    
    for (int i = 0; i < transactionCount; i++) {
        cout << left << setw(10) << transactions[i].id 
             << setw(12) << transactions[i].cashierId 
             << setw(15) << transactions[i].date 
             << "Rp " << transactions[i].total << endl;
    }
    cout << "==================================================\n";
}

void tampilkanMenuLaporan(Transaction transactions[], int transactionCount) {
    int pilihan;
    do {
        bersihkanLayar();
        tampilkanMenuLaporanUI();
        pilihan = inputChoice(0, 3);

        switch (pilihan) {
            case 1:
                transactionHistory(transactions, transactionCount);
                jedaLayar();
                break;
            case 2:
                totalSales(transactions, transactionCount);
                jedaLayar();
                break;
            case 3:
                soldProducts(transactions, transactionCount);
                jedaLayar();
                break;
            case 0:
                break;
        }
    } while (pilihan != 0);
}

void tampilkanPetunjukUI() {
    cout << CYAN << "=========================================\n";
    cout << "                PETUNJUK                 \n";
    cout << "=========================================\n" << RESET;
    cout << "- Ketik [Kode Barang] untuk menambah ke keranjang\n";
    cout << "- Ketik 'q' untuk mengubah jumlah (qty) barang terakhir\n";
    cout << "- Ketik 'c' untuk lanjut ke Checkout\n";
    cout << "- Ketik 'x' untuk membatalkan transaksi\n";
    cout << "-----------------------------------------\n";
}

void headerRiwayatTransaksiUI() {
    cout << CYAN << "=================================================================\n";
    cout << "                       RIWAYAT TRANSAKSI                         \n";
    cout << "=================================================================\n" << RESET;
    cout << left << setw(10) << "ID TRX" 
         << setw(10) << "KASIR" 
         << setw(15) << "TANGGAL" 
         << setw(12) << "TOTAL" 
         << setw(12) << "DIBAYAR" 
         << "KEMBALIAN\n";
    cout << "-----------------------------------------------------------------\n";
}

void headerDaftarProdukTerjualUI() {
    cout << CYAN << "==================================================\n";
    cout << "               DAFTAR PRODUK TERJUAL              \n";
    cout << "==================================================\n" << RESET;
    cout << left << setw(10) << "ID TRX" 
         << setw(12) << "KASIR" 
         << setw(15) << "TANGGAL" 
         << "TOTAL\n";
    cout << "--------------------------------------------------\n";
}

void tampilkanMenuLaporanUI() {
    cout << CYAN << "==================================================\n";
    cout << "               LAPORAN TRANSAKSI                  \n";
    cout << "==================================================\n" << RESET;
    cout << "  [1] List Transaksi                              \n";
    cout << "  [2] Total Penjualan                             \n";
    cout << "  [3] Produk Terjual                              \n";
    cout << "  [0] Kembali ke Menu Kasir                       \n";
    cout << "--------------------------------------------------\n";
}