// A Cache simulator

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

enum class Operation { READ, WRITE };

struct CacheStats {
    int accesses; // Number of cache accesses
    int misses;   // Number of cache misses
};

struct CacheBlockEntry {
    unsigned int valid : 1;  // Valid bit
    unsigned int dirty : 1;  // Dirty bit
    unsigned int access : 1; // Access bit
    unsigned int address;    // Memory address
};

class Cache {
  public:
    Cache(const int block_size = 64, const int associativity = 4, const int cache_size = 1024,
          const int hit_latency = 1, const int miss_latency = 100)
        : block_size(block_size), associativity(associativity), cache_size(cache_size), hit_latency(hit_latency),
          miss_latency(miss_latency) {

        // Check cache parameters
        try {
            check_cache_parameters();
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        num_sets = cache_size / (block_size * associativity);

        // Initialize cache container
        CacheBlockEntry cbe = {0, 0, 0, 0};
        std::vector<CacheBlockEntry> v(associativity, cbe);
        container.resize(num_sets, v);

        // Initialize cache statistics
        stats.accesses = 0;
        stats.misses = 0;
    }

    void access(const unsigned int address, Operation op);
    void print_stats(void);
    ~Cache() {}

  private:
    int block_size;    // Cache line size in bytes
    int associativity; // Cache associativity
    int cache_size;    // Cache size in bytes
    int num_sets;      // Number of sets
    int hit_latency;   // Hit latency in cycles
    int miss_latency;  // Miss latency in cycles
    CacheStats stats;
    std::vector<std::vector<CacheBlockEntry>> container;

    void check_cache_parameters(void);
    bool is_power_of_2(const int n);
    bool is_cache_hit(const unsigned int address, Operation op);
    void add_address_to_cache(const unsigned int address, Operation op);
    void replace_cache_block(const unsigned int address, Operation op, std::vector<CacheBlockEntry> cache_set);
    unsigned int get_tag(const unsigned int address);
    unsigned int get_index(const unsigned int address);
};

bool Cache::is_power_of_2(const int n) {
    // A number is a power of two if it has exactly one bit set in its binary
    // representation. This can be verified using the property that for a power
    // of two, n and n-1 have no common set bits.
    if (n <= 0) {
        return false;
    } else {
        return (n & (n - 1)) == 0;
    }
}

void Cache::check_cache_parameters(void) {
    if (block_size < 0 || associativity < 0 || cache_size < 0 || hit_latency < 0 || miss_latency < 0) {
        throw std::invalid_argument("One or more cache parameters < 0");
    }

    if (!is_power_of_2(block_size) || !is_power_of_2(associativity) || !is_power_of_2(cache_size)) {
        throw std::invalid_argument("One or more cache parameters is not a power of 2");
    }

    if (ceil(cache_size / (block_size * associativity)) != floor(cache_size / (block_size * associativity))) {
        throw std::invalid_argument("Invalid block size, cache_size, or associativity");
    }
}

void Cache::access(const unsigned int address, Operation op) {
    stats.accesses++;
    if (!is_cache_hit(address, op)) {
        // Cache miss
        stats.misses++;
        add_address_to_cache(address, op);
    }
}

bool Cache::is_cache_hit(const unsigned int address, Operation op) {
    auto index = get_index(address);
    assert(index >= 0 && index < container.size());

    auto &cache_set = container[index];

    for (auto &cbe : cache_set) {
        if (cbe.valid && (get_tag(address) == get_tag(cbe.address))) {
            std::cout << "Cache hit - address: " << std::hex << std::showbase << address << std::dec
                      << " index: " << index << std::endl;
            cbe.access = 1;
            if (op == Operation::WRITE) {
                cbe.dirty = 1;
            }
            return true;
        }
    }

    std::cout << "Cache miss - address: " << std::hex << std::showbase << address << " index: " << std::dec << index
              << std::endl;
    return false;
}

void Cache::add_address_to_cache(const unsigned int address, Operation op) {
    auto index = get_index(address);
    assert(index >= 0 && index < container.size());

    auto &cache_set = container[index];

    for (auto &cbe : cache_set) {
        if (!cbe.valid) {
            // Available cache block
            cbe.address = address;
            cbe.access = 1;
            cbe.valid = 1;
            if (op == Operation::WRITE) {
                cbe.dirty = 1;
            }
            return;
        }
    }

    // Replace cache block in set
    replace_cache_block(address, op, cache_set);
}

void Cache::replace_cache_block(const unsigned int address, Operation op, std::vector<CacheBlockEntry> cache_set) {
    // Random replacement policy
    int index = rand() % associativity;
    auto &cbe = cache_set[index];

    std::cout << "Replacing cache block - address: " << std::hex << std::showbase << cbe.address << std::dec
              << " index: " << index << std::endl;

    if (cbe.dirty) {
        // Flush to memory
    } else {
        cbe.address = address;
        cbe.access = 1;
        cbe.valid = 1;
        if (op == Operation::WRITE) {
            cbe.dirty = 1;
        } else {
            cbe.dirty = 0;
        }
    }
}

unsigned int Cache::get_index(const unsigned int address) {
    unsigned int num_block_bits = log2(block_size);
    unsigned int num_index_bits = log2(num_sets);
    unsigned int num_tag_bits = sizeof(address) * 8 - (num_block_bits + num_index_bits);

    unsigned int index = (address << num_tag_bits) >> (num_block_bits + num_tag_bits);
    return index;
}

unsigned int Cache::get_tag(const unsigned int address) {
    unsigned int num_block_bits = log2(block_size);
    unsigned int num_index_bits = log2(num_sets);

    return address >> (num_block_bits + num_index_bits);
}

void Cache::print_stats(void) {
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "Cache size: " << cache_size << " bytes" << std::endl;
    std::cout << "Block size: " << block_size << " bytes" << std::endl;
    std::cout << "Associativity: " << associativity << std::endl;
    std::cout << "Cache accesses: " << stats.accesses << std::endl;
    std::cout << "Cache misses: " << stats.misses << std::endl;
    std::cout << "Hit rate: " << static_cast<double>(stats.accesses - stats.misses) / stats.accesses << std::endl;
}

int main(int argc, char **argv) {
    srand(time(0));

    try {
        Cache cache = Cache(8, 1, 1024, 1, 100);

        for (int i = 0; i < 100; i++) {
            unsigned int address = rand() % 10000;
            cache.access(address, Operation::READ);
            cache.access(address, Operation::WRITE);
        }

        cache.print_stats();
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
