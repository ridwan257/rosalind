#ifndef FETCH_HPP
#define FETCH_HPP

#include <iostream>
#include <curl/curl.h>

typedef struct {
  char *data;
  size_t size;
} Response;

Response fetch_data(char *url);



#endif