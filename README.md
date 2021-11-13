Sample I/O

```
>>> del one
File not found.

>>> add one 1
File name and file size: Index block at position 45.
Block 0 at position 15.

>>> disk
Out of 64 blocks, these are occupied:
15 45

>>> add two 5
File name and file size: Index block at position 6.
Block 0 at position 41.
Block 1 at position 4.
Block 2 at position 52.
Block 3 at position 56.
Block 4 at position 24.

>>> disk
Out of 64 blocks, these are occupied:
4 6 15 24 41 45 52 56

>>> del three
File not found.

>>> seek three 0
File not found.

>>> add three 10
File name and file size: Index block at position 40.
Block 0 at position 39.
Block 1 at position 63.
Block 2 at position 0.
Block 3 at position 43.
Block 4 at position 49.
Block 5 at position 60.
Block 6 at position 25.
Block 7 at position 58.
Block 8 at position 22.
Block 9 at position 9.

>>> disk
Out of 64 blocks, these are occupied:
0 4 6 9 15 22 24 25 39 40 41 43 45 49 52 56 58 60 63

>>> seek three 5
The block no. on disk is 60.

>>> del two

>>> disk
Out of 64 blocks, these are occupied:
0 9 15 22 25 39 40 43 45 49 58 60 63

>>> del one

>>> disk
Out of 64 blocks, these are occupied:
0 9 22 25 39 40 43 49 58 60 63

>>> list
three

>>> add four 40
File name and file size: Index block at position 44.
Block 0 at position 37.
Block 1 at position 23.
Block 2 at position 52.
Block 3 at position 36.
Block 4 at position 4.
Block 5 at position 47.
Block 6 at position 21.
Block 7 at position 41.
Block 8 at position 38.
Block 9 at position 42.
Block 10 at position 24.
Block 11 at position 27.
Block 12 at position 30.
Block 13 at position 32.
Block 14 at position 59.
Block 15 at position 56.
Block 16 at position 45.
Block 17 at position 14.
Block 18 at position 46.
Block 19 at position 20.
Block 20 at position 19.
Block 21 at position 48.
Block 22 at position 26.
Block 23 at position 50.
Block 24 at position 5.
Block 25 at position 31.
Block 26 at position 28.
Block 27 at position 13.
Block 28 at position 3.
Block 29 at position 61.
Block 30 at position 62.
Block 31 at position 16.
Block 32 at position 29.
Block 33 at position 10.
Block 34 at position 33.
Block 35 at position 1.
Block 36 at position 55.
Block 37 at position 6.
Block 38 at position 51.
Block 39 at position 53.

>>> seek four 1
The block no. on disk is 23.

>>> seek four 41
File does not have block 41.

>>> disk
Out of 64 blocks, these are occupied:
0 1 3 4 5 6 9 10 13 14 16 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 55 56 58 59 60 61 62 63

>>> add five 10
File name and file size: Index block at position 34.
Block 0 at position 8.
Block 1 at position 54.
Block 2 at position 57.
Block 3 at position 2.
Block 4 at position 35.
Block 5 at position 7.
Block 6 at position 11.
Block 7 at position 12.
Block 8 at position 15.
Block 9 at position 17.

>>> list
three
four
five

>>> exit
```

A few corner cases:

1. One enormous file having as much size as the disk. It can't be placed in the disk because there is no space for the index block.

```
>>> add one 64
File name and file size: Not enough disk space.

>>> list
Empty Directory.

>>> disk
Out of 64 blocks, none are occupied.

>>> exit
```

2. The largest file that can fit in the disk.

```
>>> add one 63
File name and file size: Index block at position 45.
Block 0 at position 15.
Block 1 at position 6.
Block 2 at position 41.
Block 3 at position 4.
Block 4 at position 52.
Block 5 at position 56.
Block 6 at position 24.
Block 7 at position 40.
Block 8 at position 39.
Block 9 at position 63.
Block 10 at position 0.
Block 11 at position 43.
Block 12 at position 49.
Block 13 at position 60.
Block 14 at position 25.
Block 15 at position 58.
Block 16 at position 22.
Block 17 at position 9.
Block 18 at position 44.
Block 19 at position 37.
Block 20 at position 23.
Block 21 at position 53.
Block 22 at position 36.
Block 23 at position 5.
Block 24 at position 47.
Block 25 at position 21.
Block 26 at position 42.
Block 27 at position 38.
Block 28 at position 46.
Block 29 at position 26.
Block 30 at position 27.
Block 31 at position 30.
Block 32 at position 32.
Block 33 at position 59.
Block 34 at position 57.
Block 35 at position 48.
Block 36 at position 14.
Block 37 at position 50.
Block 38 at position 20.
Block 39 at position 19.
Block 40 at position 51.
Block 41 at position 28.
Block 42 at position 54.
Block 43 at position 7.
Block 44 at position 31.
Block 45 at position 29.
Block 46 at position 13.
Block 47 at position 3.
Block 48 at position 61.
Block 49 at position 62.
Block 50 at position 16.
Block 51 at position 33.
Block 52 at position 10.
Block 53 at position 34.
Block 54 at position 1.
Block 55 at position 55.
Block 56 at position 8.
Block 57 at position 2.
Block 58 at position 11.
Block 59 at position 35.
Block 60 at position 12.
Block 61 at position 17.
Block 62 at position 18.

>>> list
one

>>> disk
Out of 64 blocks, these are occupied:
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63

>>> exit
```

3. Adding files till the disk is full.

```
>>> add one 10
File name and file size: Index block at position 45.
Block 0 at position 15.
Block 1 at position 6.
Block 2 at position 41.
Block 3 at position 4.
Block 4 at position 52.
Block 5 at position 56.
Block 6 at position 24.
Block 7 at position 40.
Block 8 at position 39.
Block 9 at position 63.

>>> add two 10
File name and file size: Index block at position 0.
Block 0 at position 43.
Block 1 at position 49.
Block 2 at position 60.
Block 3 at position 25.
Block 4 at position 58.
Block 5 at position 22.
Block 6 at position 9.
Block 7 at position 44.
Block 8 at position 37.
Block 9 at position 23.

>>> add three 20
File name and file size: Index block at position 53.
Block 0 at position 36.
Block 1 at position 5.
Block 2 at position 47.
Block 3 at position 21.
Block 4 at position 42.
Block 5 at position 38.
Block 6 at position 46.
Block 7 at position 26.
Block 8 at position 27.
Block 9 at position 30.
Block 10 at position 32.
Block 11 at position 59.
Block 12 at position 57.
Block 13 at position 48.
Block 14 at position 14.
Block 15 at position 50.
Block 16 at position 20.
Block 17 at position 19.
Block 18 at position 51.
Block 19 at position 28.

>>> add four 20
File name and file size: Index block at position 54.
Block 0 at position 7.
Block 1 at position 31.
Block 2 at position 29.
Block 3 at position 13.
Block 4 at position 3.
Block 5 at position 61.
Block 6 at position 62.
Block 7 at position 16.
Block 8 at position 33.
Block 9 at position 10.
Block 10 at position 34.
Block 11 at position 1.
Block 12 at position 55.
Block 13 at position 8.
Block 14 at position 2.
Block 15 at position 11.
Block 16 at position 35.
Block 17 at position 12.
Block 18 at position 17.
Block 19 at position 18.

>>> add five 0
File name and file size: Not enough disk space.

>>> list
one
two
three
four

>>> disk
Out of 64 blocks, these are occupied:
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63

>>> exit
```
