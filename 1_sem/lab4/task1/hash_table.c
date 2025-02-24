#include "hash_table.h"

#include <ctype.h>
#include <stdlib.h>

#include "util_task1.h"

HashTable* CreateHashTable(size_t size) {
    if (size <= 0) {
            return NULL;
    }
    
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        return NULL;
    }
    ht->table = (Macro**)calloc(size, sizeof(Macro*));
    if (!ht->table) {
        free(ht);
        return NULL;
    }
    ht->size = size;
    return ht;
}

Error ResizeHashTable(HashTable** ht) {
    if (!NeedRebalance(*ht)) {
        return OK;
    }

    //int newSize = GetNewTableSize((*ht)->size); 
    size_t newSize = (*ht)->size * 2; 
    HashTable* newTable = CreateHashTable(newSize);
    if (newTable == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (size_t i = 0; i < (*ht)->size; i++) {
        Macro* cur = (*ht)->table[i];
        while (cur) {
            Macro* next = cur->nextMacro;
            unsigned long newHash = cur->cached_hash % newSize;
            
            cur->nextMacro = newTable->table[newHash];
            newTable->table[newHash] = cur;
            
            cur = next;
        }
    }
    
    free((*ht)->table);
    free(*ht);

    *ht = newTable;
    return OK;
}

Error FillTable(HashTable** ht, FILE* file) {
    Error err;
    char* line = NULL;

    while ((err = ReadLine(file, &line)) == OK) {
        if (strncmp(line, "#define", 7) == 0) {
            char* name = NULL;
            char* value = NULL;
            printf("333\n");

            const char* rest = line + 7;
            while (isspace(*rest)) rest++;

            size_t i = 0;
            while (isalpha(rest[i]) || isdigit(rest[i])) {
                i++;
            }

            if (i > 0) {
                name = strndup(rest, i);
                if (!name) {
                    free(line);
                    return MEMORY_ALLOCATION_ERROR;
                }
                rest += i;
            }

            while (isspace(*rest)) rest++;
            value = strdup(rest);

            if (name && value) {
                err = InsertMacro(*ht, name, value);
                if (err != OK) {
                    free(name);
                    free(value);
                    free(line);
                    return err;
                }

                err = ResizeHashTable(ht);
                if (err != OK) {
                    free(name);
                    free(value);
                    free(line);
                    return err;
                }
            }

            free(name);
            free(value);
        }
        free(line);
    }
    return OK;
}

Error InsertMacro(HashTable* ht, const char* name, const char* value) {
    unsigned long full_hash = HashFunction(name);
    unsigned long remainder = full_hash % ht->size;
    
    Macro* newMacro = (Macro*)malloc(sizeof(Macro));
    if (!newMacro) {
        return MEMORY_ALLOCATION_ERROR;
    }
    newMacro->name = strdup(name);
    if (!newMacro->name) {
        free(newMacro);
        return MEMORY_ALLOCATION_ERROR;
    }
    newMacro->value = strdup(value);
    if (!newMacro->value) {
        free(newMacro->name);
        free(newMacro);
        return MEMORY_ALLOCATION_ERROR;
    }
    newMacro->cached_hash = full_hash;
    newMacro->nextMacro = ht->table[remainder];
    ht->table[remainder] = newMacro;
    return OK;
}

unsigned long HashFunction(const char* key) {
    unsigned long hash = 0;
    while (*key) {
        int c = *key;
        int offset;
        if (c >= '0' && c <= '9') {
            offset = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            offset = c - 'A' + 10;  // 10 цифр
        } else {
            offset = c - 'a' + 36;  //  10 цифр + 26 букв
        }
        hash = hash * 62 + (size_t)offset;
        key++;
    }
    return hash;
}

void DestroyTable(HashTable* ht) {
    for (size_t i = 0; i < ht->size; i++) {
        Macro* cur = ht->table[i];
        while (cur) {
            Macro* tmp = cur;
            cur = cur->nextMacro;
            free(tmp->name);
            free(tmp->value);
            free(tmp);
        }
    }
    free(ht->table);
    free(ht);
}

void PrintTable(const HashTable* ht) {
    if (!ht || !ht->table) {
        printf("HashTable is empty or uninitialized.\n");
        return;
    }

    printf("HashTable contents (size: %ld):\n", ht->size);
    for (size_t i = 0; i < ht->size; i++) {
        printf("Index %ld: ", i);
        Macro* current = ht->table[i];
        if (!current) {
            printf("(empty)\n");
            continue;
        }
        while (current) {
            printf("[name: %s, value: %s] -> ", current->name, current->value);
            current = current->nextMacro;
        }
        printf("NULL\n");
    }
}


bool NeedRebalance(HashTable* ht) {
    int min_len = INT_MAX, max_len = 0; //todo size_t
    int chainLength = 0;

    for (size_t i = 0; i < ht->size; i++) {
        chainLength = 0;
        Macro* cur = ht->table[i];
        while (cur) {
            chainLength++;
            cur = cur->nextMacro;
        }

        if (chainLength > max_len)
            max_len = chainLength;
        if (chainLength < min_len)
            min_len = chainLength;
    }

    return max_len >= 2 * min_len ? true : false;
}

Error ProcessFile(FILE* file, char* fileName, HashTable* ht) {
    Error err;
    char* line = NULL;
    
    FILE *tempFile = fopen("temp_output.txt", "w");
    if (!tempFile) {
        return OPEN_FILE_FAILURE;
    }
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("The file is empty.\n");
        fseek(file, 0, SEEK_SET);
        return END_OF_FILE;
    }
    fseek(file, 0, SEEK_SET); 
    
    while ((err = ReadLine(file, &line)) == OK) { // EOF когда читаем полследню строку?
        if (strncmp(line, "#define", 7) == 0) {
            printf("%s", line);
            if (fprintf(tempFile, "%s\n", line) < 0) {
                free(line);
                fclose(tempFile);
                return FILE_PROCESSING_FAILED;
            }
            
            free(line);
            continue;
        }

        char* processedLine = ProcessLine(line, ht);
        
        if (!processedLine) {
            free(line);
            fclose(tempFile);
            return FILE_PROCESSING_FAILED;
        }
        
        if (fprintf(tempFile, "%s\n", processedLine) < 0) {
            free(processedLine);
            free(line);
            fclose(tempFile);
            return FILE_PROCESSING_FAILED;
        }
        free(processedLine);
        free(line);
    }
    
    fclose(tempFile);
    
    if (err != END_OF_FILE) {
        return err;
    }
    
    fclose(file);
    if (remove(fileName) != 0) {
        return FILE_PROCESSING_FAILED;
    }
    if (rename("temp_output.txt", fileName) != 0) {
        return FILE_PROCESSING_FAILED;
    }
    
    return OK;
}

