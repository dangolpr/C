 /***********************************************************************
     * Name(s)  Andrew Park, Priyanka Dangol                               *
     * Box(s):  4336 , 3364                                                *
     * Assignment name: module 100:Image Processing Project                *
     * Assignment for  Apr 10, 2018                                     *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     swap-red-blue.c (Walker, 2014)                                  *
     *     Laboratory Exercise on Transforming Pictures (Walker, 2014)     *    
     *                                                                     *
     *   Help obtained                                                     *
     *     Professor Walker (for pictureRedder)                            *
     *     Vidush Goswami and Vijeeth Guggilla (for circleSelect)          *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/

#include <stdio.h>
#include "MyroC.h"
#include <math.h>
#include <string.h>

/*set the R, G, or B value of every pixel in the picture
 to 0 (depending on what char color is)*/
void pixelStrip (Picture * pic, char color);

/*increases the intensity of red but not past 255*/
void pictureRedder (Picture * pic);

/*increases the intensity of green but not past 255*/
void pictureGreener (Picture * pic);

/*increases the intensity of blue  but not past 255*/
void pictureBluer (Picture * pic);

/*select a circle from your picture and turn each pixel
within that circle to the corresponding grayscale value*/
void circleSelect (Picture * pic, int xCenter, int yCenter, int radius);

/*creates a picture composed of first half of the first picture
and second half of the second picture */
void mergePictures (Picture pics[]);


/*  processes all the procedure options that 
can process image in various ways*/

/* pre-conditions:  
   * the program must be connected to a robot

   post-conditions: 
   * must produce output of the procedure called 
   
   */
int main ()
{
  rConnect ("/dev/rfcomm0");

  char colour;
  Picture pic;

  int xCirc,yCirc,rad;
  pic = rTakePicture();

  /* Uncomment to use any steps */
  
  //1. PixelStrip: replaces R,G, or B with 0 
  // Asking user for pixelStrip color 
  /*printf("Please enter a color (R, G, or B): ");
  scanf("%c", &colour);
  printf("You entered: %c \n", colour);
 
  rDisplayPicture (&pic, 10, "Original"); 
  rSavePicture (&pic, "Original");
  pixelStrip(&pic, colour); 
  rDisplayPicture (&pic, 10, "pixelStrip");
  rSavePicture (&pic, "strippedColour");*/

  // 2. Redder
  /*rDisplayPicture (&pic, 2, "RedOriginal"); 
  rSavePicture (&pic, "RedOriginal");
  for(int i=0; i<100; i++)
  {
      pictureRedder(&pic);
  }
  rDisplayPicture (&pic, 2, "pictureRedder");
  rSavePicture (&pic, "pictureRedder");*/

  //3. Greener
  /*rDisplayPicture (&pic, 2, "GreenOriginal"); 
  rSavePicture (&pic, "GreenOriginal");
  for(int i=0; i<100; i++)
    {
      pictureGreener(&pic);
    }
  rDisplayPicture (&pic, 2, "pictureGreener");
  rSavePicture (&pic, "pictureGreener");*/

  //4. Bluer
  /*rDisplayPicture (&pic, 2, "BlueOriginal"); 
  rSavePicture (&pic, "BlueOriginal");
  for(int i=0; i<100; i++)
    {
      pictureBluer(&pic);
    }
  rSavePicture (&pic, "pictureBluer");
  rDisplayPicture (&pic, 2, "pictureBluer");*/
  
  //5. selectCircle
  /*printf("Please enter the x coordinate of the circle: ");
  scanf("%d", &xCirc);
  printf("Please enter the y coordinate of the circle: ");
  scanf("%d", &yCirc);
  printf("Please enter the radius of the circle: ");
  scanf("%d", &rad);  

  rDisplayPicture (&pic, 2, "Originalcircle");
  rSavePicture (&pic, "Originalcircle");
  circleSelect(&pic, xCirc, yCirc, rad); 
  rDisplayPicture (&pic, 2, "circle");
  rSavePicture (&pic, "circle");*/

  // 6. Creative procedure: mergePictures 
  /* Picture pics [2];
  pics[0] = rTakePicture ();
  rForward (1.0, 2.0);
  rTurnRight (1.0, 1.0);
  pics[1] = rTakePicture ();

  rDisplayPicture (&pics[0], 2, "Original picture 0");
  rSavePicture (&pics[0], "ZeroPicture");
  rDisplayPicture (&pics[1], 2, "Original picture 1");
  rSavePicture (&pics[1], "FirstPicture");
  mergePictures (pics);
  rDisplayPicture (&pics[0], 2, "Transformed picture 0");
  rSavePicture (&pics[0], "Merged");*/
  
  rDisconnect();
  return 0;
}


