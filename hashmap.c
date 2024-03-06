#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

hashmap_t* f_hashmap_constructor(hash_t hashing_func(key_t), int compare_func(hash_t, hash_t))
{
    hashmap_t* new_hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));
    new_hashmap->hashing_function = hashing_func;
    new_hashmap->comparing_function = compare_func;
    new_hashmap->buckets = f_list_constructor();
    return new_hashmap;
}

void f_hashmap_destructor(hashmap_t *hashmap)
{
    f_list_destructor(hashmap->buckets);
    free(hashmap);
}


/// @brief looks for a proper bucket node
/// @param hashmap hashmap pointer
/// @param hashed_key hash_t hashed key
/// @return the proper node or one after if found, NULL if not found
node_t* bucket_node_finder(hashmap_t* hashmap, hash_t hashed_key)
{
    // find the proper bucket
    node_t* found_bucket_node = NULL;
    if (hashmap->buckets->size == 0)
    {
        // if no buckets return NULL
        return NULL;
    }
    else
    {
        // otherwise traverse the list
        found_bucket_node = hashmap->buckets->head;
        while (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) > 0)
        {
            found_bucket_node = found_bucket_node->next;
            if (found_bucket_node == NULL)
            {
                break;
            }
        }

        // if found_bucket_node == NULL, we reached the end of the list
        if (found_bucket_node == NULL)
        {
            return NULL;
        }
    }

    return found_bucket_node;
}

void f_hashmap_add(hashmap_t* hashmap, key_t key, void *content)
{
    hash_t hashed_key = hashmap->hashing_function(key);
    
    // find the proper bucket
    node_t* found_bucket_node = bucket_node_finder(hashmap, hashed_key);
    if (found_bucket_node == NULL)
    {
        // if no place for bucket on the bucket list
        // add it on the back
        f_list_insert_back(hashmap->buckets, f_bucket_constructor(hashed_key));
        found_bucket_node = hashmap->buckets->tail;
    }
    else
    {
        hash_t found_bucket_hash = ((bucket_t*)(found_bucket_node->content))->hash_key;
        if (hashmap->comparing_function(found_bucket_hash, hashed_key) == 0)
        {
            // if the hashed key the same
            // good bucket found
        }

        /*
        
        // if found_bucket_node == NULL, we reached the end of the list
        if (found_bucket_node == NULL)
        {
            f_list_insert_back(hashmap->buckets, f_bucket_constructor(hashed_key));
            found_bucket_node = hashmap->buckets->tail;
        }
        // if comparing returns 0 means we found the bucket
        else if (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) == 0)
        {
            // checking if key already in
            bucket_t* found_bucket = (bucket_t*)(found_bucket_node->content);
            node_t* found_content_node = found_bucket->bucket_content->head;
            for (int i = 0; i < found_bucket->bucket_content->size; i++)
            {
                if (((content_struct_t*)(found_content_node->content))->key == key)
                {
                    // FOUND IT, replace the value
                    ((content_struct_t*)(found_content_node->content))->content = content;
                    return;
                }
                found_content_node = found_content_node->next;
            }

        }
        // if comparing function returns -1 it means we passed the place for the bucket
        else if (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) < 0)
        {
            f_list_insert_before(hashmap->buckets, f_bucket_constructor(hashed_key), found_bucket_node);
            found_bucket_node = found_bucket_node->prev;
        }  
        */
    }
    // now that we have out bucket we can add our key:value
    f_list_insert_back(((bucket_t*)(found_bucket_node->content))->bucket_content, f_content_struct_constructor(key, content));
    
}

