#include <inc/memlayout.h>
#include <kern/kheap.h>
#include <kern/memory_manager.h>

//2022: NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)
#include <inc/memlayout.h>
#include <kern/kheap.h>
#include <kern/memory_manager.h>

//2022: NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)

#define KHEAP_PAGES ((KERNEL_HEAP_MAX - KERNEL_HEAP_START) / PAGE_SIZE)
uint32 kheap_allocation_sizes[KHEAP_PAGES] = {0};


void* kmalloc(unsigned int size)
{
	// NOTE: Allocation using NEXTFIT strategy
	// NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)

	if (size == 0) return NULL;

	uint32 rounded_size = ROUNDUP(size, PAGE_SIZE);
	uint32 num_of_pages = rounded_size / PAGE_SIZE;
	static uint32 last_allocated_address = KERNEL_HEAP_START;

	uint32 curr = last_allocated_address;
	int pages_found = 0;
	uint32 block_start = 0;
	int loops_time = 0;
	uint32 *ptr_page_table = NULL;

	while(1 == 1){
		struct Frame_Info *ptr = get_frame_info(ptr_page_directory, (void*)curr, &ptr_page_table);

		if (ptr == NULL){
			if (pages_found == 0)
				block_start = curr;
			pages_found++;

			if (pages_found == num_of_pages)
				break;
		}
		else{
			block_start = 0;
			pages_found = 0;
		}

		curr = curr + PAGE_SIZE;

		if (curr >= KERNEL_HEAP_MAX){
			curr = KERNEL_HEAP_START;
			loops_time++;
			// FIX: If we wrap around, the contiguous block is broken! We must reset the counter.
			pages_found = 0;
			block_start = 0;
		}

		if(curr >= last_allocated_address && loops_time == 1){
			cprintf("No pages Available");
			return NULL;
		}
	}

	for(uint32 i = 0; i < num_of_pages; i++){
		uint32 virtual_address = block_start + i * PAGE_SIZE;
		struct Frame_Info *ptr = NULL;

		uint32 frame_for_page = allocate_frame(&ptr);
		if(frame_for_page == E_NO_MEM){
			for(int j = 0; j < i; j++){
				unmap_frame(ptr_page_directory, (void*)(block_start + j * PAGE_SIZE));
			}
			return NULL;
		}

		frame_for_page = map_frame(ptr_page_directory, ptr, (void*)virtual_address, PERM_WRITEABLE);
		if (frame_for_page == E_NO_MEM){
			free_frame(ptr);
			for(int j = 0; j < i; j++){
				unmap_frame(ptr_page_directory, (void*)(block_start + j * PAGE_SIZE));
			}
			return NULL;
		}
	}

	last_allocated_address = block_start + rounded_size;
	if(last_allocated_address >= KERNEL_HEAP_MAX)
		last_allocated_address = KERNEL_HEAP_START;

	// ==============================================================================
	// CRITICAL ADDITION FOR KFREE: Store the size of this allocation!
	uint32 alloc_index = (block_start - KERNEL_HEAP_START) / PAGE_SIZE;
	kheap_allocation_sizes[alloc_index] = num_of_pages;
	// ==============================================================================

	return (void *) block_start;
}


void kfree(void* virtual_address)
{
    if (virtual_address == NULL)
        return;

    uint32 va = (uint32)virtual_address;

    if (va < KERNEL_HEAP_START || va >= KERNEL_HEAP_MAX)
        return;

    if (va % PAGE_SIZE != 0)
        return;
    uint32 index = (va - KERNEL_HEAP_START) / PAGE_SIZE;
    uint32 num_pages = kheap_allocation_sizes[index];
    if (num_pages == 0)
        return;


    for (uint32 i = 0; i < num_pages; i++)
    {
        uint32 current_va = va + (i * PAGE_SIZE);

        // Clears the PTE and frees the frame — does NOT remove the table
        unmap_frame(ptr_page_directory, (void*)current_va);
    }

    kheap_allocation_sizes[index] = 0;
}


/*unsigned int kheap_virtual_address(unsigned int physical_address)
{
	uint32 *ptr_page_table = NULL;

	// 1. Strip the lowest 12 bits to get the BASE physical address of the frame
	// Example: physical_address 0x100050 becomes 0x100000
	uint32 frame_phys_base = physical_address & ~0xFFF;

	// 2. MUST use '<', not '<=', to prevent 32-bit integer overflow!
	for (uint32 i = KERNEL_HEAP_START; i < KERNEL_HEAP_MAX; i += PAGE_SIZE)
	{
		struct Frame_Info *ptr = get_frame_info(ptr_page_directory, (void*)i, &ptr_page_table);

		if (ptr == NULL){
			// frame is not mapped
			continue;
		}
		else {
			// frame is mapped
			uint32 pa = to_physical_address(ptr);

			// 3. Compare the base frame addresses
			if (pa == frame_phys_base)
			{
				// We found the correct frame!
				// Now, extract the exact byte offset from the original physical_address
				uint32 offset = PGOFF(physical_address);

				// Return the virtual base address + the byte offset
				return i + offset;
			}
		}
	}
	// no match found
	return 0;
}                      */
	//return the virtual address corresponding to given physical_address
	//refer to the project presentation and documentation for details

	//change this "return" according to your answer


unsigned int kheap_physical_address(unsigned int virtual_address)
{
	//TODO: [PROJECT 2026 - [4] Kernel Heap] kheap_physical_address()

	uint32 *ptr_page_table = NULL;

	struct Frame_Info *ptr_frame_info = get_frame_info(ptr_page_directory, (void*)virtual_address, &ptr_page_table);

	if (ptr_frame_info != NULL)
	{
		uint32 physical_base = to_physical_address(ptr_frame_info);

		uint32 offset = PGOFF(virtual_address);

		return physical_base + offset;
	}

	return 0;
}


