osync_bool osync_hashtable_load(OSyncHashTable *table, OSyncMember *member, OSyncError **error);
void osync_hashtable_close(OSyncHashTable *table);
void osync_hashtable_update_hash(OSyncHashTable *table, OSyncChange *change);
osync_bool osync_hashtable_detect_change(OSyncHashTable *table, OSyncChange *change);
void osync_hashtable_report_deleted(OSyncHashTable *table, OSyncContext *context, const char *objtype);
OSyncHashTable *osync_hashtable_new(void);
void osync_hashtable_free(OSyncHashTable *table);
void osync_hashtable_forget(OSyncHashTable *table);
int osync_hashtable_num_entries(OSyncHashTable *table);
osync_bool osync_hashtable_nth_entry(OSyncHashTable *table, int i, char **uid, char **hash);
void osync_hashtable_set_slow_sync(OSyncHashTable *table, const char *objtype);
