#pragma once
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T, typename Key_type = std::uint64_t>
struct slot_map
{
    using element_type = T;
    using key_type = Key_type;

private:
    std::vector<key_type> indices {}; // indices[key] = index of slot_map[key] in data
    std::vector<key_type> keys {}; // keys[i] = key that is currently mapped to index i
    std::vector<T> data {};

    key_type add_key()
    {
        std::size_t next = data.size();
        if ( next == indices.size() )
        {
            indices.push_back(static_cast<key_type>(next));
            keys.push_back(static_cast<key_type>(next));
            return static_cast<key_type>(next);
        }
        else
            return keys[next];
    }

public:
    slot_map() = default;
    slot_map(const slot_map & other) = default;
    slot_map(slot_map && other) = default;
    slot_map(const std::vector<T> & elements)
    {
        data = elements;
        indices.assign(data.size(), 0);
        keys.assign(data.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::iota(keys.begin(), keys.end(), 0);
    }
    slot_map(std::vector<T> && elements)
    {
        data = std::move(elements);
        indices.assign(data.size(), 0);
        keys.assign(data.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::iota(keys.begin(), keys.end(), 0);
    }
    slot_map & operator=(const slot_map & other) = default;
    slot_map & operator=(slot_map && other) = default;
    slot_map & operator=(const std::vector<T> & elements)
    {
        data = elements;
        indices.assign(data.size(), 0);
        keys.assign(data.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::iota(keys.begin(), keys.end(), 0);
        return *this;
    }
    slot_map & operator=(std::vector<T> && elements)
    {
        data = elements;
        indices.assign(data.size(), 0);
        keys.assign(data.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::iota(keys.begin(), keys.end(), 0);
        return *this;
    }

    const std::vector<T> & unordered_data() const { return data; }
    const std::vector<key_type> & data_indices() const { return indices; }
    const std::vector<key_type> & data_keys() const { return keys; }
    
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

    T & operator[](std::integral auto key) { return data[static_cast<std::size_t>(indices[static_cast<std::size_t>(key)])]; }
    const T & operator[](std::integral auto key) const { return data[static_cast<std::size_t>(indices[static_cast<std::size_t>(key)])]; }

    void reserve(std::size_t count)
    {
        indices.reserve(count);
        keys.reserve(count);
        data.reserve(count);
    }

    std::size_t size() const
    {
        return data.size();
    }

    template <typename Element> key_type push_back(Element && element)
    {
        key_type key = add_key();
        data.push_back(std::forward<Element>(element));
        return key;
    }

    template <typename ... Args> key_type emplace_back(Args && ... args)
    {
        key_type key = add_key();
        data.emplace_back(std::forward<Args>(args)...);
        return key;
    }

    void erase(std::integral auto key)
    {
        std::size_t erased_key = static_cast<std::size_t>(key);
        std::size_t data_size = data.size();
        if ( erased_key >= indices.size() )
            throw std::out_of_range("erase key out of range!");
        
        std::size_t erased_index = static_cast<std::size_t>(indices[erased_key]);
        if ( erased_index >= data_size )
            throw std::logic_error("attempted to erase using a dangling key!");

        if ( erased_index < data_size-1 ) // erased element is not the last element, swap to last
        {
            std::size_t last_element_key = static_cast<std::size_t>(keys[data_size-1]); 
            std::swap(indices[erased_key], indices[last_element_key]);
            std::swap(keys[erased_index], keys[data_size-1]);
            std::swap(data[erased_index], data[data_size-1]);
        }
        data.pop_back(); // pop the element
    }

    void pop_back()
    {
        data.pop_back();
    }

    void clear() {
        data = {};
        indices = {};
        keys = {};
    }

    template <typename Ostream>
    friend Ostream & operator<<(Ostream & os, slot_map map)
    {
        auto print_vec = [&os](auto & vec) {
            bool first = true;
            for ( const auto & elem : vec )
            {
                if ( first )
                {
                    os << elem;
                    first = false;
                }
                else
                    os << ", " << elem;
            }
        };

        os << "{\n"
            << "  \"indices\": [";
        print_vec(map.indices);
        os << "],\n"
            << "  \"keys\": [";
        print_vec(map.keys);
        os << "],\n"
            << "  \"data\": [";
        print_vec(map.data);
        os << "]\n"
            << "}\n";

        auto keys_copy = std::vector(map.keys.begin(), map.keys.begin()+map.data.size());
        std::sort(keys_copy.begin(), keys_copy.end());
        for ( auto key : keys_copy )
            os << key << ":" << map[key] << ", ";
        os << "\n";

        return os;
    }

};
