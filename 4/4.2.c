#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITY 256

typedef struct {
    int priority; 
    char *message; 
} QueueNode;

typedef struct {
    QueueNode **nodes; 
    int size; 
} PriorityQueue;

// Функция для создания новой очереди
PriorityQueue* createPriorityQueue() {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->nodes = malloc(MAX_PRIORITY * sizeof(QueueNode*));
    pq->size = 0;

    for (int i = 0; i < MAX_PRIORITY; i++) {
        pq->nodes[i] = NULL;
    }
    return pq;
}

// Функция для добавления элемента в очередь
void enqueue(PriorityQueue *pq, int priority, const char *message) {
    if (priority < 0 || priority >= MAX_PRIORITY) {
        printf("Недопустимый приоритет.\n");
        return;
    }

    QueueNode *node = malloc(sizeof(QueueNode));
    node->priority = priority;
    node->message = strdup(message);

    pq->nodes[pq->size++] = node; // Добавляем элемент в очередь
}

// Функция для извлечения первого элемента из очереди
QueueNode* dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Очередь пуста.\n");
        return NULL;
    }

    QueueNode *highestPriorityNode = NULL;
    int highestPriorityIndex = -1;

    for (int i = 0; i < pq->size; i++) {
        if (highestPriorityNode == NULL || pq->nodes[i]->priority < highestPriorityNode->priority) {
            highestPriorityNode = pq->nodes[i];
            highestPriorityIndex = i;
        }
    }
    QueueNode *extractedNode = highestPriorityNode;
    for (int i = highestPriorityIndex; i < pq->size - 1; i++) {
        pq->nodes[i] = pq->nodes[i + 1];
    }

    pq->size--;
    return extractedNode;
}

// Функция для извлечения элемента по заданному приоритету
QueueNode* dequeueByPriority(PriorityQueue *pq, int priority) {
    if (pq->size == 0) {
        printf("Очередь пуста.\n");
        return NULL;
    }

    QueueNode *targetNode = NULL;
    int targetIndex = -1;

    for (int i = 0; i < pq->size; i++) {
        if (pq->nodes[i]->priority == priority) {
            targetNode = pq->nodes[i];
            targetIndex = i;
            break;
        }
    }

    if (targetNode == NULL) {
        printf("Элемент с приоритетом %d не найден.\n", priority);
        return NULL;
    }

    for (int i = targetIndex; i < pq->size - 1; i++) {
        pq->nodes[i] = pq->nodes[i + 1];
    }

    pq->size--;
    return targetNode;
}

// Функция для извлечения элемента с приоритетом не ниже заданного
QueueNode* dequeueByMinPriority(PriorityQueue *pq, int minPriority) {
    if (pq->size == 0) {
        printf("Очередь пуста.\n");
        return NULL;
    }

    QueueNode *targetNode = NULL;
    int targetIndex = -1;

    for (int i = 0; i < pq->size; i++) {
        if (pq->nodes[i]->priority >= minPriority &&
            (targetNode == NULL || pq->nodes[i]->priority < targetNode->priority)) {
            targetNode = pq->nodes[i];
            targetIndex = i;
        }
    }

    if (targetNode == NULL) {
        printf("Нет элементов с приоритетом не ниже %d.\n", minPriority);
        return NULL;
    }

    for (int i = targetIndex; i < pq->size - 1; i++) {
        pq->nodes[i] = pq->nodes[i + 1];
    }

    pq->size--;
    return targetNode;
}

void freePriorityQueue(PriorityQueue *pq) {
    for (int i = 0; i < pq->size; i++) {
        free(pq->nodes[i]->message);
        free(pq->nodes[i]);
    }
    free(pq->nodes);
    free(pq);
}

int main() {
    PriorityQueue *pq = createPriorityQueue();

    enqueue(pq, 5, "Сообщение с приоритетом 5");
    enqueue(pq, 2, "Сообщение с приоритетом 2");
    enqueue(pq, 10, "Сообщение с приоритетом 10");
    enqueue(pq, 1, "Сообщение с приоритетом 1");

    QueueNode *node;

    // Извлечение первого элемента
    node = dequeue(pq);
    if (node) {
        printf("Извлечено: %s (приоритет: %d) (Первый элемент)\n", node->message, node->priority);
        free(node->message);
        free(node);
    }

    // Извлечение элемента с приоритетом 10
    node = dequeueByPriority(pq, 10);
    if (node) {
        printf("Извлечено: %s (приоритет: %d) (Элемент с приоритетом 10)\n", node->message, node->priority);
        free(node->message);
        free(node);
    }

    // Извлечение элемента с приоритетом не ниже 3
    node = dequeueByMinPriority(pq, 3);
    if (node) {
        printf("Извлечено: %s (приоритет: %d) (Элемент с приоритетом не меньше 3)\n", node->message, node->priority);
        free(node->message);
        free(node);
    }

    freePriorityQueue(pq);
    return 0;
}