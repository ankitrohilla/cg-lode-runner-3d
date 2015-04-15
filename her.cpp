#include <GL/glut.h>
#include<GL/freeglut.h>
#include "SOIL.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <list>
#include <vector>
#include <map>
#include <pthread.h>
#include <unistd.h>

#define FPS 100
#define DUG_TIMER 200
#define MAX_LIVES 3

void meRespawn();
bool meDead;

bool gameLost, gameWon;

int lostTexture, wonTexture;
int grass1, grass2, grass3;
int wall1, wall2, wall3;
int road1, road2, road3;
int ladder1, ladder2;
int destination1, destiantion2;
int botSpawn1, botSpawn2;
int heroSpawn1, heroSpawn2;
int walkOverBot1, walkOverBot2;

int coin1, coin2;

int currentLives = MAX_LIVES;

bool meMoving, meFallingDown;
bool _meMovingLeft, _meMovingRight, _meMovingUp, _meMovingDown;

// for 10 rounds, xyz coordinate where player has to go to win
int playerDestination[10][3];

int currentRound = 0;

int currentCoin;
int coinCount[10];

float eyeX = 65.0, eyeY = 15.0, eyeZ = 65.0, playerX = 49.0, playerY = 10.0, playerZ = 49.0;
int meDestY;

int getPlayerId( int x, int y, int z){ return 50*50*y + 50*z + x; }
int getPlayerX( int id){ return id%50; }
int getPlayerZ( int id){ return (id/50)%50; }

GLfloat spotDirection[3];
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };

enum axis { X, Y, Z };
enum side { LEFT, RIGHT, UP, DOWN }playerLadderSide;

void gameHandler(int i);
void blockWall( int x, int y, int z, int wallTexture, int floorTexture, side whichSide, bool isCoin );

class tile;
class bot;
// 10 rounds with yzx
tile *map[10][10][50][50];

// [y][x][z] specifies X, Z and Y values
class tile
{
    public:

        // [10] for each bot
        long id, parentId[10];
        bool isDug;
        bool isCoin;
        bool coinTaken;

        int x, y, z;

        // used to fade in and fade out the block when dug
        float alpha1 = 1.0;

        //used to fade in when bot falls in the dig
        float alpha2 = 0.0;

        // to show flicker effect
        bool goingUp = true;

        int isDugTimer = 100;

        bool isDiggable = true;
        bool isSpawnPoint = false;
        bool isReachable = true;
        bool isPlayerDestination = false;

        bool ladderPresent = false;
        // ladder at tile xyz means to come from x(y-1)z to x(y)z
        side whichSide;

        int floorTexture, wallTexture;

        std::vector<long> adjacencyList;

        // assuming that the order of tile creation will be from [y][0][0] to y[0+][0+]
        // last argument is -1 if there is no ladder
        tile( int y, int z, int x, int floorTexture, int wallTexture, side whichSide, bool isCoin)
        {
            this->x = x;
            this->z = z;
            this->y = y;

            this->floorTexture = floorTexture;
            this->wallTexture = wallTexture;

            this->isCoin = isCoin;
            this->isReachable = true;

            if( y == 1 ) isDiggable = false;

            this->isDug = false;
            this->id = 50*50*y + 50*z + x;

            if( whichSide != -1 )
            {
                this->ladderPresent = true;
                this->whichSide = whichSide;
            }

            if( z!=0     && map[currentRound][y][z-1][x] )
            {
                adjacencyList.push_back(id-50);
                map[currentRound][y][z-1][x]->adjacencyList.push_back(id);
            }
            if( z!=49    && map[currentRound][y][z+1][x] )
            {
                adjacencyList.push_back(id+50);
                map[currentRound][y][z+1][x]->adjacencyList.push_back(id);
            }
            if( x!=0     && map[currentRound][y][z][x-1] )
            {
                adjacencyList.push_back(id- 1);
                map[currentRound][y][z][x-1]->adjacencyList.push_back(id);
            }
            if( x!=49    && map[currentRound][y][z][x+1] )
            {
                adjacencyList.push_back(id+ 1);
                map[currentRound][y][z][x+1]->adjacencyList.push_back(id);
            }

//            std::cout << "adj list for id x y z " << id << " " << x << " "<< y << " "<< z;
            for( int i = 0; i < adjacencyList.size(); i++)
//                 std::cout << adjacencyList.at(i) << " ";
//            std::cout << "\n\n";
            fflush(stdout);
        }

        static int getX( int id)
        {
            return id%50;
        }
        static int getZ( int id)
        {
            return (id/50)%50;
        }

};

class bot
{
    public:

    int tilesToMove;

    int tileId;
    int botId;

    // for renderng the witch
    int bodyX = 0, bodyY= 0 ,bodyZ =0 , shoulderLeftX = 0 , shoulderLeftY = 0 , shoulderLeftZ = 0 , shoulderRightX = 0, shoulderRightY = 0 , shoulderRightZ = 0 ,elbowLeftX = 0 , elbowLeftY = 0 , elbowLeftZ = 0 , elbowRightX = 0 ,elbowRightY = 0 ,elbowRightZ = 0 , thighsLeftX = 0 , thighsLeftY = 0 , thighsLeftZ = 0 , thighsRightX = 0 ,thighsRightY = 0 , thighsRightZ = 0 , legLeftX = 0 , legLeftY = 0 , legLeftZ = 0 , legRightX = 0 , legRightY = 0 , legRightZ = 0 ;
    bool thighsGoingUp = true;
    bool elbowGoingUp = true;
    bool rightLegGoingAhead = true;
    float r1; float g1; float b1; float r2; float g2; float b2; float r3; float g3; float b3;

