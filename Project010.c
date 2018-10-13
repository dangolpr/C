    /***********************************************************************
     * Name(s) Priyanka Dangol, Andrew Park                                *
     * Box(s): 3364, 4336                                                  *
     * Assignment name module 010: Uninterpretable Dance Project           *
     * Assignment for Fri, Mar 2, 2018                                     *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *  Written/online sources used:                                       *
     *   An Introduction to Simulations (Walker, 2016)                     *   
     *   mortage-good-comments.c                                           *
     *   Help obtained                                                     *
     *     Professor Henry Walker                                          *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <eSpeakPackage.h>
#include <MyroC.h>

/* This program is intended to perform a randomized dance that is
composed of 5 dance sequences.*/

void danceMove1(double times[], double speeds[]);
void danceMove2(double halfSec, int freq);
void danceMove3(int * pitch);
void danceMove4();
void danceMove5(double durationOne []);

/* randomly chooses and executes dance moves 5 times */
int main()
{
  /*initializes the scribbler robot and eSpeak*/
  rConnect("/dev/rfcomm0");
  eSpeakConnect();

  /* arrays indicate the different levels of speed and duration that are 
     passed on to the dance functions */
  double speed[5] = {0.2, 0.4, 0.6, 0.8, 1.0};
  double duration[5] = {0.2, 0.4, 0.6, 0.8, 1.0}; 
  double halfSecond = 0.5;
  int freq = 700; 

  printf("I am going to dance!\n"); 
  /*initializes random number generator*/
  /*change the seed to the random number generator, based on time of the day */
  srand (time ((time_t *) 0) );
  
  /*carries out five random dance sequences*/
  for(int counter=0; counter<5; counter++)
    {
      /*gets a random number between 1 and 5 and passes it to func*/
      int func = (5 * ((double) rand() / (double) RAND_MAX)) + 1;
      printf("Performing Dance # %d\n", func);

      /*uses func to choose which dance function to execute*/
      switch(func)
        {
        case 1:
          danceMove1(duration, speed);
          break;
        case 2:
          danceMove2(halfSecond, freq);
          break;
        case 3:
          danceMove3(&freq);
          break;
        case 4:
          danceMove4();
          break;
        case 5:
          danceMove5(duration);
          break;
        } 
    }
  printf("Thank you for watching!\n"); 
  /* disonnects from scribbler robot and eSpeak */
  rDisconnect();
  eSpeakDisconnect();
  
  return 0; /* program ran without error */
}

/*pre-condition: count is not greater than the length of duration array
                 count is not greater than the length of speed array
                 
  post-condition: does not return a value  
                  the workstation remains connected to the robot 
                  when called, it moves forward and turns right at 
                   random speeds and lengths, ranging from 0.2 to 
                   1.0 for 5 times. 
 */

void danceMove1(double times[], double speeds[])
{
  eSpeakTalk("dance move 1");
  
  srand (time ((time_t *) 0) );
  
  for(int count=0; count<5; count++) {
    
    int ran = 6 * ((double) rand() / (double) RAND_MAX); 
    rForward (speeds[ran], times[ran]);
    rTurnRight (speeds[ran], times[ran]);
    
  }
}

/*pre-condition: the program has already connected to a robot
                 freq is a non-negative integer 
  
  post-condition: does not return a value
                  the workstation remains connected to the robot
                  when called, it turns left, forward, beeps once at freq,
                  and then turns right, forward, beeps once at freq once more 
 */

void danceMove2(double halfSec, int freq)
{
  eSpeakTalk("dance move 2");
  
  rTurnLeft(1.0, halfSec);
  rForward(1.0, halfSec);
  rBeep(0.5, freq);
  
  rTurnRight(1.0, halfSec);
  rForward(-1.0, halfSec);
  rBeep(1.0, freq);
}

/*pre-condition: the program has already connected to a robot
                 pitch is the address of freq 
  
  post-condition: does not return a value
                  the workstation remains connected to the robot
                  when called, it moves forward 4 times, beeps once at *pitch,
                   and then turns right, left, and right then beeps two times at                   *pitch 
 */

void danceMove3(int * pitch)
{
  eSpeakTalk("dance move 3");

  /* increases the value stored in the address that is stored in pitch, which is freq, by 150 */
  *pitch += 150;
  
  rForward(1.0, 0.3);
  rForward(-1.0, 0.4);
  rForward(1.0, 0.3); 
  rForward(-1.0, 0.4);
  rBeep(0.5, *pitch);

  rTurnRight(1.0, 0.5);
  rTurnLeft(1.0, 0.3);
  rTurnRight(1.0, 0.3);

  rBeep(0.5, *pitch);
  rBeep(0.5, *pitch);
}

/*pre-condition: none
  
  post-condition: does not return a value
                  the workstation remains connected to the robot
                  when called, it beeps once, moves forward, then turns left 4 
                  times, turns right 4 times, and lastly moves forward once. 
 */

void danceMove4()
{
  eSpeakTalk("dance move 4");
  
  rBeep(0.5, 700);
  rForward(1.0, 1.0);
  
  /* robot turns left and right 4 times for each turn. */
  for(int count=0; count<4; count++)
    {
      rTurnLeft(1.0, 0.2);
    }
  for(int count=0; count<4; count++)
    {
      rTurnRight(1.0, 0.3);
    }
  rForward(-1.0, 1.0); 
}

/*pre-condition: count is not greater than the length of duration array 
                  
  post-condition: does not return a value
                  the workstation remains connected to the robot
                  when called, it  moves forward, beeps, and then moves forward                   again with the duration of durationOne[count]
 */

void danceMove5(double durationOne [])
{
  eSpeakTalk("dance move 5");
  
  /* increases duration of moving forward by 0.2 */
  for (int count=0; count<3; count++)
    {
      rForward(-1.0, 0.5);
      rBeep(0.5, 600);
      rForward(1.0, durationOne[count]);
    }
}
