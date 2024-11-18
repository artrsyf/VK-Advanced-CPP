#pragma once

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>

template<typename T>
class FixedVector {
public:
    FixedVector() = default;

    explicit FixedVector(size_t size)
        : data(size)
        , maxSize(size)
    {
    }

    void initialize(size_t size)
    {
        if (!data.empty())
            throw std::runtime_error("Already initialized");
        if (size < data.size()) {
            throw std::invalid_argument("New size must be greater than or equal to the current size");
        }
        maxSize = size;
    }

    T removeMaxByCriteria(std::function<bool(const T&, const T&)> criterion)
    {
        if (data.empty()) {
            throw std::runtime_error("Can't remove element, struct is empty.");
        }

        auto maxIt = std::max_element(data.begin(), data.end(),
            [&](const T& a, const T& b) {
                return criterion(a, b);
            });

        T maxElement = *maxIt;
        data.erase(maxIt);

        return maxElement;
    }

    void add(const T& item)
    {
        if (data.size() >= maxSize) {
            throw std::overflow_error("FixedVector overflow: Maximum size reached");
        }
        data.push_back(item);
    }

    T& operator[](size_t index)
    {
        return data.at(index);
    }

    const T& operator[](size_t index) const
    {
        return data.at(index);
    }

    size_t size() const
    {
        return data.size();
    }

    bool empty() const
    {
        return data.empty();
    }

    size_t capacity() const
    {
        return maxSize;
    }

    typename std::vector<T>::iterator begin() { return data.begin(); }
    typename std::vector<T>::iterator end() { return data.end(); }
    typename std::vector<T>::const_iterator begin() const { return data.begin(); }
    typename std::vector<T>::const_iterator end() const { return data.end(); }

private:
    std::vector<T> data;
    size_t maxSize = 0;
};
