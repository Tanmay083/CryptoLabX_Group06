#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

using namespace std;

double ENGLISH_FREQ[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074
};

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Remove spaces and keep only letters
string clean_ciphertext(const string& text) {
    string result;

    for (char c : text) {
        if (isalpha(c))
            result += toupper(c);
    }

    return result;
}

// Find repeated patterns
map<string, vector<int>> find_repeated_patterns(
    const string& text, int length) {

    map<string, vector<int>> patterns;

    for (int i = 0; i <= (int)text.length() - length; i++) {
        string pattern = text.substr(i, length);
        patterns[pattern].push_back(i);
    }

    map<string, vector<int>> repeated;

    for (auto& p : patterns) {
        if (p.second.size() > 1)
            repeated[p.first] = p.second;
    }

    return repeated;
}

// Calculate distances between repeated patterns
vector<int> calculate_distances(
    const map<string, vector<int>>& patterns) {

    vector<int> distances;

    for (auto& p : patterns) {
        const vector<int>& positions = p.second;

        for (int i = 1; i < (int)positions.size(); i++)
            distances.push_back(positions[i] - positions[i - 1]);
    }

    return distances;
}

// Find factors of distances
map<int, int> find_factors(const vector<int>& distances) {

    map<int, int> factor_count;

    for (int distance : distances) {
        for (int factor = 2; factor <= 20; factor++) {
            if (distance % factor == 0)
                factor_count[factor]++;
        }
    }

    return factor_count;
}

// Kasiski analysis
int kasiski_analysis(const string& text) {

    vector<int> distances;

    for (int length = 3; length <= 5; length++) {

        auto repeated = find_repeated_patterns(text, length);
        auto d = calculate_distances(repeated);

        if (length == 5)
            distances = d;
    }

    if (distances.empty())
        return 0;

    int result = distances[0];

    for (int d : distances)
        result = gcd(result, d);

    return result;
}

// Index of coincidence
double calculate_ic(const string& text) {

    if (text.length() < 2)
        return 0.0;

    int frequency[26] = {0};

    for (char c : text)
        frequency[c - 'A']++;

    double numerator = 0;

    for (int i = 0; i < 26; i++)
        numerator += frequency[i] * (frequency[i] - 1);

    double denominator = text.length() * (text.length() - 1);

    return numerator / denominator;
}

// Divide ciphertext into groups
vector<string> split_into_groups(
    const string& text, int key_length) {

    vector<string> groups(key_length);

    for (int i = 0; i < (int)text.length(); i++)
        groups[i % key_length] += text[i];

    return groups;
}

// Frequency analysis
vector<int> frequency_analysis(const string& group) {

    vector<int> frequency(26, 0);

    for (char c : group)
        frequency[c - 'A']++;

    return frequency;
}

// Find probable Caesar shift using chi-square
int find_shift(const string& group) {

    vector<int> observed = frequency_analysis(group);

    int n = group.length();
    double best_score = 1e18;
    int best_shift = 0;

    for (int shift = 0; shift < 26; shift++) {

        double score = 0;

        for (int i = 0; i < 26; i++) {

            int cipher_index = (i + shift) % 26;
            double expected = ENGLISH_FREQ[i] * n;

            if (expected > 0) {
                double difference =
                    observed[cipher_index] - expected;

                score +=
                    (difference * difference) / expected;
            }
        }

        if (score < best_score) {
            best_score = score;
            best_shift = shift;
        }
    }

    return best_shift;
}

// Find complete key
string find_key(const vector<string>& groups) {

    string key;

    for (const string& group : groups) {
        int shift = find_shift(group);
        key += char('A' + shift);
    }

    return key;
}

// Vigenere decryption
string vigenere_decrypt(
    const string& ciphertext,
    const string& key) {

    string plaintext;

    for (int i = 0; i < (int)ciphertext.length(); i++) {

        int c = ciphertext[i] - 'A';
        int k = key[i % key.length()] - 'A';

        int p = (c - k + 26) % 26;

        plaintext += char('A' + p);
    }

    return plaintext;
}

