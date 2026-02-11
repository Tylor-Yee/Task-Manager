#include <iostream>
#include <string>

struct item {
public:
	std::string item_name;
	std::string item_description;
	void print_item_content();
};

class list {
public:
	std::string title;
	std::string description;
	item* array_of_items;
	int length;
	void add_item();
	void remove_item();
	void print_contents();
};

struct node {
	list* list_node;
	node* next;
	node* previous;
};

class linked_list {
public:
	node* head = nullptr;
	int length = 0; 
};

bool check_if_go_back(std::string user_input) {
	if (user_input == "back") {
		return true;	
	}

	return false;
}

void clear_screen() {
	for (int i = 0; i < 60; i++) {
		std::cout << std::endl;
	}
}

void item::print_item_content() {
	std::cout << "Task: " << this->item_name << " | Description: "
			<< this->item_description << std::endl;
}

void list::add_item() {
	item new_item;

	std::cout << "Adding a Task: Name" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "What is the Task's name?" << std::endl;
	std::cout << "If you want to go back, type back" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string name_input;

	std::cin >> name_input;
	
	bool return_to_list = check_if_go_back(name_input);

	clear_screen();

	if (return_to_list) {
		return;
	}

	new_item.item_name = name_input;

	std::cout << "Adding a list: Description" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "What is the Task's description?" << std::endl;
	std::cout << "If you want to go back, type back" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string description_input;

	std::cin >> description_input;
	
	return_to_list = check_if_go_back(description_input);

	clear_screen();

	if (return_to_list) {
		return;
	}
	
	new_item.item_description = description_input;
	
	this->array_of_items[length] = new_item;
	this->length += 1;

	return;
 
}

void list::remove_item() {
	

}

void list::print_contents() {
	while (true) {
		std::cout << "List Name: " << this->title << "\nDescription: "
				<< this->description << std::endl;
		std::cout << "------------------------------------------------------" << std::endl;
	
		if (this->length == 0) {
			std::cout << "There are no items in this list!" << std::endl;
		} else {
			for (int i = 0; i < this->length; i++) {
				array_of_items[i].print_item_content();
			}
		}
		
		std::cout << "\nWhat do you want to do?" << std::endl;
		std::cout << "1) Add an item" << std::endl;
		std::cout << "2) Remove an item" << std::endl;
		std::cout << "3) Go back" << std::endl;

		std::cout << "------------------------------------------------------" << std::endl;
		std::cout << "> ";

		std::string user_input;

		std::cin.ignore();
	
		std::getline(std::cin, user_input);
	
		clear_screen();

		if (user_input == "3") {
			break;
		} else if (user_input == "1") {
			this->add_item();
		} else if (user_input == "2") {
			this->remove_item();
		}
	}
}

void welcome_user() {
	std::cout << "Welcome" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "Hello, welcome to the Task Manager!" << std::endl;
	std::cout << "This program is made to track, add," 
				<< "and remove lists." << std::endl;
	std::cout << "You can also add/remove reminders, tasks, and " 
				<< "items in a list." << std::endl;
	std::cout << "This allows you to make lists, planners, and managers " 
				<< "that shape the way you \nmanage your day to day actions." << std::endl;
	std::cout << "\nPress ENTER to continue." << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string user_input;

	std::getline(std::cin, user_input);

	return;
}

int get_main_menu_choice() {
	std::cout << "Main Menu" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "What do you want to do?" << std::endl;
	std::cout << "1) Create a list" << std::endl;
	std::cout << "2) Remove a list" << std::endl;
	std::cout << "3) Check lists" << std::endl;
	std::cout << "4) Guide" << std::endl;
	std::cout << "5) Tutorial" << std::endl;
	std::cout << "6) Exit" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	int user_input;

	std::cin >> user_input;

	return user_input;
}

void add_list(list new_list, linked_list* list_manager) {
	node* new_node = new node;
	new_node->list_node = new list;

	new_node->list_node->title = new_list.title;
	new_node->list_node->description = new_list.description;
	new_node->next = nullptr;
	new_node->previous = nullptr;

	if (list_manager->length == 0) {
		list_manager->head = new_node;
	} else {
		node* current_node = list_manager->head;

		while (current_node->next != nullptr) {
			current_node = current_node->next;
		}

		current_node->next = new_node;
		new_node->previous = current_node;
	}

	list_manager->length += 1;
}

