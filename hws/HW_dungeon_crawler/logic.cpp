#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    
    ifstream file(fileName);
    if (!file.is_open()) {
        return nullptr;
    }

    file >> maxRow >> maxCol;
    file >> player.row >> player.col;

    if (maxRow <= 0 || maxCol <= 0 || player.row < 0 || player.col < 0 || player.row >= maxRow || player.col >= maxCol || maxRow >= INT32_MAX / maxCol || maxCol >= INT32_MAX / maxRow || maxRow >= INT32_MAX || maxCol >= INT32_MAX) {
        return nullptr;
    }
    
    char** dungeonMap = createMap(maxRow, maxCol);
    bool hasExit = false;
    char temp;

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {

            file >> dungeonMap[i][j];

            if (dungeonMap[i][j] != TILE_PILLAR && dungeonMap[i][j] != TILE_MONSTER && dungeonMap[i][j] != TILE_OPEN && dungeonMap[i][j] != TILE_AMULET && dungeonMap[i][j] != TILE_TREASURE && dungeonMap[i][j] != TILE_EXIT && dungeonMap[i][j] != TILE_DOOR) {
                deleteMap(dungeonMap, maxRow);
                return nullptr;
            }

            if (dungeonMap[i][j] == TILE_EXIT || dungeonMap[i][j] == TILE_DOOR) {
                hasExit = true;
            }
    
            if (i == player.row && j == player.col) {
                dungeonMap[i][j] = TILE_PLAYER;
            }
        }
    }

    if (file >> temp || hasExit == false) {
        deleteMap(dungeonMap, maxRow);
        return nullptr;
    }

    return dungeonMap;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    
    if (input == MOVE_LEFT) {
        nextCol -= 1;
    } else if (input == MOVE_RIGHT) {
         nextCol += 1;
    } else if (input == MOVE_DOWN) {
         nextRow += 1;
    } else if (input == MOVE_UP) {
         nextRow -= 1;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    
    char** dungeonMap = new char*[maxRow];

    for (int i = 0; i < maxRow; i++) {
        dungeonMap[i] = new char[maxCol];
        for (int j = 0; j < maxCol; j++) {
            dungeonMap[i][j] = TILE_OPEN;
        }
    }

    return dungeonMap;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    
    if (map != nullptr && maxRow > 0) {
        for (int i = 0; i < maxRow; i++) {
            delete [] map[i];
        }
    }
    delete [] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    
    if (map == nullptr || maxCol < 1 || maxRow < 1 || maxRow >= INT32_MAX / 2 || maxCol >= INT32_MAX / 2) {
        return nullptr;
    }

    char** newDungeon = createMap(2 * maxRow, 2 * maxCol);

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            newDungeon[i][j] = map[i][j];
        }
    }

    for (int i = maxRow; i < maxRow * 2; i++) {
        for (int j = maxCol; j < maxCol * 2; j++) {
            if (map[i - maxRow][j - maxCol] == TILE_PLAYER) {
                newDungeon[i][j] = TILE_OPEN;
            } else {
                newDungeon[i][j] = map[i - maxRow][j - maxCol];
            }
        }
    }
    
    for (int i = 0; i < maxRow; i++) {
        for (int j = maxCol; j < maxCol * 2; j++) {
            if (map[i][j - maxCol] == TILE_PLAYER) {
                newDungeon[i][j] = TILE_OPEN;
            } else {
                newDungeon[i][j] = map[i][j - maxCol];
            }
        }
    }

    for (int i = maxRow; i < maxRow * 2; i++) {
        for (int j = 0; j < maxCol; j++) {
            if (map[i - maxRow][j] == TILE_PLAYER) {
                newDungeon[i][j] = TILE_OPEN;
            } else {
                newDungeon[i][j] = map[i - maxRow][j];
            }
        }
    }

    int temp = maxRow;
    deleteMap(map, temp);

    maxCol *= 2;
    maxRow *= 2;

    return newDungeon;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
        
    if (nextRow >= maxRow || nextRow < 0 || nextCol >= maxCol || nextCol < 0 || map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER) {
        nextRow = player.row;
        nextCol = player.col;
        return STATUS_STAY;
    }

    if (map[nextRow][nextCol] == TILE_TREASURE) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        player.treasure += 1;
        return STATUS_TREASURE;
    }

    if (map[nextRow][nextCol] == TILE_AMULET) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_AMULET;
    }

    if (map[nextRow][nextCol] == TILE_DOOR) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return STATUS_LEAVE;
    }

    if (map[nextRow][nextCol] == TILE_EXIT) {
        if (player.treasure > 0) {
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;
            player.row = nextRow;
            player.col = nextCol;
            return STATUS_ESCAPE;
        } else {
            nextRow = player.row;
            nextCol = player.col;
            return STATUS_STAY;
        }
    }
    
    map[player.row][player.col] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    player.row = nextRow;
    player.col = nextCol;
    return STATUS_MOVE;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    
    bool reachesPlayer = false;
    
    for(int i = player.row - 1; i > -1; i--) {
        if (map[i][player.col] == TILE_PILLAR){
            break;
        }
        if (map[i][player.col] == TILE_MONSTER && map[i + 1][player.col] == TILE_PLAYER) {
            reachesPlayer = true;
            map[i][player.col] = TILE_OPEN;
            map[i + 1][player.col] = TILE_MONSTER;
        } else if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i + 1][player.col] = TILE_MONSTER;
        }
    }

    for (int i = player.row + 1; i < maxRow; i++) {
        if (map[i][player.col] == TILE_PILLAR){
            break;
        }
        if (map[i][player.col] == TILE_MONSTER && map[i - 1][player.col] == TILE_PLAYER){
            reachesPlayer = true;
            map[i][player.col] = TILE_OPEN;
            map[i - 1][player.col] = TILE_MONSTER;
        } else if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i - 1][player.col] = TILE_MONSTER;
        }
    }

    for (int i = player.col - 1; i > -1; i--) {
        if (map[player.row][i] == TILE_PILLAR){
            break;
        }
        if (map[player.row][i] == TILE_MONSTER && map[player.row][i + 1] == TILE_PLAYER) {
            reachesPlayer = true;
            map[player.row][i] = TILE_OPEN;
            map[player.row][i + 1] = TILE_MONSTER;
        } else if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i] = TILE_OPEN;
            map[player.row][i + 1] = TILE_MONSTER;
        }
    }

    for (int i = player.col + 1; i < maxCol; i++) {
        if (map[player.row][i] == TILE_PILLAR){
            break;
        }
        if (map[player.row][i] == TILE_MONSTER && map[player.row][i - 1] == TILE_PLAYER) {
            reachesPlayer = true;
            map[player.row][i] = TILE_OPEN;
            map[player.row][i - 1] = TILE_MONSTER;
        } else if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i] = TILE_OPEN;
            map[player.row][i - 1] = TILE_MONSTER;
        }
    }

    return reachesPlayer;
}