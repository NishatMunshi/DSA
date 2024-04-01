#include <stdio.h>
#include <stdlib.h>
#define NUMBER_OF_QUEUES 3
typedef struct Node {
  char name;
  unsigned arrivalTime, transactionDuration;
  struct Node *next;
  unsigned timeSpentInBank, howMuchWorkIsDone;
} Node;
typedef Node Customer;

typedef struct Queue {
  Customer *front, *rear;
  unsigned size;
} Queue;
int empty(Queue const *const _queue) { return _queue->size == 0; }

void initialize_queue(Queue *const _queue) {
  _queue->front = (Node *)malloc(sizeof(Node));
  _queue->rear = (Node *)malloc(sizeof(Node));
  _queue->front->next = _queue->rear;
  _queue->rear->next = NULL;
  _queue->size = 0;
}
void add_customer(Queue *const _queue, Customer const _customer) {
  *(_queue->rear) = _customer;

  Node *newNode = (Node *)malloc(sizeof(Node));
  _queue->rear->next = newNode;
  newNode->next = NULL;
  _queue->rear = newNode;

  ++_queue->size;
}

unsigned remove_customer(Queue *const _queue) {
  if (_queue->size == 0) {
    printf("\nUnderfLow Error!\n");
    return UINT_MAX;
  }
  Node *toFree = _queue->front;
  _queue->front = _queue->front->next;
  free(toFree);

  --_queue->size;
  return _queue->front->timeSpentInBank;
}

void print_queue(Queue const *const _queue) {
  for (Node *node = _queue->front->next; node != _queue->rear; node = node->next) {
    printf("%c ", node->name);
  }
  printf("\n\t");
}

float simulate_bank(Queue *_queues, Queue const _customers) {
  float totalTimeSpentByCustomers = 0.f;
  char nameOfCustomer = 'A';

    // one tick of simulation
  for (unsigned currentTime = 0, numCustomersServed = 0; numCustomersServed != _customers.size; currentTime++) {
    for (unsigned queueIndex = 0; queueIndex < NUMBER_OF_QUEUES; ++queueIndex) {
      if (empty(_queues + queueIndex))
        continue;
      // give service to all customers in the front of the non empty queues
      _queues[queueIndex].front->next->howMuchWorkIsDone++;

      // increment time spent of each customer who's in the bank
      for (Customer *customer = _queues[queueIndex].front->next; customer != _queues[queueIndex].rear; customer = customer->next) {
        customer->timeSpentInBank++;
      }
    }

    // now Check if any of the non empty queues' front customer is done
    for (unsigned queueIndex = 0; queueIndex < NUMBER_OF_QUEUES; ++queueIndex) {
      if (empty(_queues + queueIndex))
        continue;

      Customer *frontCustomer = _queues[queueIndex].front->next;
      if (frontCustomer->howMuchWorkIsDone ==
          frontCustomer->transactionDuration) {
        totalTimeSpentByCustomers += remove_customer(_queues + queueIndex);
        numCustomersServed++;
      }
    }

    // check if a customer enters the bank at this clock tick
    for (Customer *customer = _customers.front->next; customer != _customers.rear; customer = customer->next) {
      if (_customers.size == 0)
        break;
      if (customer->arrivalTime == currentTime) {
        customer->name = nameOfCustomer++;
        customer->timeSpentInBank = 0;   // start tracking his time
        customer->howMuchWorkIsDone = 0; // no work is done yet
        // add him to the queue of least size (most practical)
        Queue *shortestQueue = _queues + 0;
        for (unsigned queueIndex = 0; queueIndex < NUMBER_OF_QUEUES; ++queueIndex) {
          if (_queues[queueIndex].size < shortestQueue->size)
            shortestQueue = _queues + queueIndex;
        }
        add_customer(shortestQueue, *customer); // make a copy
      }
    }

    // show the current situaion of the queues
    printf("\nTime %d:\t", currentTime);
    for (unsigned queueIndex = 0; queueIndex < NUMBER_OF_QUEUES; ++queueIndex) {
      printf("Queue %d: ", queueIndex + 1);
      print_queue(_queues + queueIndex);
    }
  }
  if (_customers.size != 0)
    return totalTimeSpentByCustomers / _customers.size;
  return 0.f;
}

int main() {
  int numCustomers;
  printf("Enter the number of customers: ");
  scanf("%d", &numCustomers);

  Queue queues[NUMBER_OF_QUEUES];
  for (unsigned queueIndex = 0; queueIndex < NUMBER_OF_QUEUES; ++queueIndex) {
    initialize_queue(queues + queueIndex);
  }

  Queue customers; // for saving all data entered by user
  initialize_queue(&customers);
  for (unsigned customerIndex = 0; customerIndex < numCustomers;
       ++customerIndex) {
    int arrivalTime, transactionDuration;
    printf("Enter arrival time and transaction duration for customer %d: ",
           customerIndex + 1);
    scanf("%d %d", &arrivalTime, &transactionDuration);

    Customer customer;
    customer.arrivalTime = arrivalTime;
    customer.transactionDuration = transactionDuration;
    add_customer(&customers, customer);
  }

  float avgWaitingTime = simulate_bank(queues, customers);

  printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);

  return 0;
}
