GLUquadricObj *body     = gluNewQuadric();

GLUquadricObj *leftArmUpper  = gluNewQuadric();
GLUquadricObj *rightArmUpper = gluNewQuadric();
GLUquadricObj *leftLegUpper  = gluNewQuadric();
GLUquadricObj *rightLegUpper = gluNewQuadric();

GLUquadricObj *leftArmLower  = gluNewQuadric();
GLUquadricObj *rightArmLower = gluNewQuadric();
GLUquadricObj *leftLegLower  = gluNewQuadric();
GLUquadricObj *rightLegLower = gluNewQuadric();

void showHero()
{
    static int bodyX = 0, bodyY= 0 ,bodyZ =0 , shoulderLeftX = 0 , shoulderLeftY = 0 , shoulderLeftZ = 0 , shoulderRightX = 0, shoulderRightY = 0 , shoulderRightZ = 0 ,elbowLeftX = 0 , elbowLeftY = 0 , elbowLeftZ = 0 , elbowRightX = 0 ,elbowRightY = 0 ,elbowRightZ = 0 , thighsLeftX = 0 , thighsLeftY = 0 , thighsLeftZ = 0 , thighsRightX = 0 ,thighsRightY = 0 , thighsRightZ = 0 , legLeftX = 0 , legLeftY = 0 , legLeftZ = 0 , legRightX = 0 , legRightY = 0 , legRightZ = 0 ;
    bool static thighsGoingUp = true;
    bool static elbowGoingUp = true;
    bool static rightLegGoingAhead = true;

    glColor4f(0.8, 0.8 , 0.5 , 1.0);
    glPushMatrix();

    if( _meMovingRight )
        glRotatef( 90+thighsRightX, 0, 1, 0);
    if( _meMovingUp )
        glRotatef(180+thighsRightX, 0, 1, 0);
    if( _meMovingLeft )
        glRotatef(270+thighsRightX, 0, 1, 0);
    if( _meMovingDown )
        glRotatef(  0+thighsRightX, 0, 1, 0);

    glTranslatef( 0.0, 0.6+(float)thighsRightX/360, 0.0);
        glScalef( 0.7, 0.6, 0.7);

    // moving effect
    if( meMoving )
    {
        if( thighsRightX >= 30 ) thighsGoingUp = false;
        if( thighsRightX <=-30 ) thighsGoingUp = true;

/*
        if( thighsRightX >= 0  &&  thighsGoingUp ) { leftLegGoingAhead = true;  rightLegGoingAhead = false; }
        if( thighsRightX >= 0  &&  thighsGoingUp ) { leftLegGoingAhead = false; rightLegGoingAhead = true; }
        if( thighsRightX <= 0  && !thighsGoingUp ) { leftLegGoingAhead = false; rightLegGoingAhead = false; }
        if( thighsRightX >=-30 &&  thighsGoingUp ) { leftLegGoingAhead = false;  rightLegGoingAhead = false; }

        if( leftLegGoingAhead )
        {
            legLeftX -= 20;
            legRightX-= 20;
        }
        else if( rightLegGoingAhead )
        {
            legLeftX += 20;
            legRightX+= 20;
        }
*/
        if( thighsGoingUp )
        {
            thighsRightX+=5;
            thighsLeftX-=5;
            shoulderRightX-=10;
            shoulderLeftX+=10;
            elbowRightX-=5;
            elbowLeftX+=5;
        }
        else if( !thighsGoingUp )
        {
            thighsRightX-=5;
            thighsLeftX+=5;
            shoulderRightX+=10;
            shoulderLeftX-=10;
            elbowRightX+=5;
            elbowLeftX-=5;
        }
    }

 // main body
    //glTranslatef (-0.5, 0.0, 0.0);
    glRotatef ((GLfloat) bodyX, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) bodyY, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) bodyZ, 0.0, 0.0, 1.0);
    //glTranslatef (0.5, 0.0, 0.0);

    glPushMatrix();
    gluQuadricDrawStyle(body ,GLU_FILL);
    glScalef(1.0 , 1.0 , 0.9);
    glTranslatef(0.0 , 0.43 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.25);
    gluCylinder(body , 0.3 , 0.0 ,0.3,100,100);  // collar
    glPopMatrix();

    glPushMatrix();
    glScalef (0.9, 1.4, 0.8);
    glutSolidSphere (0.5 ,100 ,100);   // for body
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0 , -0.6 , 0.0);
    glScalef(1.0 , 0.45 , 0.9);
    glutSolidSphere(0.3 , 100,100);  // lower body sphere
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle(body ,GLU_FILL);
    glScalef(1.0 , 1.0 , 0.9);
    glTranslatef(0.0 , -0.6 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.25);
    gluCylinder(body , 0.39 , 0.3,0.3,100,100);  // middle body cylinder
    glPopMatrix();

    glPushMatrix();   // face
    glTranslatef(0.0 , 0.95 , 0.0);

    glPushMatrix();
    glScalef (0.5, 0.6, 0.5);
    glutSolidSphere (0.5 ,100 ,100);
    glPopMatrix();

    glPushMatrix();                    //eyes
    glColor3f(0.0,0.0,0.0);
    glTranslatef(-0.1 , 0.0 , 0.21);
    glutSolidSphere(0.04, 100,100);
    glPopMatrix();

    glPushMatrix();            //eyes
    glColor3f(0.0,0.0,0.0);
    glTranslatef(0.1 , 0.0 , 0.21);
    glutSolidSphere(0.04, 100,100);
    glPopMatrix();

    glPushMatrix();                 // smile
    glBegin(GL_POINTS);
    glVertex3f(-0.1 , -0.18 , 0.185);
    glVertex3f(-0.075 , -0.19 , 0.19);
    glVertex3f(-0.05 , -0.195 , 0.19);
    glVertex3f(-0.025 , -0.2 , 0.195);
    glVertex3f( 0.0 , -0.2 , 0.195);
    glVertex3f(0.025 , -0.2 , 0.195);
    glVertex3f(0.05 , -0.195 , 0.19);
    glVertex3f(0.075 , -0.19 ,0.19);
    glVertex3f( 0.1 , -0.18 , 0.185);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glColor4f(0.8, 0.8 , 0.5 , 1.0);

    glPushMatrix();
    gluQuadricDrawStyle(body , GLU_FILL);
    glScalef(1.0 ,1.0 ,0.9);
    glTranslatef(0.0 , 0.6 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.05);
    gluCylinder(body , 0.2 , 0.28,0.1,100,100); //upper body cylinder
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle(body , GLU_FILL);
    glScalef(1.0 ,1.0 ,0.9);
    glTranslatef(0.0 , 0.65 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.05);
    gluCylinder(body , 0.1 , 0.2 ,0.05,100,100); // upper body cylinder
    glPopMatrix();

    // right arm
    glPushMatrix();
    glRotatef(30 , 0.0 , 0.0 ,1.0);
    glTranslatef (0.45, 0.2, 0.0);
    glRotatef ((GLfloat) shoulderRightX, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulderRightY, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) shoulderRightZ, 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(-90 , 0.0 , 0.0 , 1.0 );
    glTranslatef (0.5, 0.0, 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightArmUpper , GLU_FILL);
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightArmUpper , 0.25 , 0.18 , 0.5 , 100 , 100);      //upper right arm
    glPopMatrix();

    glPushMatrix();                                                    // upper right arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,100 , 100);
    glPopMatrix();


    //lower right arm
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef(-35 ,0.0,0.0,1.0);
    glRotatef ((GLfloat)elbowRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat)elbowRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat)elbowRightZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(-90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightArmLower , GLU_FILL );
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightArmLower , 0.18 , 0.15 , 0.5 ,100 , 100 );
    glPopMatrix();

    glPushMatrix();                                                    //  lower right arm lower sphere
    glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3 , 0.3);
    glutSolidSphere(0.2 ,100 , 100);
    glPopMatrix();

    glPushMatrix();                                                    // lower right arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.2 ,100 , 100);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    // left arm

    glPushMatrix();
    glRotatef(-30 , 0.0 , 0.0 ,1.0);
    glTranslatef (-0.45, 0.2, 0.0);
    glRotatef ((GLfloat) shoulderLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulderLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) shoulderLeftZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(90 , 0.0 , 0.0 , 1.0);
    glTranslatef (-0.5, 0.0, 0.0);
    glScalef (1.0, 0.3 , 0.3);
    //glutSolidCube (1.0);
    gluQuadricDrawStyle ( leftArmUpper , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftArmUpper , 0.25 , 0.18 , 0.5 ,100 , 100 );        // left upper arm
    glPopMatrix();

    glPushMatrix();                                                    // left upper arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,100 , 100);
    glPopMatrix();

    //lower left arm
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef(35,0.0,0.0,1.0);
    glRotatef ((GLfloat) elbowLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) elbowLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) elbowLeftZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(-0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( leftArmLower , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftArmLower , 0.18 , 0.15 , 0.5 ,100 , 100 );
    glPopMatrix();

    glPushMatrix();                                                    // left lower arm lower sphere
    glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3 , 0.3);
    glutSolidSphere(0.2 ,100 , 100);
    glPopMatrix();

    glPushMatrix();                                                    // left lower arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.2 ,100 , 100);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();


    // right leg

    glPushMatrix();
    glTranslatef (0.2, -0.7 , 0.0);
    glRotatef ((GLfloat) thighsRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) thighsRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) thighsRightZ , 0.0, 0.0, 1.0);

    //right leg upper
    glPushMatrix();

   // glRotatef( -20 , 1.0 , 0.0 , 0.0 );
    glRotatef(-90 , 0.0 , 0.0 , 1.0 );
    glTranslatef (0.5, 0.0, 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightLegUpper , GLU_FILL );
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightLegUpper , 0.35 , 0.2 , 0.5 ,100 , 100 );         // right upper leg
    glPopMatrix();

    glPushMatrix();                                                    // right upper leg upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.35,100 , 100);
    glPopMatrix();

    //rigth leg lower
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef ((GLfloat) legRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) legRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) legRightZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef( -90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightLegLower , GLU_FILL );
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightLegLower , 0.21 , 0.15 , 0.5 ,100 , 100 );
    glPopMatrix();

    glPushMatrix();                                                    // right leg lower sphere formation
    glTranslatef(0.0 , -0.5 , 0.1);
    glScalef(0.3, 0.1 , 0.6);
    glutSolidSphere(0.2 ,100 , 100);
    glPopMatrix();

    glPushMatrix();                                                    // right leg lower sphere formation
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,100 , 100);
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();


    //left leg

    glPushMatrix();
    glTranslatef (-0.2, -0.7 , 0.0);
    glRotatef ((GLfloat)thighsLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat)thighsLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat)thighsLeftZ , 0.0, 0.0, 1.0);

    // left leg upper
    glPushMatrix();

    glRotatef(90 , 0.0 , 0.0 , 1.0 );
    glTranslatef (-0.5, 0.0, 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( leftLegUpper , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftLegUpper , 0.35 , 0.2 , 0.5 ,100 , 100 );

    glPopMatrix();

    glPushMatrix();                                                    // left leg upper sphere formation
   // glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.35,100 , 100);
    glPopMatrix();

    //left leg lower
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef ((GLfloat)legLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat)legLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat)legLeftZ , 0.0, 0.0, 1.0);

    glPushMatrix();                                                      //  left leg lower formation
    glRotatef( 90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(-0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( leftLegLower , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftLegLower , 0.21 , 0.15 , 0.5 ,100 , 100 );
    glPopMatrix();

    glPushMatrix();                                                    // left leg lower sphere formation
    glTranslatef(0.0 , -0.5 , 0.1);
    glScalef(0.3, 0.1, 0.6);
    glutSolidSphere(0.2,100 , 100);
    glPopMatrix();

    glPushMatrix();                                                    // left leg lower sphere formation
    //glTranslatef(0.0 , 0.0 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,100 , 100);
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();


   // end
    glPopMatrix();

}


void bot::showWitch()  // 1 for dress , 2 for body ,  3 for belt
{

    glColor4f(0.8, 0.8 , 0.5 , 1.0);
    glPushMatrix();

    if( _movingRight )
        glRotatef( 90+thighsRightX, 0, 1, 0);
    if( _movingUp )
        glRotatef(180+thighsRightX, 0, 1, 0);
    if( _movingLeft )
        glRotatef(270+thighsRightX, 0, 1, 0);
    if( _movingDown )
        glRotatef(  0+thighsRightX, 0, 1, 0);

    glTranslatef( 0.0, 0.6+(float)thighsRightX/360, 0.0);
    glScalef( 0.7, 0.6, 0.7);

    // moving effect
    if( moving )
    {
        if( thighsRightX >= 30 ) thighsGoingUp = false;
        if( thighsRightX <=-30 ) thighsGoingUp = true;

/*
        if( thighsRightX >= 0  &&  thighsGoingUp ) { leftLegGoingAhead = true;  rightLegGoingAhead = false; }
        if( thighsRightX >= 0  &&  thighsGoingUp ) { leftLegGoingAhead = false; rightLegGoingAhead = true; }
        if( thighsRightX <= 0  && !thighsGoingUp ) { leftLegGoingAhead = false; rightLegGoingAhead = false; }
        if( thighsRightX >=-30 &&  thighsGoingUp ) { leftLegGoingAhead = false;  rightLegGoingAhead = false; }

        if( leftLegGoingAhead )
        {
            legLeftX -= 20;
            legRightX-= 20;
        }
        else if( rightLegGoingAhead )
        {
            legLeftX += 20;
            legRightX+= 20;
        }
*/
        if( thighsGoingUp )
        {
            thighsRightX+=5;
            thighsLeftX-=5;
            shoulderRightX-=10;
            shoulderLeftX+=10;
            elbowRightX-=5;
            elbowLeftX+=5;
        }
        else if( !thighsGoingUp )
        {
            thighsRightX-=5;
            thighsLeftX+=5;
            shoulderRightX+=10;
            shoulderLeftX-=10;
            elbowRightX+=5;
            elbowLeftX-=5;
        }
    }

    glColor4f(r1, g1 , b1 , 1.0);
    glPushMatrix();

 // main body
    //glTranslatef (-0.5, 0.0, 0.0);
    glRotatef ((GLfloat)bodyX, 1.0, 0.0, 0.0);
    glRotatef ((GLfloat)bodyY, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat)bodyZ, 0.0, 0.0, 1.0);
    //glTranslatef (0.5, 0.0, 0.0);

    glPushMatrix();
    gluQuadricDrawStyle(body ,GLU_FILL);
    glScalef(1.0 , 1.0 , 0.9);
    glTranslatef(0.0 , 1.6 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.25);
    gluCylinder(body , 0.0 , 0.2 ,0.7,20,20);  // hat
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle(body ,GLU_FILL);
    glScalef(1.0 , 1.0 , 0.9);
    glTranslatef(0.0 , -0.9 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.75);
    gluCylinder(body , 0.3 , 0.7 ,1.5,20,20);  // skirt
    glPopMatrix();


    glPushMatrix();
    glColor3f(r3,g3,b3);
    gluQuadricDrawStyle(body ,GLU_FILL);
    glScalef(1.0 , 1.0 , 0.9);
    glTranslatef(0.0 , -0.4 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.05);
    gluCylinder(body , 0.4 , 0.4 ,0.1,20,20);  // belt
    glPopMatrix();


    glColor4f(r1 , g1 , b1 , 1.0);

    glPushMatrix();
    glTranslatef(0.05 , 1.8 , 0.0);
    glutSolidSphere(0.05,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1 , 1.72 , 0.0);
    glutSolidSphere(0.08,50,50);
    glPopMatrix();

    glPushMatrix();
    glScalef (0.9, 1.4, 0.8);
    glutSolidSphere (0.5 ,20 ,20);   // for body
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0 , -0.6 , 0.0);
    glScalef(1.0 , 0.45 , 0.9);
    glutSolidSphere(0.3 , 20,20);  // lower body sphere
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle(body ,GLU_FILL);
    glScalef(1.0 , 1.0 , 0.9);
    glTranslatef(0.0 , -0.6 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.25);
    gluCylinder(body , 0.39 , 0.3,0.3,20,20);  // middle body cylinder
    glPopMatrix();


    glColor3f(r2 ,g2 ,b2);
    glPushMatrix();   // face
    glTranslatef(0.0 , 0.95 , 0.0);

    glPushMatrix();
    glScalef (0.5, 0.6, 0.5);
    glutSolidSphere (0.5 ,20 ,20);
    glPopMatrix();

    glPushMatrix();                    //eyes
    glColor3f( 0.0 , 0.0 , 0.0);
    glTranslatef(-0.1 , 0.0 , 0.21);
    glutSolidSphere(0.04, 20,20);
    glPopMatrix();

    glPushMatrix();            //eyes
    glColor3f( 0.0 , 0.0 , 0.0);
    glTranslatef(0.1 , 0.0 , 0.21);
    glutSolidSphere(0.04, 20,20);
    glPopMatrix();

    glPushMatrix();                 // smile
    glBegin(GL_POINTS);
    glVertex3f(-0.1 , -0.18 , 0.185);
    glVertex3f(-0.075 , -0.19 , 0.19);
    glVertex3f(-0.05 , -0.195 , 0.19);
    glVertex3f(-0.025 , -0.2 , 0.195);
    glVertex3f( 0.0 , -0.2 , 0.195);
    glVertex3f(0.025 , -0.2 , 0.195);
    glVertex3f(0.05 , -0.195 , 0.19);
    glVertex3f(0.075 , -0.19 ,0.19);
    glVertex3f( 0.1 , -0.18 , 0.185);
    glEnd();
    glPopMatrix();

    glPopMatrix();


  glColor4f(r1, g1 , b1 , 1.0);
    glPushMatrix();
    gluQuadricDrawStyle(body , GLU_FILL);
    glScalef(1.0 ,1.0 ,0.9);
    glTranslatef(0.0 , 0.6 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.05);
    gluCylinder(body , 0.2 , 0.28,0.1,20,20); //upper body cylinder
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle(body , GLU_FILL);
    glScalef(1.0 ,1.0 ,0.9);
    glTranslatef(0.0 , 0.65 ,0.0);
    glRotatef(90 , 1.0,0.0,0.0);
    glTranslatef(0.0 , 0.0 , -0.05);
    gluCylinder(body , 0.1 , 0.2 ,0.05,20,20); // upper body cylinder
    glPopMatrix();

     glColor3f( r2 ,g2 ,b2);
    // right arm
    glPushMatrix();
    glRotatef(30 , 0.0 , 0.0 ,1.0);
    glTranslatef (0.45, 0.2, 0.0);
    glRotatef ((GLfloat)shoulderRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat)shoulderRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat)shoulderRightZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(-90 , 0.0 , 0.0 , 1.0 );
    glTranslatef (0.5, 0.0, 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightArmUpper , GLU_FILL);
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightArmUpper , 0.25 , 0.18 , 0.5 , 20 , 20);      //upper right arm
    glPopMatrix();

    glPushMatrix();                                                    // upper right arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,20 , 20);
    glPopMatrix();


    //lower right arm
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef(-35 ,0.0,0.0,1.0);
    glRotatef ((GLfloat)elbowRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat)elbowRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat)elbowRightZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(-90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightArmLower , GLU_FILL );
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightArmLower , 0.18 , 0.15 , 0.5 ,20 , 20 );
    glPopMatrix();

    glPushMatrix();                                                    //  lower right arm lower sphere
    glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3 , 0.3);
    glutSolidSphere(0.2 ,20 , 20);
    glPopMatrix();

    glPushMatrix();                                                    // lower right arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.2 ,20 , 20);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    // left arm

    glPushMatrix();
    glRotatef(-30 , 0.0 , 0.0 ,1.0);
    glTranslatef (-0.45, 0.2, 0.0);
    glRotatef ((GLfloat) shoulderLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulderLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) shoulderLeftZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(90 , 0.0 , 0.0 , 1.0);
    glTranslatef (-0.5, 0.0, 0.0);
    glScalef (1.0, 0.3 , 0.3);
    //glutSolidCube (1.0);
    gluQuadricDrawStyle ( leftArmUpper , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftArmUpper , 0.25 , 0.18 , 0.5 ,20 , 20 );        // left upper arm
    glPopMatrix();

    glPushMatrix();                                                    // left upper arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,20 , 20);
    glPopMatrix();

    //lower left arm
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef(35,0.0,0.0,1.0);
    glRotatef ((GLfloat) elbowLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) elbowLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) elbowLeftZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef(90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(-0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( leftArmLower , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftArmLower , 0.18 , 0.15 , 0.5 ,20 , 20 );
    glPopMatrix();

    glPushMatrix();                                                    // left lower arm lower sphere
    glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3 , 0.3);
    glutSolidSphere(0.2 ,20 , 20);
    glPopMatrix();

    glPushMatrix();                                                    // left lower arm upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.2 ,20 , 20);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();


    // right leg

    glPushMatrix();
    glTranslatef (0.2, -0.7 , 0.0);
    glRotatef ((GLfloat) thighsRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) thighsRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) thighsRightZ , 0.0, 0.0, 1.0);

    //right leg upper
    glPushMatrix();

   // glRotatef( -20 , 1.0 , 0.0 , 0.0 );
    glRotatef(-90 , 0.0 , 0.0 , 1.0 );
    glTranslatef (0.5, 0.0, 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightLegUpper , GLU_FILL );
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightLegUpper , 0.35 , 0.2 , 0.5 ,20 , 20 );         // right upper leg
    glPopMatrix();

    glPushMatrix();                                                    // right upper leg upper sphere
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.35,20 , 20);
    glPopMatrix();

    //right leg lower
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef ((GLfloat) legRightX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) legRightY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) legRightZ , 0.0, 0.0, 1.0);

    glPushMatrix();
    glRotatef( -90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( rightLegLower , GLU_FILL );
    glRotatef( 90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( rightLegLower , 0.21 , 0.15 , 0.5 ,20 , 20 );
    glPopMatrix();

    glPushMatrix();                                                    // right leg lower sphere formation
    glTranslatef(0.0 , -0.5 , 0.1);
    glScalef(0.3, 0.1 , 0.6);
    glutSolidSphere(0.2 ,20 , 20);
    glPopMatrix();

    glPushMatrix();                                                    // left leg lower sphere formation
    //glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,20 , 20);
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();


    //left leg

    glPushMatrix();
    glTranslatef (-0.2, -0.7 , 0.0);
    glRotatef ((GLfloat) thighsLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) thighsLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) thighsLeftZ , 0.0, 0.0, 1.0);

    // left leg upper
    glPushMatrix();

    glRotatef(90 , 0.0 , 0.0 , 1.0 );
    glTranslatef (-0.5, 0.0, 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( leftLegUpper , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftLegUpper , 0.35 , 0.2 , 0.5 ,20 , 20 );

    glPopMatrix();

    glPushMatrix();                                                    // left leg upper sphere formation
   // glTranslatef(0.0 , -0.5 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.35,20 , 20);
    glPopMatrix();

    //left leg lower
    glPushMatrix();
    glTranslatef( 0.0 , -0.5 ,0.0);
    glRotatef ((GLfloat) legLeftX , 1.0, 0.0, 0.0);
    glRotatef ((GLfloat) legLeftY , 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) legLeftZ , 0.0, 0.0, 1.0);

    glPushMatrix();                                                      //  left leg lower formation
    glRotatef( 90 , 0.0 ,0.0 ,1.0 );
    glTranslatef(-0.5 ,0.0 , 0.0);
    glScalef (1.0, 0.3, 0.3);
    gluQuadricDrawStyle ( leftLegLower , GLU_FILL );
    glRotatef( -90 , 0.0 , 1.0 , 0.0 );
    glTranslatef(0.0 , 0.0 , -0.5);
    gluCylinder( leftLegLower , 0.21 , 0.15 , 0.5 ,20 , 20 );
    glPopMatrix();

    glPushMatrix();                                                    // left leg lower sphere formation
    glTranslatef(0.0 , -0.5 , 0.1);
    glScalef(0.3, 0.1, 0.6);
    glutSolidSphere(0.2,20 , 20);
    glPopMatrix();

    glPushMatrix();                                                    // left leg lower sphere formation
    //glTranslatef(0.0 , 0.0 , 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(0.25 ,20 , 20);
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();


   // end
    glPopMatrix();

}



















