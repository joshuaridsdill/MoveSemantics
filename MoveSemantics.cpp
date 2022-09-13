// MoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Entity
{
public:
    Entity(std::string&& name) noexcept
    {
        m_Name = name;
    }

    Entity(Entity& e) noexcept
    {
        m_Name = new char[sizeof(e.m_Name)];
        std::cout << "Copied!\n";
    }

    Entity(Entity&& e) noexcept
    {
        m_Name = e.m_Name;
        e.m_Name = "";
        std::cout << "Moved!\n";
    }

    ~Entity()
    {
        std::cout << "Destroyed!\n";
    }

private:
    std::string m_Name;
};

class String
{
public:

    String(const char* str)
    {
        m_Size = strlen(str);
        m_Data = new char[m_Size + 1];
        //memcpy_s(&m_Data, m_Size, str, m_Size);
        memcpy(m_Data, str, m_Size);
        *(m_Data + m_Size) = 0;
        std::cout << "Created!\n";
    }

    String(const String& str) noexcept
    {
        m_Size = str.m_Size;
        m_Data = new char[m_Size];
        memcpy_s(&m_Data, m_Size, str.m_Data, m_Size);
        std::cout << "Copied!\n";
    }
    
    String(String&& str) noexcept
    {
        m_Size = str.m_Size;
        m_Data = str.m_Data;

        str.m_Data = nullptr;
        str.m_Size = 0;

        std::cout << "Moved!\n";
    }

    ~String()
    {
        //delete m_Data;
    }

    friend std::ostream& operator<<(std::ostream& os, String& str);

    void Print()
    {
        /*for (int i = 0; i < m_Size; i++)
        {
            std::cout << m_Data[i];
        }
        std::cout << '\n';*/

        std::cout << m_Data << '\n';
    }

    size_t Size()
    {
        return m_Size;
    }

private:
    char* m_Data;
    size_t m_Size;
};

std::ostream& operator<<(std::ostream& os, String& str)
{
    os << str.m_Data;

    return os;
}

int main()
{
    String str = "Hello, World!";
    String str2 = "Goodbye, World!";
    //String str3(std::move(str));

    std::cout << str << '\n';
    str.Print();
    std::cout << str.Size() << '\n';

    //Entity e("Entity1");
    //Entity e2(e);   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file