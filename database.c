#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NLEN  30
#define FLEN  35
#define ELEN  40
#define PLEN  14

//Function Prototypes
void input_name();
void error(char *);
void signup();
void login();
void show_user_info();
void what_to_do();
void show_user_info(); 
//void show_bookings();
void show_all_bookings();
void book_slot();
void logout();
void del_acc();


//Global variables
FILE *fp = NULL;
char file[FLEN];
char slots_file[FLEN];

struct usr
{
  char user_name[NLEN];
  char fullname[NLEN];
  char email[ELEN];
  char passwd[PLEN];
  char phno[11];
  int age;
  float from_time;
  float to_time;
  int booked_slots;
}user;

struct booked
{
  char user[NLEN];
  float from_time;
  float to_time;
}slots;


//Main function
int main()
{
  int ch = -1;

  strcpy(slots_file, "./users/"); //Every user maintains his/her own file 
  strcat(slots_file, "booked_slots"); //under the directory 

  while (ch > 2 || ch < 1) //Loop until a valid number us picked
  {
      printf("1.SIGNUP.\n");
      printf("2.LOGIN.\n");
      printf("Enter your choice: ");
      scanf("%d", &ch);
  }
  if (ch == 1)
  {
      signup(); //Call the signup function to register new user
      login();  //then call the login funciton for the new use to login
  }
  else if(ch == 2)
  {
      login();  //call the login function to login
  }

  exit (0);
}

//A function to print errors
void error(char *msg)
{
  char err_msg[31];
  strcpy(err_msg, "[!!]Fatal error ");
  strcat(err_msg, msg);
  perror(err_msg); //Print error

  exit(1);
}

//Function to register new user
void signup()
{
  int len = 0;
  char pass1[PLEN], pass2[PLEN];

  printf("\n\n-=-=-=-=\x1b[33mSIGN UP\x1b[0m=-=-=-=-\n\n");

  printf("Your Full Name: ");
  input_name(); //Something like gets function in windows
  printf("Your age: ");
  scanf("%d", &user.age);
  printf("Your Email: ");
  scanf("%s", user.email);

  while (1) //Loop infinitely
  {
      printf("Your Phone Number: ");
      scanf("%s", user.phno);
      len = strlen(user.phno);
      if (len != 10) //If phno is not of len 10 then loop again
      {
          printf("Invalid Phone Number....Try again\n");
	  continue;
      }
      else //If phno is of length 10 then accept it and break the loop 
      {
          break;
      }
  }
  printf("set user name: ");
  scanf("%s", user.user_name);

  while(1) //Loop infinitely
  {
      printf("Set a passsword: "); //get password
      scanf("%s", pass1);
      printf("re-enter passsword: "); //get the confirmation password
      scanf("%s", pass2);
      if(strcmp(pass1, pass2) == 0) //If both are same then accept and break
      {
          strcpy(user.passwd, pass1);
          break;
      }
      else //If not same then loop again
      {
          printf("passwords are not same...try again\n");
          continue;
      }
  }
 
  strcpy(file, "./users/"); //Every user maintains his/her own file 
  strcat(file, user.user_name); //under the directory 
  printf("File: %s\n", file);
  
  fp = fopen(file, "w"); //Open the file in write mode
  if (fp == NULL) //Error checking
  {
      error("While opening file"); //call the error checking function
  }
  
  fwrite(&user, sizeof(struct usr), 1, fp); //Write the user data into the file
  fclose(fp);//close the file
  printf("Resistered successfully\n");
  return;
}

//To accept the name with spaces
void input_name()
{
  char *name_ptr, input_char = '\n';

  while (input_char == '\n')
	  scanf("%c", &input_char);

  name_ptr = (char *) &(user.fullname);
  while (input_char != '\n')
  {
      *name_ptr = input_char;
      scanf("%c", &input_char);
      name_ptr++;
  }
  *name_ptr = 0;

  return;
}

