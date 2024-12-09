cmake_minimum_required(VERSION 3.13)
project(binary_tree C)

set(project_sources
binary_tree.c
list.c
utility.c
main.c)

set(include_directories
./packages/glfw.3.4.0/build/native/include/
./packages/glm.1.0.1/build/native/include/
./packages/nupengl.core.0.1.0.1/build/native/include/
)


set(libraly_names
${PROJECT_SOURCE_DIR}/packages/nupengl.core.0.1.0.1/build/native/lib/x64/freeglut.lib
${PROJECT_SOURCE_DIR}/packages/glfw.3.4.0/build/native/lib/static/v140/x64/glfw3.lib
${PROJECT_SOURCE_DIR}/packages/nupengl.core.0.1.0.1/build/native/lib/x64/glew32.lib
${PROJECT_SOURCE_DIR}/packages/nupengl.core.0.1.0.1/build/native/lib/x64/glfw3dll.lib
)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

add_executable(binary_tree ${project_sources})

target_include_directories(binary_tree PRIVATE ${include_directories})

target_link_directories(binary_tree PRIVATE ${libraly_directories})

target_link_libraries(binary_tree PUBLIC ${libraly_names})

#.cファイルと同じ階層にCMakeLists.txtを作る　そして必要事項を書き込む
#buildフォルダを作りその中に入る
#cmake .. -G "Visual Studio 16 2019"コマンドによりconfigure処理とgenetator処理を行う。　ここでビルドシステムの選択をする　..によりCMakeLists.txtを指す
#上の操作により初めてそのシステムでビルドするための設定ファイルなどができる msbuildなら.vcxprojなど
#cmake --build . コマンドによりここで初めて指定したシステムでビルドを行う
#./build/Debug/の中に実行ファイルができるので実行

#あとソースファイル中に日本語あるとバグったので気を付ける
#https://teratail.com/questions/308679

#インクルードパスはプログラム中で""を使っているなら、ソースコードのある位置から検索するので相対パスでよし
#<>の時は絶対パスで指定
#ライブラリパスはシステムから見たいちなので絶対パスを指定すること。この際cmakelists.txtファイルにプライバシーや柔軟性の観点から
#絶対パスをハードコーディングしたくないときはあらかじめある変数を使う事
#CMAKE_SOURCE_DIR	ソースツリーのトップディレクトリ
#CMAKE_BINARY_DIR	上記に対応するビルドディレクトリ
#CMAKE_CURRENT_SOURCE_DIR	現在処理中の CMakeLists.txt の配置ディレクトリ
#CMAKE_CURRENT_BINARY_DIR	上記に対応するビルドディレクトリ
#PROJECT_SOURCE_DIR	現在のプロジェクトのトップディレクトリ
#PROJECT_BINARY_DIR	上記に対応するビルドディレクトリ
#<name>_SOURCE_DIR	プロジェクト name のトップディレクトリ
#<name>_BINARY_DIR	上記に対応するビルドディレクトリ
#CMAKE_CURRENT_LIST_DIR	現在処理中の cmake ファイルの配置ディレクトリ

#動的にリンクされる標準ファイルがあるらしく、そのモードが一致してないと警告出るらしい。

#古いライブラリ使ったらいくつかの標準ライブラリの関数が解決できなくなっていたので注意
#https://qiita.com/tanachiu/items/d20ada532f5d1d2857ec
#今回はv140を使うことで解決