#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 100 // Tamanho da tabela hash

// Estrutura para lista de inteiros
typedef struct IntListNode {
    int value;
    struct IntListNode *next;
} IntListNode;

// Estrutura para entrada na tabela hash
typedef struct HashEntry {
    char *word;
    IntListNode *list;
} HashEntry;

// Estrutura para tabela hash
typedef struct HashTable {
    HashEntry *table;
    int size;
} HashTable;

// Função para criar uma nova lista de inteiros
IntListNode *create_int_list_node(int value) {
    IntListNode *new_node = (IntListNode *)malloc(sizeof(IntListNode));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Função para adicionar um valor à lista de inteiros
void add_to_int_list(IntListNode **head, int value) {
    IntListNode *new_node = create_int_list_node(value);
    new_node->next = *head;
    *head = new_node;
}

// Função hash simples para strings
unsigned int hash(const char *str) {
    unsigned int hash_value = 0;
    while (*str) {
        hash_value = (hash_value * 31) + *str;
        str++;
    }
    return hash_value % TABLE_SIZE;
}

// Função para criar uma tabela hash
HashTable *create_hash_table(int size) {
    HashTable *hash_table = (HashTable *)malloc(sizeof(HashTable));
    hash_table->size = size;
    hash_table->table = (HashEntry *)calloc(size, sizeof(HashEntry));
    return hash_table;
}

// Função para adicionar uma palavra na tabela hash
void add_to_hash_table(HashTable *hash_table, const char *word, int count) {
    unsigned int index = hash(word);
    unsigned int original_index = index;
    int probing_count = 0;

    while (hash_table->table[index].word != NULL) {
        if (strcmp(hash_table->table[index].word, word) == 0) {
            // Palavra encontrada, adicionar o contador à lista
            add_to_int_list(&(hash_table->table[index].list), count);
            return;
        }

        // Palavra não encontrada, realizar sondagem linear
        index = (original_index + (++probing_count)) % hash_table->size;
    }

    // Posição vazia encontrada, inserir nova palavra
    hash_table->table[index].word = strdup(word);
    hash_table->table[index].list = NULL;
    add_to_int_list(&(hash_table->table[index].list), count);
}

// Função para imprimir a tabela hash
void print_hash_table(HashTable *hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        if (hash_table->table[i].word != NULL) {
            printf("Index %d: %s -> ", i, hash_table->table[i].word);
            IntListNode *current = hash_table->table[i].list;
            while (current != NULL) {
                printf("%d ", current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}
// Função para processar cada palavra
void process_word(const char *word, int tweet_number) {
    printf("Tweet %d: %s\n", tweet_number, word);
}

// Função de teste
void test() {
    HashTable *hash_table = create_hash_table(TABLE_SIZE);

    // Adicionar palavras à tabela hash
    add_to_hash_table(hash_table, "apple", 1);
    add_to_hash_table(hash_table, "banana", 1);
    add_to_hash_table(hash_table, "apple", 2);
    add_to_hash_table(hash_table, "orange", 1);
    add_to_hash_table(hash_table, "apple", 3);
    add_to_hash_table(hash_table, "banana", 2);
    add_to_hash_table(hash_table, "grape", 1);

    // Imprimir tabela hash
    print_hash_table(hash_table);
}

// Função para buscar os inteiros associados a uma palavra na tabela hash
int *find_integers_for_word(HashTable *hash_table, const char *word, int *size) {
    unsigned int index = hash(word);
    unsigned int original_index = index;
    int probing_count = 0;

    while (hash_table->table[index].word != NULL) {
        if (strcmp(hash_table->table[index].word, word) == 0) {
            // Palavra encontrada, copiar inteiros para um vetor
            IntListNode *current = hash_table->table[index].list;
            int count = 0;

            // Contar o número de inteiros na lista
            while (current != NULL) {
                count++;
                current = current->next;
            }

            // Alocar memória para o vetor de inteiros
            int *integers = (int *)malloc(count * sizeof(int));
            current = hash_table->table[index].list;
            for (int i = 0; i < count; i++) {
                integers[i] = current->value;
                current = current->next;
            }

            *size = count; // Definir o tamanho do vetor
            return integers; // Retornar o vetor de inteiros
        }

        // Palavra não encontrada, realizar sondagem linear
        index = (original_index + (++probing_count)) % hash_table->size;
    }

    // Palavra não encontrada na tabela hash
    *size = 0;
    return NULL;
}

int main() {
    //test();
    printf("Pesquisar: ");
    char searchWord[20];
    scanf("%s", searchWord);
    
    FILE *file = fopen("teste.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    HashTable *hash_table = create_hash_table(TABLE_SIZE);
    
    char line[1024];
    int tweet_number = 0;

    // Ler o arquivo linha a linha
    while (fgets(line, sizeof(line), file)) {
        char *ptr = line;

        // Ignorar os dois primeiros números na linha
        while (*ptr && isdigit(*ptr)) ptr++; // Ignorar o primeiro número
        while (*ptr && isspace(*ptr)) ptr++; // Ignorar espaço
        while (*ptr && isdigit(*ptr)) ptr++; // Ignorar o segundo número
        while (*ptr && isspace(*ptr)) ptr++; // Ignorar espaço

        // Processar palavras na linha
        char word[256];
        int word_index = 0;
        while (*ptr) {
            if (isalpha(*ptr)) {
                word[word_index++] = *ptr; // Adicionar caractere à palavra
            } else if (word_index > 0) {
                word[word_index] = '\0'; // Fechar a palavra
                //process_word(word, tweet_number); // Processar a palavra
                add_to_hash_table(hash_table, word, tweet_number);
                word_index = 0; // Resetar o índice da palavra
            }
            ptr++;
        }

        // Verificar se há uma última palavra a ser processada
        if (word_index > 0) {
            word[word_index] = '\0';
            //process_word(word, tweet_number);
            add_to_hash_table(hash_table, word, tweet_number);
        }

        tweet_number++; // Incrementar o número do tweet
    }
    print_hash_table(hash_table);
    int size;
    //como buscar e exibir uma palavra especifica
    int *integers = find_integers_for_word(hash_table, searchWord, &size);
    if (integers != NULL) {
        printf("\ntweets com a palavra '%s': ", searchWord);
        for (int i = 0; i < size; i++) {
            printf("%d ", integers[i]);
        }
        printf("\n");
        free(integers);
    } else {
        printf("palavra truco nao esta na tabela.\n");
    }

    fclose(file);

    return 0;
}
