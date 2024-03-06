#include "list.h"

typedef int hash_t;
typedef int key_t;

typedef struct hashmap{

    hash_t (*hashing_function)(key_t);
    int (*comparing_function)(hash_t, hash_t);

    list_t* buckets;

}hashmap_t;

typedef struct bucket{

    hash_t hash_key;
    list_t* bucket_content;

}bucket_t;

typedef struct content_struct{
    key_t key;
    void* content;
}content_struct_t;

/// @brief allocates space for a bucket with a set hash_key
/// @param hash_key hashed key type
/// @return pointer to the allocated bucket
bucket_t* f_bucket_constructor(hash_t hash_key);

/// @brief destroys the bucket_content list
/// @param bucket pointer to bucket_t
void f_bucket_content_freeer(bucket_t* bucket);

/// @brief allocates space for a content struct
/// @param key key of the value
/// @param content pointer to the value
/// @return pointer to the allocated struct
content_struct_t* f_content_struct_constructor(key_t key, void* content);

/// @brief allocates space for a hashmap struct and initialises the bucket list
/// @param hashing_func key_t -> hash_t
/// @param compare_func (hash_t, hash_t) -> {-1, 0, 1}
/// @return pointer to the allocated struct
hashmap_t* f_hashmap_constructor(hash_t hashing_func(key_t), int compare_func(hash_t, hash_t));

/// @brief frees the allocated hashmap struct with destroying the bucket list
/// @param hashmap pointer to the allocated hashmap
void f_hashmap_destructor(hashmap_t* hashmap);

/// @brief adds a key:value element to the hashmap
/// @param hashmap pointer to the hashmap
/// @param key key_t key
/// @param content pointer to the value
void f_hashmap_add(hashmap_t* hashmap, key_t key, void* content);

/// @brief removes an element under a key, does nothing if the key is not in the hashmap
/// @param hashmap pointer to the hashmap
/// @param key key_t key 
void f_hashmap_remove(hashmap_t* hashmap, key_t key);

/// @brief returns the pointer to the value stored in the hashmap
/// @param hashmap pointer to the hashmap
/// @param key key_t key
/// @return pointer if found, NULL if not
void* f_hashmap_find(hashmap_t* hashmap, key_t key);

/// @brief prints info about the hashmap
/// @param hashmap pointer to the hashmap
void f_hashmap_print(hashmap_t* hashmap);