void remove_list(linked_list* list_manager, std::string list_name) {
	node* current_node = list_manager->head;

	while(current_node != nullptr) {
		if (current_node->list_node->title == list_name) {
			if (current_node == list_manager->head) {
				current_node = current_node->next;
				delete list_manager->head->list_node;
				delete list_manager->head;
				list_manager->head = current_node;
			} else if (current_node->next == nullptr) {
				node* previous_node = current_node->previous;
				delete current_node->list_node;
				delete current_node;
			} else {
				node* previous_node = current_node->previous;
				node* deleted_node = current_node;
				current_node = current_node->next;
				current_node->previous = previous_node;
				previous_node->next = current_node;
				delete current_node->list_node;
				delete current_node;
			}

			list_manager->length -= 1;
			break;
		}

		current_node = current_node->next;
	}
}

void show_guide_screen() {
	std::cout << "Guide" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "Here are the options you can decide on:" << std::endl;
	std::cout << "1) Create a list: Create a new list that can hold reminders, tasks, and events" << std::endl;
	std::cout << "2) Remove a list: Remove a list that you have made" << std::endl;
	std::cout << "3) Check lists: Check out the lists you have made" << std::endl;
	std::cout << "4) Guide: You are here! Learn a short bit about each option" << std::endl;
	std::cout << "5) Tutorial: Get a more in depth explanation how to use the program" << std::endl;
	std::cout << "6) Exit: Exit the program" << std::endl;
	std::cout << "\nPress ENTER to go to the Main Menu" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string user_input;

	std::cin.ignore();

	std::getline(std::cin, user_input);

	clear_screen();

	return;
}

void start_tutorial() {
	std::cout << "Tutorial: Creating a list" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "To create a list, input 1 in the main menu screen." << std::endl;
	std::cout << "This will then pull up a new screen that asks for the new list's name" << std::endl;
	std::cout << "Input any name you like and press Enter to continue" << std::endl;
	std::cout << "or type 'back' and press Enter to go back to the main menu." << std::endl;
	std::cout << "You will do the same thing for adding a description, and you can" << std::endl;
	std::cout << "Also go back by typing 'back' and pressing Enter" << std::endl;
	std::cout << "\nPress ENTER to continue or type 'back' to stop the tutorial" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string user_input;

	std::cin.ignore();

	std::getline(std::cin, user_input);
	
	bool return_to_main_menu = check_if_go_back(user_input);
	
	clear_screen();

	if (return_to_main_menu) {
		return;
	}

	std::cout << "Tutorial: Removing a list" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "To remove a list, input 2 in the main menu screen." << std::endl;
	std::cout << "This will then pull up a new screen that asks for list name that you want to remove" << std::endl;
	std::cout << "Input a name that has been made. If you input an incorrect name, it will ask again." << std::endl;
	std::cout << "If you don't want to remove a list, type 'back' to go back to the main menu." << std::endl;
	std::cout << "It will then ask you to confirm if you want to remove this list." << std::endl;
	std::cout << "You can type yes to continue or no to stop removing the list" << std::endl;
	std::cout << "\nPress ENTER to continue or type 'back' to stop the tutorial" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::cin.ignore();

	std::getline(std::cin, user_input);
	
	return_to_main_menu = check_if_go_back(user_input);
	
	clear_screen();

	if (return_to_main_menu) {
		return;
	}
	
	std::cout << "Tutorial: Checking Lists" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "To check the lists you have created, press 3 to " << std::endl;
	std::cout << "This will then pull up a new screen that asks for list name that you want to remove" << std::endl;
	std::cout << "Input a name that has been made. If you input an incorrect name, it will ask again." << std::endl;
	std::cout << "If you don't want to remove a list, type 'back' to go back to the main menu." << std::endl;
	std::cout << "It will then ask you to confirm if you want to remove this list." << std::endl;
	std::cout << "You can type yes to continue or no to stop removing the list" << std::endl;
	std::cout << "\nPress ENTER to continue or type 'back' to stop the tutorial" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::cin.ignore();

	std::getline(std::cin, user_input);
	
	return_to_main_menu = check_if_go_back(user_input);
	
	clear_screen();

	if (return_to_main_menu) {
		return;
	}

	std::cout << "Tutorial: Finished Tutorial" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "Congrats! You have finished the tutorial!" << std::endl;
	std::cout << "You can come back to this tutorial anytime to refresh your knowledge of how to use this program." << std::endl;
	std::cout << "\nPress ENTER to go back to the Main Menu" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::cin.ignore();

	std::getline(std::cin, user_input);

	clear_screen();

	return;

}