    int stepsMoved = 0;

    bool _movingRight, _movingLeft, _movingUp, _movingDown;
    bool botFallingDown = false;
    bool botDead;

    // where the bot will fall
    int destY;
    int spawnX, spawnY, spawnZ;
    float x, y, z;
    bool moving;
    std::vector<int> path;

    bot(){}

    // botId is used to access particular parent Id of the common map
    // creating different maps for different bots will be too time consuming and complex
    bot( int x, int y, int z, int botId, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3 )
    {
        this->r1 = r1;
        this->r2 = r2;
        this->r3 = r3;
        this->g1 = g1;
        this->g2 = g2;
        this->g3 = g3;
        this->b1 = b1;
        this->b2 = b2;
        this->b3 = b3;

        this->botId = botId;

        this->spawnX = (int)x;
        this->spawnY = (int)y;
        this->spawnZ = (int)z;
        this->x = (int)x;
        this->y = (int)y;
        this->z = (int)z;

        // make the spawn points undiggable
        map[currentRound][spawnY][spawnZ][spawnX]->isSpawnPoint = true;
        map[currentRound][spawnY][spawnZ][spawnX]->isDiggable = false;
    }

    int getId()
    {
        return 50*50*y + 50*z + x;
    }

    void movingLeft(int i);
    void movingRight(int i);
    void movingDown(int i);
    void movingUp(int i);

    void showWitch();
    void respawn();
    void BFS();
    void pathFinder();
    void moveSingleStep();
    void botHandler();
    void botFallHandler();

    void display()
    {
        glutSolidSphere( 0.5, 40, 40);
    }

};
std::vector<bot> bots;

#include "mapsetter.h"
#include "modelling.h"

// returns true if there is a bot between position x(y)z and x(y-1)z
bool allBotCheck( int x, int y, int z, int botId)
{
    for( int i = 0; i < bots.size(); i++ )
    {
        if( bots.at(i).x == x && y - bots.at(i).y <= 1.2 && bots.at(i).z == z && i != botId )
            return true;
    }
    return false;
}

void bot::BFS()
{
    // any node that is not reachable will have parentId[botId] of -2
    for( int i = 0; i < 50; i++ )
    {
        for( int j = 0; j < 50; j++ )
            if( map[currentRound][(int)y][i][j] )
                map[currentRound][(int)y][i][j]->parentId[botId] = -2;   // which version of map[currentRound] will be used depends upon (int)y
    }

    std::list<int> bfsQueue;
    std::map<int,bool> visitedSet;

    x = floor( x + 0.5 );
    y = floor( y + 0.5 );
    z = floor( z + 0.5 );

    int sourceId  = map[currentRound][(int)y][(int)z][(int)x]->id;
    int sourceX = x;
    int sourceZ = z;

    bfsQueue.clear();
    visitedSet.clear();
    path.clear();
    path.resize( 0, 0);

    bfsQueue.push_back( sourceId );
    visitedSet[ sourceId ] = true;
    map[currentRound][(int)y][sourceZ][sourceX]->parentId[botId] = -1;

    int neighbourId, neighbourX, neighbourZ;

    int currentId = sourceId;
    int currentX  = sourceX;
    int currentZ  = sourceZ;

//    std::cout << "current idxz are - " << currentId << " " << currentX << " " << currentZ << "\n";

    while(bfsQueue.size() != 0)
    {
        currentId = bfsQueue.front();

        currentX = tile::getX( currentId );
        currentZ = tile::getZ( currentId );

//        std::cout << " x and z from currnt id - " << currentX << " " << currentZ << " " << currentId << "\n";

        visitedSet[ currentId ] = true;
        bfsQueue.pop_front();

//        std::cout << "checking adj list size";fflush(stdout);
//        std::cout << y << " " << currentZ << " " << currentX;fflush(stdout);
        for( int i = 0; i < map[currentRound][(int)y][currentZ][currentX]->adjacencyList.size(); i++ )
        {//std::cout << "ad jlist elem - " << map[currentRound][(int)y][currentZ][currentX]->adjacencyList.at(i) <<"\n";

            neighbourId = map[currentRound][(int)y][currentZ][currentX]->adjacencyList.at(i);
            neighbourX = tile::getX( neighbourId );
            neighbourZ = tile::getZ( neighbourId );

            if( !visitedSet[neighbourId] )
            {
                map[currentRound][(int)y][neighbourZ][neighbourX]->parentId[botId] = currentId;
                bfsQueue.push_back(neighbourId);

                visitedSet[neighbourId] = true;
            }
        }
//        std::cout << "\n\n\n";
    }

    tilesToMove = 0;

    // check if the player is reachable or not
    if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->parentId[botId] != -2 )
    {
        pathFinder();
        tilesToMove = path.size();
    }
}

void bot::pathFinder()
{
    int currentId = map[currentRound][(int)y][(int)playerZ][(int)playerX]->id;

//    std::cout << "Player id " << currentId << "\n";

    int toX = playerX;
    int toZ = playerZ;

    int currentX = toX;
    int currentZ = toZ;

    int fromX = x;
    int fromZ = z;

    fflush(stdout);

    while(( currentX != fromX || currentZ != fromZ ))
    {
//        std::cout << currentX << " " << fromX << "\n";
        path.push_back(currentId);

        currentId = map[currentRound][(int)y][currentZ][currentX]->parentId[botId];
        currentX = tile::getX( currentId );
        currentZ = tile::getZ( currentId );
    }

    // reverse the path
    for( int i = 0; i < path.size()/2; i++)
    {
        int temp =  path.at(i);
        path.at(i) = path.at(path.size()-i-1);
        path.at(path.size()-i-1) = temp;
    }

    for( int i = 0; i < path.size(); i++)
    {
//        std::cout << "PATH - " << path.at(i) << " ";
    }

}