char* ProcessLine(char* line, HashTable* ht) {
    size_t res_capacity = INITIAL_LINE_LENGTH;
    char* result = (char*)malloc(res_capacity);
    if (!result) {
        return NULL;
    }

    size_t buf_capacity = INITIAL_LINE_LENGTH;
    char* buffer = (char*)malloc(buf_capacity);
    if (!buffer) {
        free(result);
        return NULL;
    }

    size_t res_idx = 0, buf_idx = 0;
    
    for (const char* p = line; *p; p++) {
        if (isalnum(*p)) {
            if (buf_idx >= buf_capacity) {
                buf_capacity *= 2;
                char* new_buffer = realloc(buffer, buf_capacity);
                if (!new_buffer) {
                    free(buffer);
                    free(result);
                    return NULL;
                }
                buffer = new_buffer;
            }
            buffer[buf_idx++] = *p;
        } else {
            
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                printf("Looking for macro: %s\n", buffer);
                char* replacement = FindMacro(buffer, ht);
                printf("Macro %s %s found\n", buffer, replacement ? "was" : "was not");
                if (replacement) {
                    if (SubstituteReplacement(&result, &res_idx, &res_capacity, replacement) ==
                        MEMORY_ALLOCATION_ERROR) {
                        free(buffer);
                        free(result);
                        return NULL;
                    }
                } else {
                    if (SubstituteOriginal(&result, &res_idx, &res_capacity, buffer, buf_idx) ==
                        MEMORY_ALLOCATION_ERROR) {
                        free(buffer);
                        free(result);
                        return NULL;
                    }
                }
                buf_idx = 0;
            }
            result[res_idx++] = *p;
        }
    }
        
    if (buf_idx > 0) {
        
        buffer[buf_idx] = '\0';
        printf("Looking for macro: %s\n", buffer);
        char* replacement = FindMacro(buffer, ht);
        printf("Macro %s %s found\n", buffer, replacement ? "was" : "was not");
        if (replacement) {
            
            if (SubstituteReplacement(&result, &res_idx, &res_capacity, replacement) == MEMORY_ALLOCATION_ERROR) {
                free(buffer);
                free(result);
                return NULL;
            }
        } else {
            
            if (SubstituteOriginal(&result, &res_idx, &res_capacity, buffer, buf_idx) == MEMORY_ALLOCATION_ERROR) {
                free(buffer);
                free(result);
                return NULL;
            }
        }
    }

    result[res_idx] = '\0';
    free(buffer);
    return result;
}

char* FindMacro(char* name, HashTable* ht) {
    if (!ht || !ht->table) {
            return NULL;
    }
    
    unsigned long full_hash = HashFunction(name);
    unsigned long remainder = full_hash % ht->size;
    
    Macro* curMacro = ht->table[remainder];
    while (curMacro) {
        if (strcmp(curMacro->name, name) == 0) {
            return curMacro->value;
        }
        curMacro = curMacro->nextMacro;
    }
    return NULL;
}

Error SubstituteReplacement(char** result, size_t* res_idx, size_t* res_capacity, const char* replacement) {
    size_t len = strlen(replacement);
    while (*res_idx + len >= *res_capacity) {
        *res_capacity *= 2;
        char* new_result = realloc(*result, *res_capacity);
        if (!new_result) {
            return MEMORY_ALLOCATION_ERROR;
        }
        *result = new_result;
    }
    strcpy(&(*result)[*res_idx], replacement);
    *res_idx += len;
    return OK;
}

Error SubstituteOriginal(char** result, size_t* res_idx, size_t* res_capacity, const char* buffer, size_t buf_idx) {
    while (*res_idx + buf_idx >= *res_capacity) {
        *res_capacity *= 2;
        char* new_result = realloc(*result, *res_capacity);
        if (!new_result) {
            return MEMORY_ALLOCATION_ERROR;
        }
        *result = new_result;
    }
    strncpy(&(*result)[*res_idx], buffer, buf_idx);
    *res_idx += buf_idx;
    return OK;
}
