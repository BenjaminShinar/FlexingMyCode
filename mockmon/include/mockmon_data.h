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
        explicit Mockmon():m_name("Nameless"){}
        void ChangeName(const std::string & newName); //needs to be somewhere else.
        void GrantExperiencePoints(long points);
        MockmonExp CheckExperiencePoints() const {return MockmonExp{level,experience_points};};
        protected:

        private:
        std::string m_name;
        long level =1;
        long experience_points = 0;
        void LevelUp();
    };
}
