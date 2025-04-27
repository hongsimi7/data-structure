#include "utils.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

/*
    [Task 1] List

    Description:
        Implement a function that can insert or delete an integer into the list.
        A user can insert an element in ascending order
        or delete an element at the specific index.
        If the specified index is out of range of the given list, print "ERROR".

    Input:
        Sequence of commands, which is one of the following:
        - ('insert',integer value): insert integer value at the appropriate
          position in the list, ensuring that the elements within the array are
          always in ascending order.
        - ('delete',index): delete an element at the index in the list.
        - Index indicates zero-based index.

    Output:
        - After all sequence of commands are processed, the resulting string of
          list elements should have spaces between each element, but no space
          after the last element.
        - "ERROR" should be printed if the deleting index is out of range.
*/

struct NodeL {
  int value;
  NodeL* next;
};

void insert_node(NodeL** head, int value) {
  NodeL* element = new NodeL;                 //요소 생성
  element->value = value;
  element->next = nullptr;
  NodeL* finder = *head;

  if(finder == NULL) {    //리스트가 비어 있을 때
    *head = element;  
  }

  else if(value <= finder->value) {   //리스트 맨 앞에 와야할 때
    element->next = *head;
    *head = element; 
  }

  else {                              //나머지 경우
      while (finder->next != nullptr) {
        if (value >= finder->value && value <= finder->next->value) {
          element->next = finder->next;
          finder->next = element;
          return;
        }
        finder = finder->next;
      }
      finder->next = element;
  }

  // TODO: Implement insert operation
}

void delete_node(NodeL** head, int index) {
  NodeL* finder = *head;            
  
  if(index == 0) {                //맨 앞의 요소를 제거해야 할 때
    *head = finder->next;
    delete finder;
    return;
  }

  else {                          //나머지 경우
    for(int i = 0; i < index - 1; i++)
    {
      if(finder->next == nullptr) {
        return;
      }
      finder = finder->next;
    }

    NodeL* eraser = finder->next;
    if(eraser == nullptr) {
      return;
    }
    finder->next = eraser->next;
    delete eraser;
  }
  
  // TODO: Implement delete operation
}

void task_1(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  NodeL* list = NULL;
  int size = 0;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("insert") == 0) {                            //삽입
      size += 1;                                               
      insert_node(&list, instr_seq->instructions[i].value);
    }   
    else if (command.compare("delete") == 0) {                    //삭제

      if(instr_seq->instructions[i].value + 1 > size) {             //out of range(ERROR)
        answer = "ERROR";
        continue;
      }
      else {                                                        //정상 작동
        size -= 1;
        delete_node(&list, instr_seq->instructions[i].value);
      }
    } 
    else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (answer != "ERROR") {          //에러가 아닐 때
    NodeL* temp = list;
    while (temp != NULL) {
      answer += to_string(temp->value);
      if (temp->next != NULL) {
        answer += " ";
      }
      temp = temp->next;
    }
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 1]" << endl;
  fout << answer << endl;
}
// =================================
// End of Task 1
// =================================

/*
    [Task 2] Postfix Expression Calculator / Stack

    Description:
        Implement an array-based stack and a function EvaluatePostfix.
        Postfix expression is the expression of the form
            [operand1] [operand2] [operator]
        c.f. Infix expression is the expression of the form
            [operand1] [operator] [operand2]
        This function returns the string that contains the evaluated value of
        the given postfix expression, utilizing your implementation of stack.

    Input:
        A string of postfix expression. Input is given without space.
        The operators that need to be implemented is shown below:
        - '+': addition
          * 34+ => 7
        - '-': subtraction
          * 51- => 4
        - '*': multiplication
          * 42* => 8
        - '/': integer division (You should also handle division by zero case)
          * 83/ => 2
        The operands can be 1-digit integers between 0-9.
        - Values other than 0-9 should be also handled during evaluation.

    Output:
        - "ERROR" for the cases:
          * The operator does not have enough number of available operands
          * More than one value left after evaluation
        - "DIVISIONBYZERO" for division by zero case
        - Otherwise, the resulting Integer value of the expression
          * Use to_string(int value) to convert int to string
        - You need not to handle the case of exceeding maximum stack capacity

    Some Example Inputs and Outputs:
        1. 2 => 2
        2. 234+* => 14
        3. 56*34*+ => 42
        4. 68-* => ERROR
        5. 71 => ERROR
        6. 733-/ => DIVISIONBYZERO
*/

