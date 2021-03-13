#pragma once
//#include <string_view>
#include <string>
#include <iostream>

namespace mockmon
{

    struct MockmonExp
    {      
        const long CurrentLevel;
        const long CurrentExperience;

        friend std::ostream& operator<<(std::ostream& os,const MockmonExp& mx);

    };

    class Mockmon
    {   
        /*
        name
        id
        original trainer id

        base type
        current type:
        level:
        exp:


        stats:
        ev
        iv

        moves:
        */
        public:
        explicit Mockmon(bool silent = false):m_name("Nameless"),m_outputEvents(silent){}
        void ChangeName(const std::string & newName); //needs to be somewhere else.
        void GrantExperiencePoints(long points);
        MockmonExp CheckExperiencePoints() const {return MockmonExp{level,experience_points};};\
        long ExpFromDefeating()const;
        void GainExperienceFromVictory(const Mockmon & defeatedMon);
        void LoseSomehow();
        void FullRestore();
        bool IsAbleToBattle() const;
        bool IsWild() const {return false;}
        protected:

        private:
        std::string m_name;
        long level =1;
        long experience_points = 0;
        void LevelUp();
        bool m_outputEvents;
        bool m_ableToBattle;
        const long m_speciesExp = 35;
    };
}
