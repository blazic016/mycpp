#ifndef _MY_UNIQUE_PTR_
#define _MY_UNIQUE_PTR_

template <typename T>

class MyUniquePtr
{
private:
    T *main_ptr;

public:
    MyUniquePtr(T *ptr = nullptr) : main_ptr(ptr) {}

    MyUniquePtr(MyUniquePtr &&other)
    {
        std::cout << "Move Ctor" << std::endl;
        main_ptr = other.main_ptr;
        other.main_ptr = nullptr;
    }

    ~MyUniquePtr() {}

    MyUniquePtr(const MyUniquePtr &) = delete;
    MyUniquePtr &operator=(const MyUniquePtr &) = delete;

    MyUniquePtr &operator=(MyUniquePtr &&other)
    {
        if (this != &other)
        {
            delete main_ptr;
            main_ptr = other.main_ptr;
            other.main_ptr = nullptr;
        }
        return *this;
    }

    T *get() const
    {
        return main_ptr;
    }

    T &operator*() const
    {
        return *main_ptr;
    }

    T *operator->() const
    {
        return main_ptr;
    }
};

#endif