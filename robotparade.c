#include <string.h>
#include <stdio.h>
#include "MyroC.h"
#include "scale-notes.h"
#include <time.h>

/*
  This program makes the robot follow a common script that specifies actions 
  along a pre-determined route or it allows the user to chose  amongst a list 
  of preset option. It allows them to run various commands and works until the 
  user types quit or until the program reads quit from the file. */


/* makes the robot play a set song */
/* pre-conditions : robot must be on
   post-conditions: the robot plays a song once */
void rsong (int repeat);

/* prints the commands and its parameters, the time and the light sensor *
 * readings into a file specified by the user from command line          */
/* pre-conditions : robot must be on                          *
 *                  logFile is a pre-existing file, type FILE *
 * post-conditions: each command performed will be logged in the file *
 *                  only commands that were performed will be logged in the file*/  

void logging (FILE * logFile, char command[], double par1, double par2);

int main(int argc, char * argv[])
{
  
  // initializes the robot
  rConnect ("/dev/rfcomm0");
  
  //The user presses enter to start the robot
  char start; 
  printf("Press Enter to start \n");
  scanf ("%c", &start);
  if (start == '\n')
    {
      rMotors(0.25, 0.25);
    }
  //The user presses enter to make the robot move after crossing the start line
  printf("Press Enter to stop  \n");
  scanf ("%c", &start);
  if (start == '\n')
    {
      rMotors(0.0,0.0);
    }
  
  /* add variable to identify reading source */
  FILE * inputSource = stdin;
  FILE * logfile = NULL;

  
  for (int i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "-input") == 0)
        inputSource = fopen(argv[i+1],"r");
      else if (strcmp (argv[i], "-log") == 0)
        {
          logfile = fopen (argv[i+1], "w");
          fprintf (logfile, "                                              sensor  sensor   sensor \n");
          fprintf (logfile, "command (par1 par2)   time                    Left    Middle   Right \n");
        }
      else
        printf ("unrecognized command-line argument\n");
    }
 
  // declares variables to be used within the loop 
  double speed;
  double duration;
  double frequency;
  int repeat;
  int counter = 0;
  
  // declares an array of chars to be assigned user input
  char option[10];

  // the program loops as long as the user does not input 'quit'
  while (!(strcmp (option, "quit") == 0))
    {
      // prints menu table 
      printf ("This program makes the robot obey your every command. \n");
      printf ("Menu Options\n");
      printf ("  forward \n");
      printf ("  backward \n");
      printf ("  turnRight \n");
      printf ("  turnLeft \n");
      printf ("  beep  \n");
      printf ("  song  \n");
      printf ("  quit \n");
      printf ("Enter option:  ");

      fscanf(inputSource, " %s", option);
      printf(" %s \n", option);


      /* makes the robot move forward according to the speed and duration
         supplied by the user */
      if (strcmp (option, "forward") == 0)
        {
          if (inputSource == stdin)
            printf(" enter speed and duration \n");
          fscanf(inputSource, " %lf %lf", &speed, &duration);
          rForward (speed,duration);
          logging (logfile, "forward", speed, duration);
        }

      /* makes the robot move backward according to the speed and duration
         supplied by the user */
      else if (strcmp (option, "backward") == 0)
        {
          if (inputSource == stdin)
            printf(" enter speed and duration \n");
          fscanf(inputSource, " %lf %lf", &speed, &duration);
          rBackward (speed, duration);
          logging (logfile, "backward", speed, duration);
        }

      /* makes the robot turn right according to the speed and duration
         supplied by the user */
      else if (strcmp (option, "turnRight") == 0)
        {
          if (inputSource == stdin)
            printf(" enter speed and duration \n");
          fscanf(inputSource, " %lf %lf", &speed, &duration);
          rTurnRight (speed,duration);
          logging (logfile, "turnRight", speed, duration);
           
        }

      /* makes the robot turn left according to the speed and duration
         supplied by the user */
      else if (strcmp (option, "turnLeft") == 0)
        {
          if (inputSource == stdin)
            printf(" enter speed and duration \n");
          fscanf(inputSource, " %lf %lf", &speed, &duration);
          rTurnLeft (speed,duration);
          logging (logfile, "turnLeft", speed, duration);
        }

      /* makes the robot beep according to the duration and frequency
         supplied by the user */
      else if (strcmp (option, "beep") == 0)
        {
          if (inputSource == stdin)
            printf(" enter duration and frequency \n");
          fscanf(inputSource, " %lf %lf", &duration, &frequency);
          rBeep (duration,frequency);
          logging (logfile, "beep", duration, frequency);
        
        }
      //plays the song for 'repeat' number of times
      else if (strcmp (option, "song") == 0)
        {
          if (inputSource == stdin)
            printf(" enter no. of repetitions \n");
          fscanf(inputSource, " %d", &repeat);
          rsong(repeat);
          logging (logfile, "rsong",repeat, 0);
        }
      
      else if (strcmp (option, "quit") == 0)
        logging (logfile, "quit", 0, 0);
      
      counter++;
      printf ("\n"); 
    }

  rForward(0.25, 10); 
  printf ("The robot has performed %d command(s), including quit \n", counter--);
  printf ("Program has ended.\n  ");

  //closes the files
  if (inputSource != stdin)
    {
      fclose(inputSource);
      fclose(logfile);
    }

  rDisconnect();
  return 0;    
}


void rsong(int repeat)
{
  //loops the two second song for repeat number of times
  for (int i=0; i<repeat; i++)
    {
      rBeep(.4,pitchE4);
      rBeep(.4,pitchGs6);
      rBeep(.2,pitchB4);
      rBeep(.6,pitchGs6);
      rBeep2(.4,pitchCs6,pitchCs4);
    }
}

void logging (FILE * logFile, char command[], double par1, double par2)
{
  /* determine time and print it */
  time_t mytime = time (NULL);
  char * timeStr = ctime (&mytime);
  if (logFile == NULL)
    {
      return;
    }
  else
    {
      /*remove '\n' at end of time string, if present */
      if (timeStr[strlen(timeStr)-1] == '\n')
        {
          timeStr[strlen(timeStr)-1] = 0;
        }

      //get the reading from three sensors in the robot
      int sensorLeft = rGetLightTxt ("left", 5);
      int sensorMiddle = rGetLightTxt ("middle", 5);
      int sensorRight = rGetLightTxt ("right", 5);

      //prints the line with the command, parameters, time, and the three sensors
      if (par2 == 0)
        {
          fprintf (logFile, "%s [%0.2lf] %6s (%6d,%6d,%6d) \n", command, par1, timeStr, sensorLeft, sensorMiddle, sensorRight);
        }
      else
        {
          fprintf (logFile, "%s [%0.2lf, %0.2lf] %6s (%6d,%6d,%6d) \n", command, par1, par2, timeStr, sensorLeft, sensorMiddle, sensorRight);

        }
    }
}
