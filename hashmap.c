#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

int get_valid_location(HashMap * map, char * key)
{
  int pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL && map->buckets[pos]->key != key)
  {
    pos = (pos + 1) % map->capacity;
  }
  return pos;
}


void insertMap(HashMap * map, char * key, void * value) 
{
  if (map->size >= 0.7*map->capacity)
  {
    enlarge(map);
  }
  int pos = get_valid_location(map, key);

  map->buckets[pos] = createPair(key, value);
  map->size++;
}

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)
  Pair** oldArray = map->buckets;
  int oldCapacity = map->capacity;
  int newCapacity = map->capacity *2;
  Pair** newArray = (Pair**)malloc(newCapacity * sizeof(Pair**));

  for (int i = 0; i < newCapacity; i++)
    {
      newArray[i] = NULL;
    }
  map->capacity = newCapacity;
  map->buckets = newArray;

  for(int i = 0; i < oldCapacity; i++)
    {
      if(oldArray[i] != NULL){
        insertMap(map, oldArray[i]->key, oldArray[i]->value);
      }
    }
  
  free(oldArray);
}


HashMap * createMap(long capacity) 
{
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL){
    return NULL;
  }
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  map->buckets = (Pair**) malloc(capacity * sizeof(Pair**));

  for (long i = 0; i < capacity; i++){
    map->buckets[i] = NULL;
  }
  return map;
}

void eraseMap(HashMap * map,  char * key) 
{    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
  int pos = get_valid_location(map, key);
  if (strcmp(map->buckets[pos]->key, key) == 0){
    return map->buckets[pos];
  }
  else
    return NULL;
}

Pair * firstMap(HashMap * map) 
{

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
