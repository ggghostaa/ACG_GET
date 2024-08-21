//
// Created by dd on 2024/8/16.
//

#include <stdio.h>
#include <curl/curl.h>
int main() {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl_global_cleanup();
  printf("Hello World\n");
}
