#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <bitset>
#include <sstream>

class Message {
private:
    std::string text;
    static const int CHAR_SIZE = 8;
    static const int ALPHABET_SIZE = 256;
    std::vector<char> characters;
    std::vector<int> frequencyOfChars;

public:
    Message(const std::string& text) : text(text) {
        if (text.length() <= 0) {
            throw std::runtime_error("Error: Message size <= 0");
        }
        characters = getChars();
        frequencyOfChars = buildFrequencyTable();
    }

    std::string getMessage() const { return text; }
    int getTotalFrequency() const { return text.length(); }
    const std::vector<char>& getCharacters() const { return characters; }
    const std::vector<int>& getFrequencies() const { return frequencyOfChars; }
    bool isEmpty() const { return getTotalFrequency() == 0; }

    int getSize() const {
        return CHAR_SIZE * getTotalFrequency();
    }

private:
    std::vector<char> getChars() {
        std::unordered_map<char, bool> seen;
        std::vector<char> uniqueChars;
        for (const char& ch : text) {
            if (seen.find(ch) == seen.end()) {
                uniqueChars.push_back(ch);
                seen[ch] = true;
            }
        }
        return uniqueChars;
    }

public:
    int calcFrequencyOfChar(const char ch) const {
        int charFreq = 0;
        for (const char& c : text) {
            if (c == ch) {
                charFreq++;
            }
        }
        return charFreq;
    }

private:
    std::vector<int> buildFrequencyTable() {
        std::vector<int> frequencies(ALPHABET_SIZE, 0);
        for (const char& ch : text) {
            frequencies[ch]++;
        }
        return frequencies;
    }

public:
    std::string binaryCode() const {
        std::stringstream binarySequence;
        for (const char& ch : text) {
            binarySequence << convertBinary(static_cast<int>(ch));
        }
        return binarySequence.str();
    }
    
    std::vector<std::string> binaryOfChars() const {
        std::vector<std::string> binarySequence(characters.size());
        for (size_t i = 0; i < characters.size(); ++i) {
            binarySequence[i] = convertBinary(static_cast<int>(characters[i]));
        }
        return binarySequence;
    }

    std::string convertBinary(int decimal) const {
        std::bitset<CHAR_SIZE> binary(decimal);
        return binary.to_string();
    }
};
