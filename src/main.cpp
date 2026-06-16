#include "model.hpp"
#include "cart.hpp"
#include "transaction.hpp"
#include "stocks.hpp"

int main() {
    Product products[100];
    int productCount = 2;
    int pilih;
    
    products[0] = Product{"BR001", "Indomie", 3500, 50};
    products[1] = Product{"BR002", "Aqua", 4000, 30};

    Transaction transactions[100];
    int transactionCount = 0;

    Cash cash;
    cash.balance = 100000;

    string cashierId = "KS001";

	do{ //ubah sesuai kebutuhan atau kalau mau testing
		cout << "Test menu\n";
		cout << "1. Transaction\n";
		cout << "2. Manage Stock\n";
		cout << "Select menu : ";
		cin >> pilih;
		switch (pilih){
			case 1:
    startTransaction(
        products,
        productCount,
        transactions,
        transactionCount,
        &cash,
        cashierId
    );
			case 2:
			Stokmenu(products, productCount);				
		}
	}while (pilih != 3);

    return 0;
}