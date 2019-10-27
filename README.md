# get_next_line

Ugly code, because the initial [french subject](https://cdn.intra.42.fr/pdf/pdf/6802/fr.subject.pdf)  (not this) could have suggested to do it with five functions maximum (and read/malloc/free from libc allowed).
So have a cleaner code, with chained list to hold multiple files descriptor, with max 5 functions was a pain.
Tests files and main is from [ncolomer](https://github.com/Glagan/42-get_next_line)
Support dev/random, but can may lose data on binaries.
