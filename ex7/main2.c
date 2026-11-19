#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int price;
    char title[128];
} book_t;

void total_price(const book_t books[], size_t count)
{
    size_t i;
    int total = 0;

    for (i = 0; i < count; i++) {
        total += books[i].price;
    }

    printf("所有書籍總價：%d\n\n", total);
}

void list_books(const book_t books[], size_t count)
{
    size_t i;

    printf("%-5s %-8s %s\n", "ID", "Price", "Title");
    printf("-----------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%-5d %-8d %s\n",
               books[i].id,
               books[i].price,
               books[i].title);
    }
}

int main(void)
{
    book_t books[] = {
        {1, 1000, "All the Light We Cannot See"},
        {2,  300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4,  550, "Killers of the Flower Moon"},
        {5,  870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    book_t loaded_books[sizeof(books) / sizeof(books[0])];
    size_t book_count = sizeof(books) / sizeof(books[0]);
    size_t loaded_count;
    FILE *file;

    file = fopen("Book.bin", "wb");
    if (file == NULL) {
        printf("無法建立 Book.bin。\n");
        return 1;
    }

    fwrite(books, sizeof(book_t), book_count, file);
    fclose(file);

    file = fopen("Book.bin", "rb");
    if (file == NULL) {
        printf("無法開啟 Book.bin。\n");
        return 1;
    }

    loaded_count = fread(
        loaded_books,
        sizeof(book_t),
        book_count,
        file
    );

    fclose(file);

    total_price(loaded_books, loaded_count);
    list_books(loaded_books, loaded_count);

    return 0;
}