/* the user inputs a color (R, G, or B) then makes 
the value to be 0 in the picture*/

/* pre-conditions:  
   * color must be char, either 'R', 'G', or 'B'
   * robot must take a picture

   post-conditions: 
   * If color == 'R', red component of picture must be 0
   * If color == 'G', green component of picture must be 0
   * If color == 'B', blue component of picture must be 0
   */
void pixelStrip (Picture * pic, char color)
{
  //change the character entered bby the user to uppercase
  color = toupper(color);
  int i, j, width, height;
  height = (*pic).height;
  width = (*pic).width;

  //removes the specified color from every pixel in the photo
  for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
        {
          if(color == 'R')
            {
              (*pic).pix_array[i][j].R =0;
            }
          else if(color == 'G')
            {
              (*pic).pix_array[i][j].G = 0;
            }
          else if(color == 'B')
            {
              (*pic).pix_array[i][j].B = 0;
            }
        }
    }
}

/* intensifies red component of picture */

/* pre-conditions:  
   * robot must take picture

   post-conditions: 
   * red component must intensify more if red component is low
   * red component must intensify less if red component is already high
*/
void pictureRedder (Picture * pic)
{
  int i, j, width, height;
  height = (*pic).height;
  width = (*pic).width;
 
  for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
        {
          (*pic).pix_array[i][j].R = (*pic).pix_array[i][j].R + (254 / ((*pic).pix_array[i][j].R + 1));}
    }
}

/* intensifies blue component of picture */

/* pre-conditions:  
   * robot must take picture

   post-conditions: 
   * blue component must intensify more if blue component is low
   * blue component must intensify less if blue component is already high
*/
void pictureBluer (Picture * pic)
{
  int i, j, width, height;
  height = (*pic).height;
  width = (*pic).width;
 
  for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
        {
          (*pic).pix_array[i][j].B = (*pic).pix_array[i][j].B + (254 / ((*pic).pix_array[i][j].B + 1));
        }
    }
}

/* intensifies green component of picture */

/* pre-conditions:  
   * robot must take picture

   post-conditions: 
   * green component must intensify more if green component is low
   * green component must intensify less if green component is already high
*/
void pictureGreener (Picture * pic)
{
  int i, j, width, height;
  height = (*pic).height;
  width = (*pic).width;
 
  for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
        {
          (*pic).pix_array[i][j].G = (*pic).pix_array[i][j].G + (254 / ((*pic).pix_array[i][j].G + 1));
        }
    }
}

/* selects a circle and changes color within circle
to corresponding grayscale */

/* pre-conditions:  
   * robot must take picture
   * xCenter must be an integer greater than 0 and less than 256
   * yCenter must be an integer greater than 0 and less than 192
   * radius must be an integer 
   
   post-conditions: 
   * selects a circle size based on user input then changes
      the RGB components of pixels inside the circle to corresponding 
      grayscale. 
*/
void circleSelect(Picture * pic, int xCenter, int yCenter, int radius)
{
  int i, j, width, height;
  height = (*pic).height;
  width = (*pic).width;
  Pixel blackpix = {0, 0, 0};
  
  for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
        {
          if(sqrt((pow((xCenter - i), 2.0)) + (pow((yCenter - j), 2.0))) <= radius)
            {
              (*pic).pix_array[i][j].R *= .30;
              (*pic).pix_array[i][j].G *= .59;
              (*pic).pix_array[i][j].B *= .11;            
 
              int comp = (*pic).pix_array[i][j].R + (*pic).pix_array[i][j].G + (*pic).pix_array[i][j].B;
                
              Pixel grayscale = {comp, comp, comp};
              (*pic).pix_array[i][j] = grayscale; 
            }
        }
    }
}

/* creates a picture composed of first half of the first picture
and second half of the second picture */ 

/* pre-conditions:  
   * robot must take pictures corresponding to the length of pics[] array
      robot must take two pictures

   post-conditions: 
   * second half width of first picture is changed to the second half 
      width of the second picture
*/
void mergePictures(Picture pics[])
{
  int i, j, width, height;
  double midWidth;
  height = pics[0].height;
  width = pics[0].width;
  midWidth = width / 2;
  
  for(i = 0; i < height; i++)
    {
      //replaces the pixels in the second half of the first picture with the
      //pixels in the second half of the second picture
      for(j = midWidth; j < width; j++)
        {
        pics[0].pix_array[i][j] = pics[1].pix_array[i][j];
        }
    }
}

  
