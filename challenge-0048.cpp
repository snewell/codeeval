#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    bool isOdd(unsigned int val)
    {
        return (val & 1);
    }
    
    bool isVowel(char c)
    {
        switch(std::tolower(c))
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'y':
            return true;
            break;
            
        default:
            return false;
        }
    }
    
    std::size_t countLetters(std::string const &val)
    {
        std::size_t ret{0};
        std::for_each(std::begin(val), std::end(val), [&ret](char c) {
            if(std::isalpha(c))
            {
                ++ret;
            }
        });
        return ret;
    }
    
    struct Customer
    {
        Customer(std::string name)
          : my_name{std::move(name)},
            my_letters{countLetters(my_name)},
            my_vowels{0},
            my_consts{0}
        {
            std::for_each(std::begin(my_name), std::end(my_name), [this](char c) {
                if(std::isalpha(c))
                {
                    if(isVowel(c))
                    {
                        ++my_vowels;
                    }
                    else
                    {
                        ++my_consts;
                    }
                }
            });
        }
        
        std::string my_name;
        std::size_t my_letters;
        std::size_t my_vowels;
        std::size_t my_consts;
    };
    
    double evenLength(Customer const &c)
    {
        return (c.my_vowels * 1.5);
    }
    
    double oddLength(Customer const &c)
    {
        return c.my_consts;
    }
    
   struct Product
    {
        using SSFn = double (*) (Customer const &);
        Product(std::string name)
          : my_name{std::move(name)},
            my_letters{countLetters(my_name)},
            my_ssfn{isOdd(my_letters) ? oddLength : evenLength}
        {
        }
        
        std::string my_name;
        std::size_t my_letters;
        SSFn my_ssfn;
    };
    
    struct Pair
    {
        using CustomerIt = std::vector<Customer>::const_iterator;
        using ProductIt  = std::vector<Product>::const_iterator;
        
        Pair(CustomerIt cust, ProductIt prod)
          : my_customer{std::move(cust)},
            my_product{std::move(prod)},
            my_ss{(*my_product).my_ssfn(*my_customer)}
        {
        }
        
        CustomerIt my_customer;
        ProductIt my_product;
        double my_ss;
    };
    
    bool operator < (Pair const &lhs, Pair const &rhs)
    {
        return (lhs.my_ss < rhs.my_ss);
    }
    
    bool operator == (Pair const &lhs, Pair const &rhs)
    {
        return (lhs.my_ss == rhs.my_ss);
    }
    
    double calculateMaxSs(std::vector<Customer> const &customers,
                          std::vector<Product>  const &products)
    {
        std::vector<Pair> pairs;
        pairs.reserve(customers.size() * products.size());
        for(auto custIt = std::begin(customers); custIt != std::end(customers); ++custIt)
        {
            for(auto prodIt = std::begin(products); prodIt != std::end(products); ++prodIt)
            {
                pairs.emplace_back(Pair{custIt, prodIt});
            }
        }
        std::sort(std::begin(pairs), std::end(pairs));
        
        auto ret = 0.0;
        while(!(pairs.empty()))
        {
            auto first = pairs.begin();
            ret += (*first).my_ss;
            auto custId = (*first).my_customer;
            auto prodId = (*first).my_product;
//            std::cout << (*custId).my_name << '/' << (*prodId).my_name << " -- " << (*first).my_ss << '\n';
            auto rem = std::remove_if(std::begin(pairs), std::end(pairs), [custId, prodId](Pair const &p) {
                return ((p.my_customer == custId) || (p.my_product == prodId));
            });
            pairs.erase(rem, std::end(pairs));
        }
        return ret;
    }
    
    template <typename IT, typename T>
    void readData(IT start, IT end, std::vector<T> &data)
    {
        while(start != end)
        {
            auto it = std::find(start, end, ',');
            data.emplace_back(std::string{start, it});
            if(it != end)
            {
                ++it;
            }
            start = it;
        }
    }
    
    
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    std::string line;
    
    std::vector<Customer> customers;
    std::vector<Product> products;
    
    std::getline(input, line);
    while(input)
    {
        if(line.length() > 0)
        {
            auto split = std::find(std::begin(line), std::end(line), ';');
            readData(std::begin(line), split, customers);
            ++split;
            readData(split, std::end(line), products);
        
            auto ss = calculateMaxSs(customers, products);
            std::cout << std::setprecision(2) << std::fixed << ss << '\n';
            customers.erase(std::begin(customers), std::end(customers));
            products.erase(std::begin(products), std::end(products));
        }
        std::getline(input, line);
    }
    return 0;
}
