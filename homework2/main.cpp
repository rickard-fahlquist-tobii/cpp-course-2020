#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string>
#include <filesystem>

#include "Blocks.h"

using namespace std::string_literals;


struct Account {
    hw2::Text<10> accno;
    hw2::Number<5> balance;

    friend std::ostream& operator<<(std::ostream& os, const Account& a)
    {
        os << a.accno.value();
        os << a.balance.value();
        return os;
    }

    /*
    friend std::istream& operator>>(const std::istream& is, Account& a)
    {
        std::string accno;
        std::string balanc;

        is >> a.accno.value()
    }
     */
};

template<typename ACCOUNT_T>
class BlockFile
{
public:

    struct iterator
    {
        std::fstream& _file;
        size_t pos;
        const ACCOUNT_T& operator*() {
            ACCOUNT_T out;

        }
    };

    BlockFile(std::string const & file_name)
    {
        namespace fs = std::filesystem;

        if (!fs::exists(file_name)) {
            std::fstream tmp(file_name, std::ios::out);
        }

        _file.open(file_name, std::ios::out | std::ios::in);
    }

    ~BlockFile() {
        if (_file.is_open()) {
            _file.close();
        }
    }

    iterator& begin() {
        iterator iter;
        iter.file = _file;
        iter.pos = 0;
    }
/*
    iterator& operator[](size_t pos) {
        return iterator;
    }
*/

    void append(ACCOUNT_T&& b)
    {
        _file.seekp(0, std::ios::end);
        _file << b.accno.value();
        _file << b.balance.value();
    }

    void read(unsigned ix, ACCOUNT_T& b)
    {
        _file.seekg(sizeof(ACCOUNT_T) * ix, std::ios::beg);

        _file.read(reinterpret_cast<char*>(&b), sizeof(ACCOUNT_T));
    }

private:
    std::fstream _file;


};


int main(int argc, char** argv)
{
    BlockFile<Account> bf("accounts.dat");

    Account acc_rickard;
    acc_rickard.accno.value("123-456"s);
    acc_rickard.balance.value(11111);

    Account acc_devaraj;
    acc_devaraj.accno.value("222-456"s);
    acc_devaraj.balance.value(12345);

    bf.append(std::move(acc_rickard));
    bf.append(std::move(acc_devaraj));

    Account out;
    bf.read(1, out);

    std::cout << "out: " << out << "\n";

    return 0;
}
