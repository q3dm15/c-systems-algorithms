# C Systems & Algorithms Intensive Tasks

A curated portfolio of high-performance command-line applications written in pure C (C99). This repository showcases production-grade implementation patterns for resource-constrained systems, featuring low-level memory management, stream-oriented I/O pipelines, and algorithmic efficiency.

## 🛠️ Core Engineering Philosophy
* **Zero-Leak Memory Management:** All dynamic buffers are meticulously handled with automated heap resizing and clean multi-tier deallocation sequences verified via Valgrind.
* **Deterministic O(1) Spatial Workflows:** Maximizes the usage of raw `stdin` / `stdout` byte-streams to process inputs on-the-fly, avoiding massive array allocations where possible.
* **Production-Grade Code Quality:** Enforced strict compilation profiles with `-Wall -Wextra -Werror` to treat warnings as fatal errors. Codebase architecture adheres to automated `.clang-format` layouts.

---

## 📂 Repository Structure

```text
.
├── .gitignore               # Root ignore rules for build artifacts
├── b_secret_number/         # Task 1: GCD Stream Processor
│   ├── README.md            # App documentation
│   ├── Makefile             # Standalone build automation
│   ├── .clang-format        # Linter rules
│   └── src/main.c           # Source code
├── c_token_validation/      # Task 2: Luhn Validator
│   ├── README.md
│   ├── Makefile
│   ├── .clang-format
│   └── src/main.c
└── d_xor_key/               # Task 3: XOR Stream Cipher
    ├── README.md
    ├── Makefile
    ├── .clang-format
    └── src/main.c
```

---

## 🚀 Projects Overview

### 1. Secret Number Finder (`b_secret_number`)
A number theory utility that reconstructs a hidden shared factor from a stream of intercepted messages.
* **Key Mechanisms:** Iterative Euclidean Algorithm for Greatest Common Divisor (GCD) utilizing bit-safe modulo loops instead of recursion overhead.
* **Optimization:** Runs in pure O(1) memory by parsing data on-the-fly. Built natively using `long long` bounds to safely prevent arithmetic truncation up to 10¹⁸.

### 2. Luhn Token & Card Validator (`c_token_validation`)
A stream-oriented token parsing and validation pipeline that validates custom strings or credit card formats.
* **Key Mechanisms:** Implements the **Luhn Algorithm (Mod 10)** with custom `Token` abstract data types.
* **Optimization:** Manages an elastic heap-allocated buffer using an optimized doubling re-allocation (`realloc`) scheme. Automatically filters format separators (spaces, hyphens) and flags bad inputs instantly via a zero-deadweight parsing structure.

### 3. Streaming XOR Stream Cipher & Cryptanalysis (`d_xor_key`)
A cryptographic tool designed for symmetrical data encryption layer stripping based on known plaintext headers (H).
* **Key Mechanisms:** Contextual key extraction (\(K_i = C_i \oplus H_i\)) wrapped in an isolated execution state structure, avoiding global mutable states.
* **Optimization:** Fast bitwise ASCII Hex-to-Byte decoding using direct manual nibble shifting (`<< 4 | low`). Instant file streaming with single-pass `getchar()` / `putchar()` flows.

---

## ⚡ Quick Start & Compilation

Each project contains an independent, fully configured `Makefile` adhering to standard Unix conventions.

### Build a specific module:
```bash
cd c_token_validation
make
```

### Run an application (Example using Token Validator):
```bash
./token_validator < tests/input_sample.txt
```

### Clean up build artifacts:
```bash
make clean
```

---

## 🧪 Quality Assurance & Robustness

Every program in this suite has been rigorously profiled using **Valgrind Memcheck** to ensure total memory defense.

* Zero bytes leaked / zero memory leaks in heap allocations.
* Zero uninitialized memory read jumps.
* Absolute boundary protection against uncompleted network or file stream reads (`EOF` / incomplete hex pairs).

```text
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
