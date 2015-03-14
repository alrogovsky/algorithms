#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 1024
#define STR_LEN 1024
#define ERROR_MSG "[error]"
#define unlikely(expr) __builtin_expect(!!(expr), 0)

//Функция ввода массива строк
char** input_str_array();

//Функция для обработки массива строк
char** trim_array(char** str);

//Функция обраотки одной строки
char* copy_modified(char* from, char* to);

//Очистка памяти
void clearArray(char** str, int n);

//Печать
void print_str(char** str);

int main(void)
{
    //Выделяем память
    char** str_arr = input_str_array();
    
    //Проверка на ошибку
    if( unlikely(str_arr == NULL) ) {
        printf(ERROR_MSG);
        return 0;
    }
    
    char** edited_arr = trim_array(str_arr);
    
    if( unlikely(edited_arr == NULL) ) {
        printf(ERROR_MSG);
        return 0;
    }
    
    print_str(edited_arr);
    
    clearArray(edited_arr, MAX_STR);
    clearArray(str_arr, MAX_STR);
    
    return 0;
}


//Функция для ввода массива строк
char** input_str_array()
{
    
    char** str = (char**) calloc(MAX_STR, sizeof(char*));
    
    //Если не удалось выделить память
    if ( unlikely( str == NULL) )
        return NULL;

    size_t i;
    for( i = 0; i < MAX_STR; i++) {
        str[i] = (char*) calloc(STR_LEN, sizeof(char));
        
        //Если не выделилась память
        if ( unlikely( str[i] == NULL) )
            return NULL;
    }
    
    //Ввод из потока
    i = 0;
    while ( fgets(str[i], MAX_STR, stdin) )
        i++;
    
    //Помещаем в последнюю строку EOF для ослеживания конца массива при операциях
    if(i < MAX_STR)
        str[i][0] = EOF;
    
    return str;
}



//Функция для обработки массива строк
char** trim_array(char** str)
{
    char** new_str = (char**) calloc(MAX_STR, sizeof(char*));
    
    //Если не выделилась память
    if( unlikely( str == NULL) )
        return NULL;
    
    size_t i;
    for( i = 0; i < MAX_STR; i++) {
        new_str[i] = (char*) calloc(STR_LEN, sizeof(char));
        
        //Если не выделилась память
        if( unlikely(new_str[i] == NULL) )
            return NULL;
    }
    
    i=0;
    for( i = 0; i < MAX_STR; i++) {
        if(unlikely(str[i] != NULL)) {
            if(str[i][0] == EOF)
                return new_str;
            else {
                copy_modified(str[i], new_str[i]);
            }
        }
        else
            return NULL;
    }
    
    return new_str;
}


//Функция обраотки одной строки
char* copy_modified(char* from, char* to)
{
    int i = 0; // итератор старой строки
    int j = 0; // итератор новой строки
    unsigned int wasSpace = 0;
    while( from[i] != '\0' ) {
        if(from[i] != ' ') {
            to[j] = from[i];
            wasSpace = 0;
            i++;
            j++;
        } else {
            if(!wasSpace) {
                to[j] = from[i];
                wasSpace = 1;
                i++;
                j++;
            } else {
                i++;
            }
            
        }
    }
    
    to[j] = '\0';
    to[j+1] = '\n';
    return to;
}


//Печать
void print_str(char** str)
{
    int i;
    for(i = 0; i < MAX_STR; i++) {
        if(str[i][0] != EOF)
            printf("%s", str[i]);
        else
            break;
    }

}

//Очистка памяти
void clearArray(char** str, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        free(str[i]);
    }
    
    free(str);
}


