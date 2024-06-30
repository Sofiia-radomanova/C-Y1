#include <iostream> 
#include <vector> 
#include <fstream> 

using namespace std;

// Структура для представлення маршруту
struct Route
{
    int routeNumber;    // Номер маршруту
    string startPoint;  // Початкова точка
    string endPoint;    // Кінцева точка
    float routeLength;  // Довжина маршруту

    // Конструктор за замовчуванням 
    Route() : routeNumber(0), startPoint(""), endPoint(""), routeLength(0.0) {}

    // Конструктор з параметрами 
    Route(int number, const string& start, const string& end, float length)
        : routeNumber(number), startPoint(start), endPoint(end), routeLength(length) {}

    // Перевантаження оператора виведення 
    friend ostream& operator<<(ostream& os, const Route& route)
    {
        // Виводимо дані про маршрут у форматі:
        // Номер маршруту
        // Початкова точка
        // Кінцева точка
        // Довжина маршруту
        os << route.routeNumber << "\n"
            << route.startPoint << "\n"
            << route.endPoint << "\n"
            << route.routeLength << "\n";
        return os;
    }

    // Перевантаження оператора введення 
    friend istream& operator>>(istream& is, Route& route)
    {
        cout << "Введіть номер маршруту: ";
        is >> route.routeNumber;
        cout << "Початкова точка: ";
        is >> route.startPoint;
        cout << "Кінцева точка: ";
        is >> route.endPoint;
        cout << "Довжина (км): ";
        is >> route.routeLength;
        return is;
    }

    // Перевантаження оператора додавання 
    Route operator+(const Route& other) const
    {
        // Створюємо новий маршрут, сума довжин маршрутів
        Route result;
        result.routeLength = this->routeLength + other.routeLength;
        return result;
    }

    // Перевантаження оператора порівняння 
    bool operator>(const Route& other) const 
    {
        // Порівнюємо маршрути за довжиною
        return this->routeLength > other.routeLength;
    }
};

// Збереження маршрутів у файл 
void saveToFile(const vector<Route>& routes, const string& filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        // Записуємо дані про маршрути у файл
        for (const auto& route : routes)
        {
            file << route << endl;
        }
        file.close();
        cout << "Маршрути збережено до " << filename << endl;
    }
    else
    {
        cerr << "Неможливо відкрити файл: " << filename << endl;
    }
}

// Зчитування маршрутів з файлу 
vector<Route> readFromFile(const string& filename)
{
    vector<Route> routes;
    ifstream file(filename);
    if (file.is_open())
    {
        Route route;
        // Зчитуємо дані про маршрути з файлу
        while (file >> route)
        {
            routes.push_back(route);
        }
        file.close();
        cout << "Маршрути завантажено з " << filename << endl;
    }
    else {
        cerr << "Неможливо відкрити файл: " << filename << endl;
    }
    return routes;
}

// Знаходження середньої довжини маршрутів 
float averageRouteLength(const vector<Route>& routes)
{
    Route totalRoute;
    // Обчислюємо суму довжин маршрутів
    for (const auto& route : routes)
    {
        totalRoute = totalRoute + route;
    }
    // Середня довжина - сума довжин поділена на кількість маршрутів
    return totalRoute.routeLength / routes.size();
}

// Знаходження найдовшого маршруту 
Route longestRoute(const vector<Route>& routes)
{
    Route longest = routes[0];
    // Знаходимо найдовший маршрут
    for (const auto& route : routes)
    {
        if (route > longest)
        {
            longest = route;
        }
    }
    return longest;
}

// Пошук маршруту з пересадкою 
void way(const vector<Route>& routes)
{
    string startPoint, endPoint;
    cout << "Введіть початкову точку: ";
    cin >> startPoint;
    cout << "Введіть кінцеву точку: ";
    cin >> endPoint;

    bool foundStart = false, foundEnd = false;
    // Перевіряємо чи існують маршрути з введеними точками
    for (const auto& route : routes)
    {
        if (route.startPoint == startPoint)
        {
            foundStart = true;
        }
        if (route.endPoint == endPoint)
        {
            foundEnd = true;
        }
    }

    // Якщо хоча б одна точка не знайдена, виводимо відповідне повідомлення
    if (!foundStart || !foundEnd)
    {
        cout << "Маршрут з такими точками не знайдено\n";
        return;
    }

    // Пошук маршруту з пересадкою
    for (const auto& route : routes)
    {
        if (route.startPoint == startPoint)
        {
            cout << "Сідайте на " << startPoint << " на маршрут " << route.routeNumber << endl;
            startPoint = route.endPoint;
            if (startPoint == endPoint)
            {
                cout << "Досягнуто кінцеву точку " << endPoint << endl;
                return;
            }
        }
    }
    cout << "Маршрут не знайдено\n";
}

// Пошук маршруту за початком або кінцем 
void find(const vector<Route>& routes)
{
    string Point;
    Route finded;
    cin >> Point;
    cout << "Маршрути:\n";
    // Пошук маршрутів за початком або кінцем
    for (const auto& route : routes)
    {
        if ((route.startPoint == Point) || (route.endPoint == Point))
        {
            finded = route;
            cout << finded << endl;
        }
    }
}

// Основна функція 
int main()
{
    vector<Route> routes; // Вектор для зберігання маршрутів
    string filename = "routes.txt"; // Назва файлу для зберігання маршрутів

    int choice;
    do
    {
        // Виведення меню
        cout << "Меню:\n"
            << "1. Додати маршрут\n"
            << "2. Зберегти у файл\n"
            << "3. Завантажити з файлу\n"
            << "4. Середня довжина маршрутів\n"
            << "5. Найдовша дорога\n"
            << "6. Знайти за початком/кінцем\n"
            << "7. З пересадкою\n"
            << "8. Вихід\n"
            << "Введіть вибір: ";
        cin >> choice;

        // Обробка вибору користувача
        switch (choice)
        {
        case 1:
        {
            // Додавання нового маршруту
            Route route;
            cin >> route;
            routes.push_back(route);
            break;
        }
        case 2:
            // Збереження маршрутів у файл
            saveToFile(routes, filename);
            break;
        case 3:
            // Завантаження маршрутів з файлу
            routes = readFromFile(filename);
            break;
        case 4:
            // Виведення середньої довжини маршрутів
            cout << "Середня довжина: " << averageRouteLength(routes) << " km\n";
            break;
        case 5:
            // Виведення найдовшого маршруту
            cout << "Найдовший маршрут:\n" << longestRoute(routes) << endl;
            break;
        case 6:
            // Пошук маршруту за початком або кінцем
            cout << "Назва зупинки : \n";
            find(routes);
            break;
        case 7:
            // Пошук маршруту з пересадкою
            way(routes);
            break;
        case 8:
            // Вихід з програми
            cout << "Вихід...\n";
            break;
        default:
            // Неправильний ввід
            cout << "Неправильний вибір, оберіть від 1-го до 7-ми.\n";
        }
    } while (choice != 8); // Повторюємо цикл до вибору виходу з програми

    return 0;
}
