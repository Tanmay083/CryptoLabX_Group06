#include "vigenere_frequency.h"
#include "vigenere_cipher.h"
#include "kasiski_analysis.h"

#include <vector>
#include <string>


// ------------------------------------------------------------
// Frequency Analysis
// ------------------------------------------------------------

std::vector<std::vector<FrequencyEntry>>
frequency_analysis(
    const std::string& ciphertext,
    int key_length
) {
    std::vector<std::vector<FrequencyEntry>> all_groups;

    // Remove spaces, punctuation and convert to uppercase.
    std::string cleaned =
        clean_ciphertext(ciphertext);

    // Create one frequency table for every key position.
    for (int group_index = 0;
         group_index < key_length;
         group_index++) {

        int counts[26] = {0};

        int total = 0;

        // Characters belonging to this key position.
        for (int i = group_index;
             i < static_cast<int>(cleaned.size());
             i += key_length) {

            counts[cleaned[i] - 'A']++;
            total++;
        }

        std::vector<FrequencyEntry> frequencies;

        // Store A-Z frequency information.
        for (int i = 0; i < 26; i++) {

            FrequencyEntry entry;

            entry.letter =
                static_cast<char>('A' + i);

            entry.count =
                counts[i];

            if (total > 0) {

                entry.percentage =
                    static_cast<double>(counts[i]) *
                    100.0 /
                    total;

            } else {

                entry.percentage = 0.0;
            }

            frequencies.push_back(entry);
        }

        all_groups.push_back(frequencies);
    }

    return all_groups;
}


// ------------------------------------------------------------
// Find Shift Using Chi-Square
// ------------------------------------------------------------

int find_shift(
    const std::vector<FrequencyEntry>& frequencies
) {
    /*
        Standard English letter frequencies.

        Values are percentages:
        A = 8.167%
        B = 1.492%
        ...
        Z = 0.074%
    */

    const double english_frequency[26] = {

        8.167, 1.492, 2.782, 4.253,
        12.702, 2.228, 2.015, 6.094,
        6.966, 0.153, 0.772, 4.025,
        2.406, 6.749, 7.507, 1.929,
        0.095, 5.987, 6.327, 9.056,
        2.758, 0.978, 2.360, 0.150,
        1.974, 0.074
    };


    // Calculate total number of characters
    // in this group.
    int total = 0;

    for (const auto& entry : frequencies) {
        total += entry.count;
    }


    /*
        Try every possible Caesar shift.

        shift = 0  -> A remains A
        shift = 1  -> B becomes A
        shift = 2  -> C becomes A
        ...
        shift = 25
    */

    double best_score = 1e18;

    int best_shift = 0;


    for (int shift = 0;
         shift < 26;
         shift++) {

        double chi_square = 0.0;


        /*
            For every ciphertext letter,
            determine which plaintext letter
            it would represent for this shift.
        */

        for (int cipher_letter = 0;
             cipher_letter < 26;
             cipher_letter++) {

            int plain_letter =
                (cipher_letter - shift + 26) % 26;


            /*
                Expected frequency is a percentage.

                Convert it into an expected count.

                Example:

                If group has 64 characters and
                English expects E = 12.702%,

                expected count =
                0.12702 * 64
            */

            double expected_count =
                (english_frequency[plain_letter] /
                 100.0) *
                total;


            // Observed number of this ciphertext letter.
            int observed =
                frequencies[cipher_letter].count;


            /*
                Chi-square formula:

                    (observed - expected)^2
                    ---------------------
                         expected
            */

            if (expected_count > 0.0) {

                double difference =
                    observed - expected_count;

                chi_square +=
                    (difference * difference) /
                    expected_count;
            }
        }


        /*
            The shift having the smallest
            chi-square value is considered
            the most likely shift.
        */

        if (chi_square < best_score) {

            best_score = chi_square;

            best_shift = shift;
        }
    }


    return best_shift;
}


// ------------------------------------------------------------
// Find Complete Vigenere Key
// ------------------------------------------------------------

std::string find_key(
    const std::string& ciphertext,
    int key_length
) {
    std::string key;

    /*
        Get frequency table for every
        key position.
    */

    std::vector<std::vector<FrequencyEntry>>
        all_groups =
            frequency_analysis(
                ciphertext,
                key_length
            );


    /*
        Solve each group independently.

        Group 0 -> first key character
        Group 1 -> second key character
        ...
    */

    for (int i = 0;
         i < key_length;
         i++) {

        int shift =
            find_shift(all_groups[i]);


        /*
            Convert numerical shift to
            alphabetic key character.

            0  -> A
            1  -> B
            2  -> C
            ...
            25 -> Z
        */

        key +=
            static_cast<char>('A' + shift);
    }


    return key;
}