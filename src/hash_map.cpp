#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "hash_table.h"

#define HT_PRIME_1 123
#define HT_PRIME_2 114


class HashTable {
private:
    struct HT_Item {
        bool _empty = true;
        std::string _key;
        std::string _value;
    };
    int get_hash (std::string s, const long num_buckets, const int attempt) {
        const int hash_a = hash(s, HT_PRIME_1, num_buckets);
        const int hash_b = hash(s, HT_PRIME_2, num_buckets);
        return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
    };
    int hash(std::string s, const int h_power, const long num_of_buckets) {
        long hash = 0;
        const int len_s = s.size();
        for (int i = 0; i < len_s; i++) {
            hash += (long)pow(h_power, len_s - (i+1)) * s[i];
            hash = hash % num_of_buckets;
        }
        return (int)hash;
    }
    int _count = 0;
    std::vector<HT_Item> _items;
public:
    HashTable(int size) : _items(size) {};
    HashTable() = delete;
    int size() const {
        return _items.size();
    }
    int count() const {
        return _count;
    }
    const std::vector<HT_Item>& items() const {
        return this -> _items;
    }
    void print_items() const {
        for (HT_Item item : _items) {
            if (item._empty) continue;
            std::cout << item._key << ": " << item._value << "\n";
        }
    }
    void insert(std::string& key, std::string& value) {
        HT_Item &item = keyLookup(key);
        item._key = key;
        item._value = value;
        item._empty = false;
        _count++;
    }
    std::string& operator[] (const std::string& key) {
        HT_Item &item = keyLookup(key);
        if (key != item._key) {
            item._key = key;
            item._value = "";
            item._empty = false;
            _count++;
        };
        return item._value;
    }

    std::string search(std::string& key) {
        HT_Item &item = keyLookup(key);
        if (key != item._key) return "-1";
        return item._value;
    }
    HT_Item& keyLookup(const std::string &key) {
        int index = get_hash(key, size(), 0);
        HT_Item &item = _items[index];
        int attempts = 1;
        while (!item._empty) {
            if (key == item._key) return item;
            index = get_hash(key, size(), attempts);
            item = _items[index];
            attempts++; 
        }
        return item;
    }
    void deleteItem(std::string& key) {
        HT_Item &item = keyLookup(key);
        if (key != item._key) throw std::out_of_range("Key doesn't exist");
        item._key = "";
        item._value = "";
        item._empty = true;
    }
    
    
};

/*
TODO: Make Hash Table Resizeable
*/


int main() {
    HashTable ht(5);

    std::string k[] = {"1", "2", "3" , "4", "5"};
    std::string v[] = {"6", "7", "8", "9", "10"};

    ht["0"] = "1";
    ht.print_items();
    std::cout <<  ht["0"];
    

    
}