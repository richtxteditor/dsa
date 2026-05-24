# Workspace Lessons & Design Patterns

This document details key architectural insights, design patterns, and programming lessons discovered across the DSA workspace.

---

## 1. C++ Template Resource Management (The Rule of Five)
When writing custom data structures that manage raw pointers (like `Array<T>` or `LTMatrix`):
*   **Destructors** must release resources (`delete[] A`).
*   **Copy constructors and copy assignments** must perform deep copying to prevent multiple instances from referencing the same heap buffer (which leads to segmentation faults or double-free failures).
*   Alternatively, copy operations can be explicitly deleted (`= delete`) to enforce single ownership patterns.
*   **Move constructors and move assignments** should be implemented to support efficient resource transfer from temporary/R-value objects.

---

## 2. API Safety & Robustness
*   **Avoid Magic Values:** Instead of returning `-1` or other magic numbers on lookup misses, use `std::optional<T>` (defined in `<optional>`). Callers can safely inspect values using `.has_value()` or `.value_or()`.
*   **Input Validation:** Always clean and validate standard library input streams (`std::cin.clear()` and `std::cin.ignore()`) to prevent infinite input loops on mismatched data types.

---

## 3. Compact Matrix Storage (Flat 1D Representation)
When representing custom structural matrices (like a Lower Triangular Matrix of size $n \times n$):
*   Do not waste $O(n^2)$ memory storing default zero values. Store only the non-zero elements in a flat 1D array of size $n(n+1)/2$.
*   Use standard mathematical index-mapping formulas to project $1$-based matrix coordinates $(i, j)$ into $0$-based flat indexes:
    *   **Row-Major Layout:**
        $$\text{Index} = \frac{i(i - 1)}{2} + j - 1$$
    *   **Column-Major Layout:**
        $$\text{Index} = \left(n(j - 1) - \frac{(j - 2)(j - 1)}{2}\right) + (i - j)$$
*   Centralize these formulas in layout-specific helper functions (e.g. `rowMajorIndex(i, j)`) to keep `Set`, `Get`, and `Display` clean and maintainable.
