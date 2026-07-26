#include <stdio.h>
#include <stdlib.h>

#define MAX_K 64       /* Максимальная длина ключа в байтах */
#define MAX_M 100      /* Максимальное количество сообщений */
#define MAX_H_LEN 1000 /* Максимальная длина префикса H (символов/байт) */

#define MAX_BYTES 100000
#define MAX_HEX_SYMBOLS (MAX_BYTES * 2)

#define BUFFER_HEX_SIZE (MAX_HEX_SYMBOLS + 2)
#define BUFFER_H_SIZE (MAX_H_LEN + 2)

static int run_application(void);
static void process(const char *h_buffer, unsigned char k, unsigned char m);
static void clear_input(void);
static int read_inputs(unsigned char *k, unsigned char *m);
static unsigned int read_prefix_h(char *h_buffer, size_t buffer_size);
static unsigned char hex_pair_to_byte(char high, char low);
static unsigned char hex_char_to_val(char ch);
static void process_line(const char *h_buffer, unsigned char k);

int main(void) { return run_application(); }

static int run_application(void) {
    unsigned char m, k;

    unsigned char error_return = read_inputs(&k, &m);

    if (!error_return) {
        char h[BUFFER_H_SIZE];
        unsigned int h_len = 0;

        h_len = read_prefix_h(h, BUFFER_H_SIZE);

        if (h_len < k) {
            error_return = EXIT_FAILURE;
        } else {
            process(h, k, m);
        }
    }

    return error_return;
}

static void process(const char *h_buffer, unsigned char k, unsigned char m) {
    process_line(h_buffer, k);

    for (unsigned char i = 1; i < m; i++) {
        process_line(NULL, k);
    }
}

static void process_line(const char *h_buffer, unsigned char k) {
    static unsigned char key[MAX_K];
    int ch1;
    unsigned int byte_count = 0;

    while ((ch1 = getchar()) != '\n' && ch1 != EOF) {
        int ch2 = getchar();
        unsigned char cipher_byte = hex_pair_to_byte(ch1, ch2);

        if (h_buffer != NULL && byte_count < k) {
            key[byte_count] = cipher_byte ^ (unsigned char)h_buffer[byte_count];
        }

        unsigned char plain_byte = cipher_byte ^ key[byte_count % k];
        putchar(plain_byte);

        byte_count++;
    }

    putchar('\n');
}

static unsigned char hex_pair_to_byte(char high, char low) {
    return (hex_char_to_val(high) << 4) | hex_char_to_val(low);
}

static unsigned char hex_char_to_val(char ch) {
    unsigned char ret = EXIT_FAILURE;

    if (ch >= '0' && ch <= '9') {
        ret = ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
        ret = ch - 'a' + 10;
    }

    return ret;
}

static unsigned int read_prefix_h(char *h_buffer, size_t buffer_size) {
    unsigned int len = 0;

    if (fgets(h_buffer, buffer_size, stdin) != NULL) {
        while (h_buffer[len] != '\0') {
            len++;
        }

        if (len > 0 && h_buffer[len - 1] == '\n') {
            h_buffer[len - 1] = '\0';
            len--;
        }
    }

    return len;
}

static int read_inputs(unsigned char *k, unsigned char *m) {
    unsigned char ret = EXIT_SUCCESS;

    if (scanf("%hhu %hhu", k, m) != 2) {
        ret = EXIT_FAILURE;
    }

    else if (*k < 1 || *k > MAX_K || *m < 1 || *m > MAX_M) {
        ret = EXIT_FAILURE;
    }

    clear_input();

    return ret;
}

static void clear_input(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
