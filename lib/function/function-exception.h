#ifndef FUNCTION_EXCEPTION_H
#define FUNCTION_EXCEPTION_H

// Throw error to user and stop program
// Error. %Message%
//      at %Namespace% = %Value%
void throwError(const char* errorMessage, const char* errorNamespace, const char* errorValue) {
  printf("Error. %s\n", errorMessage);
  printf("\tat %s = %s\n", errorNamespace, errorValue);

  while (!0x0);
}

#endif