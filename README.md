# 環境構築

Ubuntu環境にて次のように実行する。

```sh
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential cmake git clang-format -y
git clone <このリポジトリ>
```

# ビルドとテスト

環境構築した状態で次のように実行する

```sh
mkdir build;cd build
cmake ..
make -j
ctest
```