// Vigenere encryption
string vigenere_encrypt(
    const string& plaintext,
    const string& key) {

    string ciphertext;

    for (int i = 0; i < (int)plaintext.length(); i++) {

        int p = plaintext[i] - 'A';
        int k = key[i % key.length()] - 'A';

        int c = (p + k) % 26;

        ciphertext += char('A' + c);
    }

    return ciphertext;
}

// Verification
bool verify(
    const string& original,
    const string& plaintext,
    const string& key) {

    string encrypted = vigenere_encrypt(plaintext, key);

    return encrypted == original;
}

int main() {

    cout << "========================================\n";
    cout << "      VIGENERE CRYPTANALYSIS\n";
    cout << "========================================\n\n";

    ifstream file("../inputs/ciphertext.txt");

    if (!file) {
        cout << "Error: Could not open ciphertext.txt\n";
        return 1;
    }

    string input;
    string line;

    while (getline(file, line))
        input += line;

    file.close();

    string ciphertext = clean_ciphertext(input);

    cout << "Cleaned ciphertext length: "
         << ciphertext.length() << "\n\n";


    // ---------------- KASISKI ----------------

    cout << "========================================\n";
    cout << "          KASISKI EXAMINATION\n";
    cout << "========================================\n\n";

    int key_length = kasiski_analysis(ciphertext);

    cout << "GCD of 5-letter repeated-pattern distances = "
         << key_length << "\n";

    cout << "Estimated key length = "
         << key_length << "\n\n";


    // ---------------- IC BONUS ----------------

    cout << "========================================\n";
    cout << "       INDEX OF COINCIDENCE BONUS\n";
    cout << "========================================\n\n";

    cout << fixed << setprecision(4);

    cout << "Whole ciphertext IC = "
         << calculate_ic(ciphertext) << "\n";

    vector<string> groups =
        split_into_groups(ciphertext, key_length);

    double total_ic = 0;

    for (int i = 0; i < key_length; i++) {

        double ic = calculate_ic(groups[i]);

        total_ic += ic;

        cout << "Group " << i + 1
             << " IC = " << ic << "\n";
    }

    cout << "Average IC = "
         << total_ic / key_length << "\n\n";


    // ---------------- FREQUENCY ----------------

    cout << "========================================\n";
    cout << "          FREQUENCY ANALYSIS\n";
    cout << "========================================\n\n";

    for (int i = 0; i < key_length; i++) {

        vector<int> frequency =
            frequency_analysis(groups[i]);

        cout << "Group " << i + 1 << ":\n";

        cout << "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n";

        for (int j = 0; j < 26; j++)
            cout << frequency[j] << " ";

        cout << "\n\n";
    }


    // ---------------- KEY ----------------

    cout << "========================================\n";
    cout << "             KEY RECOVERY\n";
    cout << "========================================\n\n";

    string key = find_key(groups);

    for (int i = 0; i < key_length; i++) {

        int shift = key[i] - 'A';

        cout << "Group " << i + 1
             << " -> Shift = "
             << shift
             << " -> "
             << key[i]
             << "\n";
    }

    cout << "\nRecovered Key: "
         << key << "\n\n";


    // ---------------- DECRYPT ----------------

    string plaintext =
        vigenere_decrypt(ciphertext, key);

    cout << "========================================\n";
    cout << "        RECOVERED PLAINTEXT\n";
    cout << "========================================\n\n";

    cout << plaintext << "\n\n";


    // ---------------- VERIFY ----------------

    cout << "========================================\n";
    cout << "            VERIFICATION\n";
    cout << "========================================\n\n";

    if (verify(ciphertext, plaintext, key)) {
        cout << "SUCCESS\n";
        cout << "Re-encrypted ciphertext matches the original ciphertext.\n";
    }
    else {
        cout << "FAILED\n";
        cout << "Re-encrypted ciphertext does not match the original ciphertext.\n";
    }

    return 0;
}