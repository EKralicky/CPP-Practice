#pragma once
#include <iostream>
#include <cstddef>
#include <cassert>
#include <cstdint>
#include <memory>
#include <cstring>
#include <algorithm>

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2*sizeof(void *))
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
		uintptr_t curr_ptr = (uintptr_t)buffer + (uintptr_t)curr_offset;
		uintptr_t offset = align_forward(curr_ptr, align);
		offset -= (uintptr_t)buffer; // Change to relative offset

		// Check to see if the backing memory has space left
		if (offset+size <= buffer_len) {
			void *ptr = &buffer[offset];
			prev_offset = offset;
			curr_offset = offset+size;

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

	void free(void *ptr) {
		// Do nothing
	}

	void free_all() {
		curr_offset = 0;
		prev_offset = 0;
	}

private:
	std::byte* buffer; // points to beginning of buffer of bytes
	size_t buffer_len;
	size_t prev_offset;
	size_t curr_offset; // Where we are currently in the arena


	bool is_power_of_two(uintptr_t x) {
		return (x & (x-1)) == 0;
	}

	uintptr_t align_forward(uintptr_t ptr, size_t align) {
		uintptr_t p, a, modulo;

		assert(is_power_of_two(align));

		p = ptr;
		a = (uintptr_t)align;
		// Same as (p % a) but faster as 'a' is a power of two
		modulo = p & (a-1);

		if (modulo != 0) {
			// If 'p' address is not aligned, push the address to the
			// next value which is aligned
			p += a - modulo;
		}
		return p;
	}

};