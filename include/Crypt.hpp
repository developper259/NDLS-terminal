#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Key {
private:
    std::vector<std::pair<char, char>> _keys;
    std::string _loc;
    int min = 0;
    int max = 500;
    int place = 72;
    std::string letters;

public:
    Key(const std::string& loc) : _loc(loc), letters("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ") {}

    void randomEncoding() {
        std::vector<char> encoding;
        while (true) {
            int rdm = rand() % letters.length();
            char c = letters[rdm];

            bool found = false;
            for (char existing : encoding) {
                if (existing == c) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                encoding.push_back(c);
            }

            if (encoding.size() == letters.length()) {
                break;
            }
        }

        for (size_t index = 0; index < encoding.size(); index++) {
            _keys.push_back(std::make_pair(letters[index], encoding[index]));
        }
    }



    void secure() {
        if (_loc.empty() || _keys.empty()) {
            return;
        }

        int n = rand() % (max - min + 1) + min;
        std::string nb = gen_nb_key_line(n) + "\n";

        std::ofstream file(_loc);
        if (file.is_open()) {
            file << nb;

            for (const auto& keyPair : _keys) {
                std::string line;
                for (int i = 0; i < 500; i++) {
                    if (i != n) {
                        int rdm = rand() % letters.length();
                        char c = letters[rdm];
                        line += c;
                    } else {
                        line += keyPair.second;
                    }
                }

                file << line << "\n";
            }

            file.close();
        }
    }

    void get() {
        std::ifstream file(_loc);
        if (file.is_open()) {
            std::string nb_line;
            std::getline(file, nb_line);
            std::string nb;
            int n = nb_line.length() / place;

            for (int i = 1; i <= n; i++) {
                nb += nb_line[i * place - 1];
            }

            try {
                n = std::stoi(nb);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error to get NCkey" << std::endl;
                exit(0);
            }

            std::vector<std::pair<char, char>> encoding;

            for (size_t i = 0; i < letters.length(); i++) {
                std::string line;
                std::getline(file, line);
                if (!line.empty()) {
                    encoding.push_back(std::make_pair(letters[i], line[n]));
                }
            }

            if (encoding.size() == letters.length()) {
                _keys = encoding;
            }

            file.close();
        }
    }

    std::vector<std::pair<char, char>> getKeys() {
        return _keys;
    }

private:
    std::string gen_nb_key_line(int n) {
        std::string n_str = std::to_string(n);
        std::vector<std::string> t;

        for (size_t i = 0; i < n_str.length(); i++) {
            std::string c;
            for (int j = 0; j < place; j++) {
                int rdm = rand() % letters.length();
                if (j == place - 1) {
                    c += n_str[i];
                } else {
                    c += letters[rdm];
                }
            }

            t.push_back(c);
        }

        return join(t);
    }

    std::string get_nb_key_line(const std::string& l) {
        std::string l_str = l.substr(0, l.length() - 1);
        size_t n = l_str.length() / place;
        int nb = 0;
        std::string t;

        for (size_t i = 0; i < n; i++) {
            nb += place;
            t += l_str[nb - 1];
        }

        return t;
    }

    std::string join(const std::vector<std::string>& strings) {
        std::string result;
        for (const auto& str : strings) {
            result += str;
        }
        return result;
    }
};

class Crypt {
private:
    std::string _loc;
    Key _key;

public:
    Crypt(const std::string& loc) : _loc(loc), _key(loc) {
        if (!fileExists(loc)) {
            _key.randomEncoding();
            _key.secure();
        } else {
            _key.get();
        }
    }

    std::string encode(const std::string& msg) {
        std::string encoding;
        for (char c : msg) {
            char encodedChar = encodingLetter(c);
            if (encodedChar != '\0') {
                encoding += encodedChar;
            }
        }
        return encoding;
    }

    std::string decode(const std::string& msg) {
        std::string decoding;
        for (char c : msg) {
            char decodedChar = decodingLetter(c);
            if (decodedChar != '\0') {
                decoding += decodedChar;
            }
        }
        return decoding;
    }

private:
    bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }

    char encodingLetter(char letter) {
        for (const auto& keyPair : _key.getKeys()) {
            if (keyPair.first == letter) {
                return keyPair.second;
            }
        }
        return '\0';
    }

    char decodingLetter(char letter) {
        for (const auto& keyPair : _key.getKeys()) {
            if (keyPair.second == letter) {
                return keyPair.first;
            }
        }
        return '\0';
    }
};
