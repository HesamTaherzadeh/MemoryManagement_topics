![CI](https://github.com/HesamTaherzadeh/MemoryManagement_topics/actions/workflows/ci.yaml/badge.svg)

# Advanced Memory Management in C++

This repository explores advanced topics in memory management in C++. Each example demonstrates best practices and techniques for managing memory efficiently and avoiding common pitfalls such as memory leaks and undefined behavior.

The repository covers concepts such as smart pointers, custom deleters, avoiding circular references, and more.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Examples](#examples)
   - [1. Custom Deleters with `std::unique_ptr`](#1-custom-deleters-with-stdunique_ptr)
   - [2. Avoiding Circular References with `std::weak_ptr`](#2-avoiding-circular-references-with-stdweak_ptr)
   - [3. Garbage Collection with Mark-and-Sweep](#3-garbage-collection-with-mark-and-sweep)
3. [Upcoming Topics](#upcoming-topics)

---

## Introduction

Memory management is a critical aspect of C++ programming. This repository aims to deepen your understanding of advanced techniques for managing memory, including:
- Efficient allocation and deallocation.
- Using smart pointers to manage object lifetimes.
- Avoiding memory leaks and undefined behavior.
- Exploring custom memory management strategies.

The examples provided are intended to serve as building blocks for more complex applications.

---

## Examples

### 1. Custom Deleters with `std::unique_ptr`

#### Description

This example demonstrates how to use `std::unique_ptr` with custom deleters to manage memory allocated with `malloc` and constructed using placement new. The use of a custom deleter ensures that the destructor is called, and memory is properly deallocated, avoiding potential leaks.

#### Reference

See the code in [`custom_deleters.cpp`](./custom_deleters.cpp).

---

### 2. Avoiding Circular References with `std::weak_ptr`

#### Description

This example addresses the issue of circular references when using `std::shared_ptr`. By using `std::weak_ptr`, the code avoids memory leaks caused by circular dependencies. It also demonstrates the use of `std::unique_ptr` for exclusive ownership of objects.

#### Reference

See the code in [`circular_references.cpp`](./circular_references.cpp).

---

### 3. Garbage Collection with Mark-and-Sweep

#### Description

This example demonstrates how to implement a basic garbage collection mechanism in C++ using the **mark-and-sweep** technique. The example introduces a `GarbageCollector` class that:
- Tracks dynamically allocated objects.
- Uses a **mark phase** to identify reachable objects.
- Performs a **sweep phase** to deallocate unreachable objects.

This approach helps manage complex memory relationships, such as cyclic references, which are not handled by traditional smart pointers.

#### Features
- **Mark-and-Sweep Algorithm**: Identifies and removes unreachable objects.
- **Object Management**: Tracks `Map`, `Frame`, and `Keypoint` objects, simulating a real-world scenario with hierarchical relationships.
- **Automatic Cleanup**: Demonstrates safe memory deallocation in a controlled environment.

#### Reference

See the code in [`garbage_collector.cpp`](./garbage_collector.cpp).

---

## Upcoming Topics

Here are some topics planned for future updates to this repository:
- **Custom Memory Allocators**: Implementing custom memory allocation strategies for performance-critical applications.
- **Pool Allocators**: Managing objects in pools for frequent allocations and deallocations.
- **RAII (Resource Acquisition Is Initialization)**: Best practices for resource management using RAII patterns.
- **Analyzing Memory Usage**: Tools and techniques for profiling and debugging memory usage in C++ applications.
- **Thread-Safe Memory Management**: Strategies for managing memory safely in multithreaded applications.

---

## Contributing

Contributions are welcome! If you have ideas for new topics or improvements, feel free to submit a pull request or open an issue.

---