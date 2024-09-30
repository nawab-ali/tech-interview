// Cache Simulator

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

enum class operation { READ, WRITE };

struct CacheStats {
    int accesses; // Number of memory references
    int misses;   // Number of cache misses
};

struct CacheBlockEntry {
    unsigned int valid : 1;
    unsigned int dirty : 1;
    unsigned int access : 1;
    unsigned int address;
};

class Cache {
  public:
    Cache(const int block_size = 64, const int associativity = 4,
          const int cache_size = 1024, const int hit_latency = 1,
          const int miss_latency = 100)
        : block_size(block_size), associativity(associativity),
          cache_size(cache_size), hit_latency(hit_latency),
          miss_latency(miss_latency) {
        // Check cache parameters
        check_cache_params();

        num_sets = cache_size / (block_size * associativity);

        // Initialize cache container
        CacheBlockEntry cbe = {0, 0, 0, 0};
        vector<CacheBlockEntry> v(associativity, cbe);
        container = vector<vector<CacheBlockEntry>>(num_sets, v);

        // Initialize stats
        stats.accesses = 0;
        stats.misses = 0;
    }

    void access(const unsigned int address, operation op) {
        stats.accesses++;

        if (!cache_hit(address, op)) {
            // Cache miss
            stats.misses++;
            add_address_to_cache(address, op);
        }
    }

    void print_stats(void) {
        cout << setprecision(2) << fixed;
        cout << "Cache size: " << cache_size << " bytes" << endl;
        cout << "Block size: " << block_size << " bytes" << endl;
        cout << "Associativity: " << associativity << endl;
        cout << "Cache accesses: " << stats.accesses << endl;
        cout << "Cache misses: " << stats.misses << endl;
        cout << "Hit rate: "
             << static_cast<double>(stats.accesses - stats.misses) /
                    stats.accesses
             << endl;
    }

    ~Cache() {}

  private:
    int num_sets;
    int block_size; // in bytes
    int associativity;
    int cache_size;   // in bytes
    int hit_latency;  // in cycles
    int miss_latency; // in cycles
    CacheStats stats;
    vector<vector<CacheBlockEntry>> container;

    bool is_power_of_2(const int n) {
        if (n < 1) {
            return (false);
        } else {
            return (ceil(log2(n)) == floor(log2(n)));
        }
    }

    void check_cache_params(void) {
        if (block_size < 0 || associativity < 0 || cache_size < 0 ||
            hit_latency < 0 || miss_latency < 0) {
            throw invalid_argument("One or more cache parameters < 0");
        }

        if (!is_power_of_2(block_size) || !is_power_of_2(associativity) ||
            !is_power_of_2(cache_size)) {
            throw invalid_argument(
                "One or more cache parameters not a power of 2");
        }

        if (ceil(cache_size / (block_size * associativity)) !=
            floor(cache_size / (block_size * associativity))) {
            throw invalid_argument(
                "Invalid cache_size, block_size, or associativity");
        }
    }

    unsigned int get_index(const unsigned int address) {
        unsigned int num_block_bits = log2(block_size);
        unsigned int num_index_bits = log2(num_sets);
        unsigned int num_tag_bits =
            sizeof(address) * 8 - (num_block_bits + num_index_bits);

        unsigned int index =
            (address << num_tag_bits) >> (num_block_bits + num_tag_bits);

        return (index);
    }

    unsigned int get_tag(const unsigned int address) {
        unsigned int num_block_bits = log2(block_size);
        unsigned int num_index_bits = log2(num_sets);

        return (address >> (num_block_bits + num_index_bits));
    }

    bool cache_hit(const unsigned int address, operation op) {
        auto index = get_index(address);

        assert(index >= 0 && index < container.size());
        vector<CacheBlockEntry> &cache_set = container[index];

        for (auto &cbe : cache_set) {
            if (cbe.valid && (get_tag(address) == get_tag(cbe.address))) {
                cout << "Cache hit - address: " << address
                     << " index: " << index << endl;
                cbe.access = 1;
                if (op == operation::WRITE) {
                    cbe.dirty = 1;
                }
                return (true);
            }
        }

        cout << "Cache miss - address: " << address << " index: " << index
             << endl;
        return (false);
    }

    void replace_cache_block(const unsigned int address, operation op,
                             vector<CacheBlockEntry> &cache_set) {
        // Random replacement policy
        int index = rand() % associativity;
        CacheBlockEntry &cbe = cache_set[index];

        cout << "Replacing cache block - address: " << cbe.address
             << " index: " << index << endl;

        if (cbe.dirty) {
            // Flush to memory
        } else {
            cbe.valid = 1;
            cbe.access = 1;
            if (op == operation::WRITE) {
                cbe.dirty = 1;
            } else {
                cbe.dirty = 0;
            }
            cbe.address = address;
        }
    }

    void add_address_to_cache(const unsigned int address, operation op) {
        auto index = get_index(address);

        assert(index >= 0 && index < container.size());
        vector<CacheBlockEntry> &cache_set = container[index];

        for (auto &cbe : cache_set) {
            if (!cbe.valid) {
                // Available cache block
                cbe.valid = 1;
                cbe.access = 1;
                if (op == operation::WRITE) {
                    cbe.dirty = 1;
                }
                cbe.address = address;
                return;
            }
        }

        // Replace block in set
        replace_cache_block(address, op, cache_set);
    }
};

int main(int argc, char **argv) {
    srand(time(0));

    try {
        Cache cache = Cache(8, 1, 1024, 1, 100);

        for (int i = 0; i < 100; i++) {
            unsigned int address = rand() % 10000;
            cache.access(address, operation::READ);
            cache.access(address, operation::WRITE);
        }

        cache.print_stats();
    } catch (exception &e) {
        cout << e.what() << endl;
        return (1);
    }

    return (0);
}
