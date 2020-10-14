#include <iostream>
using namespace std;
const int razm = 10;
class Hash {
public:
    struct hhash
    {
        int key;
        string znach;
        hhash(int key, string znach);
        hhash();
    };
    hhash* tabl[razm];
    Hash();
    void addmemb(hhash* memb);
    void seememb();
    bool deletememb(int key);
    string searchmemb(int key);
    int gethash(int kkey);
    bool chekmemb(int hash);
};

int main()
{
    setlocale(LC_ALL, "Russian");

    Hash obl;
    Hash::hhash mem;
    int key;
    string znach = "", znach1;
    while (true)
    {
        int sup;
        cout << "Введите, что хотите сделать:\n1. Добавить книжку\n2. Посмотреть таблицу\n3. Удалить книжку\n4. Найти книжку\n5. Выйти" << endl;
        cin >> sup;
        switch (sup)
        {
        case 1:
            cout << "Введите номер книжки, ФИО и адрес проживания(в конце адреса поставьте точку)" << endl;
            cin >> key >> znach;
            znach += ' ';
            while (znach[znach.length() - 2] != '.')
            {
                cin >> znach1;
                znach1 += ' ';
                znach += znach1;
            }
            znach[znach.length() - 1] = NULL;
            mem.key = key;
            mem.znach = znach;
            obl.addmemb(&mem);
            cout << "Ваша книжка успешна добавлена\n";
            break;
        case 2:
            cout << "Таблица: " << endl;
            obl.seememb();
            break;
        case 3:
            cout << "Введите номер книжки которую хотите удалить" << endl;
            cin >> key;
            if (obl.deletememb(key))
                cout << "Эта книжка успешна удалена" << endl;
            else
                cout << "Этой книжки не было" << endl;
            break;
        case 4:
            cout << "Введите номер книжки который хотите найти" << endl;
            cin >> key;
            cout << "Вот ФИО и адрес владельца: " << obl.searchmemb(key) << endl;
            break;
        case 5:
            cout << "До свидания!" << endl;
            return 0;
        default:
            cout << "Не верное значение" << endl;
            break;
        }
    }
}

Hash::Hash()
{
    for (int i = 0; i < razm; i++)
    {
        tabl[i] = NULL;
    }
}

void Hash::addmemb(hhash* memb)
{
    int hash = this->gethash((*memb).key);
    int i = 1;
    while(chekmemb(hash))
    {
        hash += i * i;
        i++;
        hash %= razm;
    }
    hhash* member = new hhash((*memb).key, (*memb).znach);
    this->tabl[hash] = member;
}

void Hash::seememb()
{
    for (int i = 0; i < razm; i++)
    {
        if(tabl[i] != NULL)
            cout << i << ' ' << (*tabl[i]).key << ' ' << (*tabl[i]).znach << endl;
    }
}

bool Hash::deletememb(int key)
{
    for (int i = 0; i < razm; i++)
    {
        if (this->tabl[i] != NULL)
        {
            if ((*tabl[i]).key == key)
            {
                tabl[i] = NULL;
                return true;
            }
        }
    }
    return false;
}

string Hash::searchmemb(int key)
{
    for (int i = 0; i < razm; i++)
    {
        if (this->tabl[i] != NULL)
        {
            if (this->tabl[i]->key == key)
                return this->tabl[i]->znach;
        }
    }
    return "Не найдено";
}

int Hash::gethash(int kkey)
{
    return kkey % razm;
}

bool Hash::chekmemb(int hash)
{
    if (tabl[hash] != NULL)
        return true;
    else
        return false;
}

Hash::hhash::hhash(int key, string znach)
{
    this->key = key;
    this->znach = znach;
}

Hash::hhash::hhash()
{
}
