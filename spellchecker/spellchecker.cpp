#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <bits/stdc++.h>

struct word {
    std::string text;
    int line;
    int column;
};

bool read_words(const std::string input_file_name, std::vector<word>& words)
{
    std::ifstream input_file(input_file_name);
    if (input_file.fail()) {
        return false;
    }
    std::regex reg_exp("[a-zA-Z]+");
    std::smatch match;
    std::string text;
    int line = 0;
    int column = 0;

    while (std::getline(input_file, text)) {
        ++line;
        column = 1;
        while (std::regex_search(text, match, reg_exp)) {
            column += match.position();

            //make text into lowercase
            std::string match_lower = match.str();
            std::transform(match_lower.begin(), match_lower.end(), match_lower.begin(), ::tolower);


            int presente = 0;
            for (int i = 0; i < words.size(); i++)
            {
                if (match_lower == words[i].text)
                {
                    presente = 1;
                }
            }
            if (presente == 0)
            {
                words.push_back({match_lower, line, column});
            }

            column += match.length();
            text = match.suffix().str();
        }
    }
    return true;
}

/*
std::string get_soundex(std::string palabra)
{
    std::vector<char> palabra_array;

    //convert the string into a vector for ease of use
    for(int i = 0; i < palabra.length(); i++)
    {
        palabra_array.push_back(std::tolower(palabra[i]));
    }

    //this is to test that the words are being read properly
    
    std::cout << "palabra: " << palabra << "\n";
    std::cout << "sizeof(palabra_array): " << palabra_array.size() << "\n";
    for(int i = 0; i < palabra_array.size(); i++)
    {
        std::cout << palabra_array[i];
    }
    std::cout << "\n";
    
    

    std::string soundex = "";
    std::string add = "";

    std::cout << "------------------------\n"; 
    std::cout << "palabra: " << palabra << "\n";
    std::cout << "palabra_array.size(): " << palabra_array.size() << "\n";
    int desfase = 0;
    for(int i = 0; i < palabra_array.size(); i++)
    {
        std::cout << "i: " << i << "\n";
        int j = i - desfase;

        std::cout << "Palabra para el loop: ";
        for(int k = 0; k < palabra_array.size(); k++)
        {
            std::cout << palabra_array[k];
        }

        std::cout << "\nValor en palabra_array[" << j << "]: " << palabra_array.at(j) << "\n";

        if(palabra_array.at(j) == 'a' || palabra_array.at(j) == 'e' || palabra_array.at(j) == 'i' || palabra_array.at(j) == 'o' 
            || palabra_array.at(j) == 'u' || palabra_array.at(j) == 'h' || palabra_array.at(j) == 'w' || palabra_array.at(j) == 'y')
        {
            palabra_array.erase(palabra_array.begin() + j);
            desfase++;

            std::cout << "Se borró algo \n";
            std::cout << "palabra_array después de haber borrado: ";
            for(int k = 0; k < palabra_array.size(); k++)
            {
                std::cout << palabra_array[k];
            }
            std::cout << "\n";
        }
        
        if(palabra[i] == 'b' || palabra[i] == 'f' || palabra[i] == 'p' || palabra[i] == 'v')
        {
            add = "1";
            soundex.append(add);
        }
        if(palabra[i] == 'c' || palabra[i] == 'g' || palabra[i] == 'j' || palabra[i] == 'k' || palabra[i] == 'q' 
            || palabra[i] == 's' || palabra[i] == 'x' || palabra[i] == 'z')
        {
            add = "2";
            soundex.append(add);
        }
        if(palabra[i] == 'd' || palabra[i] == 't')
        {
            add = "3";
            soundex.append(add);
        }
        if(palabra[i] == 'l')
        {
            add = "4";
            soundex.append(add);
        }
        if(palabra[i] == 'm' || palabra[i] == 'n')
        {
            add = "5";
            soundex.append(add);
        }
        if(palabra[i] == 'r')
        {
            add = "6";
            soundex.append(add);
        }
        
        
    }

    std::cout << "palabra_array final: ";
    for(int m = 0; m < palabra_array.size(); m++)
    {
        std::cout << palabra_array[m];
    }
    std::cout << "\n";
    return "1";
}
*/

std::string soundex(const std::string& str) {
    if (str.empty()) {
        return "";
    }

    // Map letters to Soundex digits
    std::unordered_map<char, char> soundex_map = {
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'},
        {'L', '4'},
        {'M', '5'}, {'N', '5'},
        {'R', '6'}
    };

    // Uppercase first character and retain it
    char first_letter = std::toupper(str[0]);

    std::string result;
    result += first_letter;

    // Convert the rest of the string to Soundex code
    for (size_t i = 1; i < str.size(); ++i) {
        char current_char = std::toupper(str[i]);

        // Ignore non-alphabetical characters
        if (!std::isalpha(current_char)) {
            continue;
        }

        // Get the corresponding digit from the map
        char current_digit = soundex_map.count(current_char) ? soundex_map[current_char] : '0';

        // Include the digit unless it's a vowel (vowels map to '0')
        if (current_digit != '0') {
            result += current_digit;
        }
    }

    // Pad with zeros or truncate to ensure the length is 7
    result = result.substr(0, 7);
    while (result.size() < 7) {
        result += '0';
    }

    return result;
}

void make_dictionary(const std::string input_file_name, std::map<std::string, std::string>& dict)
{
    std::ifstream file("words.txt");
    std::string word;

    while (getline(file, word))
    {
        //adds every word to the dictionary, the word itself is the key and the soundex code is the value 
        dict[word] = soundex(word);
    }

    file.close();
}

int main()
{
    std::string file_name = "tooinkle.txt";
    std::vector<word> words;

    //map with all the valid words
    std::string words_file = "words.txt";
    std::map<std::string, std::string> valid;
    make_dictionary(words_file, valid);

    std::cout << "Valido: " << valid["come"] << "\n"; 
    std::cout << "No valido: " << valid["ofpamfs"] << "\n";
    
    if (read_words(file_name, words)) {
        for (word w : words) {
            //check 
            if (valid[w.text] == "")
            {
                std::cout << "\n\nUnrecognized word: \"" << w.text << "\". First found at line " << w.line << ", column " << w.column
            << ".\nSuggestions: ";

            //Iterate through the entire map to find all the keys that have the same soundex code as te word



            }
        }
    } else {
        std::cout << "Unable to read file: "
            << file_name << "\n";
    }
    
}