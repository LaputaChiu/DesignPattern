////////////////////////////////////////////////////////////////////////////////////////////
// Generic Singleton Class
class NonCopyable
{
protected:
    NonCopyable() {}
    virtual ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable &rhv);
    const NonCopyable &operator = (const NonCopyable &rhv);
};

// http://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton
template<typename TBase, typename TDerived = TBase>
class Singleton : private NonCopyable
{
public:
    static TBase * GetInstance()
    {
        static TDerived instance;
        return &instance;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}
};

////////////////////////////////////////////////////////////////////////////////////////////
// Singleton of derived class
class Car
{
public:
    virtual void Drive() const = 0;

protected:
    Car() {}
    virtual ~Car() {}
};

class Ford : public Car, public Singleton<Car, Ford>
{
    friend class Singleton<Car, Ford>;

public:
    virtual void Drive() const
    {
        std::cout << "FORD" << std::endl;
    }

private:
    Ford() {}
    virtual ~Ford() {}
};

////////////////////////////////////////////////////////////////////////////////////////////
// Singleton of common class
class Dummy : public Singleton<Dummy>
{
    friend class Singleton<Dummy>;

public:
    void Print()
    {
        std::cout << "Dummy" << std::endl;
    }

private:
    Dummy() {}
    ~Dummy() {}
};

int main() {
    Ford::GetInstance()->Drive();
    Dummy::GetInstance()->Print();
    return 0;
}
