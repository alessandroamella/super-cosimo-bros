#ifndef _MAPS_HPP_
#define _MAPS_HPP_

#include "../room/room.hpp"
#include "../list/list.hpp"
#include "../shared/settings.hpp"
#include "../shared/position.hpp"


class Maps {
protected:
public:
    static Room layout1(GameTimer timer);
    static Room layout2(GameTimer timer);
    static Room layout3(GameTimer timer);
    
    //eccetera per tutte le altre stanze
};


#endif  // _MAPS_HPP_