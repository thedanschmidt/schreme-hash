#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schreme_hash.h"

int schreme_fkey_lookup_table_insert(schreme_fkey_lookup_table* tbl, 
                                     uint32_t key, schreme_tbl_val val)
{
  schreme_tbl_val lookup;
  schreme_fkey_lookup_table_lookup(tbl, key, &lookup);
  if (lookup.size)
    return 0;

  if (tbl->kv_tbl_size == tbl->kv_tbl_capacity)
  {
    // resize kv_tbl
    uint32_t new_size = tbl->kv_tbl_size * SCHREME_TBL_GROWTH_FACTOR;
    if (new_size == 0) new_size = SCHREME_TBL_MIN_SIZE;
    schreme_fkey_lookup_table_resize_kv_tbl(tbl, new_size);
  }
  if (tbl->val_tbl_size + val.size >= tbl->val_tbl_capacity)
  {
    // resize val_tbl
    uint32_t new_size = tbl->val_tbl_size * SCHREME_TBL_GROWTH_FACTOR;
    if (new_size == 0) new_size = SCHREME_TBL_MIN_SIZE;
    schreme_fkey_lookup_table_resize_val_tbl(tbl, new_size);
  }

  // TODO make sure new size is big enough
  
  schreme_kv* new_kv = tbl->kv_tbl + tbl->kv_tbl_size;
  uint8_t* new_val_ptr = tbl->val_tbl + tbl->val_tbl_size;
  memcpy(new_val_ptr, val.data, val.size * sizeof(uint8_t));
  new_kv->key = key;
  new_kv->val_offset = new_val_ptr - tbl->val_tbl;
  new_kv->val_size = val.size;

  ++tbl->kv_tbl_size;
  ++tbl->val_tbl_size;
}

void schreme_fkey_lookup_table_lookup(schreme_fkey_lookup_table* tbl, 
                                      uint32_t key, schreme_tbl_val* val)
{
  for (size_t i = 0; i < tbl->kv_tbl_size; ++i)
  {
    if (tbl->kv_tbl[i].key == key)
    {
      val->data = tbl->kv_tbl[i].val_offset + tbl->val_tbl;
      val->size = tbl->kv_tbl[i].val_size;
      return;
    }
  }
  val->size = 0;
  val->data = NULL;
}

/*
int schreme_tbl_erase_fkey(uint32_t key, schreme_tbl_val* val)
{
  return 0;
}
*/

void schreme_fkey_lookup_table_init(schreme_fkey_lookup_table* tbl)
{
  tbl->kv_tbl = NULL;
  tbl->val_tbl = NULL;
  tbl->kv_tbl_size = 0;
  tbl->val_tbl_size = 0;
  tbl->kv_tbl_capacity = 0;
  tbl->val_tbl_capacity = 0;
}

void schreme_fkey_lookup_table_resize_kv_tbl(schreme_fkey_lookup_table* tbl, uint32_t size)
{
  schreme_table_resize((void**) &tbl->kv_tbl, sizeof(tbl->kv_tbl), tbl->kv_tbl_size, size);
  tbl->kv_tbl_capacity = size;
}

void schreme_fkey_lookup_table_resize_val_tbl(schreme_fkey_lookup_table* tbl, uint32_t size)
{
  schreme_table_resize((void**) &tbl->val_tbl, sizeof(tbl->val_tbl), tbl->val_tbl_size, size);
  tbl->val_tbl_capacity = size;
}

void schreme_table_resize(void** tbl, uint32_t entry_size, uint32_t old_size, uint32_t new_size)
{
  void* old_tbl = *tbl;
  void* new_tbl = malloc(new_size * entry_size);
  if (old_tbl)
  {
    if (new_size < old_size)
    {
      memcpy(new_tbl, old_tbl, new_size * entry_size);
    }
    else
    {
      memcpy(new_tbl, old_tbl, old_size*entry_size);
      memset(new_tbl + old_size, 0, (new_size - old_size) * entry_size);
    }
    free(old_tbl);
  }
  else
  {
    memset(new_tbl, 0, new_size * entry_size);
  }
  *tbl = new_tbl;
}
