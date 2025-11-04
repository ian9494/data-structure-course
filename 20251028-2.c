#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Huffman tree node
typedef struct Node {
    char data; // character or '*' for internal
    int freq;
    struct Node *left, *right;
    int id;              // creation id for stable tie-break
    unsigned char min_char; // smallest leaf char in subtree (for tie-break)
} Node;

Node* createNode(char data, int freq, int id, unsigned char min_char) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = data;
    p->freq = freq;
    p->left = p->right = NULL;
    p->id = id;
    p->min_char = min_char;
    return p;
}

// print tree rotated (right first) similar to sample
void printTree(Node* root, int level) {
    if (!root) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("\t");
    if (root->data == '*') printf("(*, %d)\n", root->freq);
    else printf("(%c, %d)\n", root->data, root->freq);
    printTree(root->left, level + 1);
}

// collect unique chars and freqs from input string
int collect_freq(const char* s, char chars[], int freq[]) {
    int map[256] = {0};
    int total = 0;
    for (const char* p = s; *p; ++p) {
        unsigned char c = (unsigned char)*p;
        map[c]++;
        total++;
    }
    int idx = 0;
    for (int c = 0; c < 256; ++c) {
        if (map[c] > 0) {
            chars[idx] = (char)c;
            freq[idx] = map[c];
            idx++;
        }
    }
    return idx;
}

// build huffman tree using simple O(n^2) method (fine for small alphabet)
// comparator for qsort: freq asc, then min_char asc, then leaf-first, then id asc
int node_cmp(const void* a, const void* b) {
    const Node* A = *(const Node* const*)a;
    const Node* B = *(const Node* const*)b;
    if (A->freq != B->freq) return (A->freq < B->freq) ? -1 : 1;
    if (A->min_char != B->min_char) return (A->min_char < B->min_char) ? -1 : 1;
    int A_leaf = (!A->left && !A->right);
    int B_leaf = (!B->left && !B->right);
    if (A_leaf != B_leaf) return A_leaf ? -1 : 1; // leaf first
    if (A->id != B->id) return (A->id < B->id) ? -1 : 1;
    return 0;
}

Node* buildHuffman(char chars[], int freq[], int n) {
    // array of Node* dynamic
    Node** list = (Node**)malloc(sizeof(Node*) * (2*n + 5));
    int size = 0;
    int next_id = 0;
    for (int i = 0; i < n; ++i) {
        unsigned char mc = (unsigned char)chars[i];
        list[size++] = createNode(chars[i], freq[i], next_id++, mc);
    }

    while (size > 1) {
        // stable sort by comparator
        qsort(list, size, sizeof(Node*), node_cmp);
        Node* left = list[0];
        Node* right = list[1];
        unsigned char mc = (left->min_char < right->min_char) ? left->min_char : right->min_char;
        Node* top = createNode('*', left->freq + right->freq, next_id++, mc);
        top->left = left; top->right = right;
        // replace first two with top and shift remaining
        list[0] = top;
        for (int i = 1; i < size-1; ++i) list[i] = list[i+1];
        size--;
    }
    Node* root = list[0];
    free(list);
    return root;
}

// generate codes recursively
void genCodes(Node* root, char* code, int depth, char codes[256][128]) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->data], code);
        return;
    }
    if (root->left) {
        code[depth] = '0';
        genCodes(root->left, code, depth+1, codes);
    }
    if (root->right) {
        code[depth] = '1';
        genCodes(root->right, code, depth+1, codes);
    }
}

// decode bitstring using tree
void decodeBits(Node* root, const char* bits, char* out) {
    Node* cur = root;
    int pos = 0;
    for (const char* p = bits; *p; ++p) {
        if (*p == '0') cur = cur->left;
        else if (*p == '1') cur = cur->right;
        else continue; // ignore 防呆
        if (!cur->left && !cur->right) {
            out[pos++] = cur->data;
            cur = root;
        }
    }
    out[pos] = '\0';
}

/* free tree (postorder) */
void freeTree(Node* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

// helper for sorting printed codes
typedef struct { char ch; char code[128]; } CodeEntry;
int code_cmp_entries(const void* a, const void* b) {
    const CodeEntry* A = (const CodeEntry*)a;
    const CodeEntry* B = (const CodeEntry*)b;
    return strcmp(A->code, B->code);
}

int main() {
    // sample input from assignment
    const char* input = "ENERAGENOGOGOGOEENYEEGYE"; // provided sample
    printf("Input string: %s\n\n", input);
    // collect frequencies
    char chars[256]; int freq[256];
    int n = collect_freq(input, chars, freq);
    int total = strlen(input);

    printf("Frequencies and probabilities:\n");
    int prob[256];
    for (int i = 0; i < n; ++i) {
        prob[i] = (int)(freq[i] / (double)total * 100.0 + 0.5); //四捨五入只留整數部分
        printf("%c: %d (%d%%)\n", chars[i], freq[i], prob[i]);
    }
    printf("\n");

    // Build Huffman tree using integer percentages (prob)
    Node* root = buildHuffman(chars, prob, n);
    printf("Huffman tree:\n");
    printTree(root, 0);
    printf("\n");

    // generate codes
    char codes[256][128];
    for (int i = 0; i < 256; ++i) codes[i][0] = '\0';
    char code[128];
    genCodes(root, code, 0, codes);

    // print codes sorted by binary string (lexicographic on '0'/'1')
    printf("Huffman codes:\n");
    CodeEntry* entries = (CodeEntry*)malloc(sizeof(CodeEntry) * n);
    for (int i = 0; i < n; ++i) {
        entries[i].ch = chars[i];
        strcpy(entries[i].code, codes[(unsigned char)chars[i]]);
    }
    qsort(entries, n, sizeof(CodeEntry), code_cmp_entries);
    for (int i = 0; i < n; ++i) {
        printf("%c: %s\n", entries[i].ch, entries[i].code);
    }
    free(entries);
    // decode the provided compressed bitstring and show restored text
    const char* bits = "11100111010101101101000100"; // user-provided compressed string
    char decoded[1024];
    decodeBits(root, bits, decoded);
    // printf("Compressed bitstring: %s\n", bits);
    printf("\nDecoded text: %s\n", decoded);

    // free tree (postorder)
    freeTree(root);

    
    return 0;
}