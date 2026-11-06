
import secrets
import time
from sympy import isprime


def generate_candidate(bits):
    """Generate an odd random integer with exactly 'bits' bits."""
    candidate = secrets.randbits(bits)
    candidate |= (1 << (bits - 1))  # Set the highest bit
    candidate |= 1                 # Ensure candidate is odd
    return candidate


def miller_rabin(n, rounds):
    """Perform Miller-Rabin and return result with tested bases."""

    if n < 2:
        return False, []

    small_primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]

    for p in small_primes:
        if n == p:
            return True, []
        if n % p == 0:
            return False, []

    if n % 2 == 0:
        return False, []

    d = n - 1
    s = 0

    while d % 2 == 0:
        d //= 2
        s += 1

    tested_bases = []

    for _ in range(rounds):
        a = secrets.randbelow(n - 3) + 2
        tested_bases.append(a)

        x = pow(a, d, n)

        if x == 1 or x == n - 1:
            continue

        for _ in range(s - 1):
            x = pow(x, 2, n)

            if x == n - 1:
                break
        else:
            return False, tested_bases

    return True, tested_bases


def generate_probable_prime(bits=512, rounds=40):
    """Generate a probable prime and collect experimental statistics."""

    candidates_tested = 0
    start_time = time.perf_counter()

    while True:
        candidate = generate_candidate(bits)
        candidates_tested += 1

        is_probable_prime, bases = miller_rabin(candidate, rounds)

        if is_probable_prime:
            break

    execution_time = time.perf_counter() - start_time

    return candidate, candidates_tested, rounds, execution_time, bases


def main():
    BIT_LENGTH = 512
    ROUNDS = 40

    print("=" * 70)
    print("       CRYPTOGRAPHIC PRIME GENERATION USING MILLER-RABIN")
    print("=" * 70)

    prime, count, rounds, elapsed, bases = generate_probable_prime(
        BIT_LENGTH, ROUNDS
    )

    actual_bits = prime.bit_length()

    print("\n[1] EXPERIMENTAL RESULTS")
    print("-" * 70)
    print(f"Assigned bit length       : {BIT_LENGTH}")
    print(f"Generated prime candidate : {prime}")
    print(f"Actual bit length         : {actual_bits}")
    print(f"Number of candidates      : {count}")
    print(f"Miller-Rabin rounds       : {rounds}")
    print(f"Total execution time      : {elapsed:.6f} seconds")

    print("\n[2] MILLER-RABIN VERIFICATION")
    print("-" * 70)
    print(f"Number of bases tested    : {len(bases)}")

    for index, base in enumerate(bases, start=1):
        print(f"Round {index:02d} base            : {base}")

    mr_result, verification_bases = miller_rabin(prime, rounds)

    print(f"\nPassed all rounds         : {mr_result}")
    print(f"Exact bit length verified : {actual_bits == BIT_LENGTH}")

    print("\n[3] INDEPENDENT VERIFICATION (SymPy)")
    print("-" * 70)

    sympy_result = isprime(prime)
    print(f"SymPy isprime result      : {sympy_result}")

    if actual_bits == BIT_LENGTH and mr_result and sympy_result:
        print("\n[SUCCESS] A 512-bit probable prime was generated and verified.")
    else:
        print("\n[ERROR] Verification failed.")

    print("=" * 70)


if __name__ == "__main__":
    main()