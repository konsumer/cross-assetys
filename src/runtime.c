#include <stdio.h>  // for printf

#define ASSETSYS_IMPLEMENTATION
#define STRPOOL_IMPLEMENTATION
#include "assetsys.h"

void list_assets(assetsys_t* assetsys, char const* path, int indent) {
  // Print folder names and recursively list assets
  for (int i = 0; i < assetsys_subdir_count(assetsys, path); ++i) {
    char const* subdir_name = assetsys_subdir_name(assetsys, path, i);
    for (int j = 0; j < indent; ++j) {
      printf("  ");
    }
    printf("%s/\n", subdir_name);

    char const* subdir_path = assetsys_subdir_path(assetsys, path, i);
    list_assets(assetsys, subdir_path, indent + 1);
  }

  // Print file names
  for (int i = 0; i < assetsys_file_count(assetsys, path); ++i) {
    char const* file_name = assetsys_file_name(assetsys, path, i);
    for (int j = 0; j < indent; ++j) {
      printf("  ");
    }
    printf("%s\n", file_name);
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <ZIP_FILE>", argv[0]);
    return 1;
  }

  printf("loading: %s\n", argv[1]);

  assetsys_t* assetsys = assetsys_create(0);

  // Mount current working folder as a virtual "/data" path
  assetsys_mount(assetsys, argv[1], "/data");

  // Print all files and subfolders
  list_assets(assetsys, "/", 0);  // Start at root

  // Load a file
  assetsys_file_t file;
  assetsys_file(assetsys, "/data/readme.txt", &file);
  int size = assetsys_file_size(assetsys, file);
  char* content = (char*)malloc(size + 1);  // extra space for '\0'
  int readsize = 0;
  assetsys_file_load(assetsys, file, &readsize, content, size);

  content[size] = '\0';  // zero terminate the text file
  printf("%s\n", content);
  free(content);

  assetsys_destroy(assetsys);
}