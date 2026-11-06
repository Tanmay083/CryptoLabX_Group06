
import unittest

from attacks.miller_rabin.main import (
    miller_rabin,
    generate_candidate,
    generate_probable_prime
)


class TestMillerRabin(unittest.TestCase):

    def test_small_primes(self):
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 97, 101, 997]

        for number in primes:
            with self.subTest(number=number):
                result, _ = miller_rabin(number, 40)
                self.assertTrue(result)

    def test_composite_numbers(self):
        composites = [0, 1, 4, 6, 8, 9, 15, 21, 25, 100, 221, 1001]

        for number in composites:
            with self.subTest(number=number):
                result, _ = miller_rabin(number, 40)
                self.assertFalse(result)

    def test_known_pseudoprimes(self):
        pseudoprimes = [2047, 1373653, 25326001]

        for number in pseudoprimes:
            with self.subTest(number=number):
                result, _ = miller_rabin(number, 40)
                self.assertFalse(result)

    def test_candidate_bit_length(self):
        for bits in [64, 128, 256, 512]:
            candidate = generate_candidate(bits)

            self.assertEqual(candidate.bit_length(), bits)
            self.assertEqual(candidate % 2, 1)

    def test_generated_probable_prime(self):
        prime, count, rounds, elapsed, bases = generate_probable_prime(
            512, 40
        )

        result, _ = miller_rabin(prime, 40)

        self.assertEqual(prime.bit_length(), 512)
        self.assertTrue(result)
        self.assertGreaterEqual(count, 1)
        self.assertEqual(rounds, 40)
        self.assertEqual(len(bases), 40)
        self.assertGreaterEqual(elapsed, 0)

    def test_base_range(self):
        prime, _, rounds, _, bases = generate_probable_prime(512, 40)

        self.assertEqual(len(bases), rounds)

        for base in bases:
            self.assertGreaterEqual(base, 2)
            self.assertLessEqual(base, prime - 2)


if __name__ == "__main__":
    unittest.main(verbosity=2)
