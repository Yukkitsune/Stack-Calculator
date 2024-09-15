#include <iostream>
#include <stack> // Используем стек
#include <string> // Строки
#include <sstream> // Рассматриваем строку как поток, преобразовываем её элементы в числовой тип данных при необходимости
#include <cmath> // Используем математику
#ifndef M_PI // Объявляем константу Пи
#define M_PI (3.14159265358979323846)
#endif
struct Leksema { // Лексема - Неделимый элемент выражения (формулы)
    char type; // '(' ')' '+' '-' '*' '/'  0 - число
    double value; //Значение (только для чисел). У операций значение всегда "0"
};
int getPriority(char Ch) { // Определяем приоритет операций
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;
    if (Ch == '^') return 3;
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e') return 4;
    else return -1;
}
bool calculations(std::stack<Leksema>& stack_numbers, std::stack<Leksema>& stack_operations, Leksema& item) { // Расчеты
    double first = 0.0;
    double second = 0.0;
    double result = 0.0;
    first = stack_numbers.top().value; // Присваиваем переменной значение элемента на вершине стека
    stack_numbers.pop(); // Удаляем элемент с вершины стека
    switch (stack_operations.top().type) { // Переключатель в зависимости от операции
    case '+': // Сложение
        second = stack_numbers.top().value; // Присваиваем переменной значение элемента на вершине стека
        stack_numbers.pop(); // Удаляем элемент с вершины стека
        result = first + second; // Результат операции сложения
        item.type = '0'; // Присваиваем объекту тип "0", так как возвращаем число
        item.value = result; // Присваиваем объекту значение результата операции
        stack_numbers.push(item); // Добавляем число в стек с числами
        stack_operations.pop(); // Удаляем операцию сложения из стека
        break;
    case '-':
        second = stack_numbers.top().value; // Аналогично с операцией сложения
        stack_numbers.pop();
        result = second - first;
        item.type = '0';
        item.value = result;
        stack_numbers.push(item);
        stack_operations.pop();
        break;
    case '*':
        second = stack_numbers.top().value; // Аналогично с операцией сложения
        stack_numbers.pop();
        result = first * second;
        item.type = '0';
        item.value = result;
        stack_numbers.push(item);
        stack_operations.pop();
        break;
    case '/':
        second = stack_numbers.top().value; // Аналогично с операцией сложения
        if (second == 0) { // Ошибка в случае деления на ноль
            std::cerr << "Incorrect equasion - division by zero :(\n";
            return false;
        }
        else {
            stack_numbers.pop();
            result = second / first;
            item.type = '0';
            item.value = result;
            stack_numbers.push(item);
            stack_operations.pop();
            break; 
        }
    case '^':
        second = stack_numbers.top().value; // Аналогично с операцией сложения
        stack_numbers.pop();
        result = pow(second, first);
        item.type = '0';
        item.value = result;
        stack_numbers.push(item);
        stack_operations.pop();
        break;
    case 's':
        result = sin(first); // Вычисляем синус первого элемента с вершины стека
        item.type = '0';
        item.value = result;
        stack_numbers.push(item);
        stack_operations.pop();
        break;
    case 'c':
        result = cos(first); // Аналогично с синусом
        item.type = '0';
        item.value = result;
        stack_numbers.push(item);
        stack_operations.pop();
        break;
    case 't':
        if (cos(first) == 0) { // Случай, когда тангенс не существует
            std::cerr << "Tan doesn't exist\n";
            return false;
        }
        else {
            result = tan(first); // Аналогично с синусом
            item.type = '0';
            item.value = result;
            stack_numbers.push(item);
            stack_operations.pop();
            break;
        }
    case 'g':
        if (sin(first) == 0) { // Случай, когда котангенс не существует
            std::cerr << "Ctg doesn't exist\n";
            return false;
        }
        else {
            result = cos(first) / sin(first); // Вычисляем значение котангенса
            item.type = '0';
            item.value = result;
            stack_numbers.push(item);
            stack_operations.pop();
            break;
        }
    case 'e':
        result = exp(first); // Экспонента
        item.type = '0';
        item.value = result;
        stack_numbers.push(item);
        stack_operations.pop();
        break;
    default:
        std::cerr << "Incorrect equasion! :<\n"; // Случай, когда символ не подходит ни под одну из операций
        return false;
        break;
    }
    return true; // В случае корректных вычислений возвращаем true
}
int main()
{
    setlocale(LC_ALL, "russian");
    std::cout << "Welcome to calculator\n";
    std::cout << "You can use these operations: '+', '-', '*', '/', '^'\n";
    std::cout << "To use 'sin', 'cos', 'tan', 'ctg' type these words letter by letter like i did there\n";
    std::cout << "To use the E number type 'exp'\n";
    std::cout << "To use the Pi number type 'p'\n";
    while (true) {
        std::cout << "Input equasion: ";
        std::string equasion; // Строка с выражением
        std::getline(std::cin, equasion); // Получаем строку
        std::stringstream sequasion{ equasion }; // Рассматриваем строку как поток, преобразовываем её элементы в числовой тип данных при необходимости
        char Ch; //Переменная, в которую будет записываться текущий обрабатываемый символ
        double value;
        bool flag = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
        std::stack<Leksema> stack_numbers; // Стек чисел
        std::stack<Leksema> stack_operations; // Стек операций
        Leksema item; // Объект типа Leksema
        while (true) {
            Ch = sequasion.peek(); // Смотрим символ
            if (Ch == '\377') break; //Если достигнут конец строки, выходим из цикла
            if (Ch == ' ') { // Игнорируем пробелы
                sequasion.ignore();
                continue;
            }
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == true) { // Если прочитано число или унарный минус
                sequasion >> value; // Считываем значение
                item.type = '0';
                item.value = value;
                stack_numbers.push(item);
                flag = false;
                continue;
            }
            if (Ch == '+' || Ch == '-' && flag == false || Ch == '*' || Ch == '/' || Ch == '^') { // Если прочитана операция
                if (stack_operations.size() == 0) { // Если стек операций пустой, добавляем операцию
                    item.type = Ch; 
                    item.value = 0;
                    stack_operations.push(item);
                    sequasion.ignore();
                    continue;
                }// Если стек непустой и приоритет операции выше приоритета на вершине стека, добавляем операцию в стек
                if (stack_operations.size() != 0 && getPriority(Ch) > getPriority(stack_operations.top().type)) { 
                    item.type = Ch;
                    item.value = 0;
                    stack_operations.push(item);
                    sequasion.ignore();
                    continue;
                }// Если стек непустой и приоритет операции меньше приоритета на вершине стека, вычисляем выражение
                if (stack_operations.size() != 0 && getPriority(Ch) <= getPriority(stack_operations.top().type)) {
                    if (calculations(stack_numbers, stack_operations, item)) continue;
                    else {
                        system("pause");
                        return -1;
                    }
                }
            }
            if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e') { // Тригонометрические операции и экспонента
                char massive[3];
                for (int i = 0; i < 3; ++i) { // Создаем временный массив на три элемента и считываем в него три символа из строки
                    Ch = sequasion.peek();
                    massive[i] = Ch;
                    sequasion.ignore();
                }
                if (massive[0] == 's' && massive[1] == 'i' && massive[2] == 'n') { // Если считан синус, добавляем операцию в стек
                    item.type = 's';
                    item.value = 0;
                    stack_operations.push(item);
                    continue;
                }
                if (massive[0] == 'c' && massive[1] == 'o' && massive[2] == 's') { // Косинус аналогично синусу
                    item.type = 'c';
                    item.value = 0;
                    stack_operations.push(item);
                    continue;
                }
                if (massive[0] == 't' && massive[1] == 'a' && massive[2] == 'n') { // Тангенс аналогично синусу
                    item.type = 't';
                    item.value = 0;
                    stack_operations.push(item);
                    continue;
                }
                if (massive[0] == 'c' && massive[1] == 't' && massive[2] == 'g') { // Котангенс аналогично синусу
                    item.type = 'c';
                    item.value = 0;
                    stack_operations.push(item);
                    continue;
                }
                if (massive[0] == 'e' && massive[1] == 'x' && massive[2] == 'p') { // Экспонента аналогично синусу
                    item.type = 'e';
                    item.value = 0;
                    stack_operations.push(item);
                    continue;
                }
            }
            if (Ch == 'p') { // Если считано число пи, добавляем его в стек чисел
                item.type = '0';
                item.value = M_PI;
                stack_numbers.push(item);
                flag = false;
                sequasion.ignore();
                continue;
            }
            if (Ch == '(') { // Если считана открывающая скобка, добавляем в стек с операциями
                item.type = Ch;
                item.value = 0;
                stack_operations.push(item);
                sequasion.ignore();
                continue;
            }
            if (Ch == ')') { // Если считана закрывающая скобка
                // Идем по стеку операций, пока его верхний элемент не станет открывающей скобко и последовательно выполняем операции с вершины
                while (stack_operations.top().type != '(') { 
                    if (calculations(stack_numbers, stack_operations, item)) continue;
                    else {
                        system("pause");
                        return -1;
                    }
                }
                stack_operations.pop(); // Удаляем скобку с вершины стека операций
                sequasion.ignore();
                continue;
            }
            else {
                std::cerr << "Incorrect equasion :(\n";// Если введено непонятное выражение
                system("pause");
                return -1;
            }
            
        }
            while (stack_operations.size() != 0) { // Выполняем операции до тех пор, пока стек с ними не пуст или пока выражение не окажется неверным
                if (calculations(stack_numbers, stack_operations, item)) continue;
                else {
                    system("pause");
                    return -1;
                }
            }
        std::cout << "answer: " << stack_numbers.top().value << std::endl; // Пишем ответ
        system("pause");
    }
    
    return 0;
}