/* DO NOT MODIFY */

class ArrayStack {
  int top;
  int container[1000];

public:
  ArrayStack() { top = -1; }
  void push(int value);
  int pop();
};

/* DO NOT MODIFY */

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
void ArrayStack::push(int value) {      //push 함수
  // TODO: Implement push operation
  top += 1;
  container[top] = value;
}

int ArrayStack::pop() {                 //pop 함수
  // TODO: Implement pop operation
  if(top < 0) {   //요소가 더 이상 없을 때
    return -1;
  }
  int temp = container[top];
  container[top] = -1;
  top -= 1;
  return temp;
}

string EvaluatePostfix(string expression) {
  // TODO: Implement postfix expression evaluation
  ArrayStack stack;
  string result = "";
  int count = 0;
  int num1 = -1;
  int num2 = -1;
  int oper_count = 0;

  while(1)
  {
    if(expression.length() == count) {    //모든 계산이 끝났을 때
      if(oper_count == 0 && count > 1)    //operator가 존재하지 않고 숫자 2개 이상만 존재할 때      
      {
        result = "ERROR";
      }
      else {                             //정상 작동     
        result = to_string(stack.pop());
      }
      
      break;
    }

    else if(expression[count] == '0') {                            // 0일 때
      stack.push(0);
      count++;
      continue;
    }
    else if(expression[count] == '1') {                            // 1일 때
      stack.push(1);
      count++;
      continue;
    }
    else if(expression[count] == '2') {                            // 2일 때
      stack.push(2);
      count++;
      continue;
    }
    else if(expression[count] == '3') {                            // 3일 때
      stack.push(3);
      count++;
      continue;
    }
    else if(expression[count] == '4') {                            // 4일 때
      stack.push(4);
      count++;
      continue;
    }
    else if(expression[count] == '5') {                            // 5일 때
      stack.push(5);
      count++;
      continue;
    }
    else if(expression[count] == '6') {                            // 6일 때
      stack.push(6);
      count++;
      continue;
    }
    else if(expression[count] == '7') {                            // 7일 때
      stack.push(7);
      count++;
      continue;
    }
    else if(expression[count] == '8') {                            // 8일 때
      stack.push(8);
      count++;
      continue;
    }
    else if(expression[count] == '9') {                            // 9일 때
      stack.push(9);
      count++;
      continue;
    }
    else {                              //operator를 감지했을 때
      oper_count++;
      num2 = stack.pop();
      num1 = stack.pop();

      if(num1 == -1 || num2 == -1) {    //계산이 불가능(숫자 부족)
        result = "ERROR";
        break;
      } 

      if(expression[count] == 43) {     //+ 계산
        stack.push(num1 + num2);
        count++;
        continue;
      }
      if(expression[count] == 45) {     //- 계산
        if(num1 - num2 < 0) {           //계산이 음수가 나올 때
          result = "ERROR";
          break;
        }
        stack.push(num1 - num2);        //정상 작동
        count++;
        continue;
      }
      if(expression[count] == 42) {     //* 계산
        stack.push(num1 * num2);
        count++;
        continue;
      }
      if(expression[count] == 47) {     // / 계산
        if(num2 == 0) {                 //0으로 나누려할 때
          result = "DIVISIONBYZERO";
          break;
        }
        stack.push(num1 / num2);      //정상 작동
        count++;
        continue;
      }
    }
  }
  return result;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

void task_2(ofstream &fout, string expression) {
  int expr_length = expression.length();
  string answer;

  answer = EvaluatePostfix(expression);

  fout << "[Task 2]" << endl;
  fout << answer << endl;
}

// =================================
// End of Task 2
// =================================

/*
    [Task 3] Round Robin / Circular Queue

    Description:
        Round-robin (RR) is one of the CPU scheduling algorithms, where each
        process is allocated with equal share of CPU time. Processes are put
        into a circular queue, and when the allocated time expires, the process
        goes to the very back of the queue, allowing the next process to be
        processed by the CPU. For further knowledge, see the link below:
        https://en.wikipedia.org/wiki/Round-robin_scheduling

        Implement RR algorithm utilizing circular queue.
        For the simplicity of the given task, you only need to handle the case
        where all processes arrive at the queue at the same arrival time.

        Hint: implenent rotate() without using enqueue and dequeue, which is to
        be used in moving unfinished process to the back

    Input:
        Sequence of instructions, each containing process name and its burst
        time (total time required to complete the process)
        -	(process_name,t): enqueue the process named process_name with
          burst time t to the circular queue
        Assume that the time quantum = 1, which is the allocated time for a
        process to run in a preemptive manner.
    
    Output:
        Sequence of names of the processes handled at each time point
        (t = 0, 1, 2, 3, ...) until the end of the execution. The names should
        be separated with a blank ' '.
        See below examples for better understanding

    Example Inputs and Outputs:
    1. [('P0',5), ('P1',3)]
      => P0 P1 P0 P1 P0 P1 P0 P0
    2. [('P0',3)]
      => P0 P0 P0
    3. [('P0',2), ('P1',1), ('P2',3)]
      => P0 P1 P2 P0 P2 P2
*/

/* DO NOT MODIFY */

struct NodeQ {
  string process_name;
  int time;
  NodeQ* next;
};

class CircularQueue {
  NodeQ *front;
  NodeQ *rear;

public:
  CircularQueue() {
    front = NULL;
    rear = NULL;
  }
  void enqueue(string process_name, int t);
  void dequeue();
  NodeQ* peek();
  void rotate();
  bool isEmpty();
};

/* DO NOT MODIFY */

void CircularQueue::enqueue(string process_name, int t) {
  // TODO: Implement enqueue operation
  NodeQ* element = new NodeQ;               //요소 생성
  element->process_name = process_name;
  element->time = t;
  element->next = NULL;
  
  if(rear == NULL) {          //맨 뒤가 비어있을 때
    front = rear = element;
  }
  else {                      //아닐 때
    rear->next = element;
    rear = element;
  }
  
}

void CircularQueue::dequeue() {
  // TODO: Implement dequeue operation
  NodeQ* temp = front;      //요소 삭제를 위한 temp 생성
  front = front->next;
  delete temp;
}

NodeQ* CircularQueue::peek() {      //front 리턴
  // TODO: Implement peek operation
  return front;
}

void CircularQueue::rotate() {    
  /*
  TODO: Implement rotate operation, where you move element at
  the front to the rear of the queue
  */
 if(front->next == NULL) {    //front와 rear가 같을 때(요소가 하나일 때)
    front->time--;
    return;
 }                            //나머지 경우
  NodeQ* temp = front;
  front = front->next;
  temp->next = NULL;
  rear->next = temp;
  rear = temp;

  temp->time--;
}

bool CircularQueue::isEmpty() {
  return front == NULL;
}

void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;
  CircularQueue queue;
  int time = 0;

  for (int i = 0; i < instr_seq->length; i++) {
    string process_name = instr_seq->instructions[i].command;
    int t = instr_seq->instructions[i].value;
    // TODO: Implement here
    queue.enqueue(process_name, t);     //삽입
    time += t;
  }

  while (!queue.isEmpty()) {            //queue가 비어있지 않을 까지
    // TODO: Implement here
    answer += queue.peek()->process_name;
    
    if(queue.peek()->time == 1) {       //한 번 남았을 떼
      queue.dequeue();
    }

    else {                              //순환
      queue.rotate();
      time--;
    }

    if(queue.peek() != NULL) {          //queue가 비어있지 않을 때   
      answer += " ";
    }
  }

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}
// =================================
// End of Task 3
// =================================

// DO NOT CHANGE main() function!!
// ==================================================================================

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;
  string expression;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    if (task_num == 2)
      expression = argv[2];
    else {
      try {
        instr_seq = ParseInstructions(argv[2]);
      } catch (const char *e) {
        cerr << e << endl;
        return -1;
      }
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout, instr_seq);
    break;
  case 2:
    task_2(fout, expression);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 0:
    InstructionSequence *instr_seq_1;
    instr_seq_1 = ParseInstructions(TASK_1_DEFAULT_ARGUMENT);
    task_1(fout, instr_seq_1);

    InstructionSequence *instr_seq_2;
    expression = TASK_2_DEFAULT_ARGUMENT;
    task_2(fout, expression);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