void login()
{
  char uname[NLEN], pass[PLEN];
  int trails = 0;

  strcpy(file, "./users/"); //Folder to maintain user files

  printf("\n\n-=-=-=-=\x1b[33mLOGIN\x1b[0m=-=-=-=-\n\n");

  printf("Enter your user name: ");
  scanf("%s", uname);

  strcat(file, uname);
  fp = fopen(file, "r");
  if (fp == NULL) //If the user file doesn't exist
  {
      printf("No such user!!");
      printf("It seems you are a new user..Go a head and signup\n");
      signup();
  }
  else
  {
      fread(&user, sizeof(struct usr), 1, fp);
      while (trails < 3)
      {
          printf("Enter password: ");
          scanf("%s", pass);
          if (!strcmp(pass, user.passwd))
          {
              printf("Welcome!! %s\n", user.fullname);
	      what_to_do();
              return;
          }
          else
          {
	      trails++;
	      if (trails == 3)
              {
	          printf("Tried too many times. Try After sometime\n");
                  return;
              }
              printf("Wrong pasword...Try again\n");
          }
      }
  }
  fclose(fp);
  return;
}

void show_user_info()
{
  printf("\n\n\x1b[32mUser Info\x1b[0m\n\n");
  printf("fullname: %s\n", user.fullname);
  printf("email: %s\n", user.email);
  printf("user name: %s\n", user.user_name);
  printf("ph no: %s\n", user.phno);
  printf("age: %d\n", user.age);
  
  return;
}

void what_to_do()
{
  int choice = -1;

  while(choice != 5)
  {
      while(choice < 1 || choice > 6)
      {
          printf("\n1. Show your info.\n");
          printf("2. Show Booked slots by you.\n");
          printf("3. Show All booked slots\n");
          printf("4. Book a slot.\n");
          printf("5. Logout\n");
	  printf("6. Delete your account.\n");
          printf("Enter your choice: ");
          scanf("%d", &choice);
      }

      switch(choice)
      {
          case 1 : show_user_info();
                   break;
          case 2 : //show_bookings();
                   break;
          case 3 : show_all_bookings();
                   break;
          case 4 : book_slot();
                   break;
          case 5 : logout();
                   break;
          case 6 : del_acc();
                   break;
      }
      choice = -1;
  }
  return;
}

void logout()
{
  printf("Thanks for using..Comeback soon..Bye\n");
  exit (0);
}

void del_acc()
{
  int op;

  printf("Removing your account will erase all your data.!\n");
  printf("Are you really sure?\n ");
  printf("\b1. Yes\n");
  printf("2. No\n");
  scanf("%d", &op);
  if (op == 1)
  {
      printf("Are you really sure?\n");
      printf("1. Yes\n");
      printf(" 2. No\n");
      scanf("%d", &op);

      if(op == 1)
      {
          printf("Cleaning all the data....\n");
	  sleep(2);
	  printf("Deleting your account...\n");
	  sleep(2);
	  printf("File: %s\n", file);
	  if(remove(file) == -1)
	  {
	      error("While removing account!!\n");
	  }
	  printf("Deleted Successfully\n");
	  exit (0);
      }
      else
      {
          printf("OK!!\n");
      }
  }
  else
  {
      printf("OK!!\n");
  }
  return;
}

void book_slot()
{
  printf("\n\nSlot Booking Counter\n\n");
  printf("You can book any available slots from 9.00 Am to 5.00 Am\n");
  printf("!(Seperate hours and time with \".\")!\n");
  printf("For eg:  9.00   8.30 ..etc\n\n");
  printf("Enter from time: ");
  scanf("%f", &user.from_time);
  printf("Enter to time: ");
  scanf("%f", &user.to_time);
  user.booked_slots++;

  fp = fopen(file, "w"); //Open the file in write mode
  if (fp == NULL) //Error checking
  {
      error("While opening file"); //call the error checking function
  }
  
  fwrite(&user, sizeof(struct usr), 1, fp); //Write the user data into the file
  fclose(fp);//close the file

  strcpy(slots.user, user.user_name);
  slots.from_time = user.from_time;
  slots.to_time = user.to_time;

  printf("slots file : %s\n", slots_file);
  fp = fopen(slots_file, "a");
  if (fp == NULL) //Error checking
  {
      error("While opening slots file"); //call the error checking function
  }
  
  fwrite(&slots, sizeof(struct booked), 1, fp); //Write the booking data into the file
  fclose(fp);//close the file

  show_all_bookings();

  return;
}

void show_all_bookings()
{
  fp = fopen(slots_file, "r");
  if (fp == NULL)
  {
      error("While opening slots file");
  }
  fread(&slots, sizeof(struct booked), 1, fp);
  printf("User: %s\n", slots.user);
  printf("From %f\n", slots.from_time);
  printf("To %f\n", slots.to_time);
  return;
}
