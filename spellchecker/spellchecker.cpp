/*----------------------------------------------------------
 * Project: Spell Checker
 *
 * Date: 27-Nov-2024
 * Authors:
 *           A01751433 Israel González Huerta
 *           A01751729 Andrés Méndez Cortez
 ----------------------------------------------------------*/

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

std::string soundex(const std::string& str)
{
    if (str.empty()) {
        return "";
    }

    //keep the first character after capitalizing it
    char first_letter = std::toupper(str[0]);

    //map with the values for each valid letter
    std::unordered_map<char, char> soundex_map = {
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'},
        {'L', '4'},
        {'M', '5'}, {'N', '5'},
        {'R', '6'}
    };

    std::string result;
    result += first_letter;

    for (size_t i = 1; i < str.size(); ++i)
    {
        //make the current char into uppercase for the map
        char current_char = std::toupper(str[i]);

        //skips a character if it isn't a letter
        if (!std::isalpha(current_char))
        {
            continue;
        }

        char current_digit;
        if (soundex_map.count(current_char)) //.count() checks if what you sent as an argument is on the map
        {
            current_digit = soundex_map[current_char];
        } else {
            current_digit = '0';
        }

        //if a chracter is on the map then the correspoding digit is added
        if (current_digit != '0') {
            result += current_digit;
        }
    }

    //truncate or add zeros
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
        /*I believe the code would be faster if this was the other way around, where the soundex is the key and 
        all values with said soundex are joined in a linked list or some other structure. I decided to keep it this way 
        because while it is clear that the program takes time to iterate through the dictionary the implementation 
        is simpler this way and load times for each individual word are reasonable, specially in the context that
        the average word is more likely to be properly written than not*/
        dict[word] = soundex(word);
    }

    file.close();
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Please specify the name of the input file.\n";
        std::exit(1);
    }
    std::string file_name = argv[1];
    std::vector<word> words;

    //map with all the valid words
    std::string words_file = "words.txt";
    std::map<std::string, std::string> valid;
    make_dictionary(words_file, valid);
    
    if (read_words(file_name, words)) {
        for (word w : words) {
            //check 
            if (valid[w.text] == "")
            {
                std::cout << "\n\nUnrecognized word: \"" << w.text << "\". First found at line " << w.line << ", column " << w.column << ".\n";

                //Iterate through the entire map to find all the keys that have the same soundex code as the word
                std::ifstream file("words.txt");
                std::string palabra;

                bool next_word = 0;
                int sugg = 0;
                while (getline(file, palabra)) //most of this is to get the format right
                {
                    if (valid[palabra] == soundex(w.text))
                    {
                        sugg++;
                        if (sugg == 1)
                        {
                            std::cout << "Suggestions: ";
                            sugg++;
                        }

                        if (next_word)
                        {
                            std::cout << ", ";
                        }
                        std::cout << palabra;
                        next_word = 1;
                    }
                }
                if (sugg == 0)
                {
                std::cout << "No suggestions.\n";
                }
            }
        }
    } else {
        std::cout << "Unable to read file: "
            << file_name << "\n";
    }
    
}