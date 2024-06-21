
#include <iostream>
using namespace std;

template <class T>
class node
{
public:
    T data;
    node *next;
    node(T &d)
    {
        data = d;
        next = NULL;
    }
};
// basic linkedlist functionality
template <class T>
class ll
{

    node<T> *head;
    node<T> *tail;
    int size;

public:
    ll()
    {
        head = tail = NULL;
        size = 0;
    }
    void insertion_at_start(T &d)
    {
        node<T> *newnode = new node<T>(d);
        if (head == NULL)
        {
            tail = newnode;
        }
        newnode->next = head;
        head = newnode;
        size++;
    }
    void insert_atend(T &d)
    {
        node<T> *newnode = new node<T>(d);
        if (tail == NULL)
        {
            head = tail = newnode;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
        }
        size++;
    }
    void deletefromstart()
    {
        if (head != NULL)
        {
            node<T> *temp = head;
            head = head->next;
            temp->next = NULL;
            if (size == 1)
            {
                tail = head;
            }
            size--;
        }
    }
    void deletefromend()
    {
        if (head != NULL)
        {
            node<T> *temp = head;
            if (size == 1)
            {
                head = tail = NULL;
            }
            else
            {
                while (temp->next != tail)
                {
                    temp = temp->next;
                }
                tail = temp;
                tail->next = NULL;
            }
            size--;
        }
    }
    void SortedInsert(T &d)
    {

        if (size == 0)
        {
            insertion_at_start(d);
        }
        else
        {
            bool flag = false;
            node<T> *current = head;
            node<T> *prev = head;

            while (!flag && current != NULL)
            {
                if (current->data > d)
                {
                    if (current == head)
                    {
                        insertion_at_start(d);
                    }
                    else
                    {
                        node<T> *newnode = new node<T>(d);
                        newnode->next = current;
                        prev->next = newnode;
                        size++;
                    }
                    flag = true;
                }
                prev = current;
                current = current->next;
            }
            if (!flag)
            {
                insert_atend(d);
            }
        }
    }

    void removethenode(T &d)
    {
        if (head != NULL)
        {
            node<T> *temp = head;
            node<T> *prev = head;
            while (temp != NULL)
            {
                if (temp->data == d)
                {
                    if (temp == head)
                    {
                        prev = temp;
                        temp = temp->next;
                        deletefromstart();
                    }
                    else if (temp == tail)
                    {
                        deletefromend();
                    }
                    else
                    {
                        prev->next = temp->next;
                        temp->next = NULL;
                        size--;
                    }
                    break;
                }
                else
                {
                    prev = temp;
                    temp = temp->next;
                }
            }
        }
    }

    T *search_id(int id) //searches the exact data
    {

        T *temp = nullptr;
        node<T> *current = head;
        while (current != NULL)
        {
            if (current->data == id)
            {
                temp = &(current->data);
                break;
            }
            current = current->next;
        }
        return temp;
    }
    T *close_search(int d) // just checks the closest value around
    {
        node<T> *current = head;
        T *temp = nullptr;
        while (current != NULL)
        {
            if (current->data == d)
            {
                if (temp != NULL)
                {
                    if (current->data < *temp)
                    {
                        temp = &(current->data);
                    }
                }
                else
                {
                    temp = &(current->data);
                }
            }
            current = current->next;
        }
        return temp;
    }

    void Print()
    {
        node<T> *current = head;
        while (current != NULL)
        {
            cout << current->data;
            current = current->next;
        }
    }
    T *getHead()
    {
        return &(head->data);
    }
    ~ll()
    {
        while (head != NULL)
        {
            if (head != NULL)
            {
                node<T> *current = head;
                current = current->next;
                delete current;
                if (size == 1)
                {
                    tail = head;
                }
                size--;
            }
        }
    }
};

class block
{
private:
    int start_byteid;

public:
    int totalbytes;
    block()
    {
        start_byteid = 0;
        totalbytes = 0;
    }
    block(int id, int total)
    {
        start_byteid = id;
        totalbytes = total;
    }
    block(block &bytes)
    {
        start_byteid = bytes.start_byteid;
        totalbytes = bytes.totalbytes;
    }
    bool operator>(block &byte)
    {
        if (start_byteid > byte.start_byteid)
        {
            return true;
        }
        return false;
    }
    block *updating_block(int size)
    {
        block *newblock = nullptr;
        if (totalbytes - size != 0)
        {
            newblock = new block(start_byteid, size);
            start_byteid = start_byteid + size;
            totalbytes = totalbytes - size;
        }
        return newblock;
    }

