#include "stocks.hpp"
#include "utils.hpp"
#include "cart.hpp" //buat ambil findProduct
#include <iostream>

void Stokmenu(Product products[], int productCount){
	cin.get();
	clearScreen();
	int opsi;
	while(true){
	cout << "=== Menu Manajemen Stok ===\n";
	cout << "1. Tambah Stok\n";
	cout << "2. Kurangi Stok\n";
	cout << "3. Lihat Semua Stok\n";
	cout << "0. Kembali\n";
	cout << "Pilih Opsi : ";
	cin >> opsi;
	
	if(cin.fail()){
		cout << "Opsi hanya berupa angka!\n";
		cin.clear();
		cin.ignore(1000, '\n');
		system("pause");
		clearScreen();
		continue;
	}
	switch (opsi){
		case 0:
			return;
		case 1:
			tambahStok(products, productCount);
			break;
		case 2:
			kurangStok(products, productCount);
			break;
		case 3:
			lihatStok(products, productCount);
			break;
		default:
			cout << "Pilih angka yang ada di opsi\n";
	}
	}
}

void tambahStok(Product products[], int productCount){
	string code;
	int jumlah;
	cin.get();
	clearScreen();
	cout << "===TAMBAH STOK===\n\n";
	cout << ">> Masukkan KODE Produk : ";
	cin >> code;
	
	Product* prdt = findProduct(products, productCount, code);
	
	if (prdt == nullptr){
		cout << "Produk Tidak Ditemukan!\n";
		system("pause");
		clearScreen();
		return;
	}else{
		cout << "Nama Produk : " << prdt->name << endl;
		cout << "Stok Tersedia : " << prdt->stock << endl;
	}
	
	cout << "\n>> Masukkan jumlah yang ingin ditambahkan ke Produk ini : ";
	cin >> jumlah;
	if (jumlah <= 0){
		cout << "Jumlah harus lebih dari 0\n";
		return;
	}else{
	prdt->stock += jumlah;
	cout << "\n---------------------------\n";	
	cout << "Stok Berhasil ditambahkan!\n";
	cout << "Jumlah Stok Pada Barang Ini adalah " << prdt->stock << endl << endl;
	}
	system("pause");
	clearScreen();
}

void kurangStok(Product products[], int productCount){
	string code;
	int jumlah;
	cin.get();
	clearScreen();
	cout << "=== KURANGI STOK===\n\n";
	cout << ">> Masukkan KODE Produk : ";
	cin >> code;
	
	Product* prdt = findProduct(products, productCount, code);
	
	if (prdt == nullptr){
		cout << "Produk Tidak Ditemukan!\n";
		system("pause");
		clearScreen();
		return;
	}else{
		cout << "Nama Produk : " << prdt->name << endl;
		cout << "Stok Tersedia : " << prdt->stock << endl;
	}
	
	cout << "\n>> Masukkan jumlah yang ingin dikurangi ke Produk ini : ";
	cin >> jumlah;
	
	if(jumlah <= 0){
    cout << "Jumlah harus lebih dari 0!\n";
	} else if (jumlah > prdt->stock){
    cout << "Stok tidak mencukupi!\n";
	} else{
    prdt->stock -= jumlah;
    cout << "\n---------------------------\n";
    cout << "Stok berhasil dikurangi!\n";
	cout << "Jumlah Stok Pada Barang Ini adalah " << prdt->stock << endl << endl;
	}
	system("pause");
	clearScreen();
}

void lihatStok(Product products[], int productCount) {
	cin.get();
	clearScreen();
    cout << "=== DAFTAR PRODUK ===\n";

    cout << "Kode\tNama\t\tHarga\tStok\n";

    for(int i = 0; i < productCount; i++) {
        cout << products[i].id << "\t"
             << products[i].name << "\t\t"
             << products[i].price << "\t"
             << products[i].stock << endl;
    }
    system("pause");
    clearScreen();
}