void f_hashmap_remove(hashmap_t *hashmap, key_t key)
{
    hash_t hashed_key = hashmap->hashing_function(key);
    
    // find the proper bucket
    node_t* found_bucket_node = NULL;
    if (hashmap->buckets->size == 0)
    {
        // if no buckets, leave
        return;
    }
    else
    {
        // otherwise traverse the list
        found_bucket_node = hashmap->buckets->head;
        while (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) > 0)
        {
            found_bucket_node = found_bucket_node->next;
            if (found_bucket_node == NULL)
            {
                break;
            }
        }

        // if found_bucket_node == NULL, we reached the end of the list
        if (found_bucket_node == NULL)
        {
            return;
        }
        // if comparing returns 0 means we found the bucket
        else if (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) == 0)
        {
            // we need to traverse the bucket
            bucket_t* found_bucket = (bucket_t*)(found_bucket_node->content);
            node_t* found_content_node = found_bucket->bucket_content->head;
            for (int i = 0; i < found_bucket->bucket_content->size; i++)
            {
                if (((content_struct_t*)(found_content_node->content))->key == key)
                {
                    // FOUND IT
                    f_list_remove(found_bucket->bucket_content, found_content_node);
                    if (found_bucket->bucket_content->size == 0)
                    {
                        f_bucket_content_freeer(found_bucket);
                        f_list_remove(hashmap->buckets, found_bucket_node);
                    }
                    return;
                }
                found_content_node = found_content_node->next;
            }
        }
        // if comparing function returns -1 it means we passed the place for the bucket
        else if (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) < 0)
        {
            return;
        }  
    }
}

void *f_hashmap_find(hashmap_t* hashmap, key_t key)
{

    hash_t hashed_key = hashmap->hashing_function(key);
    
    // find the proper bucket
    node_t* found_bucket_node = NULL;
    if (hashmap->buckets->size == 0)
    {
        // if no buckets, leave
        return NULL;
    }
    else
    {
        // otherwise traverse the list
        found_bucket_node = hashmap->buckets->head;
        while (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) > 0)
        {
            found_bucket_node = found_bucket_node->next;
            if (found_bucket_node == NULL)
            {
                break;
            }
        }

        // if found_bucket_node == NULL, we reached the end of the list
        if (found_bucket_node == NULL)
        {
            return NULL;
        }
        // if comparing returns 0 means we found the bucket
        else if (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) == 0)
        {
            // we need to traverse the bucket
            bucket_t* found_bucket = (bucket_t*)(found_bucket_node->content);
            node_t* found_content_node = found_bucket->bucket_content->head;
            for (int i = 0; i < found_bucket->bucket_content->size; i++)
            {
                if (((content_struct_t*)(found_content_node->content))->key == key)
                {
                    // FOUND IT
                    return ((content_struct_t*)(found_content_node->content))->content;
                }
                found_content_node = found_content_node->next;
            }
        }
        // if comparing function returns -1 it means we passed the place for the bucket
        else if (hashmap->comparing_function(hashed_key, ((bucket_t*)(found_bucket_node->content))->hash_key) < 0)
        {
            return NULL;
        }  
    }
    return NULL;
}

void f_hashmap_print(hashmap_t *hashmap)
{
    printf("HASHMAP ALLOCATED AT: %p\n", hashmap);
    printf("number of allocated buckets: %d\n", hashmap->buckets->size);
    node_t* node = hashmap->buckets->head;
    node_t* bucket_node = NULL;
    bucket_t* bucket = NULL;
    for (int i = 1; i <= hashmap->buckets->size; i++)
    {
        bucket = node->content;
        printf("Bucket %d at %p\n", i, bucket);
        printf("Hashed Key: %d, %d Items\n", bucket->hash_key, bucket->bucket_content->size);
        bucket_node = bucket->bucket_content->head;
        for (int j = 1; j <= bucket->bucket_content->size; j++)
        {
            content_struct_t* content_struct = bucket_node->content;
            printf("Item %d: Key %d, Value at %p\n", j, content_struct->key, content_struct->content);
            bucket_node = bucket_node->next;
        }
        node = node->next;


    }

}

bucket_t *f_bucket_constructor(hash_t hash_key)
{
    bucket_t* new_bucket = (bucket_t*)malloc(sizeof(bucket_t));
    new_bucket->hash_key = hash_key;
    new_bucket->bucket_content = f_list_constructor();
    return new_bucket;
}

void f_bucket_content_freeer(bucket_t *bucket)
{
    f_list_destructor(bucket->bucket_content);
    //free(bucket);
    return;
}

content_struct_t *f_content_struct_constructor(key_t key, void *content)
{
    content_struct_t* new_struct = (content_struct_t*)malloc(sizeof(content_struct_t));
    new_struct->key = key;
    new_struct->content = content;
    return new_struct;
}

