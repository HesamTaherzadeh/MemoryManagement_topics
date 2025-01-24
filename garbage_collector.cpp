#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

typedef class CollectableObject* CollectableObjectPtr;

enum class ObjStatus { FAILURE, SUCCESS, ALREADY_MARKED };

class CollectableObject {
public:
  CollectableObject() : marked(false) {}

  virtual ~CollectableObject() {}

  void mark() { marked = true; }

  void unmark() { marked = false; }

  bool getMarked() const { return marked; }

private:
  bool marked;
};

class Keypoint : public CollectableObject {
public:
  explicit Keypoint(int id) : id(id) {}
  ~Keypoint() { std::cout << "Destroying Keypoint " << id << std::endl; }

private:
  int id;
};

class Frame : public CollectableObject {
public:
  explicit Frame(int id) : id(id) {}
  ~Frame() { std::cout << "Destroying Frame " << id << std::endl; }

private:
  int id;
};

class Map : public CollectableObject {
public:
  explicit Map(int id) : id(id) {}
  ~Map() { std::cout << "Destroying Map " << id << std::endl; }

private:
  int id;
};

class GarbageCollector {
public:
  ObjStatus markObj(CollectableObjectPtr root) {
    if (root == nullptr) return ObjStatus::FAILURE;
    if (root->getMarked()) return ObjStatus::ALREADY_MARKED;
    root->mark();
    for (CollectableObjectPtr ref : refrences[root]) {
      markObj(ref);
    }
    return ObjStatus::SUCCESS;
  }

  ObjStatus addObj(CollectableObjectPtr obj) {
    if (obj == nullptr) {
      return ObjStatus::FAILURE;
    }
    vecOfObj.push_back(obj);
    return ObjStatus::SUCCESS;
  }

  ObjStatus addRefrences(CollectableObjectPtr from, CollectableObjectPtr to) {
    if (from != nullptr && to != nullptr) {
      refrences[from].push_back(to);
      return ObjStatus::SUCCESS;
    } else {
      return ObjStatus::FAILURE;
    }
  }

  ObjStatus sweep() {
    for (auto it = vecOfObj.begin(); it != vecOfObj.end();) {
      if ((*it)->getMarked()) {
        delete *it;
        it = vecOfObj.erase(it);
      } else {
        ++it;
      }
    }
    return ObjStatus::SUCCESS;
  }

private:
  std::vector<CollectableObjectPtr> vecOfObj;
  std::unordered_map<CollectableObjectPtr, std::vector<CollectableObjectPtr>> refrences;
};

int main(int argc, char** argv) {
  GarbageCollector gc;

  Map* map = new Map(1);
  Map* map2 = new Map(2);
  Frame* frame = new Frame(1);
  Keypoint* keypoint1 = new Keypoint(1);
  Keypoint* keypoint2 = new Keypoint(2);

  gc.addObj(map);
  gc.addObj(map2);
  gc.addObj(frame);
  gc.addObj(keypoint1);
  gc.addObj(keypoint2);

  // Add references
  gc.addRefrences(map, frame);
  gc.addRefrences(frame, keypoint1);
  gc.addRefrences(frame, keypoint2);

  gc.markObj(map);
  gc.markObj(map2);

  std::cout << "Running Garbage Collector..." << std::endl;
  gc.sweep();

  std::cout << "Running Garbage Collector after breaking root..." << std::endl;
  gc.sweep();

  return 0;
}
