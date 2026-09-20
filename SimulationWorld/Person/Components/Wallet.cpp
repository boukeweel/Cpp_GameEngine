//
// Created by boeken-work on 9/20/26.
//

#include "Wallet.h"

#include <cassert>

namespace SimWorld
{
    Wallet::Wallet(Person& person)
        : m_owner(person)
        , m_balance(0)
    {
    }

    Wallet::Wallet(Person& person, int startingBalance)
        : m_owner(person)
        , m_balance(startingBalance)
    {
        assert(startingBalance >= 0 && "Wallet cannot start with a negative balance");
    }

    bool Wallet::Withdraw(int amount)
    {
        assert(amount >= 0 && "Cannot withdraw a negative amount");

        if (!CanAfford(amount))
        {
            return false;
        }

        m_balance -= amount;
        return true;
    }

    void Wallet::Deposit(int amount)
    {
        assert(amount >= 0 && "Cannot deposit a negative amount");
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

    Person& Wallet::GetOwner() const
    {
        return m_owner;
    }
} // SimWorld