void bot::moveSingleStep()
{
    if( path.size() < 1 )
        return;

    if( fabs(x - playerX) < 1.0 && fabs(y - playerY) < 0.1 && fabs(z - playerZ) < 1.0 )
    {
        std::cout << "bot killed me";
        currentLives--;
        meDead = true;
        meRespawn();
    }

    moving = true;

    // positive X
    if( getId() - path.at(0) == -1 || _movingRight ) { x += 0.05; _movingRight = true; }

    // negative X
    if( getId() - path.at(0) ==  1 || _movingLeft ) { x -= 0.05; _movingLeft = true; }

    // positive Z
    if( getId() - path.at(0) == -50 || _movingDown ) { z += 0.05; _movingDown = true; }

    // negative Z
    if( getId() - path.at(0) ==  50 || _movingUp ) { z -= 0.05; _movingUp = true; }

    stepsMoved++;
}

void bot::botHandler()
{
    if( botDead ) { botDead = false; return; }

    // round off the values to nearest integer
    if( !(stepsMoved % 20) )
    {
        x = floor( 0.5+x );
        y = floor( 0.5+y );
        z = floor( 0.5+z );

        moving = false;
        _movingRight = false;
        _movingLeft = false;
        _movingUp = false;
        _movingDown = false;

        if( map[currentRound][(int)y][(int)z][(int)x]->isDug && !allBotCheck((int)x, (int)y, (int)z, botId) )
        {
            destY = 0;
            botFallingDown = true;
            for( int j = y-1; j > -1; j-- )
            {
                // if their is a tile at level i, fall down
                if( map[currentRound][j][(int)z][(int)x] )
                {
                    destY = j;
                    break;
                }
            }
            return;
        }

        // update path of bots
        BFS();

    }
    moveSingleStep();
//        std::cout << "Bot steps moved - " << stepsMoved << "\n";

}

void bot::botFallHandler()
{
    if( y >= destY )
        y -= 0.1;
    else
    {
        botFallingDown = false;
        y = destY;
    }
    if( y == 0 )
    {
        botDead = true;
        respawn();
    }
}

void bot::respawn()
{
    x = spawnX;
    y = spawnY;
    z = spawnZ;
}


void meRespawn()
{
    if( currentLives > 0 )
    {
        playerX = 49;
        playerY = 2;
        playerZ = 49;
        eyeX = 70;
        eyeY = 20;
        eyeZ = 70;

        // each bot will start from its original position
        for( int i = 0; i < bots.size(); i++ )
        {
            bots.at(i).botDead = true;
            bots.at(i).respawn();
        }
    }
    else
        gameLost = true;
}

void meFallHandler()
{
    meMoving = true;
    if( playerY >= meDestY )
        playerY -= 0.1;
    else
    {
        meMoving = false;
        meFallingDown = false;
        playerY = meDestY;
        meDestY = 0;
    }

    if( playerY == 0 )
    {
        std::cout << "i fell down and died";
        currentLives--;
        meDead = true;
        meRespawn();
    }
}

// xyz is no longer reachable
void adjustNeighboursDel(int x, int y, int z)
{
    int id = map[currentRound][y][z][x]->id;
    if( z != 0  && map[currentRound][y][z-1][x] )
    {
        for( int i = 0; i < map[currentRound][y][z-1][x]->adjacencyList.size(); i++ )
        {
            if( map[currentRound][y][z-1][x]->adjacencyList.at(i) == id )
            {
                map[currentRound][y][z-1][x]->adjacencyList.erase( map[currentRound][y][z-1][x]->adjacencyList.begin()+i );
                break;
            }
        }
    }
    if( z != 49 && map[currentRound][y][z+1][x] )
    {
        for( int i = 0; i < map[currentRound][y][z+1][x]->adjacencyList.size(); i++ )
        {
            if( map[currentRound][y][z+1][x]->adjacencyList.at(i) == id )
            {
                map[currentRound][y][z+1][x]->adjacencyList.erase( map[currentRound][y][z+1][x]->adjacencyList.begin()+i );
                break;
            }
        }
    }
    if( x != 0  && map[currentRound][y][z][x-1] )
    {
        for( int i = 0; i < map[currentRound][y][z][x-1]->adjacencyList.size(); i++ )
        {
            if( map[currentRound][y][z][x-1]->adjacencyList.at(i) == id )
            {
                map[currentRound][y][z][x-1]->adjacencyList.erase( map[currentRound][y][z][x-1]->adjacencyList.begin()+i );
                break;
            }
        }
    }
    if( x != 49 && map[currentRound][y][z][x+1] )
    {
        for( int i = 0; i < map[currentRound][y][z][x+1]->adjacencyList.size(); i++ )
        {
            if( map[currentRound][y][z][x+1]->adjacencyList.at(i) == id )
            {
                map[currentRound][y][z][x+1]->adjacencyList.erase( map[currentRound][y][z][x+1]->adjacencyList.begin()+i );
                break;
            }
        }
    }

    // entry exists but I cannot move to xyz because there is a wall
    map[currentRound][y][z][x]->isReachable = false;

    // now check if I was present here, make me respawn
    if( fabs(playerX-x) <= 0.4 && fabs(playerY-y) <= 0.4 && fabs(playerZ-z) <= 0.4 )
    {
        std::cout << " a wall killed me";
        currentLives--;
        meDead = true;
        meRespawn();
    }

    // now check if any bot or hero was present here, make it respawn
    for( int i = 0; i < bots.size(); i++)
    {
        if( fabs(bots.at(i).x-x) <= 0.4 && fabs(bots.at(i).y-y) <= 0.4 && fabs(bots.at(i).z-z) <= 0.4 )
        {
            bots.at(i).botDead = true;
            bots.at(i).respawn();
        }
    }
}

