//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_TYPES_H
#define TWIG_ENGINE_TYPES_H

#include <cstdint>
#include <algorithm>

namespace TE {
    namespace Types {
        template <typename T>
        struct Array {
        private:
            uint32_t size;
            T* data;
        public:
            Array(uint32_t size)
            {
                this->size = size;
                data = new T[size];
            }
            Array (uint32_t size, T data[])
            {
                this->size = size;
                for (uint32_t i = 0; i < size; i++)
                    this->data[i] = data[i];
            }
            inline T& Get(uint32_t index) { return data[index]; }
            inline T* Get() { return data; }
            inline uint32_t Size() { return size; }
        };
    }
}

#endif //TWIG_ENGINE_TYPES_H
