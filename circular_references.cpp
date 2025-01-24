#include <iostream>
#include <memory>

class Frame;
class KeypointsInFrame;

class KeypointsInFrame {
public:
  KeypointsInFrame() { std::cout << " KeypointsInFrame() " << std::endl; }

  ~KeypointsInFrame() { std::cout << " ~KeypointsInFrame() " << std::endl; }

  // Sets the associated Frame using a weak pointer
  void setFrame(std::weak_ptr<Frame> frame) {
    if (!frame.expired()) {  // Check if the weak pointer is still valid
      this->frame = frame;
    }
  }

private:
  std::weak_ptr<Frame> frame;  // Weak reference to avoid circular dependency
};

class Frame {
public:
  Frame() { std::cout << " Frame() " << std::endl; }

  ~Frame() { std::cout << " ~Frame() " << std::endl; }

  // Sets the KeypointsInFrame object for this Frame using a unique pointer
  void setKeyPoint(std::unique_ptr<KeypointsInFrame> kp) {
    keypointsInFrame = std::move(kp);  // Transfer ownership of the unique pointer
  }

private:
  std::unique_ptr<KeypointsInFrame> keypointsInFrame;  // Unique ownership of KeypointsInFrame
};

int main() {
  /*
   * This setup avoids circular references:
   * - The Frame holds a unique_ptr to its KeypointsInFrame, ensuring unique ownership.
   * - The KeypointsInFrame holds a weak_ptr to the Frame, avoiding circular dependency.
   *
   * If both members used shared_ptr, a circular reference would occur, leading to memory leaks.
   * Using weak_ptr ensures that the memory of the Frame is properly released when no other
   * shared_ptr references exist.
   */

  // Create a shared Frame
  std::shared_ptr<Frame> frame = std::make_shared<Frame>();

  // Create a unique KeypointsInFrame
  auto kp = std::make_unique<KeypointsInFrame>();

  // Associate the Frame with KeypointsInFrame
  kp->setFrame(frame);

  // Associate the KeypointsInFrame with the Frame
  frame->setKeyPoint(std::move(kp));

  // Frame and KeypointsInFrame will be properly destroyed when they go out of scope
  return 0;
}