// needed to add xyz to neighbours adjacency list when xyz is dug
void adjustNeighboursAdd(int x, int y, int z)
{
    int id = map[currentRound][y][z][x]->id;

    if( z != 0  && map[currentRound][y][z-1][x] && map[currentRound][y][z-1][x]->isReachable )
        map[currentRound][y][z-1][x]->adjacencyList.push_back(id);
    if( z !=49  && map[currentRound][y][z+1][x] && map[currentRound][y][z+1][x]->isReachable )
        map[currentRound][y][z+1][x]->adjacencyList.push_back(id);
    if( x != 0  && map[currentRound][y][z][x-1] && map[currentRound][y][z][x-1]->isReachable )
        map[currentRound][y][z][x-1]->adjacencyList.push_back(id);
    if( x !=49  && map[currentRound][y][z][x+1] && map[currentRound][y][z][x+1]->isReachable )
        map[currentRound][y][z][x+1]->adjacencyList.push_back(id);

    map[currentRound][y][z][x]->isReachable = true;
}

void gameHandler(int i)
{
//    std::cout << "\ncurrent coin and max coin - " << currentCoin << " " << coinCount[currentRound];
    for( int k = 0; k < bots.size(); k++ )
    {
        // if bot is at another level, leave the bot inactive
        if( bots.at(k).y == playerY && !bots.at(k).botFallingDown )
            bots.at(k).botHandler();
        else if( bots.at(k).botFallingDown )
            bots.at(k).botFallHandler();
        else
            bots.at(k).moving = false;
    }

    if( meFallingDown )
        meFallHandler();

    if( fabs(playerX-playerDestination[currentRound][0]) < 0.2 &&
        fabs(playerY-playerDestination[currentRound][1]) < 0.2 &&
        fabs(playerZ-playerDestination[currentRound][2]) < 0.2 &&
        currentCoin == coinCount[currentRound]                 &&
        !meMoving )
    {
        currentRound++;
        playerY = 10;

        // game over
        if( currentRound == 3 )
        {
            gameWon = true;
            currentRound--;
            return;
        }
        setUpMap(currentRound);
        return;
    }

    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 50; j++ )
        {
            for( int k = 0; k < 50; k++ )
            {
                if( map[currentRound][i][j][k] )
                {
                    if( map[currentRound][i][j][k]->isDug )
                    {
                        map[currentRound][i][j][k]->isDugTimer--;
                        if( map[currentRound][i][j][k]->isDugTimer <= 0 )
                        {
                            map[currentRound][i][j][k]->isDug = false;

                            // if x(y)z is dug and its timer is over,
                            // adjust the neighbours of the tile on level below
                            if( map[currentRound][i-1][j][k] )
                                adjustNeighboursDel(k,i-1,j);
                        }
                    }
                }
           }
       }
    }


    glutPostRedisplay();
    glutTimerFunc( 5, gameHandler, 10);
}

void showBots()
{
    for( int i = 0; i < bots.size(); i++)
    {
        glPushMatrix();
        glTranslatef( bots.at(i).x+0.5, 2*bots.at(i).y+0.5, bots.at(i).z+0.5);
        bots.at(i).showWitch();
        glPopMatrix();
    }
}

int applyTexture( char* file)
{
    return SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        file,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_COMPRESS_TO_DXT
    );
}

