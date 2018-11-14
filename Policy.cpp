////////////////////////////////////////////////////////////////////////////////////////////
// Strategy (Policy-based)
class Woman
{
public:
    const static int power = 6;
    const static int speed = 12;
};

class Man
{
public:
    const static int power = 10;
    const static int speed = 8;
};

class Weapon
{
protected:
    virtual int Damage() const = 0;
    virtual int Speed() const = 0;
};

template<typename T>
class Sword : public Weapon
{
protected:
    virtual int Damage() const
    {
        return T::power * 3;
    }

    virtual int Speed() const
    {
        return T::speed * 5;
    }
};

template<typename T>
class Axe
{
protected:
    virtual int Damage() const
    {
        return T::power * 6;
    }

    virtual int Speed() const
    {
        return T::speed * 1;
    }
};

template<
    typename Gender,
    template<typename> typename Equip >
class Character : public Equip<Gender>
{
public:
    void Attack()
    {
        std::cout << "Damage : " << Equip<Gender>::Damage() * Equip<Gender>::Speed() << std::endl;
    }
};

typedef Character<Man, Sword> SwordMan;
typedef Character<Woman, Sword> SwordWoman;
typedef Character<Man, Axe> AxeMan;

int main() {
    SwordMan sm;
    sm.Attack();

    SwordWoman sw;
    sw.Attack();

    AxeMan am;
    am.Attack();

    return 0;
}