void check_current_lists(linked_list* list_manager) {
	std::cout << "Lists" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	
	if (list_manager->length != 0) {
		node* current_node = list_manager->head;

		while(current_node != nullptr) {
			std::cout << "Name: " << current_node->list_node->title << 
				" | Description: " << current_node->list_node->description << std::endl;
			current_node = current_node->next;
		}

	} else {
		std::cout << "There are no lists made. Go back to the Main Menu to create on!" << std::endl;
	}

	std::cout << "\nPress ENTER to go back to the Main Menu" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";
	
	std::string user_input;

	std::cin.ignore();

	std::getline(std::cin, user_input);

	clear_screen();

	return;

}

bool check_list_for_task(std::string name_input, linked_list* list_manager) {
	node* current_node = list_manager->head;

	while(current_node != nullptr) {
		if (current_node->list_node->title == name_input) {
			return true;
		}

		current_node = current_node->next;
	
	}

	return false;
}

void remove_list(linked_list* list_manager) {
	std::string name_input;

	while(true) {
		std::cout << "Removing a list: Name" << std::endl;
		std::cout << "------------------------------------------------------" << std::endl;
		std::cout << "What is the list's name?" << std::endl;
		std::cout << "If you want to go back, type back" << std::endl;
		std::cout << "------------------------------------------------------" << std::endl;
		std::cout << "> ";	
	
		std::cin >> name_input;
		
		bool return_to_main_menu = check_if_go_back(name_input);
		bool list_exists = check_list_for_task(name_input, list_manager);
	
		clear_screen();
	
		if (return_to_main_menu) {
			return;
		} else if (!list_exists) {
			std::cout << "------------------------------------------------------" << std::endl;
			std::cout << "Error: You inputted a list name that doesn't exist, please try again." << std::endl;
			std::cout << "------------------------------------------------------" << std::endl;
		
			for (int i = 0; i < 10; i++) {
				std::cout << std::endl;
			}

			continue;
		} else {
			break;
		}
	}

	std::cout << "Removing a list: Confirmation" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "Are you sure you want to delete the list?" << std::endl;
	std::cout << "The list will be removed permenantly." << std::endl;
	std::cout << "Type 'yes' to continue and 'no' to go back" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string confirmation_input;

	std::cin >> confirmation_input;

	clear_screen();

	if (confirmation_input == "no") {
		return;
	}

	remove_list(list_manager, name_input);

	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "You have successfully removed the list titled: " << name_input << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;

	for (int i = 0; i < 10; i++) {
		std::cout << std::endl;
	}

}

void create_new_list(linked_list* list_manager) {
	list new_list;

	std::cout << "Adding a list: Name" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "What is the list's name?" << std::endl;
	std::cout << "If you want to go back, type back" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string name_input;

	std::cin >> name_input;
	
	bool return_to_main_menu = check_if_go_back(name_input);

	clear_screen();

	if (return_to_main_menu) {
		return;
	}

	new_list.title = name_input;

	std::cout << "Adding a list: Description" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "What is the list's description?" << std::endl;
	std::cout << "If you want to go back, type back" << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "> ";

	std::string description_input;

	std::cin >> description_input;
	
	return_to_main_menu = check_if_go_back(description_input);

	clear_screen();

	if (return_to_main_menu) {
		return;
	}

	new_list.description = description_input;

	add_list(new_list, list_manager);

	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "You have made a new list titled: " << name_input << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;

	for (int i = 0; i < 10; i++) {
		std::cout << std::endl;
	}
	
	return;
}

void delete_list(linked_list* list_manager) {
	node* current_node = list_manager->head;

	while (current_node != nullptr) {
		node* deleted_node = current_node;
		current_node = current_node->next;
		
		delete deleted_node->list_node;
		delete deleted_node;
	}

	list_manager->length = 0;

	delete list_manager;
	list_manager = nullptr;
}

void process_choice(int main_menu_choice, linked_list* list_manager) {
	if (main_menu_choice == 1) {
		create_new_list(list_manager);
	} else if (main_menu_choice == 2) {
		remove_list(list_manager);
	} else if (main_menu_choice == 3) {
		check_current_lists(list_manager);
	} else if (main_menu_choice == 4) {
		show_guide_screen();
	} else if (main_menu_choice == 5) {
		start_tutorial();
	}

	return;
}

int main() {
	clear_screen();

	welcome_user();

	clear_screen();
	
	linked_list* list_manager = new linked_list;

	while(true) {
		int main_menu_choice = get_main_menu_choice();
		
		clear_screen();

		if (main_menu_choice == 6) {
			std::cout << "Have a good day! Exiting Program..." << std::endl;
			break;
		}

		process_choice(main_menu_choice, list_manager);
	}

	delete_list(list_manager);

	return 0;
}
