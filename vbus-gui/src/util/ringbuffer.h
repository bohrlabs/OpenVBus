#pragma once
#include <vector>
#include <cstddef>

namespace ovb {

    template<class T>
    class RingBuffer {
        std::vector<T> data;
        size_t         head = 0;
        bool           full = false;

      public:
        explicit RingBuffer(size_t cap)
            : data(cap) {}
        void push(const T &v) {
            data[head] = v;
            head       = (head + 1) % data.size();
            if (head == 0)
                full = true;
        }
        template<class F>
        void for_each(F f) const {
            size_t n = full ? data.size() : head;
            for (size_t i = 0; i < n; i++) {
                f(data[(full ? head : 0) + i % data.size()]);
            }
        }
    };

} // namespace ovb