    bool operator<(block &b)
    {
        if (totalbytes < b.totalbytes)
        {
            return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &out, block &b)
    {
        out << "Block ID:" << b.start_byteid << endl;
        cout << "Total Bytes:" << b.totalbytes << endl;
        return out;
    }
    bool operator==(int b)
    {
        if (totalbytes >= b)
        {
            return true;
        }
        return false;
    }
    bool operator==(block &b)
    {
        if (start_byteid == b.start_byteid && totalbytes == b.totalbytes)
        {
            return true;
        }
        return false;
    }
};

class Program
{
private:
    int id;
    int size;
    ll<block> blocks;

public:
    Program()
    {
        id = 0;
        size = 0;
    }
    Program(int ID)
    {
        id = ID;
        size = 0;
    }
    void adding_block(block &b, int s)
    {
        blocks.SortedInsert(b);
        size = size + s;
    }
    block *delete_theblock()
    {
        block *current = blocks.getHead();
        blocks.deletefromstart();
        return current;
    }
    void Print()
    {
        cout << "-------Program ID------:" << id << endl;
        cout << "Size:" << size << endl;
        cout << "Memory Blocks:" << endl;
        blocks.Print();
    }
    bool operator==(int p)
    {
        if (id == p)
        {
            return true;
        }
        return false;
    }
};

class memory_management
{
private:
    ll<block> memorypool;
    ll<Program> programs;
    int sizeOfMemory;
    bool strategy;
    int programcount;

public:
    memory_management(bool s)
    {
        block *newblock = new block(1, 300);
        memorypool.SortedInsert(*newblock);
   //     sizeOfMemory = 100 * 1024;
        strategy = s;
        programcount = 0;
    }

    bool GetMem(int id, int size)
    {
        bool allocation = false;

        if (strategy == false)
        {
            allocation= FirstFit(id, size);
        }
        else
        {
            allocation = BestFit(id, size);
        }

        return allocation;
    }

    void addingtopool(int id, int total)
    {
        block *newBlock = new block(id, total);
        memorypool.SortedInsert(*newBlock);
    }
    void AddProgram()
    {
        programcount++;
        Program *newProgram = new Program(programcount);
        programs.insert_atend(*newProgram);
    }
    bool BestFit(int id, int size)
    {
      //  cout << "best fit strategy for this" << endl;
        block *block_current = memorypool.close_search(size);
        if (block_current== 0)
        {
            return false;
        }
        block *newblock = block_current->updating_block(size);
        Program *programptr = programs.search_id(id);
        if (programptr == 0)
        {
            AddProgram();
            programptr = programs.search_id(id);
        }
        if (newblock != 0)
        {
            programptr->adding_block(*newblock, size);
        }
        else
        {
            programptr->adding_block(*block_current, size);
            memorypool.removethenode(*block_current);
        }
        return true;
    }
    bool FirstFit(int id, int size)
    {
     //   cout << "first fit stratgy for this" << endl;
        block *block_current =memorypool.search_id(size);
        if (block_current == 0)
        {
            return false;
        }
        block *newblock = block_current->updating_block(size);
        Program *program_allo = programs.search_id(id);
        if (program_allo == 0)
        {
            AddProgram();
            program_allo = programs.search_id(id);
        }
        if (newblock!= 0)
        {
            program_allo->adding_block(*newblock, size);
        }
        else
        {
            program_allo->adding_block(*block_current, size);
           memorypool.removethenode(*block_current);
        }
        return true;
    }
    void printp()
    {
       memorypool.Print();
    }
    void program_print(int id)
    {
        Program *current = programs.search_id(id);
        if (current != 0)
        {
            current->Print();
        }
    }
};

int main()
{

    memory_management memory(false);
    memory.addingtopool(40, 200);
    memory.addingtopool(1500,500);
  //  memory.addingtopool(4000, 9900);
    cout<<"---------------------------------------------------------"<<endl;
    cout << "initially before allocation " << endl;
    memory.printp();
    cout<<endl;
    memory.GetMem(1, 200);
   // memory.printp();
    memory.GetMem(2, 350);
    memory.GetMem(1, 100);
    cout << "----------- MEMORY POOL ---------(after allocations)--" << endl;
    memory.printp();
    cout << endl;
    cout << "-----PROGRAMS DETAILS------------" << endl;
    memory.program_print(1);
    cout << "---------------------------------" << endl;
    memory.program_print(2);
    cout << "--------------------------------" << endl;
    memory.program_print(3);
    cout << "-------------------------------" << endl;
    memory.program_print(4);
    cout << "-------------------------------" << endl;

    system("pause");
    return 0;
}