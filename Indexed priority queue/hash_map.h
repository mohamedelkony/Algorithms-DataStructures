#ifndef hash_map_h
#define hash_map_h


#define int_key_type 1
//#define float_key_type 1
//#define string_key_type 1

typedef int key_type;
typedef int value_type;

typedef struct _item item;

typedef struct _hash_map hash_map;



hash_map* new_hash_map(int);



void h_map_insert(hash_map* t, key_type key, value_type value);

int h_map_contains(hash_map* t, key_type key);

void h_map_erase(hash_map*, key_type);

//O(1) avg
value_type h_map_get_value(hash_map*, key_type);

void h_map_print(hash_map*);

static unsigned hash_string(hash_map*, char*);
static unsigned xorHash_string(hash_map*, char*);
static unsigned hash_int(hash_map*, int);
static unsigned hash_float(hash_map*, float);

static unsigned hash_generic(hash_map*t, key_type key);
static int is_equal_generic(key_type k1, key_type k2);

unsigned long long  comparsions;//for time analysis;

#endif