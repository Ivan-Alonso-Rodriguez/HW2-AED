#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
};

template<typename T>
class CircularDoubleLinkedList {
private:
    Node<T>* head;
    int tam;
public:
    CircularDoubleLinkedList() {
        head = nullptr;
        tam = 0;
    }

    T front() {
        return head->data;
    }

    T back() {
        return head->prev->data;
    }

    void push_front(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
        tam++;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
        }
        tam++;
    }

    T pop_front() {
        if (head == nullptr) {
            return T();
        }
        T value = head->data;
        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Node<T>* temp = head;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete temp;
        }
        tam--;
        return value;
    }

    T pop_back() {
        if (head == nullptr) {
            return T();
        }
        T value = head->prev->data;
        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Node<T>* temp = head->prev;
            temp->prev->next = head;
            head->prev = temp->prev;
            delete temp;
        }
        tam--;
        return value;
    }

    void insert(T value, int index) {
        if (index < 0 || index > tam) {
            return;
        }
        if (index == 0) {
            push_front(value);
        }
        else if (index == tam) {
            push_back(value);
        }
        else {
            Node<T>* newNode = new Node<T>;
            newNode->data = value;

            Node<T>* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            tam++;
        }
    }

    void remove(int index) {
        if (index < 0 || index >= tam) {
            return;
        }
        if (index == 0) {
            pop_front();
        }
        else if (index == tam - 1) {
            pop_back();
        }
        else {
            Node<T>* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            tam--;
        }
    }

    T operator [](int index) {
        if (index < 0 || index >= tam) {
            return T();
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        return tam;
    }

    void reverse() {
        if (head == nullptr || head->next == head) {
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < tam; i++) {
            Node<T>* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        }
        head = head->prev;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
};

int main() {
    CircularDoubleLinkedList<int> lista;

    // Insertar al frente y al final
    lista.push_front(10);
    lista.push_back(20);
    lista.push_front(5);
    lista.push_back(30);

    cout << "Elementos de la lista:" << endl;
    for (int i = 0; i < lista.size(); ++i) {
        cout << lista[i] << " ";
    }
    cout << endl;

    cout << "Primero: " << lista.front() << endl;
    cout << "Ultimo: " << lista.back() << endl;

    cout << "Eliminando primero: " << lista.pop_front() << endl;
    cout << "Eliminando ultimo: " << lista.pop_back() << endl;

    cout << "Elementos actuales:" << endl;
    for (int i = 0; i < lista.size(); ++i) {
        cout << lista[i] << " ";
    }
    cout << endl;

    lista.insert(15, 1);
    cout << "Despues de insertar 15 en posicion 1:" << endl;
    for (int i = 0; i < lista.size(); ++i) {
        cout << lista[i] << " ";
    }
    cout << endl;

    lista.reverse();
    cout << "Lista invertida:" << endl;
    for (int i = 0; i < lista.size(); ++i) {
        cout << lista[i] << " ";
    }
    cout << endl;

    lista.clear();
    cout << "La lista esta vacia?: " << (lista.empty() ? "Si" : "No") << endl;
}
