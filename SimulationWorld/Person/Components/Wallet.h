//
// Created by boeken-work on 9/20/26.
//

#ifndef GAMEENGINE_WALLET_H
#define GAMEENGINE_WALLET_H

namespace SimWorld
{
    class Person;

    ///The class that will track a persons wealth
    class Wallet
    {
    public:
        Wallet(Person* person);
        Wallet(Person* person, int startingBalance);

        bool Withdraw(int amount);
        void Deposit(int amount);
        bool Transfer(Wallet& other, int amount);

        bool CanAfford(int amount) const;

        int GetBalance() const;

    private:
        Person* m_owner;
        int m_balance;
    };
} // SimWorld

#endif //GAMEENGINE_WALLET_H