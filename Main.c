#include <stdio.h>
#include <string.h>

#define MAX 100

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

void addContact();
void viewContacts();
void searchContact();
void updateContact();
void deleteContact();
void sortContacts();

int main() {
    int choice;

    do {
        printf("\n===== CONTACT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Sort Contacts by Name\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6: sortContacts(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);

    return 0;
}
void addContact() {
    FILE *fp;
    struct Contact c;

    fp = fopen("contacts.dat", "ab");
    if (!fp) {
        printf("File error!\n");
        return;
    }

    printf("Enter name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter phone: ");
    scanf(" %s", c.phone);

    printf("Enter email: ");
    scanf(" %s", c.email);

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("Contact added successfully!\n");
}
void viewContacts() {
    FILE *fp;
    struct Contact c;

    fp = fopen("contacts.dat", "rb");
    if (!fp) {
        printf("No contacts found!\n");
        return;
    }

    printf("\n--- CONTACT LIST ---\n");
    while (fread(&c, sizeof(c), 1, fp)) {
        printf("Name : %s\nPhone: %s\nEmail: %s\n\n",
               c.name, c.phone, c.email);
    }

    fclose(fp);
}
void searchContact() {
    FILE *fp;
    struct Contact c;
    char name[50];
    int found = 0;

    fp = fopen("contacts.dat", "rb");
    if (!fp) {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to search: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) == 0) {
            printf("Found!\nName: %s\nPhone: %s\nEmail: %s\n",
                   c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    fclose(fp);
}
void updateContact() {
    FILE *fp, *temp;
    struct Contact c;
    char name[50];
    int found = 0;

    fp = fopen("contacts.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter name to update: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) == 0) {
            printf("Enter new phone: ");
            scanf(" %s", c.phone);
            printf("Enter new email: ");
            scanf(" %s", c.email);
            found = 1;
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found)
        printf("Contact updated!\n");
    else
        printf("Contact not found!\n");
}
void deleteContact() {
    FILE *fp, *temp;
    struct Contact c;
    char name[50];
    int found = 0;

    fp = fopen("contacts.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) != 0)
            fwrite(&c, sizeof(c), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found)
        printf("Contact deleted!\n");
    else
        printf("Contact not found!\n");
}
void sortContacts() {
    FILE *fp;
    struct Contact c[MAX], temp;
    int count = 0, i, j;

    fp = fopen("contacts.dat", "rb");
    if (!fp) {
        printf("No contacts found!\n");
        return;
    }

    while (fread(&c[count], sizeof(struct Contact), 1, fp))
        count++;

    fclose(fp);

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(c[i].name, c[j].name) > 0) {
                temp = c[i];
                c[i] = c[j];
                c[j] = temp;
            }
        }
    }

    fp = fopen("contacts.dat", "wb");
    fwrite(c, sizeof(struct Contact), count, fp);
    fclose(fp);

    printf("Contacts sorted successfully!\n");
}
