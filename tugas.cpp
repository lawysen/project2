#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

int no_of_users;

void print_all_user();
void register_menu();
void login_menu();
void main_menu();
void user_page(int user_index);
void add_friend(int user_index);
void remove_friend(int user_index);
void view_inbox(int user_index);
void view_sent_request(int user_index);

int ada =0;


struct User{
  char username[25];
  char password[25];
  User *next;
  User *prev;
} *head,*tail;

User user[10000];

User *createUser(const char *username){
	User *newUser = (User*)malloc(sizeof(user));
	strcpy(newUser -> username, username);
		
		newUser -> next = NULL;
		newUser -> prev = NULL;
		return newUser;
}

void pushTail(const char *username){
    User *temp = createUser(username);
    if(!head){
        head = tail = temp;
    }
    else{
        temp ->prev = tail;
        tail->next = temp;
        tail = temp;
    }

}

void popMid(const char *name){

    if(!head){
        return;
    }

    else if(strcmp(name,head->username) == 0){
        ada++;
    }
    else if(strcmp(name,tail->username) == 0){ 
        ada++;
    }
    else{ 
        User *curr = head;
        while(curr != NULL && strcmp(name,curr->username) != 0){
            curr = curr->next;
        }

        if(!curr){
            printf("Tidak Ketemu\n");
            return;
        }
        
    }
}

int main(){
  no_of_users=0;
  main_menu();
  return 0;
}

void main_menu(){
  system("cls");
  printf("Oo=====================================oO\n");
  printf("              STUDY NETWORK\n");
  printf("Oo=====================================oO\n\n");
  printf("[All User]\n");
  printf("No.    Username\n");
  print_all_user();
  printf("\n-----------------------------------------\n");
  printf("[1] Register\n");
  printf("[2] Login\n");
  printf("[3] Exit\n");
  printf("-----------------------------------------\n");
  printf("Press 0 and enter to abort an operation\n");
  printf("-----------------------------------------\n");
  printf(">> ");
  int number_input;
  while(number_input>=1 || number_input<=3){
    scanf("%d", &number_input); getchar();
    if(number_input==1){
      no_of_users++;
      register_menu();
    }else if(number_input==2){
      login_menu();
    }else if(number_input==3){
      printf("You exit the program");
      exit(0);
    }else{
      printf("-----------------------------------------\n");
      printf("Invalid input, choose a number between 1 to 3\n");
      printf("-----------------------------------------\n");
      printf(">> ");
    }
  }
}

void print_all_user(){
  if(no_of_users>=1){
  int angka =1;
  User *curr = head;
  while(curr){
  	printf("%d.	%s\n",angka,curr -> username);
  	curr = curr -> next;
  	angka++;
  }
}
}

void register_menu(){
  bool is_username_unique=false;
  while(!is_username_unique){
    printf("-----------------------------------------\n");
    printf("Please type in your username [lowercase || 1..24]: ");
    scanf("%[^\n]", user[no_of_users-1].username); 
	getchar();
	pushTail(user[no_of_users-1].username);
    printf("Please type in your password [lowercase || 1..24]: ");
    scanf("%[^\n]", user[no_of_users-1].password); getchar();
  
    is_username_unique=true;
    for(int i=0; i<no_of_users-1; i++){
      if(strcmp(user[i].username, user[no_of_users-1].username)==0){
        is_username_unique=false;
        break;
      }
    }
    if(is_username_unique){
      printf("\n--- Registration Successfull ---\n");
      printf("Press enter to continue!\n");
      getchar();
      main_menu();
    }else{
      printf("\nError, that username already exists!\n");     
    }
  }
}

