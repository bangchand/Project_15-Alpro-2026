#pragma once
#include "product.hpp"
#include <string>

using namespace std;

const int MAX_CART = 100;

struct CartItem {
    string productId;
    string productName;
    double price;
    int quantity;
    double subtotal;

    void setItem(Product* product, int qty);
    void addQuantity(int qty);
};

CartItem* findCartItem(CartItem cart[], int cartCount, string productId);
Product* findProduct(Product products[], int productCount, string productId);
double calculateTotal(CartItem cart[], int cartCount);
void addToCart(Product products[], int productCount, CartItem cart[], int &cartCount, string productId, int qty);
void showCart(CartItem cart[], int cartCount);
