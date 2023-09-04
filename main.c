
void initialize_data();
void launch_system();

int main() {
    initialize_data();
    launch_system();
    return 0;
}

/*
 gcc main.c client_view.c admin_view.c bank_system.c database.c -o main.exe
 */