/****************************
void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
        case 'b': /* s key rotates at shoulder
            bodyX = (bodyX + 5) % 360;
			glutPostRedisplay();
			break;
        case 'B':
            bodyX = (bodyX - 5) % 360;
			glutPostRedisplay();
			break;
        case 'e': /* e key rotates at elbow
            elbowRightX = (elbowRightX + 5) % 360;
            elbowLeftX = (elbowLeftX - 5) % 360;
			glutPostRedisplay();
			break;
		case 'E':
            elbowRightX = (elbowRightX - 5) % 360;
            elbowLeftX = (elbowLeftX + 5) % 360;
			glutPostRedisplay();
			break;
        case 'l':
            legRightX  = (legRightX - 5) % 360;
            legLeftX  = (legLeftX + 5) % 360;
            glutPostRedisplay();
            break;
        case 'L' :
            legRightX  = (legRightX + 5) % 360;
            legLeftX  = (legLeftX - 5) % 360;
            glutPostRedisplay();
            break;
        case 't':
            thighsRightX  = (thighsRightX - 5) % 360;
            thighsLeftX   = (thighsLeftX + 5) % 360 ;
            glutPostRedisplay();
            break;
        case 'T' :
            thighsRightX  = (thighsRightX + 5) % 360;
            thighsLeftX  =(thighsLeftX - 5)%360 ;
            glutPostRedisplay();
            break;
        case 'i' :
            eyeX = (eyeX + 5) % 360;
            glutPostRedisplay();
            break;
        case 'j' :
            eyeY = (eyeY + 5) % 360;
            glutPostRedisplay();
            break;
        case 'k' :
            eyeZ = (eyeZ + 5) % 360;
            glutPostRedisplay();
            break;
		default:
			break;
	}
}
*/


