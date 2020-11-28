#pragma once
#include <stdint.h>

// table constants to tune for performance
#define SCHREME_TBL_MIN_SIZE 16
#define SCHREME_TBL_GROWTH_FACTOR 2

/*
 *  
 */

enum SCHREME_TBL_ERROR_CODES
{
  NO_ERROR = 0,
  OUT_OF_MEMORY,
  INTERNAL_ERROR
};

/*
 * Reserved keys for internal table use
 */
typedef enum
{
  KEY_EMPTY,
  KEY_TOMBSTONE
} schreme_tbl_reserved_keys;

/*
 * key value structs
 */

typedef struct
{
  uint32_t size;
  const uint8_t* data;
} schreme_tbl_val;

typedef struct
{
  uint32_t key;
  uint32_t val_offset;
  uint32_t val_size;
} schreme_kv;

/* linear time lookup tables */
typedef struct
{
  schreme_kv* kv_tbl;
  uint8_t* val_tbl;
  uint32_t kv_tbl_size;
  uint32_t val_tbl_size;
  uint32_t kv_tbl_capacity;
  uint32_t val_tbl_capacity;
} schreme_fkey_lookup_table;

typedef struct
{
  uint8_t* key_table;
  schreme_fkey_lookup_table* indexed_tbl;
} schreme_vkey_lookup_table;

/* interface for the fixed size key table */
void schreme_fkey_lookup_table_init(schreme_fkey_lookup_table* tbl);
int schreme_fkey_lookup_table_insert(schreme_fkey_lookup_table* tbl, 
                                          uint32_t key, schreme_tbl_val val);
void schreme_fkey_lookup_table_lookup(schreme_fkey_lookup_table* tbl,
                                          uint32_t key, schreme_tbl_val* val);

/* internal utilities for fixed size key table */
void schreme_fkey_lookup_table_resize_kv_tbl(schreme_fkey_lookup_table* tbl, uint32_t size);
void schreme_fkey_lookup_table_resize_val_tbl(schreme_fkey_lookup_table* tbl, uint32_t size);
void schreme_table_resize(void** tbl, uint32_t entry_size, uint32_t old_size, uint32_t new_size);

/* TODO implement if neceessary
int schreme_tbl_erase_fkey(uint32_t key, schreme_tbl_val* val);
*/


/* internal utility functions */