// in XZ plane
void draw_rect_with_tex( float l, float r, float b, float t, int texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( l, b, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( r, b, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( r, t, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( l, t, 0);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void draw_floor_with_tex( float x, float z, float h, int texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f( x, h, z);
        glTexCoord2f(1, 0);
        glVertex3f( x+1, h, z);
        glTexCoord2f(1, 1);
        glVertex3f( x+1, h, z+1);
        glTexCoord2f(0, 1);
        glVertex3f( x, h, z+1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void draw_wall_with_tex( float x, float z, axis whichAxis, float h, int texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    if( whichAxis == X )
    {
        glTexCoord2f(0, 0);
        glVertex3f( x, h, z);
        glTexCoord2f(1, 0);
        glVertex3f( x+1, h,  z);
        glTexCoord2f(1, 1);
        glVertex3f( x+1, h+2, z);
        glTexCoord2f(0, 1);
        glVertex3f( x, h+2, z);
    }
    else
    {
        glTexCoord2f(0, 0);
        glVertex3f( x, h, z);
        glTexCoord2f(1, 0);
        glVertex3f( x, h, z+1);
        glTexCoord2f(1, 1);
        glVertex3f( x, h+2, z+1);
        glTexCoord2f(0, 1);
        glVertex3f( x, h+2, z);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
}


// creates y,z,x - 2X1X1 block on y,z,x provided
// adjusts adjacency list of addjacent tiles and
// creates a new tile at y+1,z,x
// last argument is -1 if there is no ladder
void blockWall( int x, int y, int z, int wallTexture, int floorTexture, side whichSide, bool isCoin )
{
    map[currentRound][y+1][z][x] = new tile(y+1, z, x,floorTexture, wallTexture, whichSide, isCoin);

    int id;
    if( map[currentRound][y][z][x] )
        id = map[currentRound][y][z][x]->id;
    else
        return;

//    std::cout << "node id " <<id << "\n\n";fflush(stdout);

    // remove this entry from all possible adjacent nodes at the same level
    adjustNeighboursDel(x,y,z);

}

// to go from x(y-1)z to x(y)z
void ladder( int x, int y, int z, side whichSide, int texture)
{
    // ladder on the right/down side of the tile
    switch (whichSide)
    {
        case RIGHT:
            draw_wall_with_tex(x+1.1, z, Z, y-2, texture);
            break;

        case DOWN:
            draw_wall_with_tex(x, z+1.1, X, y-2, texture);
            break;

        default:
            break;
    }
}

void init(void)
{

    lostTexture = applyTexture("thumbsDown.png");
    wonTexture  = applyTexture("thumbsUp.png");

    ladder1 = applyTexture("ladder1.png");
    ladder2 = applyTexture("ladder2.png");

    grass1 = applyTexture("grass1.jpg");
    grass2 = applyTexture("grass2.jpg");
    grass3 = applyTexture("grass3.jpg");

    road1 = applyTexture("road1.jpg");
    road2 = applyTexture("road2.jpg");
    road3 = applyTexture("road3.jpg");

    wall1 = applyTexture("wall1.jpg");
    wall2 = applyTexture("wall2.jpg");
    wall3 = applyTexture("wall3.jpg");

    coin1 = applyTexture("coin1.png");

    botSpawn1 = applyTexture("botSpawn1.png");
    heroSpawn1 = applyTexture("heroSpawn1.png");
    destination1 = applyTexture("destination1.png");

    walkOverBot1 = applyTexture("walkOverBot1.png");

    // Design map

    setUpMap(currentRound);

    glEnable (GL_LIGHT0);

    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

//    std::cout << "Bots bfs started"; fflush(stdout);
    for( int i = 0; i < bots.size(); i++ )
    {
        if( bots.at(i).y == playerY )
            bots.at(i).BFS();
    }
//    std::cout << "Bots bfs ended"; fflush(stdout);

    glLineWidth( 60 );
    glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //    glutTimerFunc( 5, animate, 5);

}

void display(void)
{
//    std::cout << "XYZ" << playerX << " " << playerY << " " << playerZ << "\n";

    // rotation of spawns and destination
    static int r = 0;
    r = (r+20)%1440;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );

    if( gameWon || gameLost )
        goto AFTER_TEXT;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, w, 0, h, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glColor3f( 1.0f, 1.0f, 1.0f );

    char cC[2], mC[2], lC[2], rC[2];

    sprintf( cC, "%d", currentCoin);
    sprintf( mC, "%d", coinCount[currentRound]);
    sprintf( lC, "%d", currentLives);
    sprintf( rC, "%d", currentRound+1);

    glDisable(GL_LIGHTING);
    glRasterPos2i( w/50, h-h/20 );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"COINS - " );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)cC );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)" / " );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)mC );

    if( currentCoin == coinCount[currentRound] )
        glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)" You can now go to destination" );

    glRasterPos2i( w/50, h-h/10 );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"LIVES - " );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)lC );

    glRasterPos2i( w/50, h-h/10-h/20 );

    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"LEVEL - " );
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)rC );


    AFTER_TEXT:

    glEnable(GL_LIGHTING);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-8.0, 8.0, -4.5, 4.5, 10.0, 200.0);
    glMatrixMode (GL_MODELVIEW);


    glLoadIdentity ();



    if( gameLost || gameWon )
        gluLookAt ( 0, 0, 15, 0, 0, 0, 0, 1, 0);
    else
        gluLookAt (eyeX-5, eyeY-5, eyeZ-5, playerX, playerY, playerZ, 0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);

    showBots();

    glPushMatrix();
    glTranslatef( 0.5+playerX, 0.5+2*playerY, 0.5+playerZ);
    showHero();
    glPopMatrix();

    // check for 10X50X50 tiles and show coins
    for( int i = 0; i < 10; i++ )
    {
        for( int j = 0; j < 50; j++ )
        {
            for( int k = 0; k < 50; k++ )
            {
                if( map[currentRound][i][j][k] )
                {
                    if( map[currentRound][i][j][k]->isDug && map[currentRound][i][j][k]->alpha1 > 0.1 )
                    {
                        map[currentRound][i][j][k]->alpha1-=0.05;
                    }
                    else if( map[currentRound][i][j][k]->alpha1 < 1 )
                        map[currentRound][i][j][k]->alpha1+=0.05;

                    glColor4f( 1, 1, 1, map[currentRound][i][j][k]->alpha1);
                    draw_wall_with_tex ( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z, X, 2*i-2, map[currentRound][i][j][k]->wallTexture);
                    draw_wall_with_tex ( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z, Z, 2*i-2, map[currentRound][i][j][k]->wallTexture);
                    draw_wall_with_tex ( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z+1, X, 2*i-2, map[currentRound][i][j][k]->wallTexture);
                    draw_wall_with_tex ( map[currentRound][i][j][k]->x+1, map[currentRound][i][j][k]->z, Z, 2*i-2, map[currentRound][i][j][k]->wallTexture);
                    draw_floor_with_tex( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z, 2*i, map[currentRound][i][j][k]->floorTexture);

                    if( map[currentRound][i][j][k]->isDug && allBotCheck((int)k, (int)i, (int)j, -1) )
                    {
                        if(  map[currentRound][i][j][k]->goingUp ) map[currentRound][i][j][k]->alpha2+=0.01;
                        if( !map[currentRound][i][j][k]->goingUp ) map[currentRound][i][j][k]->alpha2-=0.01;
                        if( map[currentRound][i][j][k]->alpha2 <= 0.0 ) map[currentRound][i][j][k]->goingUp = true;
                        if( map[currentRound][i][j][k]->alpha2 >= 1.0 ) map[currentRound][i][j][k]->goingUp = false;
                        glColor4f( 1, 1, 1, map[currentRound][i][j][k]->alpha2);
                        draw_floor_with_tex( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z, 2*i+0.01, walkOverBot1);
                    }
                    else if( map[currentRound][i][j][k]->alpha2 > 0.0 )
                    {
                        glColor4f( 1, 1, 1, map[currentRound][i][j][k]->alpha2);
                        map[currentRound][i][j][k]->alpha2-=0.05;
                        draw_floor_with_tex( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z, 2*i+0.01, walkOverBot1);
                    }

                    glColor4f(1,1,1,1);

                    if( map[currentRound][i][j][k]->ladderPresent )
                    {
                        ladder( map[currentRound][i][j][k]->x, 2*i, map[currentRound][i][j][k]->z, map[currentRound][i][j][k]->whichSide, ladder2);
                    }
                    if( map[currentRound][i][j][k]->isCoin && !map[currentRound][i][j][k]->coinTaken )
                    {
                        glPushMatrix();

                        glTranslatef(+map[currentRound][i][j][k]->x+0.5,+2*i,+map[currentRound][i][j][k]->z+0.5 );
                        glRotatef(r/4, 0, 1, 0);
                        glRotatef( 90, 0, 0, 1);
                        glTranslatef(-map[currentRound][i][j][k]->x,-2*i,-map[currentRound][i][j][k]->z-0.5 );

                        // draw in XZ plane
                        draw_floor_with_tex( map[currentRound][i][j][k]->x  , map[currentRound][i][j][k]->z, 2*i, coin1);
                        glPopMatrix();
                    }
                }
           }
       }
    }

    // draw spawn points corresponding to each bot
    for( int m = 0; m < bots.size(); m++ )
    {
        glPushMatrix();

        glTranslatef( +bots.at(m).spawnX+0.5, +2*bots.at(m).spawnY, +bots.at(m).spawnZ+0.5);
        glRotatef(r, 0, 1, 0);
        glTranslatef( -bots.at(m).spawnX-0.5, -2*bots.at(m).spawnY, -bots.at(m).spawnZ-0.5);
        draw_floor_with_tex( bots.at(m).spawnX, bots.at(m).spawnZ, 2*bots.at(m).spawnY+0.1, botSpawn1);

        glPopMatrix();
    }

    // draw my spawn point
    glPushMatrix();

    glTranslatef( +49.5, +2*1, +49.5);
    glRotatef(r, 0, 1, 0);
    glTranslatef( -49.5, -2*1, -49.5);
    draw_floor_with_tex( 49, 49, 2*2+0.1, heroSpawn1);

    glPopMatrix();

    // draw destination
    glPushMatrix();

    // rotate only if all counts collected
    if( currentCoin == coinCount[currentRound] )
    {
        glTranslatef( +playerDestination[currentRound][0]+0.5, +2*playerDestination[currentRound][1], +playerDestination[currentRound][2]+0.5);
        glRotatef(r/2, 0, 1, 0);
        glTranslatef( -playerDestination[currentRound][0]-0.5, -2*playerDestination[currentRound][1], -playerDestination[currentRound][2]-0.5);
    }

    draw_floor_with_tex( playerDestination[currentRound][0], playerDestination[currentRound][2], 2*playerDestination[currentRound][1]+0.1, destination1);

    glPopMatrix();

    glPushMatrix();

    glDisable(GL_LIGHTING);
    static bool goingUp = true;
    static float a = 0.0;
    if( goingUp ) a+=0.05;
    if(!goingUp ) a-=0.05;
    if( a >= 1 ) goingUp = false;
    if( a <= 0 ) goingUp = true;
    glColor4f( 1, 1, 1, a);

    if( gameLost )
        draw_rect_with_tex( -5, +5, -5, +5, lostTexture);

    if( gameWon )
        draw_rect_with_tex( -5, +5, -5, +5, wonTexture);

    glPopMatrix();

    glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void meMovingLeft(int i)
{
    if( meDead ) { meDead = false; meMoving = false; return; }
    meMoving = true;
    _meMovingRight = false;
    _meMovingUp = false;
    _meMovingDown = false;
    _meMovingLeft = true;
    i++;
    eyeX -= 0.1;
    playerX -= 0.1;
    glutPostRedisplay();
    if( i < 10 )
    {
        glutTimerFunc( 1000/FPS, meMovingLeft, i);
    }
    else
    {
        eyeX = floor(eyeX+0.5);
        playerX = floor(playerX+0.5);
        meMoving = false;

        // if coin is present, grab it
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isCoin && !map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken )
        {
            currentCoin++;
            map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken = true;
        }

        // if it is dug and there is no bot one level below, fall down
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isDug && !allBotCheck((int)playerX, (int)playerY, (int)playerZ, -1) )
        {
            for( int j = (int)playerY-1; j > -1; j-- )
            {
                // if their is a tile at level i, fall down
                if( map[currentRound][j][(int)playerZ][(int)playerX] )
                {
                    meDestY = j;
                    break;
                }
            }

            // falling down forever
            if( meDestY == 0 )
            {
                std::cout << "Dead";
            }
            meFallingDown = true;
        }
    }
}
void meMovingRight(int i)
{
    if( meDead ) { meDead = false; meMoving = false; return; }
    meMoving = true;
    _meMovingLeft = false;
    _meMovingUp = false;
    _meMovingDown = false;
    _meMovingRight = true;
    i++;
    eyeX += 0.1;
    playerX += 0.1;
    glutPostRedisplay();
    if( i < 10 )
    {
        glutTimerFunc( 1000/FPS, meMovingRight, i);
    }
    else
    {
        eyeX = floor(eyeX+0.5);
        playerX = floor(playerX+0.5);
        meMoving = false;

        // if coin is present, grab it
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isCoin && !map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken )
        {
            currentCoin++;
            map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken = true;
        }

        // if it is dug and there is no bot one level below, fall down
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isDug && !allBotCheck((int)playerX, (int)playerY, (int)playerZ, -1) )
        {
            for( int j = (int)playerY-1; j > -1; j-- )
            {
                // if their is a tile at level i, fall down
                if( map[currentRound][j][(int)playerZ][(int)playerX] )
                {
                    meDestY = j;
                    break;
                }
            }
            meFallingDown = true;
            // falling down forever
            if( meDestY == 0 )
            {
                std::cout << "Dead";
            }
        }
    }
}
void meMovingUp(int i)
{
    if( meDead ) { meDead = false; meMoving = false; return; }
    meMoving = true;
    _meMovingLeft = false;
    _meMovingRight = false;
    _meMovingDown = false;
    _meMovingUp = true;
    i++;
    eyeZ -= 0.1;
    playerZ -= 0.1;
    glutPostRedisplay();
    if( i < 10 )
    {
        glutTimerFunc( 1000/FPS, meMovingUp, i);
    }
    else
    {
        eyeZ = floor(eyeZ+0.5);
        playerZ = floor(playerZ+0.5);
        meMoving = false;

        // if coin is present, grab it
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isCoin && !map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken )
        {
            currentCoin++;
            map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken = true;
        }

        // if it is dug and there is no bot one level below, fall down
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isDug && !allBotCheck((int)playerX, (int)playerY, (int)playerZ, -1) )
        {
            for( int j = (int)playerY-1; j > -1; j-- )
            {
                // if their is a tile at level i, fall down
                if( map[currentRound][j][(int)playerZ][(int)playerX] )
                {
                    meDestY = j;
                    break;
                }
            }
            meFallingDown = true;
            // falling down forever
            if( meDestY == 0 )
            {
                std::cout << "Dead";
            }
        }
    }
}
void meMovingDown(int i)
{
    if( meDead ) { meDead = false; meMoving = false; return; }
    meMoving = true;
    _meMovingLeft = false;
    _meMovingRight = false;
    _meMovingUp = false;
    _meMovingDown = true;
    i++;
    eyeZ += 0.1;
    playerZ += 0.1;
    glutPostRedisplay();
    if( i < 10 )
    {
        glutTimerFunc( 1000/FPS, meMovingDown, i);
    }
    else
    {
        eyeZ = floor(eyeZ+0.5);
        playerZ = floor(playerZ+0.5);
        meMoving = false;

        // if coin is present, grab it
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isCoin && !map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken )
        {
            currentCoin++;
            map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken = true;
        }

        // if it is dug and there is no bot one level below, fall down
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isDug && !allBotCheck((int)playerX, (int)playerY, (int)playerZ, -1) )
        {
            for( int j = (int)playerY-1; j > -1; j-- )
            {
                // if their is a tile at level i, fall down
                if( map[currentRound][j][(int)playerZ][(int)playerX] )
                {
                    meDestY = j;
                    break;
                }
            }
            meFallingDown = true;
            // falling down forever
            if( meDestY == 0 )
            {
                std::cout << "Dead";
            }
        }
    }
}
void meLadderUp(int i)
{
    if( playerLadderSide == RIGHT )
    {
        _meMovingRight = false;
        _meMovingUp = false;
        _meMovingDown = false;
        _meMovingLeft = true;
    }
    else
    {
        _meMovingLeft = false;
        _meMovingRight = false;
        _meMovingDown = false;
        _meMovingUp = true;
    }

    meMoving = true;
    i++;
    eyeY += 0.02;
    playerY += 0.01;
    glutPostRedisplay();
    if( i < 100 )
    {
        glutTimerFunc( 1000/FPS, meLadderUp, i);
    }
    else
    {
        eyeY = floor(eyeY+0.5);
        playerY = floor(playerY+0.5);
        if( playerLadderSide == RIGHT )
            meMovingLeft(0);
        else
            meMovingUp(0);
    }
}
void meLadderDown(int i)
{
    if( playerLadderSide == RIGHT && i == 0 )
        meMovingRight(0);
    else if( i == 0 )
        meMovingDown(0);

    meMoving = true;
    i++;
    eyeY -= 0.02;
    playerY -= 0.01;
    glutPostRedisplay();
    if( i < 100 )
    {
        glutTimerFunc( 1000/FPS, meLadderDown, i);
    }
    else
    {
        eyeY = floor(eyeY+0.5);
        playerY = floor(playerY+0.5);

        // if coin is present, grab it
        if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->isCoin )
        {
            currentCoin++;
            map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->coinTaken = true;
        }

        meMoving = false;
    }
}

