#include <iostream>
#include <string>
#include <unordered_map>

// Function to get the Soundex code for a character
char getSoundexCode(char c) {
    c = toupper(c);
    std::unordered_map<char, char> mapping = {
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'},
        {'L', '4'},
        {'M', '5'}, {'N', '5'},
        {'R', '6'}
    };
    auto it = mapping.find(c);
    return it != mapping.end() ? it->second : '0';  // Default to '0' for non-mapped characters
}

// Function to compare characters and previous code
std::string comparison(char ch, char prev_code) {
    if (ch != '0' && ch != prev_code) {
        return std::string(1, ch);
    } else {
        return "";
    }
}

// Function to map the name to Soundex codes
std::string numMap(const std::string& name, char prev_code) {
    std::string soundex;
    for (size_t i = 1; i < name.length(); ++i) {
        char ch = getSoundexCode(name[i]);
        std::string code = comparison(ch, prev_code);
        if (!code.empty()) {
            soundex += code;
            prev_code = ch;
        }
    }
    return soundex;
}

// Function to generate the Soundex for a name
std::string generateSoundex(const std::string& name) {
    if (name.empty()) {
        return "";
    } else {
        std::string soundex(1, toupper(name[0]));
        char prev_code = getSoundexCode(soundex[0]);
        soundex += numMap(name, prev_code);
        if (soundex.length() > 4) {
            soundex = soundex.substr(0, 4);
        }
    }

    // Pad with zeros if necessary
    soundex = soundex.append(4 - soundex.length(), '0');
    
    return soundex;
}

int main() {
    // Test cases
    std::cout << generateSoundex("Robert") << std::endl;  // Output: R163
    std::cout << generateSoundex("Rupert") << std::endl;  // Output: R163
    std::cout << generateSoundex("Rubin") << std::endl;   // Output: R150
    std::cout << generateSoundex("Ashcraft") << std::endl;// Output: A261
    std::cout << generateSoundex("Ashcroft") << std::endl;// Output: A261
    std::cout << generateSoundex("Pfister") << std::endl; // Output: P236

    return 0;
}
