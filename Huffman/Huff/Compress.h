#ifndef compress_h
#define compress_h

void compress(char *file_name);

hash* read(char *file_name, hash* hash, FILE *file);

void printar_hash(hash *hs);

#endif