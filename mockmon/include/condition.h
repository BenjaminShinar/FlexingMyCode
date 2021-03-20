#pragma once

#include <string>
#include <iostream>



namespace mockmon
{
   
    class Condition
    {
        public:
        int HP() const {return m_HP;};
        void ChangeHealth(int amount );
        private:
        int m_HP = 50;
    };

}