# Project 3

![project meme](meme.gif)

You job is to implement a memory manager using the
[buddy algorithm](https://drive.google.com/file/d/1G6aozf2ygXF7RL1WGg-iPBDkTusVuvNI/view) as
described by Dr. Knuth in The Art of Computer programming Volume 1 - Fundamental Algorithms.
You will use the mmap() system call to get a large block of memory to manage. From there on,
manage the chunk of memory returned by mmap using your own memory management functions.
The provided header file buddy.h is thoroughly documented with all the necessary details.

## Calculating the buddy

From the example in Knuth's book we can calculate the buddy of a block of size 16. With the table
above we know that a block of size 16 is K=4 so we will have 4 zeros at the right. Using the
[XOR operator](https://en.wikipedia.org/wiki/Exclusive_or) we can calculate the buddy as follows:

```text
   101110010110000
 ^ 000000000010000
------------------
   101110010100000
```

### XOR True table

| A | B | Output |
|---|---|--------|
| 0 | 0 | 0      |
| 0 | 1 | 1      |
| 1 | 0 | 1      |
| 1 | 1 | 0      |

## Buddy analysis

In your README.md file you will need to answer the following questions:

- Are there any drawbacks to the buddy algorithm? Please explain in detail.
- If you initially allocated 1 GiB to manage describe a method that you could use to add
  more memory after the fact. You don't have to actually implement this I am just looking
  for an idea of how to do it!

## Testing

You need to write enough tests to ensure your memory allocator is correct!

## Hints

**Warning:** Ignoring these hints could impact your final grade :)

- You are NOT allowed to use the [pow](http://www.cplusplus.com/reference/cmath/pow/) function
  in the math library!
- There should be no hard coded constants in your code. You will need to use the macros
  defined in the [C99 standard](https://en.cppreference.com/w/c/types/integer) to get the
  correct width. For example to calculate a K value 64bit system you would write
  `UINT64_C(1) << kval` NOT `1 << kval`
- Remember to take into account the size of your header when calculating your K value. If
  a user asked for 32 bytes you will need to use K=6 not K=5 to account for the header size.
- If the memory cannot be allocated, then your buddy_calloc or buddy_malloc functions should set
  errno to ENOMEM (which is defined in errno.h header file) and return NULL.
- You can't use malloc/free/realloc/calloc from the C standard library.
- You will need to make extensive use of pointer arithmetic! When you are dealing with raw
  (untyped) memory make sure and cast the pointer to the correct type so it is moved the correct
  amount.
- Be mindful of the differences between `sizeof(struct foo)` and `sizeof(struct foo*)`. The first
  instance give you the size of the struct while the second gives you the size of a pointer. If
  the size of the struct just **happens** to be the same as a pointer your code will appear to
  work until you either add a new member to `foo` OR you move to a system where the sizes of pointers
  are different. For example moving from a 64bit system to a 32 bit system or vice versa!
- Read [Chapter 14 - Interlude: Memory API](http://pages.cs.wisc.edu/~remzi/OSTEP/vm-api.pdf)

## Knuth notation to C syntax quick reference

```c
struct buddy_pool *pool;
struct avail *L;
```

| Knuth notation | C syntax               |
|----------------|------------------------|
| AVAILF[k]      | `pool->avail[k].next`  |
| AVAILB[k]      | `pool->avail[k].prev`  |
| LOC(AVAIL[k])  | `&pool->avail[k]`      |
| LINKF(L)       | `L->next`              |
| LINKB(L)       | `L->prev`              |
| TAG(L)         | `L->tag`               |
| KVAL(L)        | `L->kval`              |
| buddyk(L)      | `buddy_calc(pool, L);` |

## Power of 2 quick reference

As specified in the algorithm in order for everything to work you must work in powers of two!
This includes the address that you get back from mmap. You will need to scale the address
appropriately or you will calculate invalid buddy values. You can use the table below for a
quick reference for up to K=40.

| Power (k value) | Bytes             | KiB/MiB/GiB/TiB |
|-----------------|-------------------|-----------------|
| 2^0             | 1                 |                 |
| 1               | 2                 |                 |
| 2               | 4                 |                 |
| 3               | 8                 |                 |
| 4               | 16                |                 |
| 5               | 32                |                 |
| 6               | 64                |                 |
| 7               | 128               |                 |
| 8               | 256               |                 |
| 9               | 512               |                 |
| 10              | 1,024             | 1 KiB           |
| 11              | 2,048             | 2 KiB           |
| 12              | 4,096             | 4 KiB           |
| 13              | 8,192             | 8 KiB           |
| 14              | 16,384            | 16 KiB          |
| 15              | 32,768            | 32 KiB          |
| **16**          | 65,536            | 64 KiB          |
| 17              | 131,072           | 128 KiB         |
| 18              | 262,144           | 256 KiB         |
| 19              | 524,288           | 512 KiB         |
| 20              | 1,048,576         | 1 MiB           |
| 21              | 2,097,152         | 2 MiB           |
| 22              | 4,194,304         | 4 MiB           |
| 23              | 8,388,608         | 8 MiB           |
| 24              | 16,777,216        | 16 MiB          |
| 25              | 33,554,432        | 32 MiB          |
| 26              | 67,108,864        | 64 MiB          |
| 27              | 134,217,728       | 128 MiB         |
| 28              | 268,435,456       | 256 MiB         |
| 29              | 536,870,912       | 512 MiB         |
| 30              | 1,073,714,824     | 1 GiB           |
| 31              | 2,147,483,648     | 2 GiB           |
| **32**          | 4,294,967,296     | 4 GiB           |
| 33              | 8,589,934,592     | 8 GiB           |
| 34              | 17,179,869,184    | 16 GiB          |
| 35              | 34,359,738,368    | 32 GiB          |
| 36              | 68,719,476,736    | 64 GiB          |
| 37              | 137,438,953,472   | 128 GiB         |
| 38              | 274,877,906,944   | 256 GiB         |
| 39              | 549,755,813,888   | 512 GiB         |
| 40              | 1,099,511,627,776 | 1 TiB           |

## Grad Students (extra credit for undergrad)

After you have implemented all the required features specified in the undergrad version
you will need to extend your implementation to be thread safe and collect details about
usage.

### Make thread safe

You will need to use the pthread library to make your memory pool thread safe. Your code
should be written in such a way that multiple memory pools can be active at once. You
will then need to extend your testing code to test your thread safe implementation.

### Collect and print stats

You will need to extend the `struct buddy_pool` to allow you to collect stats so you can
calculate the amount of internal fragmentation that buddy can produce. You will then need to write
a testing function that randomly allocates and frees memory to exercise your allocator. In your
README.md you need to discuss some of the issues that the buddy algorithm has with regards to
internal fragmentation.

### Better buddy_realloc

The provided implementation for buddy_realloc is very inefficient. You need to update the code
to check if the buddy is available and then just merge the blocks. Be aware of the case where the
buddy is actually at a lower address which will require a
[memmove](http://www.cplusplus.com/reference/cstring/memmove/). If the buddy is at a higher address
then you can just merge the blocks and return!

## References

- [Dr. Knuth's algorithm](https://drive.google.com/file/d/1G6aozf2ygXF7RL1WGg-iPBDkTusVuvNI/view)
- [Appendix B. Index to Notations](https://www.oreilly.com/library/view/art-of-computer/9780321635754/app03.html)
- [C99 Standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf)

> C99 6.7.2.1 (13): Within a structure object, the non-bit-field members and the units in which
bit-fields reside have addresses that increase in the order in which they are declared. A pointer to a
structure object, suitably converted, points to its initial member (or if that member is a
bit-field, then to the unit in which it resides), and vice versa. There may be unnamed
padding within a structure object, but not at its beginning.
