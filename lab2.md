# Лабораторная работа №2
## Анализ сложности алгоритмов. Шаблоны классов

**Студент:** Черников Роман Сергеевич  
**Группа:** ПИЖ-6-о-25-1  
**Дисциплина:** Алгоритмы и структуры данных  
**Вариант:** 14  
**Уровень:** Продвинутый

---

## Цель работы

1. Научиться оценивать эффективность алгоритмов с помощью О-
нотации (Big O)
2. Освоить классы сложности: O(1), O(log n), O(n), O(n log n), O(n²)
3. Научиться проводить экспериментальный анализ
производительности алгоритмов
4. Освоить создание шаблонов функций и классов для работы с
различными типами данных
5. Получить навыки сравнения производительности различных
реализаций одной задачи

## Код программы

```cpp
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

// Базовый уровень: Шаблонная функция
template <typename T>
T getOrDefault(T arr[], int n, int index, T defaultValue) {
    return (index >= 0 && index < n) ? arr[index] : defaultValue;
}

// Продвинутый уровень: Шаблонный класс FixedQueue
template <typename T, int N>
class FixedQueue {
    T data[N];
    int head = 0, tail = 0, count = 0;
public:
    bool enqueue(const T& val) { // O(1)
        if (isFull()) return false;
        data[tail] = val;
        tail = (tail + 1) % N;
        count++;
        return true;
    }
    bool dequeue() { // O(1)
        if (isEmpty()) return false;
        head = (head + 1) % N;
        count--;
        return true;
    }
    T front() const { return data[head]; } // O(1)
    bool isEmpty() const { return count == 0; } // O(1)
    bool isFull() const { return count == N; } // O(1)
};

int main() {
    // Демонстрация работы getOrDefault
    int arr[] = {10, 20, 30};
    cout << "getOrDefault(1): " << getOrDefault(arr, 3, 1, -1) << endl;
    cout << "getOrDefault(5): " << getOrDefault(arr, 3, 5, -1) << endl;

    // Демонстрация работы FixedQueue
    FixedQueue<int, 3> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3); q.enqueue(4); // 4 не добавится
    cout << "Front: " << q.front() << endl;
    q.dequeue();
    cout << "Front after dequeue: " << q.front() << endl;

    // Экспериментальное сравнение (замер вставки/извлечения 1 млн элементов)
    const int TEST_N = 1000000;
    auto start = high_resolution_clock::now();
    queue<int> stl_q;
    for(int i = 0; i < TEST_N; i++) { stl_q.push(i); stl_q.pop(); }
    auto end = high_resolution_clock::now();
    cout << "Time std::queue: " << duration_cast<microseconds>(end - start).count() << " mks" << endl;

    return 0;
}
```
## Вывод
Один экземпляр клуба: true

=== Спортивный клуб ===
Тренеры: 1

Иван Петров

Секции: 1

Секция: Бокс

Участник: Алексей

Участник: Дмитрий

Всего участников: 2

Участников после создания: 3

Участников после уничтожения временного объекта: 2