Q1) The page numbers and offsets for the given logical addresses are presented below.

+-----------------+-------------+--------+
| Logical Address | Page Number | Offset |
+-----------------+-------------+--------+
| 3085            | 3           | 13     |
+-----------------+-------------+--------+
| 42095           | 41          | 111    |
+-----------------+-------------+--------+
| 215201          | 210         | 161    |
+-----------------+-------------+--------+
| 650000          | 634         | 784    |
+-----------------+-------------+--------+
| 2000001         | 1953        | 129    |
+-----------------+-------------+--------+


Q2) Consider a logical address space of 256 pages with a 4-KB page size,mapped onto a physical memory of 64 frames.

a) Bits required for the logical address are 12 + 8 = 20 bits. This is because there are 2^8 pages each of size 2^12. Total memory locations are 2^20, which results to 20 bits.

b) Bits required for the physical address space are 6 + 12 = 18 bits. This is because there are 2^6 frames each of size 2^12. Total memory locations are 2^28 which results to 18 bits.


Q3) Consider the following page reference string:1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6. The number of page faults for one to seven frame sizes are presented in the table below.

+------------------+-----+------+---------+
| Number of Frames | LRU | FIFO | Optimal |
+------------------+-----+------+---------+
| 1                | 20  | 20   | 20      |
+------------------+-----+------+---------+
| 2                | 18  | 18   | 15      |
+------------------+-----+------+---------+
| 3                | 15  | 16   | 11      |
+------------------+-----+------+---------+
| 4                | 10  | 14   | 8       |
+------------------+-----+------+---------+
| 5                | 8   | 10   | 7       |
+------------------+-----+------+---------+
| 6                | 7   | 10   | 7       |
+------------------+-----+------+---------+
| 7                | 7   | 7    | 7       |
+------------------+-----+------+---------+

The number of faults generally decrease as the frame size increases, however the choice of the replacement algorithm can decrease the number of page faults for a smaller frame size.