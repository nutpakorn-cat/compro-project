#ifndef FUNCTION_RENDER_MAP_H
#define FUNCTION_RENDER_MAP_H
// Rendering Ascii Text
// Files are inside FILE_URL folder
void renderMap(char* mapName) {
  FILE *ptr_file;
  char buf[BUFFER_SIZE];

  char* mapUrl = (char *) malloc(__SYSTEM_TEXT * sizeof mapUrl);

  strcat(mapUrl, FILE_URL);
  strcat(mapUrl, mapName);
  strcat(mapUrl, FILE_EXTENSION);

  // Debug
  // printf("[DEBUG] Load resource from %s\n", mapUrl);

  ptr_file = fopen(mapUrl,"r");
  if (!ptr_file)
    throwError("There is no file here", "function.renderMap.mapUrl", mapUrl);

  while (fgets(buf, BUFFER_SIZE, ptr_file) != NULL)
    printf("%s",buf);

	fclose(ptr_file);

  printf("\n");
  free(mapUrl);
}

#endif