#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "mima.txt"
#define MAX_LENGTH 100

void register_user() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char buffer[MAX_LENGTH];
    
    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }
    
    snprintf(buffer, sizeof(buffer), "%s:%s\n", username, password);
    fputs(buffer, file);
    fclose(file);

    printf("用户注册成功!\n");
}

void change_password() {
    char username[MAX_LENGTH];
    char new_password[MAX_LENGTH];
    char buffer[MAX_LENGTH];
    char temp_filename[] = "temp.txt";
    int found = 0;

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入新密码: ");
    scanf("%s", new_password);

    FILE *file = fopen(FILENAME, "r");
    FILE *temp_file = fopen(temp_filename, "w");
    if (file == NULL || temp_file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        char file_username[MAX_LENGTH], file_password[MAX_LENGTH];
        sscanf(buffer, "%[^:]:%s", file_username, file_password);
        if (strcmp(file_username, username) == 0) {
            fprintf(temp_file, "%s:%s\n", username, new_password);
            found = 1;
        } else {
            fputs(buffer, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(FILENAME);
        rename(temp_filename, FILENAME);
        printf("密码修改成功!\n");
    } else {
        remove(temp_filename);
        printf("未找到用户!\n");
    }
}

int main() {
    int choice;

    printf("请选择操作: \n");
    printf("1. 注册\n");
    printf("2. 修改密码\n");
    printf("请输入选择 (1 或 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            register_user();
            break;
        case 2:
            change_password();
            break;
        default:
            printf("无效选择!\n");
            break;
    }

    return 0;
}
