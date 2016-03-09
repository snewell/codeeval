#include <fstream>
#include <iostream>
#include <string>

namespace
{
    std::string const suffixes[] =
    {
        "",
        "Thousand",
        "Million",
        "Billion"
    };

    std::string const singles[] =
    {
        "One", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine"
    };

    std::string const tens[] =
    {
        "Twenty", "Thirty", "Forty", "Fifty",
        "Sixty", "Seventy", "Eighty", "Ninety"
    };

    std::string const teens[] =
    {
        "Ten", "Eleven", "Twelve", "Thirteen",
        "Fourteen", "Fifteen", "Sixteen",
        "Seventeen", "Eighteen", "Nineteen"
    };

    void writeChunk(unsigned int val, unsigned int suffixId)
    {
        if(val > 999)
        {
            writeChunk(val / 1000, suffixId + 1);
            val %= 1000;
        }
        if(val > 0)
        {
            auto hundredsDigit =val / 100;
            if(hundredsDigit > 0)
            {
                std::cout << singles[hundredsDigit - 1] << "Hundred";
            }
            auto tensDigit = (val % 100) / 10;
            auto singlesDigit = val % 10;
            switch(tensDigit)
            {
            case 1:
                std::cout << teens[singlesDigit];
                break;

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                std::cout << tens[tensDigit - 2];
                //fall through
            case 0:
                if(singlesDigit > 0)
                {
                    std::cout << singles[singlesDigit - 1];
                }
                break;
            }

            std::cout << suffixes[suffixId];
        }
    }
}

int main(int argc, char ** argv)
{
    std::ifstream input{argv[1]};
    unsigned int val;

    input >> val;
    while(input)
    {
        writeChunk(val, 0);
        std::cout << "Dollars\n";
        input >> val;
    }
    return 0;
}
