# BOOGLE: Trie Slang Dictionary

> A slang dictionary in C with fast prefix-based lookup.

## Overview

- Slang changes constantly, so the dictionary needs quick inserts and lookups rather than a flat list.

## Data / Scope

- Algorithms and Programming course assignment. Stores slang words with their definitions.

## Workflow

- Built a trie (prefix tree) from scratch in C, with one letter per node.
- Implemented insert/update, exact search, and prefix search (e.g. all words starting with "l").
- Added an alphabetical listing of all entries, without built-in library structures.

## Results

- Working terminal program, compiled and run.
- Four features: insert/update, exact search, prefix search, alphabetical list.
- Designed a non-trivial data structure from first principles.

## Tech Stack

C, Trie, Pointers, String search

## Repository Structure

```
boogle.cpp          Trie-based slang dictionary (insert, search, prefix search, alphabetical list)
```

## How to Run

```bash
g++ boogle.cpp -o boogle
./boogle
```

## Team

Algorithm and Programming course project (individual).

## Notes

- Source file is a single C/C++ program; comments are partly in Indonesian.

## Author

Nadya Angelie Lislie, BINUS University (Computer Science and Statistics). [LinkedIn](https://www.linkedin.com/in/nadya-angelie-lislie/) | [GitHub](https://github.com/Nadya-AngelieLislie)

## Continuous Integration

GitHub Actions (`.github/workflows/ci.yml`) runs `ruff` and `pytest` repository-health checks on every push; run them locally with `make lint test`.
