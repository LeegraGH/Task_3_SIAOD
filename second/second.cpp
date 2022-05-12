//Дано предложение, состоящее из слов, разделенных запятой или пробелами.
//Составить частотный словарь слов, указав, сколько раз данное слово встретилось в предложении.
//При этом изменить предложение: 
//-удалив повторные вхождения слов и вставив перед первым вхождением слова подстроку вида: 
//(Число), где - Число – определяет количество таких слов в предложении.

//Реализация через null терминальную строку

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cstring>

using namespace std;

char* gets(int& len)
{
    len = 0;
    int increase = 1;
    char* text = (char*)malloc(sizeof(char));
    char sym = getchar();
    while (sym != '\n')
    {
        text[len] = sym;
        len++;
        if (len >= increase) {
            increase *= 2;
            text = (char*)realloc(text, increase * sizeof(char));
        }
        sym = getchar();
    }
    text[len] = '\0';
    return text;
}

char* copy_text(char text[], int l)
{
    char* new_text = new char[l + 1];
    int i = 0;
    while (i < l)
    {
        new_text[i] = text[i];
        i++;
    }
    new_text[l] = '\0';
    return new_text;
}

int check(char text1[], char text2[], int len) // Количество повторений слова в тексте
{
    char* word = new char[len + 1];
    word[0] = '\0';
    int k = 0;
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (text1[i] == ' ' || text1[i] == ',')
        {
            if ((strcmp(word, text2) == 0) && word[0] != '\0')
            {
                k++;
            }
            word[0] = '\0';
            j = 0;
        }
        else
        {
            word[j] = text1[i];
            word[j + 1] = '\0';
            j++;
            if (i == (len - 1) && (strcmp(word, text2) == 0))
            {
                k++;
            }
        }
    }
    return k;
}

void lib(char text[], int len)
{
    char* str = copy_text(text, len);
    char* word = strtok(str, " ,");
    char lib[1];
    while (word != NULL)
    {
        cout << word << ": " << check(text, word, len) << endl;
        strcat(lib, word);
        word = strtok(NULL, " ,");
        if (word != NULL)
        {
            while (strstr(lib, word) != 0)
            {
                word = strtok(NULL, " ,");
                if (word == NULL) break;
            }
        }
    }
    delete[] str;
}

char* change(char text[], int& len) // Удаление повторяющихся слов
{
    int k = 0;
    char* str = copy_text(text, len);
    char* new_str = new char[len + 100];
    char split[] = " ,";
    char* word = strtok(str, split);
    int i = 0;
    int j = 0;
    while (word != NULL || j < len)
    {
        if (text[j] == ' ' || text[j] == ',')
        {
            if (new_str != NULL && new_str[i - 1] == ' ') j++;
            else
            {
                new_str[i] = text[j];
                i++;
                j++;
            }
        }
        else
        {
            if (check(text, word, len) > 1 && strstr(new_str, word) != 0)
            {
                j += strlen(word);
                word = strtok(NULL, split);
            }
            else
            {
                new_str[i] = '(';
                i++;
                char num = (check(text, word, len) + '0');
                new_str[i] = num;
                i++;
                new_str[i] = ')';
                i++;
                for (int k = 0; k < strlen(word); k++)
                {
                    new_str[i] = word[k];
                    i++;
                    j++;
                }
                word = strtok(NULL, split);
            }
        }
    }
    len = i;
    new_str[i] = '\0';
    delete[] str;
    return new_str;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int len;
    char* text = gets(len);
    cout << "Частотный словарь слов:" << endl;
    lib(text, len);
    text = change(text, len);
    cout << text;
    text = (char*)realloc(text, len * sizeof(char));
    free(text);
    return 0;
}
