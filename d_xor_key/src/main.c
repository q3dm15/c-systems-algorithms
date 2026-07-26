#include <stdio.h>
#include <stdlib.h>

#define MAX_K 64       /* Максимальная длина ключа в байтах */
#define MAX_M 100      /* Максимальное количество сообщений */
#define MAX_H_LEN 1000 /* Максимальная длина префикса H */

#define BUFFER_H_SIZE (MAX_H_LEN + 2)

#define HEX_BASE_VAL ('a' - 10)

typedef struct {
    char h[BUFFER_H_SIZE];
    unsigned int h_len;
    unsigned char k;
    unsigned char m;
} CryptoContext;

static int run_application(void);
static int read_context(CryptoContext *ctx);
static void process_crypto(const CryptoContext *ctx);
static void process_line(const CryptoContext *ctx, int is_first_line);
static unsigned char hex_pair_to_byte(char high, char low);
static unsigned char hex_char_to_val(char ch);
static void clear_input(void);

int main(void) { return run_application(); }

static int run_application(void) {
    CryptoContext ctx = {.h_len = 0, .k = 0, .m = 0};
    unsigned char error_return = read_context(&ctx);

    /* Считываем данные в структуру */
    if (!error_return) {
        /* Выполняем обработку на основе контекста */
        process_crypto(&ctx);
    }

    return error_return;
}

static int read_context(CryptoContext *ctx) {
    unsigned char error_return = EXIT_SUCCESS;

    /* Читаем числа k и m */
    if (scanf("%hhu %hhu", &ctx->k, &ctx->m) != 2) {
        error_return = EXIT_FAILURE;
    }

    else if (ctx->k < 1 || ctx->k > MAX_K || ctx->m < 1 || ctx->m > MAX_M) {
        error_return = EXIT_FAILURE;
    }

    else {
        clear_input();

        /* Читаем префикс h */
        if (fgets(ctx->h, BUFFER_H_SIZE, stdin) != NULL) {
            while (ctx->h[ctx->h_len] != '\0') {
                ctx->h_len++;
            }

            if (ctx->h_len > 0 && ctx->h[ctx->h_len - 1] == '\n') {
                ctx->h[ctx->h_len - 1] = '\0';
                ctx->h_len--;
            }

            /* Длина префикса не должна быть меньше ключа */
            if (ctx->h_len < ctx->k) {
                error_return = EXIT_FAILURE;
            }
        }
    }

    return error_return;
}

static void process_crypto(const CryptoContext *ctx) {
    /* Обработка первой строки (ключа) */
    process_line(ctx, 1);

    /* Обработка последующих m-1 строк */
    for (unsigned char i = 1; i < ctx->m; i++) {
        process_line(ctx, 0);
    }
}

static void process_line(const CryptoContext *ctx, int is_first_line) {
    static unsigned char key[MAX_K];
    int ch1;
    unsigned int byte_count = 0;

    while ((ch1 = getchar()) != '\n' && ch1 != EOF) {
        int ch2 = getchar();
        if (ch2 == EOF || ch2 == '\n') break; /* Защита от неполной hex-пары */

        unsigned char cipher_byte = hex_pair_to_byte(ch1, ch2);

        /* Извлекаем ключ только на первой строке */
        if (is_first_line && byte_count < ctx->k) {
            key[byte_count] = cipher_byte ^ (unsigned char)ctx->h[byte_count];
        }

        unsigned char plain_byte = cipher_byte ^ key[byte_count % ctx->k];
        putchar(plain_byte);

        byte_count++;
    }

    putchar('\n');
}

static unsigned char hex_pair_to_byte(char high, char low) {
    return (hex_char_to_val(high) << 4) | hex_char_to_val(low);
}

static unsigned char hex_char_to_val(char ch) {
    unsigned char error_return = EXIT_SUCCESS;
    if (ch >= '0' && ch <= '9') error_return = ch - '0';
    if (ch >= 'a' && ch <= 'f') error_return = ch - HEX_BASE_VAL;
    return error_return;
}

static void clear_input(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
