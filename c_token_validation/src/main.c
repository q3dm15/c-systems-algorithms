/*
 * Решение: Программа посимвольно считывает каждый токен до конца строки через
 * getchar(), игнорируя разрешенные разделители (пробелы и дефисы) и динамически
 * расширяя массив цифр. Если строка содержит сторонние символы или оказывается
 * пустой, она сразу помечается как INVALID. Для очищенных цифровых строк
 * запускается алгоритм Луна с обходом массива в обратном направлении (справа
 * налево). Каждая вторая цифра удваивается (с вычитанием 9 при превышении 9),
 * а итоговая контрольная сумма проверяется на кратность 10, определяя финальный
 * статус токена.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *digits;  // Вложенный массив символов (цифр)
    int is_valid;  // Флаг валидности: 1 - valid, 0 - invalid
    int length;    // Текущая длина строки
    int capacity;  // Выделенный размер памяти
} Token;

static void process_luna(Token *token);
static int is_digit(char ch);
static int append_to_token(Token *token, char ch);

int main(void) {
    int m;
    if (scanf("%d", &m) != 1 || m <= 0) return 0;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Массив токенов
    Token *tokens = (Token *)malloc(m * sizeof(Token));
    if (tokens == NULL) {
        return 1;
    }

    int actual_tokens_count = 0;

    for (int i = 0; i < m; i++) {
        // Инициализацичя по умолчанию
        tokens[i].capacity = 10;
        tokens[i].length = 0;
        tokens[i].is_valid = 1;
        tokens[i].digits = (char *)malloc(tokens[i].capacity * sizeof(char));

        if (tokens[i].digits == NULL) {
            return 1;
        }

        // Читаем символы пока не встретим перенос строки или конец файла
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (is_digit(ch)) {
                if (!append_to_token(&tokens[i], (char)ch)) {
                    return 1;
                }
            } else if (ch != ' ' && ch != '-') {
                // Если встретили любой символ, кроме цифры, пробела или дефиса
                tokens[i].is_valid = 0;
            }
        }

        if (tokens[i].length == 0) {
            tokens[i].is_valid = 0;
        } else {
            tokens[i].digits[tokens[i].length] = '\0';  // Закрываем строку
        }

        // Если токен изначально помечен как невалидный, алгоритм Луна не
        // запустится
        if (tokens[i].is_valid == 0) {
            // Чтобы process_luna гарантированно вывела INVALID
            tokens[i].is_valid = 0;
        }

        actual_tokens_count++;

        // Если достигнут реальный конец файла (ввод полностью пуст)
        if (ch == EOF) {
            // Инициализируем оставшиеся токены безопасными значениями
            for (int j = i + 1; j < m; j++) {
                tokens[j].digits = NULL;
                tokens[j].is_valid = 0;
                tokens[j].length = 0;
                tokens[j].capacity = 0;
            }
            break;  // только при настоящем конце ввода
        }
    }

    // Вывод результата
    for (int i = 0; i < actual_tokens_count; i++) {
        process_luna(&tokens[i]);
    }

    // Освобождение памяти
    for (int i = 0; i < m; i++) {
        if (tokens[i].digits != NULL) {
            free(tokens[i].digits);
        }
    }
    free(tokens);

    return 0;
}

int is_digit(char ch) { return ch >= '0' && ch <= '9'; }

// Служебный метод для работы с памятью
int append_to_token(Token *token, char ch) {
    if (token->length >= token->capacity - 1) {
        token->capacity *= 2;
        char *temp =
            (char *)realloc(token->digits, token->capacity * sizeof(char));
        if (temp == NULL) {
            return 0;
        }
        token->digits = temp;
    }
    token->digits[token->length++] = ch;
    return 1;
}

// Проверка алгоритма Луна
void process_luna(Token *token) {
    if (token == NULL || token->digits == NULL) {
        return;
    }

    // Если токен был признан невалидным на этапе чтения
    if (token->is_valid == 0) {
        printf("INVALID\n");
        return;
    }

    int sum = 0;
    int alternate = 0;
    for (int i = token->length - 1; i >= 0; i--) {
        int num = token->digits[i] - '0';
        if (alternate) {
            num *= 2;
            if (num > 9) {
                num -= 9;
            }
        }
        sum += num;
        alternate = !alternate;
    }

    printf("%sVALID\n", sum % 10 == 0 ? "" : "IN");
}
