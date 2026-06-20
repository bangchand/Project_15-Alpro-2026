#include "core.hpp"

void headerKeranjangUI();

void CartItem::setItem(Product* product, int qty) {
    productId = product->id;
    productName = product->name;
    price = product->price;
    quantity = qty;
    subtotal = price * quantity;
}

void CartItem::addQuantity(int qty) {
    quantity += qty;
    subtotal = price * quantity;
}

CartItem* findCartItem(CartItem cart[], int cartCount, string productId) {
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].productId == productId) {
            return &cart[i];
        }
    }
    return nullptr;
}

Product* findProduct(Product products[], int productCount, string productId) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            return &products[i];
        }
    }
    return nullptr;
}

double calculateTotal(CartItem cart[], int cartCount) {
    double total = 0;
    for (int i = 0; i < cartCount; i++) {
        total += cart[i].subtotal;
    }
    return total;
}

void addToCart(
    Product products[],
    int productCount,
    CartItem cart[],
    int &cartCount,
    string productId,
    int qty
) {
    Product* product = findProduct(products, productCount, productId);

    if (product == nullptr) {
        cout << "Produk tidak ditemukan.\n";
        return;
    }

    CartItem* item = findCartItem(cart, cartCount, productId);

    int currentQty = 0;
    if (item != nullptr) {
        currentQty = item->quantity;
    }

    if (product->stock < currentQty + qty) {
        cout << "Stok tidak cukup.\n";
        return;
    }

    if (item != nullptr) {
        item->addQuantity(qty);
    } else {
        cart[cartCount].setItem(product, qty);
        cartCount++;
    }

    cout << "Produk berhasil ditambahkan.\n";
}

void showCart(CartItem cart[], int cartCount) {
    bersihkanLayar();

    if (cartCount == 0) {
        cout << YELLOW << "Keranjang kosong.\n" << RESET;
        return;
    }

    headerKeranjangUI();

    for (int i = 0; i < cartCount; i++) {
        cout << left << setw(20) << cart[i].productName
             << setw(10) << ("x" + to_string(cart[i].quantity))
             << "Rp " << static_cast<long long>(cart[i].subtotal) << endl;
    }

    cout << CYAN << "==================================================\n" << RESET;
}

void headerKeranjangUI() {
    cout << CYAN << "==================================================\n";
    cout << "                    KERANJANG                     \n";
    cout << "==================================================\n" << RESET;
    cout << left << setw(20) << "NAMA PRODUK" << setw(10) << "JUMLAH" << "SUBTOTAL\n";
    cout << "--------------------------------------------------\n";
}
