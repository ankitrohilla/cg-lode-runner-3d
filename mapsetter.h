bot *tempBot;

void setUpMap(int i)
{
    bots.clear();
    currentCoin = 0;
    switch(i)
    {
        case 0:

        for( int i = 45; i <= 49; i++ )
        {
            for( int j = 42; j <= 49; j++ )
                blockWall(i, 0, j, wall2, grass1, (side)-1, 0);
        }

        blockWall(45, 0, 40, wall2, grass1, (side)-1, 0);
        blockWall(45, 0, 40, wall2, grass1, (side)-1, 0);
        blockWall(45, 0, 41, wall2, grass1, (side)-1, 0);
        blockWall(31, 0, 44, wall2, grass1, (side)-1, 0);

        for( int i = 32; i < 45; i++ )
            blockWall(i, 0, 44, wall2, grass1, (side)-1, 0);

        for( int i = 45; i <= 49; i++ )
        {
            for( int j = 42; j <= 49; j++ )
                blockWall(i, 1, j, wall2, grass1, (side)-1, 0);
        }

        blockWall(45, 1, 40, wall2, grass1, (side)-1, 1);
        blockWall(45, 1, 41, wall2, grass1, (side)-1, 1);
        blockWall(31, 1, 44, wall2, grass1, (side)-1, 0);

        for( int i = 32; i < 45; i++ )
            blockWall(i, 1, 44, wall2, grass1, (side)-1, 0);


        for( int i = 32; i < 45; i++ )
            blockWall(i, 2, 44, wall2, grass1, (side)-1, 0);

        blockWall(41, 2, 45, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 43, wall2, grass1, (side)-1, 0);
        blockWall(37, 2, 45, wall2, grass1, (side)-1, 0);
        blockWall(37, 2, 43, wall2, grass1, (side)-1, 0);
        blockWall(31, 2, 44, wall2, grass1, (side)-1, 1);
        blockWall(45, 2, 44, wall2, grass1, RIGHT, 1);

        coinCount[0] = 4;

        tempBot = new bot( 41, 3, 44 ,0, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 37, 3, 44 ,1, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        playerDestination[0][0] = 48;
        playerDestination[0][1] = 2;
        playerDestination[0][2] = 46;

        break;

        case 1:


        blockWall(49, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(49, 0, 48, wall2, grass1, (side)-1, 0);
        blockWall(49, 0, 47, wall2, grass1, (side)-1, 0);
        blockWall(49, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(48, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(48, 0, 48, wall2, grass1, (side)-1, 0);
        blockWall(48, 0, 47, wall2, grass1, (side)-1, 0);
        blockWall(48, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(47, 0, 49, wall2, grass1, DOWN, 0);
        blockWall(47, 0, 48, wall2, grass1, (side)-1, 0);
        blockWall(47, 0, 47, wall2, grass1, (side)-1, 0);
        blockWall(47, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(46, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(46, 0, 48, wall2, grass1, (side)-1, 0);
        blockWall(46, 0, 47, wall2, grass1, (side)-1, 0);
        blockWall(46, 0, 46, wall2, grass1, (side)-1, 0);

        blockWall(44, 0, 48, wall2, grass1, (side)-1, 0);

        blockWall(49, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(48, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(47, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(46, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(45, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(44, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(43, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(42, 0, 46, wall2, grass1, (side)-1, 0);
        blockWall(41, 0, 46, wall2, grass1, (side)-1, 0);

        blockWall(41, 0, 47, wall2, grass1, (side)-1, 0);
        blockWall(41, 0, 48, wall2, grass1, (side)-1, 0);
        blockWall(41, 0, 49, wall2, grass1, (side)-1, 0);

        blockWall(42, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(43, 0, 49, wall2, grass1, (side)-1, 0);// bot
        blockWall(43, 0, 48, wall2, grass1, (side)-1, 0);
        blockWall(43, 0, 47, wall2, grass1, (side)-1, 0);
        blockWall(44, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(45, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(46, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(47, 0, 49, wall2, grass1, (side)-1, 0);
        blockWall(42, 0, 48, wall2, grass1, (side)-1, 0);

        blockWall(49, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(49, 1, 48, wall2, grass1, (side)-1, 0);
        blockWall(49, 1, 47, wall2, grass1, (side)-1, 0);
        blockWall(49, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(48, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(48, 1, 48, wall2, grass1, (side)-1, 0);
        blockWall(48, 1, 47, wall2, grass1, (side)-1, 0);
        blockWall(48, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(47, 1, 49, wall2, grass1, DOWN, 0);
        blockWall(47, 1, 48, wall2, grass1, (side)-1, 0);
        blockWall(47, 1, 47, wall2, grass1, (side)-1, 0);
        blockWall(47, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(46, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(46, 1, 48, wall2, grass1, (side)-1, 0);
        blockWall(46, 1, 47, wall2, grass1, (side)-1, 0);
        blockWall(46, 1, 46, wall2, grass1, (side)-1, 0);

        blockWall(44, 1, 48, wall2, grass1, (side)-1, 0);

        blockWall(49, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(48, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(47, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(46, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(45, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(44, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(43, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(42, 1, 46, wall2, grass1, (side)-1, 0);
        blockWall(41, 1, 46, wall2, grass1, (side)-1, 0);

        blockWall(41, 1, 47, wall2, grass1, (side)-1, 0);
        blockWall(41, 1, 48, wall2, grass1, (side)-1, 0);
        blockWall(41, 1, 49, wall2, grass1, (side)-1, 0);

        blockWall(42, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(43, 1, 49, wall2, grass1, (side)-1, 0);// bot
        blockWall(43, 1, 48, wall2, grass1, (side)-1, 0);
        blockWall(43, 1, 47, wall2, grass1, (side)-1, 0);
        blockWall(44, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(45, 1, 49, wall2, grass1, (side)-1, 1);
        blockWall(46, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(47, 1, 49, wall2, grass1, (side)-1, 0);
        blockWall(42, 1, 48, wall2, grass1, (side)-1, 0);


        blockWall(49, 2, 46, wall2, grass1, (side)-1, 0);
        blockWall(48, 2, 46, wall2, grass1, DOWN, 0);
        blockWall(47, 2, 46, wall2, grass1, (side)-1, 0);
        blockWall(46, 2, 46, wall2, grass1, (side)-1, 1);
        blockWall(45, 2, 46, wall2, grass1, (side)-1, 0);
        blockWall(44, 2, 46, wall2, grass1, (side)-1, 0);
        blockWall(43, 2, 46, wall2, grass1, (side)-1, 0);
        blockWall(42, 2, 46, wall2, grass1, (side)-1, 1);
        blockWall(41, 2, 46, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 47, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 48, wall2, grass1, RIGHT, 0);

        blockWall(41, 2, 45, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 44, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 43, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 42, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 41, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 40, wall2, grass1, (side)-1, 1);
        blockWall(41, 2, 39, wall2, grass1, (side)-1, 0);
        blockWall(41, 2, 38, wall2, grass1, (side)-1, 0);


        blockWall(41, 3, 46, wall2, grass1, DOWN, 0);
        blockWall(41, 3, 45, wall2, grass1, (side)-1, 0);
        blockWall(41, 3, 44, wall2, grass1, (side)-1, 0);
        blockWall(41, 3, 43, wall2, grass1, (side)-1, 0);
        blockWall(41, 3, 42, wall2, grass1, (side)-1, 0);
        blockWall(41, 3, 41, wall2, grass1, (side)-1, 0);
        blockWall(41, 3, 40, wall2, grass1, (side)-1, 1);
        blockWall(41, 3, 39, wall2, grass1, (side)-1, 0);
        blockWall(41, 3, 38, wall2, grass1, (side)-1, 0);

        blockWall(41, 4, 38, wall2, grass1, DOWN, 0);
        blockWall(41, 4, 37, wall2, grass1, (side)-1, 0);
        blockWall(41, 4, 36, wall2, grass1, (side)-1, 1);
        blockWall(42, 4, 36, wall2, grass1, (side)-1, 0);

        tempBot = new bot( 43, 3, 46 ,0, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 43, 2, 48, 1, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 41, 4, 39, 2, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        playerDestination[1][0] = 42;
        playerDestination[1][1] = 5;
        playerDestination[1][2] = 36;

        coinCount[1] = 5;

        break;

        case 2:

        for( int k = 49; k >= 45; k-- )
        {
            for( int l = 49; l >= 45; l-- )
            {
                blockWall( k, 0, l, wall2, grass1, (side)-1 , 0);
            }
        }

        blockWall( 45, 0, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 44, 0, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 43, 0, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 0, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 0, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 0, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 39, 0, 44, wall2, grass1, (side)-1 , 0);

        blockWall( 42, 0, 45, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 0, 43, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 0, 42, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 0, 41, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 0, 40, wall2, grass1, (side)-1 , 0);

        blockWall( 41, 0, 48, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 0, 46, wall2, grass1, (side)-1 , 0);

        blockWall( 44, 0, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 43, 0, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 0, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 0, 45, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 0, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 0, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 39, 0, 47, wall2, grass1, (side)-1 , 0);


        blockWall( 42, 0, 39, wall2, grass1, (side)-1 , 0);











        for( int k = 49; k >= 45; k-- )
        {
            for( int l = 49; l >= 45; l-- )
            {
                blockWall( k, 1, l, wall2, grass1, (side)-1 , 0);
            }
        }

        blockWall( 45, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 44, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 43, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 39, 1, 44, wall2, grass1, (side)-1 , 0);

        blockWall( 42, 1, 45, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 1, 43, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 1, 42, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 1, 41, wall2, grass1, (side)-1 , 1);
        blockWall( 42, 1, 40, wall2, grass1, (side)-1 , 0);

        blockWall( 41, 1, 48, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 1, 46, wall2, grass1, (side)-1 , 0);

        blockWall( 44, 1, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 43, 1, 47, wall2, grass1, (side)-1 , 1);
        blockWall( 42, 1, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 1, 45, wall2, grass1, (side)-1 , 0);
        blockWall( 41, 1, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 1, 47, wall2, grass1, (side)-1 , 0);
        blockWall( 39, 1, 47, wall2, grass1, (side)-1 , 1);



        blockWall( 42, 1, 39, wall2, grass1, (side)-1 , 0);








        blockWall( 39, 2, 44, wall2, grass1, RIGHT , 0);
        blockWall( 38, 2, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 2, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 44, wall2, grass1, (side)-1 , 1);
        blockWall( 35, 2, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 43, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 42, wall2, grass1, (side)-1 , 0);         // bot
        blockWall( 35, 2, 42, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 2, 42, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 41, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 40, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 2, 40, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 2, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 38, 2, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 39, 2, 39, wall2, grass1, (side)-1 , 1);
        blockWall( 40, 2, 39, wall2, grass1, (side)-1 , 0);         // bot
        blockWall( 41, 2, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 2, 39, wall2, grass1, DOWN , 0);
        blockWall( 40, 2, 40, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 2, 38, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 2, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 2, 36, wall2, grass1, (side)-1 , 0);         // dest
        blockWall( 39, 2, 36, wall2, grass1, (side)-1 , 1);
        blockWall( 38, 2, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 2, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 2, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 2, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 2, 35, wall2, grass1, (side)-1 , 1);

        blockWall( 35, 2, 39, wall2, grass1, (side)-1 , 0);








        blockWall( 39, 1, 44, wall2, grass1, RIGHT , 0);
        blockWall( 38, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 44, wall2, grass1, (side)-1 , 1);
        blockWall( 35, 1, 44, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 43, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 42, wall2, grass1, (side)-1 , 0);         // bot
        blockWall( 35, 1, 42, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 1, 42, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 41, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 40, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 1, 40, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 1, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 38, 1, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 39, 1, 39, wall2, grass1, (side)-1 , 1);
        blockWall( 40, 1, 39, wall2, grass1, (side)-1 , 0);         // bot
        blockWall( 41, 1, 39, wall2, grass1, (side)-1 , 0);
        blockWall( 42, 1, 39, wall2, grass1, DOWN , 0);
        blockWall( 40, 1, 40, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 1, 38, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 1, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 40, 1, 36, wall2, grass1, (side)-1 , 0);         // dest
        blockWall( 39, 1, 36, wall2, grass1, (side)-1 , 1);
        blockWall( 38, 1, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 1, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 1, 35, wall2, grass1, (side)-1 , 1);

        blockWall( 35, 1, 39, wall2, grass1, (side)-1 , 0);

















        blockWall( 35, 3, 39, wall2, grass1, DOWN , 0);

        blockWall( 35, 3, 38, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 4, 38, wall2, grass1, DOWN , 0);

        blockWall( 35, 4, 37, wall2, grass1, (side)-1 , 0);

        blockWall( 35, 3, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 4, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 5, 37, wall2, grass1, DOWN , 0);

        blockWall( 35, 5, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 5, 35, wall2, grass1, (side)-1 , 1);
        blockWall( 35, 5, 34, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 5, 33, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 5, 32, wall2, grass1, (side)-1 , 0);
        blockWall( 35, 5, 31, wall2, grass1, (side)-1 , 0);

        blockWall( 36, 5, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 5, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 5, 35, wall2, grass1, (side)-1 , 1);
        blockWall( 36, 5, 34, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 5, 33, wall2, grass1, (side)-1 , 0);
        blockWall( 36, 5, 32, wall2, grass1, (side)-1 , 1);
        blockWall( 36, 5, 31, wall2, grass1, (side)-1 , 0);

        blockWall( 37, 5, 37, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 5, 36, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 5, 35, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 5, 34, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 5, 33, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 5, 32, wall2, grass1, (side)-1 , 0);
        blockWall( 37, 5, 31, wall2, grass1, (side)-1 , 0);

        tempBot = new bot( 42, 2, 44, 0, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 36, 3, 42, 1, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 40, 3, 39, 2, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 36, 6, 33, 3, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 36, 6, 34, 4, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        tempBot = new bot( 36, 3, 36, 5, 0.0, 0.3, 0.0, 0.5, 0.8, 0.8, 0.0, 0.1, 0.0);
        bots.push_back(*tempBot);

        coinCount[2] = 10;

        playerDestination[2][0] = 40;
        playerDestination[2][1] = 3;
        playerDestination[2][2] = 36;

        break;

    }

    eyeX = 70.0; eyeY = 20.0; eyeZ = 70.0; playerX = 49.0; playerY = 2.0; playerZ = 49.0;
    map[currentRound][1][49][49]->isDiggable = false;

    std::cout << "NO OF BOTS " << bots.size();
    glutTimerFunc( 5, gameHandler, 5);
}
