#pragma once
#include <iostream>
#include <cstddef>
#include <cassert>
#include <cstdint>
#include <memory>
#include <cstring>
#include <algorithm>
#include <sstream>

// Implementation based on 
// https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void*))
#endif

class ArenaAllocator
{
public:

	ArenaAllocator(void* buffer, size_t buffer_len) 
    	: buffer(static_cast<std::byte*>(buffer)),
		  buffer_len(buffer_len),
		  curr_offset(0), 
		  prev_offset(0) {
	}

	void *alloc_align(size_t size, size_t align) {
		// Align 'curr_offset' forward to the specified alignment
		uintptr_t curr_ptr = reinterpret_cast<uintptr_t>(buffer) + curr_offset;
		uintptr_t offset = align_forward(curr_ptr, align);
		offset -= reinterpret_cast<uintptr_t>(buffer); // Change to relative offset

		// Check to see if the backing memory has space left
		if (offset + size <= buffer_len) {
			void* ptr = &buffer[offset];
			prev_offset = offset;
			curr_offset = offset + size;

			// Zero new memory by default
			std::memset(ptr, 0, size);
			return ptr;
		}
		// Return NULL if the arena is out of memory (or handle differently)
		return nullptr;
	}

	void *alloc(size_t size) {
		return alloc_align(size, DEFAULT_ALIGNMENT);
	}

	void free(void* ptr) {
		// Do nothing
	}

	void free_all() {
		curr_offset = 0;
		prev_offset = 0;
	}

	size_t mem_used() const {
		return curr_offset;
	}

	size_t mem_available() const {
		return buffer_len - curr_offset;
	}

	size_t mem_total() const {
		return buffer_len;
	}

private:
	std::byte* buffer; // points to beginning of buffer of bytes
	size_t buffer_len;
	size_t prev_offset;
	size_t curr_offset; // Where we are currently in the arena


	bool is_power_of_two(uintptr_t x) {
		return (x & (x - 1)) == 0;
	}

	uintptr_t align_forward(uintptr_t ptr, size_t align) {
		uintptr_t p, a, modulo;

		assert(is_power_of_two(align));

		p = ptr;
		a = align;
		// Same as (p % a) but faster as 'a' is a power of two
		modulo = p & (a - 1);

		if (modulo != 0) {
			// If 'p' address is not aligned, push the address to the
			// next value which is aligned
			p += a - modulo;
		}
		return p;
	}
};


// For handling out of mem errors
class AllocatorOutOfMemoryError : public std::runtime_error {
public:
    AllocatorOutOfMemoryError(const ArenaAllocator& allocator)
        : std::runtime_error(create_error_message(allocator)),
          m_allocator(allocator) {}

private:
    const ArenaAllocator& m_allocator;

    static std::string create_error_message(const ArenaAllocator& allocator) {
        std::ostringstream oss;
        oss << "Allocator out of memory! "
			<< "[Bytes allocated: " << allocator.mem_total() << "] "
			<< "[Bytes used: " << allocator.mem_used() << "] "
            << "[Bytes available: " << allocator.mem_available() << "]";
        return oss.str();
    }
};