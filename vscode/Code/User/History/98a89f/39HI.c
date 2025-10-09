#include <stdio.h>

#define TABLE_SIZE 16  // must be a power of 2

unsigned int simple_hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) ^ (hash >> 27) ^ (*str);
        printf("Hash is = %d",hash);
        // shift left to multiply and spread
        // shift right to bring high bits down
        // XOR with the current character
        str++;
    }
    return hash % TABLE_SIZE; // fit into table size
}

int main() {
    printf("Index for 'dog' = %u\n", simple_hash("dog"));
    printf("Index for 'cat' = %u\n", simple_hash("cat"));
    printf("Index for 'fish' = %u\n", simple_hash("fish"));
    return 0;
}