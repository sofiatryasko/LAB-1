#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include "binary_io.hpp"
#include "book_info.hpp"
#include "character_info.hpp"
#include "book_database.hpp"
#include "tests/test_lists.cpp"
#include "tests/test_sorts.cpp"
#include "tests/test_series.cpp"
using namespace std;

void showHelp() {
    cout << "Справка по командам:" << '\n';
    cout << "load: загрузити записи з файла" << '\n';
    cout << "add: добавити запис" << '\n';
    cout << "edit: редактувати запис" << '\n';
    cout << "remove: видалити запис" << '\n';
    cout << "show: показати запис" << '\n';
    cout << "list: показати список записів" << '\n';
    cout << "findAuthor: показати список записів по автору" << '\n';
    cout << "save: зберегти зміни в файл" << '\n';
    cout << "test: запустити тести" << '\n';
    cout << "help: показати справку" << '\n';
    cout << "quit: вийти з програми" << '\n';
}

int main() {
    bookDatabase db("db.hex");
    cout << "Введіть \"help\", щоб вивести справку" << '\n' << '\n';

    while (true) {
        string action;
        cout << "> ";
        cin >> action;

        if (action == "load") {
            if (!db.load()) {
                cout << "Помилка: запис не знайдено!" << '\n';
            }
        }
        else if (action == "add") {
            cout << "Введіть дані запису:" << '\n';
            bookInfo bi = bookInfo::read();
            bi.genUid();
            cout << "індекс: " << bi.uid << '\n';
            db.add(bi);
        }
        else if (action == "edit") {
            cout << "Введіть старі данні запису:" << '\n';
            unsigned uid;
            cout << "індекс: ";
            cin >> uid;
            cout << "Введіть нові дані запису:" << '\n';
            bookInfo bi = bookInfo::read();
            if (!db.edit(bi, uid)) {
                cout <<"Помилка: запис не знайдено!" << '\n';
            }
        }
        else if (action == "remove") {
            cout << "Введіть дані видаляємого запису:" << '\n';
            unsigned uid;
            cout << "індекс: ";
            cin >> uid;
            if (!db.removeRec(uid)) {
                cout << "Помилка: запис не знайдено!" << '\n';
            }
        }
        else if (action == "show") {
            cout << "Введіть дані шуканого запису:" << '\n';
            unsigned uid;
            cout << "індекс: ";
            cin >> uid;
            auto res = db.find(uid);
            if (!res.success) {
                cout << "Помилка: запис не знайдено!" << '\n';
            }
            else {
                res.bi.print();
            }
        }
        else if (action == "list") {
            for (bookInfo bi: db.data) {
                bi.printShort();
            }
        }
        else if (action == "findAuthor") {
            cout << "Введіть автора: ";
            string author;
            cin >> author;
            auto books = db.findByAuthor(author);
            cout << "Знайдено книг: " << books.size() << '\n';
            for (bookInfo bi: books) {
                bi.printShort();
            }
        }
        else if (action == "save") {
            if (!db.save()) {
                cout << "Помилка: неможливо відкрити файл!" << '\n';
            }
        }
        else if (action == "test") {
            testLists();
            testSorts();
            testSeries();
        }
        else if (action == "help") {
            showHelp();
        }
        else if (action == "quit") {
            break;
        }
        else {
            cout << "Помилка: команда \"" << action << "\" не знайдена!" << '\n';
        }
        cout << '\n';
    }
}