# Vec

シンプルで高速な動的配列のライブラリ
このVecライブラリでは、シンプルで挙動の予測可能性の高い、そして高速に動作する動的配列のライブラリを提供しています
## 1. POD専用
メンバー関数を含むいわゆるクラスといったデータ型をサポートしないことで、
動的配列の要素に対するコンストラクタ/デストラクタの発行が起きず、挙動の予測可能性を高めています
コンストラクタやデストラクタを用いるための `new`/`delete` を用いず、 `malloc`/`realloc`/`free` のみで構成されているのはこのためです

## 2. メモリの倍々確保
メモリが不足した場合のメモリの再確保を行う際に元の2倍のメモリ領域を再確保することで、動的メモリ確保のランタイムを最小化しています

## 3. Fail-Fast
メモリが枯渇している状態から解放やスタックポインタの巻き戻しなどを行えば、正常に動くプログラムに戻せるという話は嘘です
ですから信頼性やパフォーマンスの求められるソフトウェアにおいて、メモリが枯渇している状態で、プログラムを続行させるべきではありません
さらに `try-catch` や `std::result` を使うとFail時の処理により、マシンコードが膨れるので、挙動の予測可能性の高いソフトウェアではなくなってしまいます

# Vec

A simple, highly predictable, and fast dynamic array library for C++.

## 1. POD-Only
By excluding complex data types like classes with member functions, `Vec` avoids element-wise constructor and destructor invocations, significantly enhancing runtime predictability. 
This is why the library completely avoids `new`/`delete` and relies exclusively on raw `malloc`/`realloc`/`free`.

## 2. Geometric Memory Growth (2x)
When the buffer is full, reallocation doubles the original memory capacity, minimizing the runtime overhead of dynamic memory allocation.

## 3. Fail-Fast
The idea that a program can recover from memory exhaustion through cleanup or stack unwinding is a myth. In software where high reliability and performance are critical, execution should never continue under out-of-memory conditions.
Furthermore, using `try-catch` or `std::result` introduces error-handling overhead that leads to severe machine-code bloat, ultimately compromising runtime predictability.
