//
// Created by boeken-work on 9/20/26.
//

#include "Wallet.h"

#include <cassert>

namespace SimWorld
{
    Wallet::Wallet(Person* person)
        : m_owner(person)
        , m_balance(0)
    {
    }

    Wallet::Wallet(Person* person, int startingBalance)
        : m_owner(person)
        , m_balance(startingBalance)
    {

    }

    bool Wallet::Withdraw(int amount)
    {
        if (amount <= 0) return false;;

        if (!CanAfford(amount))
        {
            return false;
        }

        m_balance -= amount;
        return true;
    }

    void Wallet::Deposit(int amount)
    {
        if (amount <= 0) return;
        m_balance += amount;
    }

    bool Wallet::Transfer(Wallet& other, int amount)
    {
        if (!Withdraw(amount))
        {
            return false;
        }

        other.Deposit(amount);
        return true;
    }

    bool Wallet::CanAfford(int amount) const
    {
        return amount >= 0 && amount <= m_balance;
    }

    int Wallet::GetBalance() const
    {
        return m_balance;
    }
} // SimWorld