void login_menu(){
  char input_username[25], input_password[25];
  bool is_login_correct=false;
  while(!is_login_correct){
    printf("-----------------------------------------\n");
    printf("Username: ");
    scanf("%[^\n]", input_username); getchar();
    printf("Password: ");
    scanf("%[^\n]", input_password); getchar();

    int i;
    for(i=0; i<no_of_users; i++){
      if(strcmp(user[i].username, input_username)==0 && strcmp(user[i].password, input_password)==0){
        is_login_correct=true;
        break;
      }
    }
    if(is_login_correct){
      printf("\n--- Login Successfull ---\n");
      printf("Press enter to continue!\n");
      getchar();
      user_page(i);
    }else{
      printf("\nError, Incorrect Username and/or Password!\n");
    }
  }

}

void user_page(int user_index){ 
  system("cls");
  printf("Oo=====================================oO\n");
  printf("Welcome, %s!\n", user[user_index].username);
  printf("Oo=====================================oO\n");
  time_t current_date_and_time;
  time(&current_date_and_time);
  printf("Logged in: %s\n", ctime(&current_date_and_time));
  printf("-----------------------------------------\n");
  printf("[All Friends of %s]\n", user[user_index].username);
  printf("No. Username\n");
 
  printf("\n-----------------------------------------\n");
  printf(" >>Menu<<\n");
  printf("-----------------------------------------\n");
  printf("[1] Add Friend\n");
  printf("[2] Remove Friend\n");
  printf("[3] View Inbox\n");
  printf("[4] View Sent Request\n");
  printf("[5] Add, Edit, Announce, Delete Note\n");
  printf("[6] Log out\n");
  printf("-----------------------------------------\n");
  printf(">> ");
  int number_input;
  while(number_input>=1 || number_input<=6){
    scanf("%d", &number_input); getchar();
    if(number_input==1){
      add_friend(user_index);
    }else if(number_input==2){
      remove_friend(user_index);
    }else if(number_input==3){
      view_inbox(user_index);
    }else if(number_input==4){
      view_sent_request(user_index);
    }else if(number_input==6){
      main_menu();
    }else{
      printf("-----------------------------------------\n");
      printf("Invalid input, choose a number between 1 to 6\n");
      printf("-----------------------------------------\n");
      printf(">> ");
    }
  }
}

void add_friend(int user_index){
	if(no_of_users < 2){
		printf("Tidak ada user\n");
		printf("Press enter to continue!\n");
  		getchar();
  		user_page(user_index);
	}
	else{
  printf("-----------------------------------------\n\n");
  printf("[All User]\n");
  printf("No.    Username\n");
  print_all_user(); 
  printf("\nWhich user do you want to add?\n");
  printf(">> ");
  char input_username[25];
  scanf("%s", input_username); getchar();
  popMid(input_username);
  
  if(ada != 0){
  printf("\n-- Your request has been sent to %s --\n", input_username);
  printf("Press enter to continue!\n");
  getchar();
  user_page(user_index);
  }
  else{
  printf("Tidak ada user dengan nama tersebut\n");
  printf("Press enter to continue!\n");
  getchar();
  user_page(user_index);
  }
	}

}

void remove_friend(int user_index){
  printf("-----------------------------------------\n\n");
  printf("[All Friends of %s]\n", user[user_index].username);
  printf("No. Username\n");

  printf("\nWhich user do you want to remove?\n");
  printf(">> ");
  char input_username[25];
  scanf("%s", input_username); getchar();
 
  printf("\n-- Your are no longer friends with %s --\n", input_username);
  printf("Press enter to continue!\n");
  getchar();
  user_page(user_index);

}

void view_inbox(int user_index){
  printf("-----------------------------------------\n\n");
  printf("[All Friend Requests of %s]\n", user[user_index].username);
  printf("No. Username\n");

  printf("\nWhich user do you want to be accepted?\n");
  printf(">> ");
  char input_username[25];
  scanf("%s", input_username); getchar();
 
  printf("\n-- You have accepted the request from %s --\n", input_username);
  printf("Press enter to continue!\n");
  getchar();
  user_page(user_index);

}

void view_sent_request(int user_index){
  printf("-----------------------------------------\n\n");
  printf("[All Your Sent Friend Requests That Are Still Pending]\n");
  printf("No. Username\n");
  
  printf("Press enter to continue!\n");
  getchar();
  user_page(user_index);
}