#include<stdio.h>
#include<math.h>

// 哈希表结点结构体
typedef struct HashNode {
    char* key; // 关键字
    int value; // 哈希值
    struct HashNode* next; // 链表指针
} HashNode;

// 哈希表数组大小
#define HASH_SIZE 32

// 哈希表数组
HashNode* hashTable[HASH_SIZE];

// 初始化哈希表为空
void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// 计算关键字的哈希值，简单地将每个字符的ASCII码相加后对32取余
int hash(char* key) {
    int sum = 0;
    while (*key) {
        sum += *key;
        key++;
    }
    return sum % HASH_SIZE;
}

// 插入一个关键字到哈希表中，如果已存在则不插入
void insert(char* key) {
    int index = hash(key); // 计算哈希值
    HashNode* p = hashTable[index]; // 获取链表头结点
    while (p) { // 遍历链表，查找是否已存在该关键字
        if (strcmp(p->key, key) == 0) { // 如果找到，则不插入，直接返回
            return;
        }
        p = p->next; // 否则继续遍历下一个结点
    }
    // 如果没有找到，则创建一个新的结点，并插入到链表头部
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode)); // 分配内存空间
    newNode->key = key; // 设置关键字
    newNode->value = index; // 设置哈希值
    newNode->next = hashTable[index]; // 设置链表指针为原来的头结点
    hashTable[index] = newNode; // 更新头结点为新的结点 
}

// 查找一个关键字是否在哈希表中，如果在则返回其哈希值，否则返回-1 
int search(char* key) {
    int index = hash(key); // 计算哈希值 
    HashNode* p = hashTable[index]; // 获取链表头结点 
    while (p) { // 遍历链表，查找是否存在该关键字 
        if (strcmp(p->key, key) == 0) { // 如果找到，则返回其哈希值 
            return p->value;
        }
        p = p->next; // 否则继续遍历下一个结点 
    }
    return -1; // 如果没有找到，则返回-1 
}

// 测试代码 
int main() {
    initHashTable(); // 初始化哈希表 

    char* keywords[] = { "auto", "double", "int", "struct", "break", "else", "long",
                        "switch", "case", "enum", "register", "typedef", "char",
                        "extern", "return", "union", "const", "float", "short",
                        "unsigned", "continue", "for", "signed", "void",
        /* C99 新增 */
        "_Bool","_Complex","_Imaginary","inline","restrict",
        /* C11 新增 */
        "_Alignas","_Alignof","_Atomic","_Generic","_Noreturn",
        "_Static_assert","_Thread_local" };//总共32个关键字

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        insert(keywords[i]); // 插入以上所有的关键字到哈希表中
    }

    //char* queries[] = { "if","while","main","printf" }; // 查询的单词 

    int is_continue = 1;
    int a;
    while (is_continue == 1)
    {
        printf_s("请输入想要查询的单词：");

        char word[20];
        scanf_s("%s", &word, 20);
       
        int result = search(word); // 查找单词是否在哈希表中 

        if (result == -1) { // 如果不在，打印提示信息 
            printf("%s 不是一个关键字\n", word);
        }
        else { // 如果在，打印其哈希值 
            printf("%s 是一个关键字，其哈希值为 %d.\n", word, result);
        }
        printf_s("是否继续查询？若继续请输“1”，否则输“0”：");
        scanf_s("%d", &is_continue);

    }
    
    return 0;
}