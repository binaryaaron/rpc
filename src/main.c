/*  * A unit test and example of how to use the simple C hashmap */
/*  *1/ */

/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include <assert.h> */

/* #include "hashmap.h" */

/* #define KEY_MAX_LENGTH (256) */
/* #define KEY_PREFIX ("somekey") */
/* #define KEY_COUNT (1024*1024) */

/* typedef struct data_struct_s */
/* { */
/*     char key_string[KEY_MAX_LENGTH]; */
/*     int number; */
/* } data_struct_t; */

/* int main(char* argv, int argc) */
/* { */
/*     int index; */
/*     int error; */
/*     map_t mymap; */
/*     char key_string[KEY_MAX_LENGTH]; */
/*     data_struct_t* value; */

/*     mymap = hashmap_new(); */

/*     /1* First, populate the hash map with ascending values *1/ */
/*     for (index=0; index<KEY_COUNT; index+=1) */
/*     { */
/*         /1* Store the key string along side the numerical value so we can free it later *1/ */
/*         value = malloc(sizeof(data_struct_t)); */
/*         snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index); */
/*         value->number = index; */

/*         error = hashmap_put(mymap, value->key_string, value); */
/*         assert(error==MAP_OK); */
/*     } */

/*     /1* Now, check all of the expected values are there *1/ */
/*     for (index=0; index<KEY_COUNT; index+=1) */
/*     { */
/*         snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index); */

/*         error = hashmap_get(mymap, key_string, (void**)(&value)); */
        
/*         /1* Make sure the value was both found and the correct number *1/ */
/*         assert(error==MAP_OK); */
/*         assert(value->number==index); */
/*     } */
    
/*     /1* Make sure that a value that wasn't in the map can't be found *1/ */
/*     snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, KEY_COUNT); */

/*     error = hashmap_get(mymap, key_string, (void**)(&value)); */
        
/*     /1* Make sure the value was not found *1/ */
/*     assert(error==MAP_MISSING); */

/*     /1* Free all of the values we allocated and remove them from the map *1/ */
/*     for (index=0; index<KEY_COUNT; index+=1) */
/*     { */
/*         snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index); */

/*         error = hashmap_get(mymap, key_string, (void**)(&value)); */
/*         assert(error==MAP_OK); */

/*         error = hashmap_remove(mymap, key_string); */
/*         assert(error==MAP_OK); */

/*         free(value); */        
/*     } */
    
/*     /1* Now, destroy the map *1/ */
/*     hashmap_free(mymap); */

/*     return 1; */
/* } */
