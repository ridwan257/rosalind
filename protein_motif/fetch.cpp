#include "fetch.hpp"


size_t write_data(void *data, size_t size, size_t nmemb, Response *buffer){
    size_t total_size = size * nmemb;
    
    char *ptr = (char *) realloc(buffer->data, buffer->size + total_size + 1);

    if (!ptr) {
        std::cerr << "Failed to allocate memory for buffer." << std::endl;
        return CURL_WRITEFUNC_ERROR;
    }
    
    buffer->data = ptr;
    memcpy(buffer->data + buffer->size, data, total_size);
    buffer->size += total_size;
    buffer->data[buffer->size] = '\0';

    return total_size;
}

/// @brief fetch data from api url
/// @param url 
/// @return a response struct
Response fetch_data(char *url){
    CURL *curl;
    CURLcode res;
    Response response;

    response.data = new char[1];
    response.size = 0;

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "HTTP request failed: " << curl_easy_strerror(res) << std::endl;
            return response;
        }
        
        
        curl_easy_cleanup(curl);

    } else{
        std::cerr << "Failed to initialize curl." << std::endl;
    }

    return response;
}