void processSpecialKeys(int key, int x, int y)
{
    if( gameLost || gameWon ) return;
    int i;
    switch(key)
    {
        case GLUT_KEY_LEFT :
            if( playerX <= 0.2                                                       ||
                meMoving                                                             ||
                !map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]                     ||
               (!map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]->isReachable        &&
                 map[currentRound][(int)playerY+1][(int)playerZ][(int)playerX-1]                   &&
                (map[currentRound][(int)playerY+1][(int)playerZ][(int)playerX-1]->whichSide != RIGHT)) ) return;

            if( map[currentRound][(int)playerY+1][(int)playerZ][(int)playerX-1]             &&
                map[currentRound][(int)playerY+1][(int)playerZ][(int)playerX-1]->whichSide == RIGHT )
            {
                playerLadderSide = RIGHT;
                meLadderUp(0);
            }
            else
                meMovingLeft(0);
            break;

        case GLUT_KEY_RIGHT :
            if( playerX >= 48.2 || meMoving ) return;

            if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->whichSide == RIGHT )
            {
                playerLadderSide = RIGHT;
                meLadderDown(0);
                break;
            }

            if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]              &&
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]->isReachable  )
                meMovingRight(0);
            break;

        case GLUT_KEY_UP :
            if( playerZ <= 0.2                                                      ||
                meMoving                                                            ||
                !map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]                    ||
               (!map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]->isReachable       &&
                 map[currentRound][(int)playerY+1][(int)playerZ-1][(int)playerX]                  &&
                (map[currentRound][(int)playerY+1][(int)playerZ-1][(int)playerX]->whichSide != DOWN)) ) return;

            if( map[currentRound][(int)playerY+1][(int)playerZ-1][(int)playerX]             &&
                map[currentRound][(int)playerY+1][(int)playerZ-1][(int)playerX]->whichSide == DOWN )
            {
                playerLadderSide = DOWN;
                meLadderUp(0);
            }
            else
                meMovingUp(0);
            break;

        case GLUT_KEY_DOWN :
            if( playerZ >= 48.2 || meMoving ) return;

            if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX]->whichSide == DOWN )
            {
                playerLadderSide = DOWN;
                meLadderDown(0);
                break;
            }

            if( map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]              &&
                map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]->isReachable  )
                meMovingDown(0);
            break;

        case GLUT_KEY_PAGE_UP:
            eyeX-= 0.4;
            eyeY-= 0.2;
            eyeZ-= 0.4;
            break;

        case GLUT_KEY_PAGE_DOWN:
            eyeX+= 0.4;
            eyeY+= 0.2;
            eyeZ+= 0.4;
            break;
    }
    glutPostRedisplay();
}


