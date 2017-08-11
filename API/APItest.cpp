/* A simple program to demonstrate the C/C++ API of Geomodeller
 * 
 * On Linux, GCC V4.3 or later is needed to compile.
 * Use the following steps to build and run the example program:
 *
 * 1. gcc -o APItest APItest.cpp -I%{INSTALL_PATH}/tutorial/API/ -L%{INSTALL_PATH}/bin/ -lgeomodellerapi -lstdc++ -lm -pthread
 * 2. cp APItest {INSTALL_PATH}/bin
 * 3. Launch GeoModeller
 * 4. Open GeoModeller project TutorialA1.xml in directory {install_directory>/tutorial/API/TutorialA1
 * 3. Use Geophysics/3D Geophysics/Shell Window to open a window with the correct runtime enviroment.
 * 4. Run APItest from within that window
 *
 * On Windows, VC2012 or later is needed to compile
 * 1. Unzip VStudioProject.zip and open APIexample.sln and configure it to build Release/x64
 * 2. copy x64\Release\APIexample.exe {INSTALL_PATH}/bin
 * 2. Open GeoModeller project TutorialA1.xml in directory {install_directory>/tutorial/API/TutorialA1
 * 3. Use Geophysics/3D Geophysics/Shell Window to open a window with the correct runtime enviroment.
 * 4. Run APIexample.exe
 *
 * (c) Intrepid Geophysics, 2015
 */

#include "geomodeller-c-api.h"
#include <stdio.h>

int compute(void);

#ifdef WIN32
#include "stdafx.h"
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char **argv, char **envp)
#endif
{
  double xmin, ymin, zmin, xmax, ymax, zmax;

  // set up licensing - querying models is allowed for anyone, write access needs a valid licence
  gmapi_initialiseReadAPI();
  gmapi_initialiseWriteAPINoArgs();

  // open the project without displaying it
  if(gmapi_openProjectWithoutDisplay("./TutorialA1.xml") != 0 )
  {
    return -1;
  }

  printf("\nGeomodeller 3D API test...\n\n");

  // get the model bounds and print to stdout
  gmapi_getModelBounds(xmin, ymin, zmin, xmax, ymax, zmax);
  printf("ModelBounds MIN xmin=%lf ymin=%lf zmin=%lf\n", xmin, ymin, zmin);
  printf("ModelBounds MAX xmax=%lf ymax=%lf zmax=%lf\n\n", xmax, ymax, zmax);

  // compute the model, see below
  if(compute() != 0)
  {
    return -1;
  }

  // query the lithology at a certain point
  double posx  =  104000.0;
  double posy  = 2002880.0;
  double posz  =    -100.0;
  int    litho =         0;
  gmapi_getComputedLithologyXYZ(posx, posy, posz, litho);
  printf("Lithology at x = %f y = %f z = %f is %d\n\n", posx, posy, posz, litho);

  // add a new interface to a formation
  double pntx =  104320.0;
  double pnty = 2002880.0;
  double pntz =     513.0;
  gmapi_add3dInterface("UpperCover", pntx, pnty, pntz);
  printf("Adding interface point at  x = %f y = %f z = %f to formation \"UpperCover\"\n\n", pntx, pnty, pntz);

  // compute the new geological model
  if(compute() != 0)
  {
    return -1;
  }

  // query the lithology at the same point again
  gmapi_getComputedLithologyXYZ(posx, posy, posz, litho);
  printf("Lithology at x = %f y = %f z = %f is %d\n\n", posx, posy, posz, litho);

  return 0;
}

int compute(void) 
{
  // clear the list of sections/series/faults that are used to compute the geological model
  gmapi_clearThisModel();

  // Define the sections we want to include in the computation of the model
  // The keyword "all" includes all sections present in the project. 
  if(gmapi_addSectionToModel("all") !=0 )
  {
    printf("Error while adding section...\n");
    return -1;
  }

  // Define the series we want to include in the computation of the model
  // The keyword "all" includes all series present in the project. 
  if(gmapi_addSeriesToModel("all") !=0 )
  {
    printf("Error while adding series...\n");
    return -1;
  }

  // compute the geological model with the data defined above
  gmapi_computeThisModel();

  return 0;
}
