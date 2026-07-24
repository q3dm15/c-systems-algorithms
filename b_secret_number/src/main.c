/*
 * Решение: Искомое число P находится как НОД (наибольший общий делитель) 
 * всех сообщений m_i с помощью быстрого алгоритма Евклида. Так как множество 
 * чисел x_i не имеет общих простых множителей, НОД(x_1, ..., x_n) = 1, что 
 * гарантирует равенство НОД(m_1, ..., m_n) = P. Использование типа long long 
 * предотвращает переполнение при m_i до 10^18, а потоковая обработка чисел 
 * в цикле на лету позволяет обойтись без массивов и затрат памяти (O(1)).
 */

#include <stdio.h>

// Алгоритм Евклида для вычисления Наибольшего Общего Делителя (НОД)
static long long evklid_algo(long long a, long long b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long secret_p;
    if (scanf("%lld", &secret_p) != 1) return 0;

    // Последовательно считываем остальные числа и обновляем НОД на лету
    for (int i = 1; i < n; ++i) {
        long long current_m;
        if (scanf("%lld", &current_m) == 1) {
            secret_p = evklid_algo(secret_p, current_m);
        }
    }

    printf("%lld\n", secret_p);

    return 0;
}
