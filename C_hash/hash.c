#include<stdio.h>
#include<math.h>

// ��ϣ����ṹ��
typedef struct HashNode {
    char* key; // �ؼ���
    int value; // ��ϣֵ
    struct HashNode* next; // ����ָ��
} HashNode;

// ��ϣ�������С
#define HASH_SIZE 32

// ��ϣ������
HashNode* hashTable[HASH_SIZE];

// ��ʼ����ϣ��Ϊ��
void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// ����ؼ��ֵĹ�ϣֵ���򵥵ؽ�ÿ���ַ���ASCII����Ӻ��32ȡ��
int hash(char* key) {
    int sum = 0;
    while (*key) {
        sum += *key;
        key++;
    }
    return sum % HASH_SIZE;
}

// ����һ���ؼ��ֵ���ϣ���У�����Ѵ����򲻲���
void insert(char* key) {
    int index = hash(key); // �����ϣֵ
    HashNode* p = hashTable[index]; // ��ȡ����ͷ���
    while (p) { // �������������Ƿ��Ѵ��ڸùؼ���
        if (strcmp(p->key, key) == 0) { // ����ҵ����򲻲��룬ֱ�ӷ���
            return;
        }
        p = p->next; // �������������һ�����
    }
    // ���û���ҵ����򴴽�һ���µĽ�㣬�����뵽����ͷ��
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode)); // �����ڴ�ռ�
    newNode->key = key; // ���ùؼ���
    newNode->value = index; // ���ù�ϣֵ
    newNode->next = hashTable[index]; // ��������ָ��Ϊԭ����ͷ���
    hashTable[index] = newNode; // ����ͷ���Ϊ�µĽ�� 
}

// ����һ���ؼ����Ƿ��ڹ�ϣ���У�������򷵻����ϣֵ�����򷵻�-1 
int search(char* key) {
    int index = hash(key); // �����ϣֵ 
    HashNode* p = hashTable[index]; // ��ȡ����ͷ��� 
    while (p) { // �������������Ƿ���ڸùؼ��� 
        if (strcmp(p->key, key) == 0) { // ����ҵ����򷵻����ϣֵ 
            return p->value;
        }
        p = p->next; // �������������һ����� 
    }
    return -1; // ���û���ҵ����򷵻�-1 
}

// ���Դ��� 
int main() {
    initHashTable(); // ��ʼ����ϣ�� 

    char* keywords[] = { "auto", "double", "int", "struct", "break", "else", "long",
                        "switch", "case", "enum", "register", "typedef", "char",
                        "extern", "return", "union", "const", "float", "short",
                        "unsigned", "continue", "for", "signed", "void",
        /* C99 ���� */
        "_Bool","_Complex","_Imaginary","inline","restrict",
        /* C11 ���� */
        "_Alignas","_Alignof","_Atomic","_Generic","_Noreturn",
        "_Static_assert","_Thread_local" };//�ܹ�32���ؼ���

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        insert(keywords[i]); // �����������еĹؼ��ֵ���ϣ����
    }

    //char* queries[] = { "if","while","main","printf" }; // ��ѯ�ĵ��� 

    int is_continue = 1;
    int a;
    while (is_continue == 1)
    {
        printf_s("��������Ҫ��ѯ�ĵ��ʣ�");

        char word[20];
        scanf_s("%s", &word, 20);
       
        int result = search(word); // ���ҵ����Ƿ��ڹ�ϣ���� 

        if (result == -1) { // ������ڣ���ӡ��ʾ��Ϣ 
            printf("%s ����һ���ؼ���\n", word);
        }
        else { // ����ڣ���ӡ���ϣֵ 
            printf("%s ��һ���ؼ��֣����ϣֵΪ %d.\n", word, result);
        }
        printf_s("�Ƿ������ѯ�����������䡰1���������䡰0����");
        scanf_s("%d", &is_continue);

    }
    
    return 0;
}