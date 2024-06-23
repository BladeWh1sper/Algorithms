#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Структура для хранения тройки (смещение, длина, следующий символ)
struct LZ77Tuple {
    int offset;
    int length;
    char next_char;
};

// Функция для сжатия строки с использованием LZ77
vector<LZ77Tuple> lz77_compress(const string& input, int window_size, int lookahead_buffer_size) {
    vector<LZ77Tuple> compressed;
    int n = input.size();
    int i = 0;

    while (i < n) {
        int match_length = 0;
        int match_offset = 0;
        char next_char = input[i];

        // Поиск наибольшего совпадения в окне
        int window_start = max(0, i - window_size);
        for (int j = window_start; j < i; j++) {
            int k = 0;
            while (k < lookahead_buffer_size && i + k < n && input[j + k] == input[i + k]) {
                k++;
            }
            if (k > match_length) {
                match_length = k;
                match_offset = i - j;
                if (i + k < n) {
                    next_char = input[i + k];
                } else {
                    next_char = '\0';
                }
            }
        }

        LZ77Tuple t;
        t.offset = match_offset;
        t.length = match_length;
        t.next_char = next_char;
        compressed.push_back(t);

        i += match_length + 1;
    }

    return compressed;
}

// Функция для декомпрессии строки с использованием LZ77
string lz77_decompress(const vector<LZ77Tuple>& compressed) {
    string decompressed;

    for (size_t i = 0; i < compressed.size(); ++i) {
        int offset = compressed[i].offset;
        int length = compressed[i].length;
        char next_char = compressed[i].next_char;

        int start_pos = decompressed.size() - offset;
        for (int j = 0; j < length; j++) {
            decompressed += decompressed[start_pos + j];
        }
        if (next_char != '\0') {
            decompressed += next_char;
        }
    }

    return decompressed;
}

int main() {
    string input;
    cout << "Введите строку для сжатия: ";
    getline(cin, input);

    int window_size = 15;
    int lookahead_buffer_size = 6;

    vector<LZ77Tuple> compressed = lz77_compress(input, window_size, lookahead_buffer_size);

    cout << "Сжатые данные (смещение, длина, следующий символ):" << endl;
    for (size_t i = 0; i < compressed.size(); ++i) {
        int offset = compressed[i].offset;
        int length = compressed[i].length;
        char next_char = compressed[i].next_char;
        cout << "(" << offset << ", " << length << ", " << next_char << ")" << endl;
    }

    string decompressed = lz77_decompress(compressed);
    cout << "Восстановленная строка: " << decompressed << endl;

    return 0;
}