void keyboard( unsigned char BUTTON, int x, int y)
{
    if( meMoving ) return;
    // ijkl - dig if tile exists
    switch(BUTTON)
    {
        case 'j':
            if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1] &&
               !map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]->ladderPresent &&
               !map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]->isDug &&
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]->isDiggable )
            {
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]->isDug = true;
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX-1]->isDugTimer = DUG_TIMER;
                for( int j = playerY-1; j > -1; j-- )
                {
                    // if their is a tile at level j, make it reachable
                    if( map[currentRound][j][(int)playerZ][(int)playerX-1] )
                    {
                        adjustNeighboursAdd((int)playerX-1, j, (int)playerZ);
                    }
                }
            }
            break;
        case 'l':
            if( map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1] &&
               !map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]->ladderPresent &&
               !map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]->isDug &&
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]->isDiggable )
            {
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]->isDug = true;
                map[currentRound][(int)playerY][(int)playerZ][(int)playerX+1]->isDugTimer = DUG_TIMER;
                for( int j = playerY-1; j > -1; j-- )
                {
                    // if their is a tile at level j, make it reachable
                    if( map[currentRound][j][(int)playerZ][(int)playerX+1] )
                    {
                        adjustNeighboursAdd((int)playerX+1, j, (int)playerZ);
                    }
                }
            }
            break;
        case 'i':
            if( map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX] &&
               !map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]->ladderPresent &&
               !map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]->isDug &&
                map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]->isDiggable )
            {
                map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]->isDug = true;
                map[currentRound][(int)playerY][(int)playerZ-1][(int)playerX]->isDugTimer = DUG_TIMER;
                for( int j = playerY-1; j > -1; j-- )
                {
                    // if their is a tile at level j, make it reachable
                    if( map[currentRound][j][(int)playerZ-1][(int)playerX] )
                    {
                        adjustNeighboursAdd((int)playerX, j, (int)playerZ-1);
                    }
                }
            }
            break;
        case 'k':
            if( map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX] &&
               !map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]->ladderPresent &&
               !map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]->isDug &&
                map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]->isDiggable )
            {
                map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]->isDug = true;
                map[currentRound][(int)playerY][(int)playerZ+1][(int)playerX]->isDugTimer = DUG_TIMER;
                for( int j = playerY-1; j > -1; j-- )
                {
                    // if their is a tile at level j, make it reachable
                    if( map[currentRound][j][(int)playerZ+1][(int)playerX] )
                    {
                        adjustNeighboursAdd((int)playerX, j, (int)playerZ+1);
                    }
                }
            }
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (0, 0);   
    glutCreateWindow (argv[0]);
    glutFullScreen();
    init (); 
    glutDisplayFunc(display);
//    glutMouseFunc(mouse);

    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
