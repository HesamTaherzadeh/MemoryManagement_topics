#include <iostream>
#include <memory>

class Frame {
public:
    Frame() {
        std::cout << " Frame() " << std::endl;
    }

    ~Frame() {
        std::cout << " ~Frame() " << std::endl;
    }
};

// Custom deleter using a struct
struct CustomDeleter {
    void operator()(Frame* frame) {
        if (frame) {
            frame->~Frame();  // Call the destructor explicitly
            free(frame);      // Free the allocated memory
        }
    }
};

// Custom deleter as a function
void custom_deleter(Frame* frame) {
    if (frame) {
        frame->~Frame();  // Call the destructor explicitly
        free(frame);      // Free the allocated memory
    }
}

int main() {
    /*
        Using raw memory allocation with malloc:
        - Allocating memory using malloc doesn't call the constructor.
        - Using placement new to initialize the object in the allocated memory.
        - If malloc fails, it returns nullptr, which we must check to avoid undefined behavior.
        - Manually calling the destructor and free to release resources.

        Proper use of unique_ptr:
        - Using std::unique_ptr with a custom deleter ensures proper cleanup, 
          including calling the destructor and freeing memory, even in case of exceptions.
    */

    // Allocate raw memory using malloc
    void* rawMemory = malloc(sizeof(Frame));
    if (!rawMemory) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return -1;
    }

    // Construct a Frame object in the allocated memory using placement new
    Frame* frame = new (rawMemory) Frame();

    // Define a lambda deleter
    auto lambda_deleter = [](Frame* ptr) {
        if (ptr) {
            ptr->~Frame();  // Explicitly call the destructor
            free(ptr);      // Free the allocated memory
        }
    };

    // Use unique_ptr with a lambda deleter
    // std::unique_ptr<Frame, decltype(lambda_deleter)> frame_ptr(frame, lambda_deleter);

    // Use unique_ptr with a custom deleter struct
    // std::unique_ptr<Frame, CustomDeleter> frame_ptr(frame, CustomDeleter());

    // Use unique_ptr with a custom deleter function
    std::unique_ptr<Frame, void(*)(Frame*)> frame_ptr(frame, custom_deleter);

    // Frame is automatically destroyed and memory freed when frame_ptr goes out of scope
    return 0;
}
