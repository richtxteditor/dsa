# Enhancements to implement before moving on to next leetcode problem

## 1. Class & Memory Management

* **✅ Use `std::vector` instead of raw pointer**
  * **Verdict:** **Understand, But Park for later.**
  * **Rationale:** This is the most important point. From a professional standpoint, you would almost always use `std::vector`. However, the entire *purpose* of this academic project is to learn *how `std::vector` works under the hood*. You have manually implemented memory management, constructors, destructors, and the Rule of Five. **This is a massive achievement and the core learning objective.** Replacing it now would be like learning to drive a manual car and then being told to switch to an automatic just before the test. You've already done the hard, essential part. Congratulate yourself and keep your implementation as is. It is a testament to your understanding.

* **✅ Optional: Implement Iterators**
  * **Verdict:** **Park For Later.**
  * **Rationale:** This is a fantastic C++-specific enhancement that teaches you about operator overloading and making your class compatible with the C++ Standard Library (STL). It's a great "Version 2.0" feature for your class, but it won't help you learn the next data structure (like Linked Lists or Trees). Keep this idea in your back pocket for when you want to deepen your C++ skills.

## 2. Modern C++ Practices

* **✅ Replace `using namespace std;`**
  * **Verdict:** **Do It Now.**
  * **Rationale:** This is a critical professional habit. It takes five minutes to fix and prevents a whole class of potential bugs in larger projects. Change `using namespace std;` to the specific `using` declarations (e.g., `using std::cout;`) or just qualify with `std::` directly.

* **✅ Use `std::optional` more consistently**
  * **Verdict:** What you have is fine. No change needed.
  * **Rationale:** The suggestion to use `std::optional` for `Delete()` is a valid design choice. However, so is throwing an exception. Throwing an exception for an "exceptional" event (like trying to delete from an empty array) is perfectly reasonable. This is a matter of error-handling philosophy. Your current implementation is robust and clear.

* **✅ Use templates**
  * **Verdict:** **Park For Later.**
  * **Rationale:** Similar to iterators, this is an excellent C++ skill for making your data structures generic. However, learning the logic of a new data structure (like a graph) and also trying to write it with templates for the first time adds significant cognitive load. Master the data structures first with a concrete type like `int`. Then, circle back and learn to make them generic.

## 3. Code Organization

* **✅ Split into `Array.h` and `Array.cpp`**
  * **Verdict:** **Do It Now.**
  * **Rationale:** This is a foundational software engineering practice. As you move on to Linked Lists, Stacks, and Trees, you will be adding more classes (`Node`, `LinkedList`, etc.). You do not want them all in one giant `main.cpp`. This is a high-value change that will make your project much easier to manage going forward.

## 4. Performance Improvements

* **✅ Optimize `FindDuplicatesSorted`**
  * **Verdict:** A nice, minor tweak. Do it if you like.
  * **Rationale:** The suggested code is slightly cleaner. It's a small refactoring that won't take long and is a good example of refining an algorithm.

* **✅ Dynamic resizing instead of overflow errors**
  * **Verdict:** **Do It Now.**
  * **Rationale:** This is a brilliant suggestion because it completes the core concept of a "dynamic array." A true dynamic array doesn't just have a fixed capacity; it *grows* when it needs to. Implementing this `resize` logic is a classic and essential part of this data structure. It's a perfect enhancement before you move on.

## 5. UX & CLI Enhancements

* **Verdict:** Ignore for now.
* **Rationale:** Adding colors and clearing the screen is cosmetic. It won't teach you anything about data structures, algorithms, or C++. Your time is better spent elsewhere.

## 6. Testing & Debugging

* **✅ Unit Tests**
  * **Verdict:** **Highly Recommended.**
  * **Rationale:** While setting up a full test suite with GoogleTest might be a distraction, the *mindset* is critical. Before you move on, I strongly recommend you write just **one or two simple test functions** in your `main.cpp` that create an array, call a method, and check the result. For example: `void test_append_and_get() { ... }`. This will force you to think about edge cases and will be an incredibly valuable skill.

---

## My Priority Recommendations for You

Before you move on to Linked Lists, here is your prioritized action plan:

1. ✅ **Split Your Code (High Priority):** Create `Array.h` for the class declaration and `Array.cpp` for the method implementations. Keep `main()` in `main.cpp`. This will prepare your project for future growth.
2. 👷🏽‍♂️ **Implement Dynamic Resizing (High Priority):** Modify `Append()` and `Insert()` to check if `length >= size`. If so, create a new, larger array (e.g., double the size), copy the old elements over, delete the old array, and then proceed with adding the new element. This is a crucial feature.
3. **Fix `using namespace std;` (Quick Win):** Get into this professional habit now.
4. **Write a Simple Test Function (Recommended):** Just create a `void test_something()` function that you can call from `main()`. This will be your first step into the world of automated testing and will pay huge dividends later.

By focusing on these specific enhancements, you will solidify your understanding of the dynamic array and prepare your project and your skills for the next chapter in your course.
