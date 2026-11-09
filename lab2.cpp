#include <iostream>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

// Базовый уровень: Шаблонная функция
// Возвращает элемент массива по индексу или значение по умолчанию
template <typename T>
T getOrDefault(T arr[], int n, int index, T defaultValue) {
    return (index >= 0 && index < n) ? arr[index] : defaultValue;
}

// Продвинутый уровень: Шаблонный класс FixedQueue
// Кольцевой буфер фиксированного размера N
template <typename T, int N>
class FixedQueue {
    T data[N];
    int head = 0, tail = 0, count = 0;
public:
    // O(1)
    bool enqueue(const T& val) { 
        if (isFull()) return false;
        data[tail] = val;
        tail = (tail + 1) % N;
        count++;
        return true;
    }
    
    // O(1)
    bool dequeue() { 
        if (isEmpty()) return false;
        head = (head + 1) % N;
        count--;
        return true;
    }
    
    // O(1)
    T front() const { 
        return data[head]; 
    }
    
    // O(1)
    bool isEmpty() const { 
        return count == 0; 
    }
    
    // O(1)
    bool isFull() const { 
        return count == N; 
    }
};

// Точка входа
int main() {
    // Демонстрация работы getOrDefault
    int arr[] = {10, 20, 30};
    cout << "--- getOrDefault ---" << endl;
    cout << "getOrDefault(1): " << getOrDefault(arr, 3, 1, -1) << endl;
    cout << "getOrDefault(5): " << getOrDefault(arr, 3, 5, -1) << endl << endl;

    // Демонстрация работы FixedQueue
    cout << "--- FixedQueue ---" << endl;
    FixedQueue<int, 3> q;
    q.enqueue(1); 
    q.enqueue(2); 
    q.enqueue(3); 
    q.enqueue(4); // 4 не добавится, так как очередь заполнена
    
    cout << "Front: " << q.front() << endl;
    q.dequeue();
    cout << "Front after dequeue: " << q.front() << endl << endl;

    // Экспериментальное сравнение (замер вставки/извлечения 1 млн элементов)
    cout << "--- Сравнение с STL ---" << endl;
    const int TEST_N = 1000000;
    auto start = high_resolution_clock::now();
    
    queue<int> stl_q;
    for(int i = 0; i < TEST_N; i++) { 
        stl_q.push(i); 
        stl_q.pop(); 
    }
    
    auto end = high_resolution_clock::now();
    cout << "Time std::queue: " << duration_cast<microseconds>(end - start).count() << " mks" << endl;

    return 0;
}