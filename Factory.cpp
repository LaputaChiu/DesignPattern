////////////////////////////////////////////////////////////////////////////////////////////
// Animal Factory with parameters
class Animal
{
public:
    Animal(const std::string& _name) { name = _name; }
    virtual ~Animal() {}
    virtual int Leg() const = 0;
    virtual void Speak() const = 0;
    void Name() const { std::cout << name << std::endl; }

private:
    std::string name;
};

class Dog : public Animal
{
public:
    Dog(const std::string& _name) :Animal(_name) {}
    virtual ~Dog() {}

    int Leg() const
    {
        return 4;
    }

    void Speak() const
    {
        std::cout << "Woof" << std::endl;
    }
};

class People : public Animal
{
public:
    People(const std::string& _name) :Animal(_name) {}
    virtual ~People() {}

    int Leg() const
    {
        return 2;
    }

    void Speak() const
    {
        std::cout << "Hi" << std::endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////
// Generic Factory Class (Params could be either set or not)
template<typename TBase, typename... Params>
class Factory : public Singleton<Factory<TBase, Params...>>
{
    friend class Singleton<Factory<TBase, Params...>>;

public:

    template<typename TDerived, typename = typename std::enable_if<std::is_base_of<TBase, TDerived>::value>::type>
    auto Create(Params&&... params)
    {
        //std::cout << typeid(*this).name() << std::endl;
        return std::make_shared<TDerived>(std::forward<Params>(params)...);
    }

private:
    Factory() {}
    ~Factory() {}
};

// Here shows how to define outside
//template<typename TBase, typename... Params>
//Factory<TBase, Params...>* Factory<TBase, Params...>::GetInstance()
//{
//    static Factory<TBase, Params...> factory;
//    return &factory;
//}

int main() {

    auto animal = Factory<Animal, std::string>::GetInstance()->Create<Dog>("Lucky");
    animal->Speak();
    animal->Name();

    auto animal2 = Factory<Animal, std::string>::GetInstance()->Create<People>("Gavin");
    animal2->Speak();
    animal2->Name();

    return 0;
}
