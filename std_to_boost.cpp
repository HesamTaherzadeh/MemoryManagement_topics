#include <iostream>
#include <boost/shared_ptr.hpp>
#include <memory>

template <typename T>
boost::shared_ptr<T> std_to_boost(std::shared_ptr<T>& std_ptr) {  
    return boost::shared_ptr<T>(std_ptr.get(), [&std_ptr](T*) mutable { std_ptr.reset(); });
}

int main() {
    std::shared_ptr<int> std_ptr = std::make_shared<int>(10);
    boost::shared_ptr<int> boost_ptr = std_to_boost(std_ptr);

    std::cout << *std_ptr << std::endl; 
    return 0;
}