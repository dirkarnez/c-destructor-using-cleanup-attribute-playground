# include <stdio.h>

/* Demo code showing the usage of the cleanup variable
   attribute. See:http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html
*/

/* cleanup function
   the argument is a int * to accept the address
   to the final value
*/

void clean_up(int *final_value)
{
    printf("Final value: %d\n",*final_value);
  printf("Cleaning up\n");

}

typedef struct {
    int a;
} OBJ;

void clean_up_obj(OBJ *final_value)
{
    printf("Final value: %d\n",(*final_value).a);
  printf("Cleaning up\n");

}
int main(int argc, char **argv)
{
  /* declare cleanup attribute along with initiliazation
     Without the cleanup attribute, this is equivalent 
     to:
     int avar = 1;
  */
  
  int avar __attribute__ ((__cleanup__(clean_up))) = 1;
  avar = 5;


    OBJ obj __attribute__ ((__cleanup__(clean_up_obj))) = { .a = 10 };

  

  return 0;
}
