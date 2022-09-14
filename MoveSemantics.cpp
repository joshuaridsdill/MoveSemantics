// MoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define NULL_TERMINATOR 1

/** MUST define to get dub strings printed to the console
*       |
*       |
*       V
* **/
        

//#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG_PRINT(x) std::cout << x << '\n'
#else
#define DEBUG_PRINT(x)
#endif

class String
{
public:
    String() = default;

    String(const char* str)
    {
        m_Size = strlen(str);
        m_Data = new char[m_Size + NULL_TERMINATOR];
        memcpy(m_Data, str, m_Size);
        *(m_Data + m_Size) = '\0';
        DEBUG_PRINT("Created!");
    }

    String(const String& str) noexcept
    {
        m_Size = str.m_Size;
        m_Data = new char[m_Size + NULL_TERMINATOR];
        memcpy(&m_Data, &str.m_Data, m_Size + NULL_TERMINATOR);
        DEBUG_PRINT("Copied!");
    }

    String(String&& str) noexcept
    {
        m_Size = str.m_Size;
        m_Data = str.m_Data;

        str.m_Data = nullptr;
        str.m_Size = 0;

        DEBUG_PRINT("Moved!");
    }

    ~String()
    {
        DEBUG_PRINT("Destroyed!");
    }

    String& operator=(const String& str)
    {
        if (this != &str)
        {
            delete[] m_Data;

            m_Size = str.m_Size;
            m_Data = new char[m_Size + NULL_TERMINATOR];
            memcpy(m_Data, str.m_Data, m_Size + NULL_TERMINATOR);
        }
        return *this;
    }

    String& operator=(String&& str) noexcept
    {
        if (this != &str)
        {
            delete[] m_Data;

            m_Data = str.m_Data;
            m_Size = str.m_Size;

            str.m_Data = nullptr;
            str.m_Size = 0;
        }

        return *this;
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

    inline size_t Size()
    {
        return m_Size;
    }

private:
    char* m_Data;
    size_t m_Size;
};

class Entity
{
public:

    Entity(String& name) noexcept
        :
        m_Name(name)
    {
        DEBUG_PRINT("Created!");
    }

    Entity(String&& name) noexcept
        :
        m_Name(std::move(name))
    {
        DEBUG_PRINT("Created!");
    }

    Entity(Entity& e) noexcept
        :
        m_Name(e.m_Name)
    {
        DEBUG_PRINT("Copied!");
    }

    Entity(Entity&& e) noexcept
        :
        m_Name(std::move(e.m_Name))
    {
        DEBUG_PRINT("Moved!");
    }

    ~Entity()
    {
        DEBUG_PRINT("Destroyed!");
    }

private:
    String m_Name;
};



std::ostream& operator<<(std::ostream& os, String& str)
{
    os << str.m_Data;

    return os;
}

int main()
{

    //Creating
    String str("Hello, World!");
    String str2("Goodbye, World!");

    //Copy
    str = str2;

    std::cout << str << '\n';
    str.Print();
    std::cout << str.Size() << '\n';

    //Copy
    Entity e(str);

    //Copy
    Entity e2(e);

    //Moved
    Entity e3("MoveSemantics");

    //Moved
    Entity e4(std::move(e2));
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