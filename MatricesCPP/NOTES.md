# Lower Triangular Matrix — Code Explanation

## The Core Problem: Why Not Just Use a 2D Array?

A lower triangular matrix looks like this (n=4):

```
1  0  0  0
2  3  0  0
4  5  6  0
7  8  9  10
```

If you store this in a standard `int[4][4]` array, you waste 6 cells on zeros that never change. For large `n`, that's `n(n-1)/2` wasted slots. The optimization: **only allocate storage for the non-zero elements**, and use a mapping function to translate `(i, j)` coordinates into a 1D index.

Non-zero count = `1 + 2 + 3 + ... + n = n(n+1)/2`. For n=4, that's 10 elements — exactly what both classes allocate.

---

## `main.cpp` — `LowerTriangle`

### Storage and Index Mapping (Row-Major)

```cpp
A = new int[n * (n + 1) / 2];
```

This allocates exactly enough for the non-zero elements. The array `A` is flat and laid out row by row:

```
Index: 0  1  2  3  4  5  6  7  8  9
Value: 1  2  3  4  5  6  7  8  9  10
       ↑        ↑           ↑
      row1    row2         row3
```

The mapping from `(i, j)` → flat index (1-based i, j):

```cpp
A[i * (i - 1) / 2 + j - 1]
```

Breaking it down:
- `i * (i-1) / 2` — how many elements exist in all rows *before* row `i`. Row 1 has 1 element, row 2 has 2, etc., so the cumulative count before row `i` is `0 + 1 + 2 + ... + (i-1) = i(i-1)/2`.
- `+ j - 1` — offset within row `i`. Since `j` is 1-based and each row starts at column 1, subtracting 1 gives the 0-based column offset.

**Example:** Get `M[3][2]` (row 3, col 2):
```
3*(3-1)/2 + 2-1 = 3 + 1 = 4  →  A[4] = 5  ✓
```

### Set and Get

```cpp
void LowerTriangle::Set(int i, int j, int x) {
    if(i >= j)
        A[i * (i - 1) / 2 + j - 1] = x;
}
```

The guard `i >= j` enforces the triangular constraint — elements above the diagonal (where `j > i`) are always zero and have no storage, so they're silently ignored. Same guard in `Get`: if you ask for `M[1][3]` it returns `0` without touching `A`.

### Display

```cpp
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
        if (i >= j)
            std::cout << A[i * (i - 1) / 2 + j - 1] << " ";
        else
            std::cout << "0 ";
    }
}
```

Iterates the full `n×n` grid. For lower-triangle positions, it reads from `A` using the same formula. For upper-triangle positions (`j > i`), it prints a literal `0`. This reconstructs the visual matrix without ever storing those zeros.

---

## `LTMatrixC++.cpp` — `LTMatrix` (Row-Major vs Column-Major)

This is the more thorough implementation. It stores the *same* data but supports two different memory layouts and demonstrates why the layout choice matters.

### Row-Major Set/Get

```cpp
int index = ((i * (i - 1))/2) + j - 1;
```

Identical logic to `main.cpp`. Elements are stored row by row in `A`:

```
A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
     r1  r2-----  r3----------  r4--------------
```

### Column-Major Set/Get

```cpp
int index = (n * (j-1) - (((j-2) * (j-1))/2)) + (i-j);
```

In column-major, data is laid out *column by column*:

```
A = [1, 2, 4, 7, 3, 5, 8, 6, 9, 10]
     col1--------  col2------  col3--  col4
```

Breaking down the formula:
- `n * (j-1)` — if every column had `n` elements, this is where column `j` would start
- `- (((j-2)*(j-1))/2)` — subtract the zeros that aren't stored. Columns get shorter as you move right: col 1 has `n` elements, col 2 has `n-1`, etc. The total elements not stored before column `j` is `0 + 1 + 2 + ... + (j-2) = (j-2)(j-1)/2`
- `+ (i-j)` — offset within column `j`. Since the first non-zero in column `j` is at row `j` (the diagonal), `i-j` is the 0-based offset into that column

**Example:** Get `M[3][2]` column-major (n=4):
```
4*(2-1) - ((0*1)/2) + (3-2) = 4 - 0 + 1 = 5  →  A[5] = 5  ✓
```

### Why Both Layouts?

Row-major is cache-friendly when you access elements *row by row*. Column-major is cache-friendly when you access *column by column*. Since `A` is contiguous memory, accessing sequential elements hits the same cache line and is fast — jumping around is slow. The layout determines which access pattern gets that benefit.

The `Display(bool row)` parameter lets you verify both layouts produce the *same logical matrix* — same data, different physical arrangement, same mathematical result.

---

## What the Code Demonstrates Overall

1. **Space optimization** — `O(n²)` → `O(n(n+1)/2)` storage
2. **Index arithmetic as abstraction** — the class hides the complexity; callers use `(i, j)` as if it's a normal 2D array
3. **Memory layout tradeoffs** — the same data can be arranged differently depending on expected access patterns
4. **RAII** — `new` in constructor, `delete[]` in destructor, no leaks

### Note on Modern C++

The raw `new`/`delete` here should ideally be `std::vector<int>` with `A.resize(n*(n+1)/2)`, which gives automatic memory management and bounds checking via `.at()`. For a DSA learning exercise focused on the index math, the raw array makes the allocation size and formula explicit — but in production code, prefer the vector.
