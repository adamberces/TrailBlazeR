#pragma once

#include <vector>
#include "tile.hpp"

class Map_c
{
    unsigned Width;
    unsigned Height;

    std::vector<Tile_t> Tiles;

    Map_c()
    {
        Tiles =
        {
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }
        };
    }
};