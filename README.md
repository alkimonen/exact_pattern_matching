# Exact Pattern Matching
# Basic Median String Search
This project implements three different exact pattern matching algorithms and compares the performances between them.

The implemented algorithms are:
- Brute force search
- Knuth-Morris-Pratt
- Rabin-Karp

## Algorithms


**Input:** Two strings T and P, where *|T|* >= *|P|*. These two strings will be given in two files in
FASTA format. Note that FASTA file allows a single string to be represented in multiple lines.
*T* file must be passed using the **-i** flag and *P* file must be passed using the **-p** flag.

**Output:** For each of the four algorithms to be implemented, report:
- Whether *P* is in *T*, and if it is, the location of *P* within *T* (1-based coordinate).
- Number of character comparisons performed.
- Run time in microseconds.

## Compilation and Run
Makefile uses **Makefile** and **gcc** as compiler. These packages should be installed into the system in order to run the project.
After navigating to the projects directory to compile the project execute
```
make
```
or
```
make build
```

The program takes text and pattern files' names as arguments in terminal. After compilation, an example to run the project can be
```
./epm -i test/T.fa -p test/P.fa
```
