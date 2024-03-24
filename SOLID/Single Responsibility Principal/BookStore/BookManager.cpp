#include<bits/stdc++.h>
using namespace std;

class Book {
public:
    string title, author;  // Title and author of the book.
    double price;          // Price of the book.
};

class BookManager {
private:
    vector<Book> books;  // Vector to store books.
public:
    // Function to add a book to the collection.
    void addBook(const string &title, const string &author, const double &price) {}

    // Function to remove a book from the collection.
    void removeBook(const string &title) {}

    // Function to display all books in the collection.
    void displayAllBooks() {}
};