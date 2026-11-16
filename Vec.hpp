#pragma once

#include <cstdlib>

// メモリ確保で推奨される配列のサイズ
constexpr const size_t DEFAULT_CAPACITY = 128;

template <typename T>
/**
 * 例外を使わず、fail-fastを意識した自作vectorの設計
 */
struct Vec {
private:
    // メモリ上に確保されたその配列分のメモリ
    size_t capacity;
    // 実際に値が代入されている部分までの長さ
    size_t len;
    T* arr;

public:
    T& operator[](size_t index) {
        return arr[index];
    }

    const T& operator[](size_t index) const {
        return arr[index];
    }

    Vec(size_t init_capacity);
    void resize(size_t new_size);
    void push_back(T element);
    size_t size();
    ~Vec();
};

/**
 * 動的配列を初期化するための関数
 */
template <typename T>
Vec<T>::Vec(size_t init_capacity) {
    if (init_capacity == 0) {
        std::exit(EXIT_FAILURE);
    }

    arr = static_cast<T*>(std::malloc(init_capacity * sizeof(T)));

    if (arr == nullptr) {
        std::exit(EXIT_FAILURE);
    }

    capacity = init_capacity;
    len = 0;
}

/**
 * 配列のサイズをリサイズする関数
 * 大きくすることも小さくすることも可能
 */
template <typename T>
void Vec<T>::resize(size_t new_size) {
    if (len <= new_size) {
        T* tmp_p = static_cast<T*>(std::realloc(arr, new_size * sizeof(T)));

        if (tmp_p == nullptr) {
            std::exit(EXIT_FAILURE);
        }

        arr = tmp_p;
    }

    len = new_size;
}

/**
 * 配列の最後尾に要素を追加できる関数
 * 足りない場合はメモリを再確保する
 */
template <typename T>
void Vec<T>::push_back(T element) {
    // メモリの再確保が必要な場面を想定
    if (len >= capacity) {
        // 倍々確保により、動的メモリ確保のランタイムを抑える
        capacity *= 2;
        T* tmp_p = static_cast<T*>(std::realloc(arr, capacity * sizeof(T)));
        if (tmp_p == nullptr) {
            std::exit(EXIT_FAILURE);
        }
        arr = tmp_p;
    }

    arr[len] = element;
    ++len;
}

template <typename T>
size_t Vec<T>::size() {
    return len;
}

template <typename T>
Vec<T>::~Vec() {
    std::free(arr);
    arr = nullptr;
}
