#pragma once

/*
 *  
 */

enum schreme_table_types =
{
  FIXED_KEY = 0,
  VAR_KEY
};

enum schreme_table_err =
{
  NO_ERROR = 0,
  OUT_OF_MEMORY,
  INTERNAL_ERROR
};

/*
 * key value structs
 */
struct schreme_tbl
{
  uint32_t key;
  uint32_t val_offset;
};

struct schreme_tbl_val
{
  uint16_t size = 0;
  const uint8_t* data = NULL;
};

/*
 * simple linear time lookup tables
 */
struct schreme_fkey_lookup_table
{
  schreme_tbl table;
  uint8_t* val_table;
};

schreme_tbl_err schreme_tbl_insert_fkey(uint32_t key, schreme_tbl_val* val);
schreme_tbl_err schreme_tbl_lookup_fkey(uint32_t key, schreme_tbl_val* val);
schreme_tbl_err schreme_tbl_erase_fkey(uint32_t key, schreme_tbl_val* val);

struct schreme_vkey_lookup_table
{
  uint8_t* key_table;
  schreme_fkey_lookup_table* indexed_tbl;
};
