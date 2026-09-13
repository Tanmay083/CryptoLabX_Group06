#include "kasiski_analysis.h"
#include "ic_analysis.h"
#include "vigenere_frequency.h"
#include "vigenere_cipher.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


int main() {

    // --------------------------------------------------------
    // 1. Read Ciphertext
    // --------------------------------------------------------

    std::ifstream input(
        "attacks/vigenere_cipher_attack/data/ciphertext.txt"
    );

    if (!input) {

        std::cout
            << "Error: Could not open ciphertext.txt\n";

        return 1;
    }


    std::string ciphertext;
    std::string line;


    while (std::getline(input, line)) {
        ciphertext += line;
    }


    // --------------------------------------------------------
    // 2. Preprocess Ciphertext
    // --------------------------------------------------------

    ciphertext =
        clean_ciphertext(ciphertext);


    std::cout
        << "========================================\n";

    std::cout
        << " VIGENERE CIPHER CRYPTANALYSIS\n";

    std::cout
        << "========================================\n\n";


    std::cout
        << "Ciphertext Length : "
        << ciphertext.length()
        << "\n\n";


    // --------------------------------------------------------
    // 3. Kasiski Examination
    // --------------------------------------------------------

    std::vector<int> kasiski_candidates =
        kasiski_analysis(ciphertext);


    std::cout
        << "=== Kasiski Candidate Key Lengths ===\n";


    for (int length : kasiski_candidates) {

        std::cout
            << length
            << " ";
    }


    std::cout << "\n\n";


    // --------------------------------------------------------
    // 4. Index of Coincidence
    // --------------------------------------------------------

    std::vector<double> ic_values =
        calculate_ic_for_key_lengths(
            ciphertext,
            20
        );


    std::cout
        << "=== Index of Coincidence ===\n";


    for (int i = 0;
         i < static_cast<int>(ic_values.size());
         i++) {

        std::cout
            << "Key Length "
            << std::setw(2)
            << i + 1
            << " : "
            << std::fixed
            << std::setprecision(6)
            << ic_values[i]
            << "\n";
    }


    // --------------------------------------------------------
    // 5. Determine Key Length
    // --------------------------------------------------------

    /*
        Kasiski provides candidate lengths.

        IC confirms which candidate produces
        groups that resemble English.

        For this ciphertext, key length 12
        has the strongest IC value.
    */

    int key_length = 12;


    std::cout
        << "\nEstimated Key Length : "
        << key_length
        << "\n\n";


    // --------------------------------------------------------
    // 6. Frequency Analysis
    // --------------------------------------------------------

    std::vector<std::vector<FrequencyEntry>>
        groups =
            frequency_analysis(
                ciphertext,
                key_length
            );


    std::cout
        << "=== Frequency Analysis ===\n\n";


    for (int group = 0;
         group < key_length;
         group++) {

        std::cout
            << "Group "
            << group + 1
            << ":\n";


        std::cout
            << std::left
            << std::setw(8)
            << "Letter"
            << std::setw(8)
            << "Count"
            << std::setw(12)
            << "Percent"
            << "\n";


        for (const auto& entry :
             groups[group]) {

            if (entry.count > 0) {

                std::cout
                    << std::left
                    << std::setw(8)
                    << entry.letter
                    << std::setw(8)
                    << entry.count
                    << std::fixed
                    << std::setprecision(2)
                    << std::setw(12)
                    << entry.percentage
                    << "%\n";
            }
        }


        std::cout << "\n";
    }


    // --------------------------------------------------------
    // 7. Recover Key
    // --------------------------------------------------------

    std::string key =
        find_key(
            ciphertext,
            key_length
        );


    std::cout
        << "=== Key Recovery ===\n\n";


    for (int i = 0;
         i < key_length;
         i++) {

        int shift =
            find_shift(groups[i]);


        std::cout
            << "Position "
            << std::setw(2)
            << i + 1
            << " : Shift = "
            << std::setw(2)
            << shift
            << ", Key Letter = "
            << static_cast<char>('A' + shift)
            << "\n";
    }


    std::cout
        << "\nRecovered Key : "
        << key
        << "\n";


    std::cout
        << "Key Length : "
        << key.length()
        << "\n\n";


    // --------------------------------------------------------
    // 8. Decrypt Ciphertext
    // --------------------------------------------------------

    std::string plaintext =
        vigenere_decrypt(
            ciphertext,
            key
        );


    std::cout
        << "=== Recovered Plaintext ===\n\n";


    std::cout
        << plaintext
        << "\n\n";


    // --------------------------------------------------------
    // 9. Verification
    // --------------------------------------------------------

    std::string regenerated_ciphertext =
        vigenere_encrypt(
            plaintext,
            key
        );


    bool verified =
        verify(
            plaintext,
            ciphertext,
            key
        );


    std::cout
        << "=== Verification ===\n\n";


    std::cout
        << "Original Ciphertext Length : "
        << ciphertext.length()
        << "\n";


    std::cout
        << "Regenerated Ciphertext Length : "
        << regenerated_ciphertext.length()
        << "\n";


    if (verified) {

        std::cout
            << "Verification Result : PASS\n";

        std::cout
            << "Re-encrypted ciphertext matches "
               "the original ciphertext.\n";

    } else {

        std::cout
            << "Verification Result : FAIL\n";

        std::cout
            << "Re-encrypted ciphertext does not "
               "match the original ciphertext.\n";
    }


    std::cout
        << "\n========================================\n";


    return 0;
}